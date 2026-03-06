#include "DiffQL/Connectors/PostgreSQL/Connector.hpp"
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/CanonicalObjectModel/TypeNormalization/TypeMapper.hpp"
#include <libpq-fe.h>
#include <iostream>
#include <map>
#include <string>

PostgreSQLConnector::PostgreSQLConnector(PostgreSQLConn conn_object)
    : m_conn_object(conn_object) {}

PostgreSQLConnector::~PostgreSQLConnector() {}

std::vector<Table> PostgreSQLConnector::get_schema()
{
  std::string conn_str = "host="      + m_conn_object.host   +
                         " user="     + m_conn_object.user   +
                         " password=" + m_conn_object.passwd +
                         " dbname="   + m_conn_object.db;

  PGconn *conn = PQconnectdb(conn_str.c_str());

  if(PQstatus(conn) != CONNECTION_OK) {
    std::cerr << "Connection error: " << PQerrorMessage(conn) << std::endl;
    PQfinish(conn);
    return {};
  }

  auto tables = fetch_tables(conn);
  PQfinish(conn);

  std::cout << "Parsing Done !" << std::endl;
  std::cout << "Tables: " << tables.size() << std::endl;

  return tables;
}

std::vector<Table> PostgreSQLConnector::fetch_tables(PGconn *conn)
{
  PGresult *result = PQexec(conn,
      "SELECT table_name FROM information_schema.tables "
      "WHERE table_schema = 'public' AND table_type = 'BASE TABLE' "
      "ORDER BY table_name");

  if(PQresultStatus(result) != PGRES_TUPLES_OK) {
    std::cerr << "Error fetching tables: " << PQerrorMessage(conn) << std::endl;
    PQclear(result);
    return {};
  }

  std::vector<Table> tables;
  int                row_count = PQntuples(result);

  for(int row = 0; row < row_count; ++row) {
    std::string table_name = PQgetvalue(result, row, 0);

    Table table;
    table.name         = table_name;
    table.schema       = "public";
    table.columns      = fetch_columns(conn, table_name);
    table.primary_key  = fetch_primary_key(conn, table_name);
    table.foreign_keys = fetch_foreign_keys(conn, table_name);
    table.indexes      = fetch_indexes(conn, table_name);
    table.checks       = fetch_checks(conn, table_name);

    tables.push_back(std::move(table));
  }

  PQclear(result);
  return tables;
}

std::vector<Column> PostgreSQLConnector::fetch_columns(PGconn *conn, const std::string &table_name)
{
  const char *params[] = {table_name.c_str()};
  PGresult   *result   = PQexecParams(conn,
      "SELECT column_name, udt_name, character_maximum_length, "
      "       numeric_precision, numeric_scale, is_nullable, column_default "
      "FROM information_schema.columns "
      "WHERE table_schema = 'public' AND table_name = $1 "
      "ORDER BY ordinal_position",
      1, nullptr, params, nullptr, nullptr, 0);

  if(PQresultStatus(result) != PGRES_TUPLES_OK) {
    std::cerr << "Error fetching columns: " << PQerrorMessage(conn) << std::endl;
    PQclear(result);
    return {};
  }

  PostgreSQLTypeMapper type_mapper;
  std::vector<Column>  columns;
  int                  row_count = PQntuples(result);

  for(int row = 0; row < row_count; ++row) {
    std::string udt_name    = PQgetvalue(result, row, 1);
    std::string is_nullable = PQgetvalue(result, row, 5);

    // character_maximum_length takes priority for char/varchar; fall back to numeric_precision
    std::optional<int> first_modifier;
    std::optional<int> second_modifier;
    if(!PQgetisnull(result, row, 2))
      first_modifier = std::stoi(PQgetvalue(result, row, 2));
    else if(!PQgetisnull(result, row, 3))
      first_modifier = std::stoi(PQgetvalue(result, row, 3));
    if(!PQgetisnull(result, row, 4))
      second_modifier = std::stoi(PQgetvalue(result, row, 4));

    // SERIAL columns have a nextval(...) default — not a user-defined default value
    bool auto_increment = false;
    if(!PQgetisnull(result, row, 6)) {
      std::string col_default = PQgetvalue(result, row, 6);
      auto_increment = col_default.starts_with("nextval(");
    }

    std::optional<std::string> default_value;
    if(!PQgetisnull(result, row, 6) && !auto_increment)
      default_value = PQgetvalue(result, row, 6);

    Column col;
    col.name           = PQgetvalue(result, row, 0);
    col.type           = type_mapper.map(udt_name, first_modifier, second_modifier);
    col.nullable       = (is_nullable == "YES");
    col.auto_increment = auto_increment;
    col.default_value  = default_value;
    col.source_dbms    = "PostgreSQL";

    columns.push_back(std::move(col));
  }

  PQclear(result);
  return columns;
}

