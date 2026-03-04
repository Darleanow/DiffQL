#pragma once

#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include <vector>

class Schema;

class BaseConnector
{
public:
  virtual std::vector<Table> get_schema() = 0;
};
