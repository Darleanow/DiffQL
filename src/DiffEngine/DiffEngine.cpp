#include "DiffQL/DiffEngine/DiffEngine.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

DiffEngine::DiffEngine(
    const std::vector<Table> &schema_origin,
    const std::vector<Table> &schema_dest
)
    : m_schema_origin(schema_origin),
      m_schema_dest(schema_dest),
      m_rename_callback([](const std::string &orig, const std::string &dest, float score) {
        std::cout << "Table '" << orig << "' -> '" << dest
                  << "' (similarity: " << score * 100 << "%)\n"
                  << "Treat as rename/modification? [y/N]: ";
        std::string answer;
        std::getline(std::cin, answer);
        return answer == "y" || answer == "Y";
      })
{
}

void DiffEngine::set_rename_callback(RenameCallback cb)
{
  m_rename_callback = std::move(cb);
}

template <typename T>
std::vector<ElementDiff<T>> DiffEngine::diff_elements(
    const std::vector<T> &origins,
    const std::vector<T> &dests) const
{
  std::vector<ElementDiff<T>> diffs;
  std::unordered_map<std::string, const T *> origin_map, dest_map;

  for(const auto &e : origins) origin_map[e.name] = &e;
  for(const auto &e : dests)   dest_map[e.name] = &e;

  for(const auto &[name, orig] : origin_map) {
    auto it = dest_map.find(name);
    if(it == dest_map.end())
      diffs.push_back({DiffAction::DROPPED, name, *orig, std::nullopt});
    else if(*orig != *it->second)
      diffs.push_back({DiffAction::MODIFIED, name, *orig, *it->second});
  }

  for(const auto &[name, dest] : dest_map)
    if(!origin_map.count(name))
      diffs.push_back({DiffAction::ADDED, name, std::nullopt, *dest});

  std::sort(diffs.begin(), diffs.end(),
            [](const auto &a, const auto &b) { return a.name < b.name; });
  return diffs;
}

template std::vector<ElementDiff<Column>> DiffEngine::diff_elements(
    const std::vector<Column> &, const std::vector<Column> &) const;
template std::vector<ElementDiff<Index>> DiffEngine::diff_elements(
    const std::vector<Index> &, const std::vector<Index> &) const;
template std::vector<ElementDiff<CheckConstraint>> DiffEngine::diff_elements(
    const std::vector<CheckConstraint> &, const std::vector<CheckConstraint> &) const;

static std::string fk_signature(const ForeignKey &fk)
{
  std::string sig;
  for(const auto &c : fk.column_names)      sig += c + ",";
  sig += "->" + fk.referenced_table + "(";
  for(const auto &c : fk.referenced_columns) sig += c + ",";
  sig += ")" + fk.on_delete + fk.on_update;
  return sig;
}

std::vector<ElementDiff<ForeignKey>> DiffEngine::diff_foreign_keys(
    const std::vector<ForeignKey> &origins,
    const std::vector<ForeignKey> &dests) const
{
  std::vector<ElementDiff<ForeignKey>> diffs;
  std::unordered_map<std::string, const ForeignKey *> origin_map, dest_map;

  for(const auto &fk : origins) origin_map[fk_signature(fk)] = &fk;
  for(const auto &fk : dests)   dest_map[fk_signature(fk)] = &fk;

  for(const auto &[sig, fk] : origin_map)
    if(!dest_map.count(sig))
      diffs.push_back({DiffAction::DROPPED, fk->name, *fk, std::nullopt});

  for(const auto &[sig, fk] : dest_map)
    if(!origin_map.count(sig))
      diffs.push_back({DiffAction::ADDED, fk->name, std::nullopt, *fk});

  std::sort(diffs.begin(), diffs.end(),
            [](const auto &a, const auto &b) { return a.name < b.name; });
  return diffs;
}

std::vector<ForeignKey> DiffEngine::normalize_fk_references(
    const std::vector<ForeignKey> &fks,
    const std::unordered_map<std::string, std::string> &renames) const
{
  if(renames.empty()) return fks;

  std::vector<ForeignKey> result = fks;
  for(auto &fk : result) {
    auto it = renames.find(fk.referenced_table);
    if(it != renames.end())
      fk.referenced_table = it->second;
  }
  return result;
}

std::optional<TableDiff> DiffEngine::compare_tables(
    const Table &origin,
    const Table &dest,
    const std::unordered_map<std::string, std::string> &renames) const
{
  TableDiff td{
      .action       = DiffAction::MODIFIED,
      .table_name   = origin.name,
      .new_name     = {},
      .column_diffs = diff_elements(origin.columns, dest.columns),
      .pk_diff      = {},
      .fk_diffs     = diff_foreign_keys(
          normalize_fk_references(origin.foreign_keys, renames),
          dest.foreign_keys),
      .index_diffs  = diff_elements(origin.indexes, dest.indexes),
      .check_diffs  = diff_elements(origin.checks, dest.checks)
  };

  auto pk_name = [](const PrimaryKey &pk) {
    return pk.constraint_name.value_or("PRIMARY");
  };

  if(origin.primary_key && dest.primary_key) {
    if(*origin.primary_key != *dest.primary_key)
      td.pk_diff = {DiffAction::MODIFIED, pk_name(*origin.primary_key),
                    origin.primary_key, dest.primary_key};
  } else if(origin.primary_key) {
    td.pk_diff = {DiffAction::DROPPED, pk_name(*origin.primary_key),
                  origin.primary_key, std::nullopt};
  } else if(dest.primary_key) {
    td.pk_diff = {DiffAction::ADDED, pk_name(*dest.primary_key),
                  std::nullopt, dest.primary_key};
  }

  bool changed = !td.column_diffs.empty() || td.pk_diff.has_value() ||
                 !td.fk_diffs.empty() || !td.index_diffs.empty() ||
                 !td.check_diffs.empty();

  return changed ? std::make_optional(std::move(td)) : std::nullopt;
}

