#include "DiffQL/MigrationGenerator/MigrationGenerator.hpp"

#include <sstream>

std::string MigrationGenerator::quote_identifier(const std::string &name) const
{
  return identifier_quote() + name + identifier_quote();
}

std::string MigrationGenerator::join_columns(const std::vector<std::string> &cols) const
{
  std::ostringstream os;
  for (size_t i = 0; i < cols.size(); ++i) {
    if (i > 0)
      os << ", ";
    os << quote_identifier(cols[i]);
  }
  return os.str();
}
