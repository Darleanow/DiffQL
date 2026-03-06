#pragma once

#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/Connectors/BaseConnector.hpp"
#include "DiffQL/UI/ConsoleLog.hpp"
#include <functional>
#include <mariadb/mysql.h>
#include <optional>
#include <vector>

struct MariaDBConn
{
  std::string        host   = "localhost";
  std::string        user;
  std::string        passwd;
  std::string        db;
  std::optional<int> port;
};

struct Table;

class MariaDBConnector final : BaseConnector
{
public:
  MariaDBConnector(MariaDBConn conn_object);
  ~MariaDBConnector();

  std::vector<Table> get_schema(ConsoleLog *log = nullptr) final;

private:
  MariaDBConn        m_conn_object;

  std::ifstream      dump();

  std::vector<Table> parse(const std::ifstream &file);
};