std::unordered_map<std::string, std::string> DiffEngine::detect_table_renames(
    const std::vector<const Table *> &only_origin,
    const std::vector<const Table *> &only_dest,
    std::vector<std::pair<const Table *, const Table *>> &out_pairs)
{
  auto lower = [](const std::string &s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), ::tolower);
    return r;
  };

  std::unordered_map<std::string, std::string> renames;
  std::unordered_set<const Table *> used;

  for(const auto *orig : only_origin) {
    const Table *best = nullptr;
    float best_score = 0.0f;

    for(const auto *dest : only_dest) {
      if(used.count(dest)) continue;
      float score = jaro_winkler(lower(orig->name), lower(dest->name));
      if(score > best_score) {
        best_score = score;
        best = dest;
      }
    }

    if(best_score > 0.85f && best) {
      if(m_rename_callback(orig->name, best->name, best_score)) {
        renames[orig->name] = best->name;
        out_pairs.push_back({orig, best});
        used.insert(best);
      }
    }
  }
  return renames;
}

const SchemaDiff &DiffEngine::compare_schemas()
{
  m_diff = {};

  std::unordered_map<std::string, const Table *> origin_map, dest_map;
  for(const auto &t : m_schema_origin) origin_map[t.name] = &t;
  for(const auto &t : m_schema_dest)   dest_map[t.name] = &t;

  std::vector<const Table *> only_origin, only_dest;
  for(const auto &[n, t] : origin_map) if(!dest_map.count(n))   only_origin.push_back(t);
  for(const auto &[n, t] : dest_map)   if(!origin_map.count(n)) only_dest.push_back(t);

  std::vector<std::pair<const Table *, const Table *>> rename_pairs;
  auto renames = detect_table_renames(only_origin, only_dest, rename_pairs);

  std::unordered_set<const Table *> matched_orig, matched_dest;
  for(const auto &[o, d] : rename_pairs) {
    matched_orig.insert(o);
    matched_dest.insert(d);
  }

  for(const auto &[name, orig] : origin_map) {
    if(auto it = dest_map.find(name); it != dest_map.end())
      if(auto td = compare_tables(*orig, *it->second, renames))
        m_diff.table_diffs.push_back(std::move(*td));
  }

  for(const auto &[orig, dest] : rename_pairs) {
    if(auto td = compare_tables(*orig, *dest, renames)) {
      td->new_name = dest->name;
      m_diff.table_diffs.push_back(std::move(*td));
    }
  }

  for(const auto *t : only_origin)
    if(!matched_orig.count(t))
      m_diff.table_diffs.push_back({DiffAction::DROPPED, t->name, {}, {}, {}, {}, {}, {}});

  for(const auto *t : only_dest)
    if(!matched_dest.count(t))
      m_diff.table_diffs.push_back({DiffAction::ADDED, t->name, {}, {}, {}, {}, {}, {}});

  std::sort(m_diff.table_diffs.begin(), m_diff.table_diffs.end(),
            [](const auto &a, const auto &b) { return a.table_name < b.table_name; });

  return m_diff;
}

float DiffEngine::jaro_winkler(const std::string &s1, const std::string &s2) const
{
  if(s1 == s2) return 1.0f;
  if(s1.empty() || s2.empty()) return 0.0f;

  size_t len1 = s1.size(), len2 = s2.size();
  size_t window = std::max(len1, len2) / 2 - 1;

  std::vector<bool> m1(len1), m2(len2);
  int matches = 0;

  for(size_t i = 0; i < len1; ++i) {
    size_t lo = (i > window) ? i - window : 0;
    size_t hi = std::min(len2 - 1, i + window);
    for(size_t j = lo; j <= hi; ++j) {
      if(!m2[j] && s1[i] == s2[j]) {
        m1[i] = m2[j] = true;
        ++matches;
        break;
      }
    }
  }

  if(matches == 0) return 0.0f;

  int transpositions = 0;
  size_t k = 0;
  for(size_t i = 0; i < len1; ++i) {
    if(!m1[i]) continue;
    while(!m2[k]) ++k;
    if(s1[i] != s2[k]) ++transpositions;
    ++k;
  }

  float m = static_cast<float>(matches);
  float jaro = (m/len1 + m/len2 + (m - transpositions/2.0f)/m) / 3.0f;

  int prefix = 0;
  for(size_t i = 0; i < std::min({len1, len2, size_t{4}}); ++i) {
    if(s1[i] == s2[i]) ++prefix;
    else break;
  }

  return jaro + prefix * 0.1f * (1.0f - jaro);
}
