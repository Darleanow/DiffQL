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
