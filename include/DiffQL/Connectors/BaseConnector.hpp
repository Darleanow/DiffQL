#pragma once

#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include <vector>

class Schema;
class ConsoleLog;

class BaseConnector
{
public:
  virtual std::vector<Table> get_schema(ConsoleLog *log = nullptr) = 0;
};
