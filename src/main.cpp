#include "DiffQL/Connectors/MariaDB/Connector.hpp"

int main(void)
{
  MariaDBConn connect_object {
      .host   = "localhost",
      .user   = "root",
      .passwd = "toor",
      .db     = "nation"
  };
  MariaDBConnector connector(connect_object);

  connector.get_schema();

  //
  // std::string           sql = "CREATE TABLE test (id INT);";
  //
  // hsql::SQLParserResult result;
  // hsql::SQLParser::parse(sql, &result);
  //
  // if(result.isValid()) {
  //   std::cout << "SQL parsed successfully!\n";
  //   std::cout << "Statements: " << result.size() << "\n";
  // } else {
  //   std::cerr << "Parse error: " << result.errorMsg() << "\n";
  // }

  return 0;
}
