#include "DiffQL/Connectors/MariaDB/Connector.hpp"
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/Parser/DDLVisitor.hpp"
#include "MariaDBDDLLexer.h"
#include "MariaDBDDLParser.h"
#include <antlr4-runtime.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

MariaDBConnector::MariaDBConnector(MariaDBConn conn_object)
    : m_conn_object(conn_object) {};

MariaDBConnector::~MariaDBConnector() {}

std::vector<Table> MariaDBConnector::get_schema()
{
  auto tables = parse(dump());

  // Dump of the parsing job, TODO(): To remove.
  std::cout << "Parsing Done !" << std::endl;
  std::cout << "Tables: " << tables.size() << std::endl;

  for(const auto &table : tables) {
    std::cout << "\n" << table.name << ":\n";
    std::cout << "  Columns: ";
    for(const auto &col : table.columns) {
      std::cout << col.name;
      if(col.auto_increment) {
        std::cout << "(AI)";
      }
      std::cout << ", ";
    }

    if(table.primary_key) {
      std::cout << "\n  PK: ";
      for(const auto &pk_col : table.primary_key->column_names) {
        std::cout << pk_col << " ";
      }
    }

    if(!table.foreign_keys.empty()) {
      std::cout << "\n  Foreign Keys:";
      for(const auto &fk : table.foreign_keys) {
        std::cout << "\n    " << fk.name << " references "
                  << fk.referenced_table << " (";
        for(const auto &ref_col : fk.referenced_columns) {
          std::cout << ref_col << " ";
        }
        std::cout << ")";
      }
    }

    if(!table.indexes.empty()) {
      std::cout << "\n  Indexes:";
      for(const auto &idx : table.indexes) {
        std::cout << "\n    " << idx.name << (idx.unique ? " (UNIQUE)" : "")
                  << " [";
        for(const auto &ic : idx.column_names) {
          std::cout << ic << " ";
        }
        std::cout << "]";
      }
    }

    std::cout << std::endl;
  }

  return tables;
}

std::ifstream MariaDBConnector::dump()
{
  std::string tmp_file = "dump.sql";
  int ret = system(("mariadb-dump -u " + m_conn_object.user + " -p" +
                    m_conn_object.passwd + " -h " + m_conn_object.host +
                    " -P " + std::to_string(m_conn_object.port.value_or(3306)) + " " +
                    m_conn_object.db +
                    " --no-data --compact --skip-comments > " + tmp_file)
                       .c_str());

  if(ret != 0) {
    std::cerr << "Error dumping the database " + m_conn_object.db;
  }

  std::ifstream file(tmp_file);
  return file;
}

std::vector<Table> MariaDBConnector::parse(const std::ifstream &file)
{
  // Read entire file into string
  std::ostringstream ss;
  ss << file.rdbuf();
  std::string sql = ss.str();

  // ANTLR pipeline: input -> lexer -> tokens -> parser -> tree
  antlr4::ANTLRInputStream  input(sql);
  MariaDBDDLLexer           lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  MariaDBDDLParser          parser(&tokens);

  // Suppress default error output for graceful skipping
  parser.removeErrorListeners();

  auto *tree = parser.script();

  // Visit the parse tree
  DDLVisitor visitor;
  visitor.visit(tree);

  return visitor.tables();
}
