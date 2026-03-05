#include "DiffQL/CanonicalObjectModel/TypeNormalization/TypeMapper.hpp"
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"

CanonicalType MariaDBTypeMapper::map(const std::string &raw)
{
  if(raw.starts_with("int")) {
    // return {CanonicalType::INTEGER, {}, {}, {}, raw};
  }

  return {CanonicalType::INTEGER, {}, {}, {}};
}
