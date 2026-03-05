#pragma once

#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"

class TypeMapper
{
public:
  virtual CanonicalType map(const std::string &raw_type) = 0;
};

class MariaDBTypeMapper : public TypeMapper
{
public:
  CanonicalType map(const std::string &raw) override;
};

class PostgreSQLTypeMapper : public TypeMapper
{
public:
  CanonicalType map(const std::string &raw) override;
};
