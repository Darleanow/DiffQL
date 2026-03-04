#pragma once

#include "DiffQL/Connectors/BaseConnector.hpp"
#include <mariadb/mysql.h>
#include <vector>

struct MariaDBConn
{
  const std::string host;
  const std::string user;
  const std::string passwd;
  const std::string db;
};

struct Table;

class MariaDBConnector final : BaseConnector
{
public:
  MariaDBConnector(MariaDBConn conn_object);
  ~MariaDBConnector();

  std::vector<Table> get_schema() final;

private:
  MariaDBConn   m_conn_object;

  std::ifstream dump();

  void          parse(std::ifstream file);
};
