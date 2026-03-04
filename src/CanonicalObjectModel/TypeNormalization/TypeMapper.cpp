#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/CanonicalObjectModel/TypeNormalization/TypeMapper.hpp"

CanonicalType MariaDBTypeMapper::map(const std::string &raw)
{
  if(raw.starts_with("int")) {
    return {CanonicalType::INTEGER, {}, {}, {}, raw};
  }

  return {CanonicalType::INTEGER, {}, {}, {}, raw};
}
