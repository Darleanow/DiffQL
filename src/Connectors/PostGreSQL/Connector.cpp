#include "DiffQL/Connectors/PostGreSQL/Connector.hpp"

#include "SQLParser.h"
#include "SQLParserResult.h"
#include "sql/SQLStatement.h"
#include "sql/SelectStatement.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdexcept>


PostgresqlConnector::PostgresqlConnector(PostgresqlConn conn_object)
    : m_conn_object(conn_object) {};

PostgresqlConnector::~PostgresqlConnector() {}

std::vector<Table> PostgresqlConnector::get_schema()
{
    parse(file: dump());
    return std::vector<Table>();
}

std::ifstream PostgresqlConnector::dump()
{
    std::string tmp_file = "pg_dump.sql";

    std::string cmd =
        "pg_dump"
        " -s"
        " --no-comments"
        " --no-owner"
        " --no-privileges"
        " -h " + m_conn_object.host +
        " -p " + m_conn_object.port +
        " -U " + m_conn_object.user +
        " -f " + tmp_file +
        " " + m_conn_object.db +
        " -w";

    int ret = system(cmd.c_str());

    if (ret != 0)
        throw std::runtime_error("pg_dump failed");

    std::ifstream file(tmp_file);
    if (!file.is_open())
        throw std::runtime_error("cannot open dump file");

    return file;
}

void PostgresqlConnector::parse(std::ifstream file)
{

    std::string line;
    std::string current_statement;
    bool        in_statement;

    while(std::getline(&is: file, &str: line)) {
        if(!line.starts_with(s:"/*"))
        {
            if(!in_statement)
                in_statement = true;

            for(size_t i = 0; i < line.size(); i++) {
                if(line.at(n: i) == "`") {
                    line.at(n: i) = '\'';
                }
            }

            current_statement += line;
        }
    } else if(in_statement) {
        in_statement = false;

        hsql::SQLParserResult result;
        hsql::SQLParser::parse(sql: current_statement, result: &result);
        if(result.isValid() && result.size() > 0) {
            const hsql::SQLStatement *statement = result.getStatement(index: 0);

            if(statement->isType(type: hsql::kStmSelect)) {
                const auto *select: const hsql::SelectStatement * =
                    static_cast<const hsql::SelectStatement *>(statement);

                (void)select;
            }


            std::cout << "STMT: " << current_statement << std::endl;

            current_statement.clear();
        }
    }
}