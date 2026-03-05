#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/DiffEngine/DiffEngine.hpp"
#include <algorithm>

DiffEngine::DiffEngine(
    const std::vector<Table> &schema_origin,
    const std::vector<Table> &schema_dest
)
    : m_schema_origin(schema_origin),
      m_schema_dest(schema_dest)
{
}

const SchemaDiff &DiffEngine::compare_schemas()
{

  for(const auto &table_origin : m_schema_origin) {
    bool found_or_in_dest {false};

    for(const auto &table_dest : m_schema_dest) {
    }
  }

  return SchemaDiff();
}

void DiffEngine::generate_report(const SchemaDiff &schema) const {}

float DiffEngine::jaro_winkler(const std::string &s1, const std::string &s2) const
{
  if(s1 == s2)
    return 1.0f;

  const size_t len1 = s1.size();
  const size_t len2 = s2.size();

  if(len1 == 0 || len2 == 0)
    return 0.0f;

  const size_t max_len      = std::max(len1, len2);
  const size_t match_window = max_len >= 2 ? max_len / 2 - 1 : 0;

  std::vector<bool> s1_matched(len1, false);
  std::vector<bool> s2_matched(len2, false);

  int matches = 0;

  for(size_t i = 0; i < len1; ++i) {
    const size_t start = i > match_window ? i - match_window : 0;
    const size_t end   = std::min(len2 - 1, i + match_window);

    for(size_t j = start; j <= end; ++j) {
      if(s2_matched[j] || s1[i] != s2[j])
        continue;
      s1_matched[i] = true;
      s2_matched[j] = true;
      ++matches;
      break;
    }
  }

  if(matches == 0)
    return 0.0f;

  // Count mismatched pairs among matched chars; t = half that count
  int    transpositions = 0;
  size_t k              = 0;
  for(size_t i = 0; i < len1; ++i) {
    if(!s1_matched[i])
      continue;
    while(!s2_matched[k])
      ++k;
    if(s1[i] != s2[k])
      ++transpositions;
    ++k;
  }

  const float m    = static_cast<float>(matches);
  const float jaro = (m / static_cast<float>(len1) + m / static_cast<float>(len2) + (m - transpositions / 2.0f) / m) / 3.0f;

  // Winkler prefix bonus (up to 4 chars)
  int          prefix       = 0;
  const size_t prefix_limit = std::min({len1, len2, size_t{4}});
  for(size_t i = 0; i < prefix_limit; ++i) {
    if(s1[i] == s2[i])
      ++prefix;
    else
      break;
  }

  return jaro + prefix * 0.1f * (1.0f - jaro);
}

std::optional<TableDiff> DiffEngine::compare_table_by_fields(
    const Table &table_origin, const Table &table_dest
) const
{

  return std::nullopt;
}

