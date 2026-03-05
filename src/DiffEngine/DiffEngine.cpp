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
      m_schema_dest(schema_dest)
{
}

template <typename T>
std::vector<ElementDiff<T>> DiffEngine::diff_elements(
    const std::vector<T> &origins, const std::vector<T> &dests
) const
{
  std::vector<ElementDiff<T>>                diffs;
  std::unordered_map<std::string, const T *> origin_map, dest_map;

  for(const auto &e : origins)
    origin_map[e.name] = &e;
  for(const auto &e : dests)
    dest_map[e.name] = &e;

  for(const auto &[name, orig] : origin_map) {
    auto it = dest_map.find(name);
    if(it == dest_map.end())
      diffs.push_back({DiffAction::DROPPED, name, *orig, std::nullopt});
    else if(*orig != *it->second)
      diffs.push_back({DiffAction::MODIFIED, name, *orig, *it->second});
  }

  for(const auto &[name, dest] : dest_map) {
    if(origin_map.find(name) == origin_map.end())
      diffs.push_back({DiffAction::ADDED, name, std::nullopt, *dest});
  }

  std::sort(diffs.begin(), diffs.end(), [](const auto &a, const auto &b) {
    return a.name < b.name;
  });

  return diffs;
}

template std::vector<ElementDiff<Column>> DiffEngine::diff_elements(
    const std::vector<Column> &, const std::vector<Column> &
) const;
template std::vector<ElementDiff<ForeignKey>> DiffEngine::diff_elements(
    const std::vector<ForeignKey> &, const std::vector<ForeignKey> &
) const;
template std::vector<ElementDiff<Index>> DiffEngine::diff_elements(
    const std::vector<Index> &, const std::vector<Index> &
) const;
template std::vector<ElementDiff<CheckConstraint>> DiffEngine::diff_elements(
    const std::vector<CheckConstraint> &, const std::vector<CheckConstraint> &
) const;

std::optional<TableDiff>
    DiffEngine::compare_tables(const Table &origin, const Table &dest) const
{
  TableDiff td {
      .action       = DiffAction::MODIFIED,
      .table_name   = origin.name,
      .column_diffs = {},
      .pk_diff      = {},
      .fk_diffs     = {},
      .index_diffs  = {},
      .check_diffs  = {}
  };

  td.column_diffs = diff_elements(origin.columns, dest.columns);
  td.fk_diffs     = diff_elements(origin.foreign_keys, dest.foreign_keys);
  td.index_diffs  = diff_elements(origin.indexes, dest.indexes);
  td.check_diffs  = diff_elements(origin.checks, dest.checks);

  auto pk_name = [](const PrimaryKey &pk) {
    return pk.constraint_name.value_or("PRIMARY");
  };

  if(origin.primary_key && dest.primary_key) {
    if(*origin.primary_key != *dest.primary_key)
      td.pk_diff = ElementDiff<PrimaryKey> {
          DiffAction::MODIFIED, pk_name(*origin.primary_key),
          origin.primary_key, dest.primary_key
      };
  } else if(origin.primary_key) {
    td.pk_diff = ElementDiff<PrimaryKey> {
        DiffAction::DROPPED, pk_name(*origin.primary_key), origin.primary_key,
        std::nullopt
    };
  } else if(dest.primary_key) {
    td.pk_diff = ElementDiff<PrimaryKey> {
        DiffAction::ADDED, pk_name(*dest.primary_key), std::nullopt,
        dest.primary_key
    };
  }

  bool changed = !td.column_diffs.empty() || td.pk_diff.has_value() ||
                 !td.fk_diffs.empty() || !td.index_diffs.empty() ||
                 !td.check_diffs.empty();

  return changed ? std::make_optional(std::move(td)) : std::nullopt;
}

