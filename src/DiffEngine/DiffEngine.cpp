#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/DiffEngine/DiffEngine.hpp"

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

std::optional<TableDiff> DiffEngine::compare_table_by_fields(
    const Table &table_origin, const Table &table_dest
) const
{

  return std::nullopt;
}

int DiffEngine::lev(const std::string &origin, const std::string &dest) const
{
  return DiffQL::lev_distance(origin, dest);
}
