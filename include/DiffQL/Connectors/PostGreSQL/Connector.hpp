#pragma once

#include "DiffQL/Connectors/BaseConnector.hpp"
#include <fstream>
#include <istream>
#include <string>
#include <vector>

struct PostgreSQLConn
{
  std::string host;
  std::string user;
  std::string passwd;
  std::string db;
  std::string port;
};

class PostgreSQLConnector final : public BaseConnector
{
public:
  explicit PostgreSQLConnector(PostgreSQLConn conn_object);
  ~PostgreSQLConnector();

  std::vector<Table> get_schema() final;

private:
  PostgreSQLConn      m_conn_object;

  std::ifstream       dump() const;
  std::vector<Table>  parse(std::istream &input) const;
};