const SchemaDiff &DiffEngine::compare_schemas()
{
  m_diff = {};

  // Index tables by name
  std::unordered_map<std::string, const Table *> origin_idx, dest_idx;
  for(const auto &t : m_schema_origin)
    origin_idx[t.name] = &t;
  for(const auto &t : m_schema_dest)
    dest_idx[t.name] = &t;

  // Partition: exact matches vs orphans
  std::vector<const Table *> only_origin, only_dest;

  for(const auto &[name, table] : origin_idx) {
    auto it = dest_idx.find(name);
    if(it != dest_idx.end()) {
      if(auto td = compare_tables(*table, *it->second))
        m_diff.table_diffs.push_back(std::move(*td));
    } else {
      only_origin.push_back(table);
    }
  }

  for(const auto &[name, table] : dest_idx) {
    if(origin_idx.find(name) == origin_idx.end())
      only_dest.push_back(table);
  }

  // Rename detection via case-insensitive Jaro-Winkler
  auto to_lower = [](const std::string &s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
  };

  std::unordered_set<const Table *> matched_orig, matched_dest;

  for(const auto *orig : only_origin) {
    const Table *best       = nullptr;
    float        best_score = 0.0f;

    for(const auto *dest : only_dest) {
      if(matched_dest.count(dest))
        continue;
      float s = jaro_winkler(to_lower(orig->name), to_lower(dest->name));
      if(s > best_score) {
        best_score = s;
        best       = dest;
      }
    }

    if(best_score > 0.85f && best) {
      std::cout << "Table '" << orig->name << "' -> '" << best->name
                << "' (similarity: " << best_score * 100 << "%)\n"
                << "Treat as rename/modification? [y/N]: ";

      std::string answer;
      std::getline(std::cin, answer);

      if(answer == "y" || answer == "Y") {
        if(auto td = compare_tables(*orig, *best))
          m_diff.table_diffs.push_back(std::move(*td));
        matched_orig.insert(orig);
        matched_dest.insert(best);
      }
    }
  }

  for(const auto *t : only_origin)
    if(!matched_orig.count(t))
      m_diff.table_diffs.push_back(
          {.action       = DiffAction::DROPPED,
           .table_name   = t->name,
           .column_diffs = {},
           .pk_diff      = {},
           .fk_diffs     = {},
           .index_diffs  = {},
           .check_diffs  = {}}
      );

  for(const auto *t : only_dest)
    if(!matched_dest.count(t))
      m_diff.table_diffs.push_back(
          {.action       = DiffAction::ADDED,
           .table_name   = t->name,
           .column_diffs = {},
           .pk_diff      = {},
           .fk_diffs     = {},
           .index_diffs  = {},
           .check_diffs  = {}}
      );

  // Sort final output by table name
  std::sort(
      m_diff.table_diffs.begin(), m_diff.table_diffs.end(),
      [](const auto &a, const auto &b) { return a.table_name < b.table_name; }
  );

  return m_diff;
}

float DiffEngine::jaro_winkler(
    const std::string &s1, const std::string &s2
) const
{
  if(s1 == s2)
    return 1.0f;

  const auto len1 = s1.size();
  const auto len2 = s2.size();
  if(len1 == 0 || len2 == 0)
    return 0.0f;

  const auto        window = std::max(len1, len2) / 2 - 1;
  std::vector<bool> m1(len1, false), m2(len2, false);
  int               matches = 0;

  for(size_t i = 0; i < len1; ++i) {
    auto lo = i > window ? i - window : 0u;
    auto hi = std::min(len2 - 1, i + window);
    for(auto j = lo; j <= hi; ++j) {
      if(m2[j] || s1[i] != s2[j])
        continue;
      m1[i] = m2[j] = true;
      ++matches;
      break;
    }
  }

  if(matches == 0)
    return 0.0f;

  int    transpositions = 0;
  size_t k              = 0;
  for(size_t i = 0; i < len1; ++i) {
    if(!m1[i])
      continue;
    while(!m2[k])
      ++k;
    if(s1[i] != s2[k])
      ++transpositions;
    ++k;
  }

  float m    = static_cast<float>(matches);
  float jaro = (m / len1 + m / len2 + (m - transpositions / 2.0f) / m) / 3.0f;

  int   prefix = 0;
  for(size_t i = 0; i < std::min({len1, len2, size_t {4}}); ++i) {
    if(s1[i] == s2[i])
      ++prefix;
    else
      break;
  }

  return jaro + prefix * 0.1f * (1.0f - jaro);
}
