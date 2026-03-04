#pragma once

#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"

class TypeMapper
{
public:
  virtual CanonicalType map(const std::string &raw_type) = 0;
};

class MariaDBTypeMapper : public TypeMapper
{
  CanonicalType map(const std::string &raw) override;
};
