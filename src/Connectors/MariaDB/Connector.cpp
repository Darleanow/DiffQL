#include "DiffQL/Connectors/MariaDB/Connector.hpp"
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/Parser/DDLVisitor.hpp"
#include "MariaDBDDLLexer.h"
#include "MariaDBDDLParser.h"
#include <antlr4-runtime.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

MariaDBConnector::MariaDBConnector(MariaDBConn conn_object)
    : m_conn_object(conn_object) {};

MariaDBConnector::~MariaDBConnector() {}

std::vector<Table> MariaDBConnector::get_schema(ConsoleLog *log)
{
  auto out = [&](const std::string &line) {
    if(log) log->append(line);
  };

  auto tables = parse(dump());

  out("Parsing Done !");
  out("Tables: " + std::to_string(tables.size()));

  for(const auto &table : tables) {
    std::string line = table.name + ":";
    out(line);

    std::string cols = "  Columns: ";
    for(const auto &col : table.columns) {
      cols += col.name;
      if(col.auto_increment) cols += "(AI)";
      cols += ", ";
    }
    out(cols);

    if(table.primary_key) {
      std::string pk = "  PK: ";
      for(const auto &pk_col : table.primary_key->column_names)
        pk += pk_col + " ";
      out(pk);
    }

    if(!table.foreign_keys.empty()) {
      out("  Foreign Keys:");
      for(const auto &fk : table.foreign_keys) {
        std::string fk_line = "    " + fk.name + " references " + fk.referenced_table + " (";
        for(const auto &ref_col : fk.referenced_columns)
          fk_line += ref_col + " ";
        fk_line += ")";
        out(fk_line);
      }
    }

    if(!table.indexes.empty()) {
      out("  Indexes:");
      for(const auto &idx : table.indexes) {
        std::string idx_line = "    " + idx.name + (idx.unique ? " (UNIQUE)" : "") + " [";
        for(const auto &ic : idx.column_names)
          idx_line += ic + " ";
        idx_line += "]";
        out(idx_line);
      }
    }

    out("");
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
