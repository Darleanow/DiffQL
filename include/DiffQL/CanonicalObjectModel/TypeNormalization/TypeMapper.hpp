#pragma once

#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include <optional>

class TypeMapper
{
public:
  virtual CanonicalType map(const std::string  &raw_type_name,
                            std::optional<int>  first_type_modifier  = {},
                            std::optional<int>  second_type_modifier = {}) = 0;
};

class MariaDBTypeMapper : public TypeMapper
{
  CanonicalType map(const std::string  &raw_type_name,
                    std::optional<int>  first_type_modifier  = {},
                    std::optional<int>  second_type_modifier = {}) override;
};

class PostgreSQLTypeMapper : public TypeMapper
{
public:
  CanonicalType map(const std::string  &raw_type_name,
                    std::optional<int>  first_type_modifier  = {},
                    std::optional<int>  second_type_modifier = {}) override;
};
