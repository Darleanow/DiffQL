#pragma once
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include <algorithm>
#include <optional>
#include <string>
#include <vector>

namespace DiffQL
{

inline float jaro_winkler(const std::string &s1, const std::string &s2)
{
  if(s1 == s2)
    return 1.0f;

  const int len1 = static_cast<int>(s1.size());
  const int len2 = static_cast<int>(s2.size());

  if(len1 == 0 || len2 == 0)
    return 0.0f;

  const int match_window = std::max(0, std::max(len1, len2) / 2 - 1);

  std::vector<bool> s1_matched(len1, false);
  std::vector<bool> s2_matched(len2, false);

  int matches = 0;

  for(int i = 0; i < len1; ++i) {
    const int start = std::max(0, i - match_window);
    const int end   = std::min(len2 - 1, i + match_window);

    for(int j = start; j <= end; ++j) {
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
  int transpositions = 0;
  int k              = 0;
  for(int i = 0; i < len1; ++i) {
    if(!s1_matched[i])
      continue;
    while(!s2_matched[k])
      ++k;
    if(s1[i] != s2[k])
      ++transpositions;
    ++k;
  }

  const float m    = static_cast<float>(matches);
  const float jaro = (m / len1 + m / len2 + (m - transpositions / 2.0f) / m) / 3.0f;

  // Winkler prefix bonus (up to 4 chars)
  int       prefix       = 0;
  const int prefix_limit = std::min({len1, len2, 4});
  for(int i = 0; i < prefix_limit; ++i) {
    if(s1[i] == s2[i])
      ++prefix;
    else
      break;
  }

  return jaro + prefix * 0.1f * (1.0f - jaro);
}

} // namespace DiffQL

enum class DiffAction
{
  ADDED,
  DROPPED,
  MODIFIED
};

template <typename T>
struct ElementDiff
{
  DiffAction       action;
  std::string      name;
  std::optional<T> before;
  std::optional<T> after;
};

struct TableDiff
{
  DiffAction                                action;
  std::string                               table_name;

  std::vector<ElementDiff<Column>>          column_diffs;
  std::optional<ElementDiff<PrimaryKey>>    pk_diffs;
  std::vector<ElementDiff<ForeignKey>>      fk_diffs;
  std::vector<ElementDiff<Index>>           index_diffs;

  std::vector<ElementDiff<CheckConstraint>> check_diffs;
};

struct SchemaDiff
{
  std::vector<TableDiff> table_diffs;
};

class DiffEngine
{
public:
  DiffEngine(
      const std::vector<Table> &schema_origin,
      const std::vector<Table> &schema_dest
  );

  const SchemaDiff &compare_schemas();
  void              generate_report(const SchemaDiff &schema) const;

private:
  std::vector<Table>       m_schema_origin, m_schema_dest;

  std::optional<TableDiff> compare_table_by_fields(
      const Table &table_origin, const Table &table_dest
  ) const;
};
