#include "DiffQL/Connectors/PostGreSQL/Connector.hpp"
#include "DiffQL/Diff/SchemaDiff.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

std::string env_or_default(const char *name, const char *fallback)
{
  const char *value = std::getenv(name);
  if(value == nullptr) {
    return std::string(fallback);
  }
  return std::string(value);
}

int main()
{
  PostgreSQLConn conn {
      .host = env_or_default("DIFFQL_PG_HOST", "localhost"),
      .user = env_or_default("DIFFQL_PG_USER", "postgres"),
      .passwd = env_or_default("DIFFQL_PG_PASSWORD", ""),
      .db = env_or_default("DIFFQL_PG_BASE_DB", "nation_v1"),
      .port = env_or_default("DIFFQL_PG_PORT", "5432")
  };

  const std::string target_db = env_or_default("DIFFQL_PG_TARGET_DB", "nation_v2");

  try {
    PostgreSQLConnector source_connector(conn);
    std::vector<Table>  source = source_connector.get_schema();

    PostgreSQLConn target_conn = conn;
    target_conn.db = target_db;
    PostgreSQLConnector target_connector(target_conn);
    std::vector<Table>  target = target_connector.get_schema();

    SchemaDiffResult result = diff_schemas(source, target);
    std::cout << diff_report_markdown(result) << "\n";

    return 0;
  } catch(const std::exception &e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
}