std::optional<PrimaryKey> PostgreSQLConnector::fetch_primary_key(PGconn *conn, const std::string &table_name)
{
  const char *params[] = {table_name.c_str()};
  PGresult   *result   = PQexecParams(conn,
      "SELECT kcu.constraint_name, kcu.column_name "
      "FROM information_schema.table_constraints tc "
      "JOIN information_schema.key_column_usage kcu "
      "    ON tc.constraint_name = kcu.constraint_name "
      "    AND tc.table_schema = kcu.table_schema "
      "    AND tc.table_name = kcu.table_name "
      "WHERE tc.constraint_type = 'PRIMARY KEY' "
      "    AND tc.table_schema = 'public' "
      "    AND tc.table_name = $1 "
      "ORDER BY kcu.ordinal_position",
      1, nullptr, params, nullptr, nullptr, 0);

  if(PQresultStatus(result) != PGRES_TUPLES_OK) {
    std::cerr << "Error fetching primary key: " << PQerrorMessage(conn) << std::endl;
    PQclear(result);
    return {};
  }

  int row_count = PQntuples(result);
  if(row_count == 0) {
    PQclear(result);
    return {};
  }

  PrimaryKey pk;
  pk.constraint_name = PQgetvalue(result, 0, 0);
  for(int row = 0; row < row_count; ++row)
    pk.column_names.push_back(PQgetvalue(result, row, 1));

  PQclear(result);
  return pk;
}

std::vector<ForeignKey> PostgreSQLConnector::fetch_foreign_keys(PGconn *conn, const std::string &table_name)
{
  const char *params[] = {table_name.c_str()};
  PGresult   *result   = PQexecParams(conn,
      "SELECT tc.constraint_name, kcu.column_name, "
      "       ccu.table_name AS referenced_table, ccu.column_name AS referenced_column, "
      "       rc.delete_rule, rc.update_rule "
      "FROM information_schema.table_constraints tc "
      "JOIN information_schema.key_column_usage kcu "
      "    ON tc.constraint_name = kcu.constraint_name "
      "    AND tc.table_schema = kcu.table_schema "
      "    AND tc.table_name = kcu.table_name "
      "JOIN information_schema.constraint_column_usage ccu "
      "    ON ccu.constraint_name = tc.constraint_name "
      "    AND ccu.table_schema = tc.table_schema "
      "JOIN information_schema.referential_constraints rc "
      "    ON rc.constraint_name = tc.constraint_name "
      "    AND rc.constraint_schema = tc.table_schema "
      "WHERE tc.constraint_type = 'FOREIGN KEY' "
      "    AND tc.table_schema = 'public' "
      "    AND tc.table_name = $1 "
      "ORDER BY tc.constraint_name, kcu.ordinal_position",
      1, nullptr, params, nullptr, nullptr, 0);

  if(PQresultStatus(result) != PGRES_TUPLES_OK) {
    std::cerr << "Error fetching foreign keys: " << PQerrorMessage(conn) << std::endl;
    PQclear(result);
    return {};
  }

  std::vector<ForeignKey>             foreign_keys;
  std::map<std::string, ForeignKey *> fk_by_name;
  int                                 row_count = PQntuples(result);

  for(int row = 0; row < row_count; ++row) {
    std::string constraint_name   = PQgetvalue(result, row, 0);
    std::string column_name       = PQgetvalue(result, row, 1);
    std::string referenced_table  = PQgetvalue(result, row, 2);
    std::string referenced_column = PQgetvalue(result, row, 3);
    std::string delete_rule       = PQgetvalue(result, row, 4);
    std::string update_rule       = PQgetvalue(result, row, 5);

    auto it = fk_by_name.find(constraint_name);
    if(it == fk_by_name.end()) {
      ForeignKey fk;
      fk.name             = constraint_name;
      fk.referenced_table = referenced_table;
      fk.on_delete        = delete_rule;
      fk.on_update        = update_rule;
      fk.column_names.push_back(column_name);
      fk.referenced_columns.push_back(referenced_column);
      foreign_keys.push_back(std::move(fk));
      fk_by_name[constraint_name] = &foreign_keys.back();
    } else {
      it->second->column_names.push_back(column_name);
      it->second->referenced_columns.push_back(referenced_column);
    }
  }

  PQclear(result);
  return foreign_keys;
}

