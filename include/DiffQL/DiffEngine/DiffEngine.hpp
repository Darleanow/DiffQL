#pragma once
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include <optional>
#include <string>
#include <vector>

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
  std::optional<std::string>                new_name;

  std::vector<ElementDiff<Column>>          column_diffs;
  std::optional<ElementDiff<PrimaryKey>>    pk_diff;
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

protected:
  float jaro_winkler(const std::string &s1, const std::string &s2) const;

private:
  std::vector<Table> m_schema_origin;
  std::vector<Table> m_schema_dest;
  SchemaDiff         m_diff;

  std::optional<TableDiff> compare_tables(
      const Table &origin, const Table &dest
  ) const;

  template <typename T>
  std::vector<ElementDiff<T>> diff_elements(
      const std::vector<T> &origins,
      const std::vector<T> &dests
  ) const;
};
