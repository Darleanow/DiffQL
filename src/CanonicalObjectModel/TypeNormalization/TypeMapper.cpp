#include "DiffQL/CanonicalObjectModel/TypeNormalization/TypeMapper.hpp"

#include <algorithm>
#include <cctype>
#include <optional>

namespace {
std::string trim(const std::string &value)
{
  size_t begin = 0;
  size_t end   = value.size();

  while(begin < end &&
        std::isspace(static_cast<unsigned char>(value[begin])) != 0) {
    ++begin;
  }
  while(end > begin &&
        std::isspace(static_cast<unsigned char>(value[end - 1])) != 0) {
    --end;
  }

  return value.substr(begin, end - begin);
}

std::string to_lower(std::string value)
{
  std::transform(
      value.begin(), value.end(), value.begin(),
      [](unsigned char c) { return static_cast<char>(std::tolower(c)); }
  );
  return value;
}

std::optional<int> to_int(const std::string &value)
{
  try {
    return std::stoi(value);
  } catch(...) {
    return std::nullopt;
  }
}

std::optional<int> parse_single_length(const std::string &normalized)
{
  const size_t open = normalized.find('(');
  const size_t close =
      normalized.find(')', open == std::string::npos ? 0 : open + 1);

  if(open == std::string::npos || close == std::string::npos ||
     close <= open + 1) {
    return std::nullopt;
  }

  return to_int(trim(normalized.substr(open + 1, close - open - 1)));
}
} // namespace

CanonicalType MariaDBTypeMapper::map(const std::string &raw)
{
  if(raw.starts_with("int")) {
    return {CanonicalType::INTEGER, {}, {}, {}, raw};
  }

  return {CanonicalType::INTEGER, {}, {}, {}, raw};
}

CanonicalType PostgreSQLTypeMapper::map(const std::string &raw)
{
  const std::string normalized = to_lower(trim(raw));

  if(normalized == "smallint" || normalized == "int2") {
    return {CanonicalType::SMALLINT, {}, {}, {}, raw};
  }
  if(normalized == "bigint" || normalized == "int8") {
    return {CanonicalType::BIGINT, {}, {}, {}, raw};
  }
  if(normalized == "integer" || normalized == "int" || normalized == "int4") {
    return {CanonicalType::INTEGER, {}, {}, {}, raw};
  }
  if(normalized.find("character varying") == 0 ||
     normalized.find("varchar") == 0) {
    const std::optional<int> length = parse_single_length(normalized);
    if(length.has_value()) {
      return {CanonicalType::VARCHAR, *length, {}, {}, raw};
    }
    return {CanonicalType::VARCHAR, {}, {}, {}, raw};
  }
  if(normalized.find("character") == 0 || normalized.find("char") == 0) {
    const std::optional<int> length = parse_single_length(normalized);
    if(length.has_value()) {
      return {CanonicalType::CHAR, *length, {}, {}, raw};
    }
    return {CanonicalType::CHAR, {}, {}, {}, raw};
  }
  if(normalized == "text") {
    return {CanonicalType::TEXT, {}, {}, {}, raw};
  }
  if(normalized.find("numeric") == 0 || normalized.find("decimal") == 0) {
    return {CanonicalType::DECIMAL, {}, {}, {}, raw};
  }
  if(normalized == "real" || normalized == "float4") {
    return {CanonicalType::FLOAT, {}, {}, {}, raw};
  }
  if(normalized == "double precision" || normalized == "float8") {
    return {CanonicalType::DOUBLE, {}, {}, {}, raw};
  }
  if(normalized == "date") {
    return {CanonicalType::DATE, {}, {}, {}, raw};
  }
  if(normalized.find("timestamp") == 0 || normalized == "timestamptz") {
    return {CanonicalType::TIMESTAMP, {}, {}, {}, raw};
  }
  if(normalized == "boolean" || normalized == "bool") {
    return {CanonicalType::BOOLEAN, {}, {}, {}, raw};
  }
  if(normalized == "bytea") {
    return {CanonicalType::BLOB, {}, {}, {}, raw};
  }
  if(normalized == "json" || normalized == "jsonb") {
    return {CanonicalType::JSON, {}, {}, {}, raw};
  }

  return {CanonicalType::TEXT, {}, {}, {}, raw};
}
