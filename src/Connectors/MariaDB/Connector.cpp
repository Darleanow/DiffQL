#include "DiffQL/Connectors/MariaDB/Connector.hpp"
#include "SQLParser.h"
#include "SQLParserResult.h"
#include "sql/SQLStatement.h"
#include "sql/SelectStatement.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

MariaDBConnector::MariaDBConnector(MariaDBConn conn_object)
    : m_conn_object(conn_object) {};

MariaDBConnector::~MariaDBConnector() {}

std::vector<Table> MariaDBConnector::get_schema()
{
  parse(dump());
  return std::vector<Table>();
}

std::ifstream MariaDBConnector::dump()
{
  std::string tmp_file = "dump.sql";
  int ret = system(("mariadb-dump -u " + m_conn_object.user + " -p" +
                    m_conn_object.passwd + " -h " + m_conn_object.host + " " +
                    m_conn_object.db +
                    " --no-data --compact --skip-comments > " + tmp_file)
                       .c_str());

  if(ret != 0) {
    std::cerr << "Error dumping the database " + m_conn_object.db;
  }

  std::ifstream file(tmp_file);
  return file;
}

void MariaDBConnector::parse(std::ifstream file)
{

  std::string line;
  std::string current_statement;
  bool        in_statement;

  while(std::getline(file, line)) {
    if(!line.starts_with("/*")) // We found a statement
    {
      if(!in_statement)
        in_statement = true;

      // Attention: We remove backquotes '`' because they aren't supported by
      // the hyrise lib to interpret.
      // This is an arbitrary choice due to time constraints, if there is an
      // update feel free to remove the following code section that trims them.
      for(size_t i = 0; i < line.size(); i++) {
        if(line.at(i) == '`') {
          line.at(i) = '\'';
        }
      }
      // END

      current_statement += line;
    } else if(in_statement) { // We finished traversal of a statement
      in_statement = false;

      hsql::SQLParserResult result;
      hsql::SQLParser::parse(current_statement, &result);
      if(result.isValid() && result.size() > 0) {
        const hsql::SQLStatement *statement = result.getStatement(0);

        if(statement->isType(hsql::kStmtSelect)) {
          const auto *select =
              static_cast<const hsql::SelectStatement *>(statement);

          (void)select;
        }
      }

      std::cout << "STMT: " << current_statement << std::endl;

      current_statement.clear();
    }
  }
}
