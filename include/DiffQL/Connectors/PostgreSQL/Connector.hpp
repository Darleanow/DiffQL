#pragma once

#include "DiffQL/Connectors/BaseConnector.hpp"
#include <libpq-fe.h>
#include <optional>
#include <string>
#include <vector>

struct PostgreSQLConn
{
  const std::string host;
  const std::string user;
  const std::string passwd;
  const std::string db;
};

class PostgreSQLConnector final : public BaseConnector
{
public:
  PostgreSQLConnector(PostgreSQLConn conn_object);
  ~PostgreSQLConnector();

  std::vector<Table> get_schema() final;

private:
  PostgreSQLConn m_conn_object;

  std::vector<Table>           fetch_tables(PGconn *conn);
  std::vector<Column>          fetch_columns(PGconn *conn, const std::string &table_name);
  std::optional<PrimaryKey>    fetch_primary_key(PGconn *conn, const std::string &table_name);
  std::vector<ForeignKey>      fetch_foreign_keys(PGconn *conn, const std::string &table_name);
  std::vector<Index>           fetch_indexes(PGconn *conn, const std::string &table_name);
  std::vector<CheckConstraint> fetch_checks(PGconn *conn, const std::string &table_name);
};
