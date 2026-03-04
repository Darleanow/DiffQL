#pragma once

#include "DiffQL/Connectors/BaseConnector.hpp"
#include <libpq-fe.h>
#include <vector>
#include <fstream>

struct PostgreSQLConn
{
  const std::string host;
  const std::string user;
  const std::string passwd;
  const std::string db;
  const std::string port;
};

struct Table;

class PostgreSQLConnector final : public BaseConnector
{
public:
  PostgreSQLConnector(PostgreSQLConn conn_object);
  ~PostgreSQLConnector();

  std::vector<Table> get_schema() final;

private:
  PostgreSQLConn m_conn_object;
  PGconn*        m_connection;

  std::ifstream  dump();

  void           parse(std::ifstream file);
};