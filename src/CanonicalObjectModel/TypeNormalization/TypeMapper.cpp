#include "DiffQL/CanonicalObjectModel/TypeNormalization/TypeMapper.hpp"
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"

CanonicalType MariaDBTypeMapper::map(const std::string  &raw_type_name,
                                     std::optional<int>  first_type_modifier,
                                     std::optional<int>  second_type_modifier)
{
  if(raw_type_name.starts_with("int"))
    return {.base = CanonicalType::INTEGER, .length = {}, .precision = {}, .scale = {}};

  return {.base = CanonicalType::TEXT, .length = {}, .precision = {}, .scale = {}};
}

CanonicalType PostgreSQLTypeMapper::map(const std::string  &raw_type_name,
                                        std::optional<int>  first_type_modifier,
                                        std::optional<int>  second_type_modifier)
{
  if(raw_type_name == "int2" || raw_type_name == "smallserial")
    return {.base = CanonicalType::SMALLINT, .length = {}, .precision = {}, .scale = {}};

  if(raw_type_name == "int4" || raw_type_name == "integer" || raw_type_name == "int" || raw_type_name == "serial")
    return {.base = CanonicalType::INTEGER, .length = {}, .precision = {}, .scale = {}};

  if(raw_type_name == "int8" || raw_type_name == "bigint" || raw_type_name == "bigserial")
    return {.base = CanonicalType::BIGINT, .length = {}, .precision = {}, .scale = {}};

  if(raw_type_name == "text")
    return {.base = CanonicalType::TEXT, .length = {}, .precision = {}, .scale = {}};

  if(raw_type_name == "varchar")
    return {.base = CanonicalType::VARCHAR, .length = first_type_modifier, .precision = {}, .scale = {}};

  if(raw_type_name == "bpchar" || raw_type_name.starts_with("char"))
    return {.base = CanonicalType::CHAR, .length = first_type_modifier, .precision = {}, .scale = {}};

  if(raw_type_name == "numeric" || raw_type_name == "decimal")
    return {.base = CanonicalType::DECIMAL, .length = {}, .precision = first_type_modifier, .scale = second_type_modifier};

  if(raw_type_name == "float4")
    return {.base = CanonicalType::FLOAT, .length = first_type_modifier, .precision = {}, .scale = {}};

  if(raw_type_name == "float8")
    return {.base = CanonicalType::DOUBLE, .length = first_type_modifier, .precision = {}, .scale = {}};

  if(raw_type_name == "date")
    return {.base = CanonicalType::DATE, .length = {}, .precision = {}, .scale = {}};

  if(raw_type_name == "timestamp" || raw_type_name == "timestamptz")
    return {.base = CanonicalType::TIMESTAMP, .length = {}, .precision = first_type_modifier, .scale = {}};

  if(raw_type_name == "time" || raw_type_name == "timetz")
    return {.base = CanonicalType::TIME, .length = {}, .precision = first_type_modifier, .scale = {}};

  if(raw_type_name == "bool")
    return {.base = CanonicalType::BOOLEAN, .length = {}, .precision = {}, .scale = {}};

  if(raw_type_name == "bytea")
    return {.base = CanonicalType::BLOB, .length = {}, .precision = {}, .scale = {}};

  if(raw_type_name == "json" || raw_type_name == "jsonb")
    return {.base = CanonicalType::JSON, .length = {}, .precision = {}, .scale = {}};

  return {.base = CanonicalType::TEXT, .length = {}, .precision = {}, .scale = {}};
}