std::vector<Index> PostgreSQLConnector::fetch_indexes(PGconn *conn, const std::string &table_name)
{
  const char *params[] = {table_name.c_str()};
  PGresult   *result   = PQexecParams(conn,
      "SELECT i.relname AS index_name, ix.indisunique AS is_unique, a.attname AS column_name "
      "FROM pg_class t "
      "JOIN pg_index ix ON t.oid = ix.indrelid "
      "JOIN pg_class i ON i.oid = ix.indexrelid "
      "JOIN pg_attribute a ON a.attrelid = t.oid AND a.attnum = ANY(ix.indkey) "
      "JOIN pg_namespace n ON n.oid = t.relnamespace "
      "WHERE t.relkind = 'r' "
      "    AND t.relname = $1 "
      "    AND n.nspname = 'public' "
      "    AND NOT ix.indisprimary "
      "ORDER BY i.relname, array_position(ix.indkey, a.attnum)",
      1, nullptr, params, nullptr, nullptr, 0);

  if(PQresultStatus(result) != PGRES_TUPLES_OK) {
    std::cerr << "Error fetching indexes: " << PQerrorMessage(conn) << std::endl;
    PQclear(result);
    return {};
  }

  std::vector<Index>             indexes;
  std::map<std::string, Index *> idx_by_name;
  int                            row_count = PQntuples(result);

  for(int row = 0; row < row_count; ++row) {
    std::string index_name  = PQgetvalue(result, row, 0);
    bool        is_unique   = (std::string(PQgetvalue(result, row, 1)) == "t");
    std::string column_name = PQgetvalue(result, row, 2);

    auto it = idx_by_name.find(index_name);
    if(it == idx_by_name.end()) {
      Index idx;
      idx.name   = index_name;
      idx.unique = is_unique;
      idx.type   = {};
      idx.column_names.push_back(column_name);
      indexes.push_back(std::move(idx));
      idx_by_name[index_name] = &indexes.back();
    } else {
      it->second->column_names.push_back(column_name);
    }
  }

  PQclear(result);
  return indexes;
}

std::vector<CheckConstraint> PostgreSQLConnector::fetch_checks(PGconn *conn, const std::string &table_name)
{
  const char *params[] = {table_name.c_str()};
  PGresult   *result   = PQexecParams(conn,
      "SELECT cc.constraint_name, cc.check_clause "
      "FROM information_schema.table_constraints tc "
      "JOIN information_schema.check_constraints cc "
      "    ON tc.constraint_name = cc.constraint_name "
      "    AND tc.constraint_schema = cc.constraint_schema "
      "WHERE tc.constraint_type = 'CHECK' "
      "    AND tc.table_schema = 'public' "
      "    AND tc.table_name = $1 "
      "    AND cc.check_clause NOT LIKE '% IS NOT NULL' "
      "ORDER BY cc.constraint_name",
      1, nullptr, params, nullptr, nullptr, 0);

  if(PQresultStatus(result) != PGRES_TUPLES_OK) {
    std::cerr << "Error fetching checks: " << PQerrorMessage(conn) << std::endl;
    PQclear(result);
    return {};
  }

  std::vector<CheckConstraint> checks;
  int                          row_count = PQntuples(result);

  for(int row = 0; row < row_count; ++row) {
    CheckConstraint check;
    check.name       = PQgetvalue(result, row, 0);
    check.expression = PQgetvalue(result, row, 1);
    checks.push_back(std::move(check));
  }

  PQclear(result);
  return checks;
}
