#include "DiffQL/Connectors/PostGreSQL/Connector.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

std::string type_to_string(const CanonicalType &type)
{
  switch(type.base) {
  case CanonicalType::INTEGER:
    return "integer";
  case CanonicalType::BIGINT:
    return "bigint";
  case CanonicalType::SMALLINT:
    return "smallint";
  case CanonicalType::VARCHAR:
    if(type.length.has_value())
      return "varchar(" + std::to_string(*type.length) + ")";
    return "varchar";
  case CanonicalType::TEXT:
    return "text";
  case CanonicalType::CHAR:
    if(type.length.has_value())
      return "char(" + std::to_string(*type.length) + ")";
    return "char";
  case CanonicalType::DECIMAL:
    if(type.precision.has_value() && type.scale.has_value()) {
      return "decimal(" + std::to_string(*type.precision) + "," +
             std::to_string(*type.scale) + ")";
    }
    if(type.precision.has_value())
      return "decimal(" + std::to_string(*type.precision) + ")";
    return "decimal";
  case CanonicalType::FLOAT:
    return "float";
  case CanonicalType::DOUBLE:
    return "double";
  case CanonicalType::DATE:
    return "date";
  case CanonicalType::DATETIME:
    return "datetime";
  case CanonicalType::TIMESTAMP:
    return "timestamp";
  case CanonicalType::BOOLEAN:
    return "boolean";
  case CanonicalType::BLOB:
    return "blob";
  case CanonicalType::JSON:
    return "json";
  }
  return "text";
}

std::string env_or_default(const char *name, const char *fallback)
{
  const char *value = std::getenv(name);
  if(value == nullptr) {
    return std::string(fallback);
  }
  return std::string(value);
}

int main()
{
  PostgreSQLConn conn {
      .host   = env_or_default("DIFFQL_PG_HOST", "localhost"),
      .user   = env_or_default("DIFFQL_PG_USER", "postgres"),
      .passwd = env_or_default("DIFFQL_PG_PASSWORD", ""),
      .db     = env_or_default("DIFFQL_PG_DB", "postgres"),
      .port   = env_or_default("DIFFQL_PG_PORT", "5432")
  };

  try {
    PostgreSQLConnector connector(conn);
    std::vector<Table>  schema = connector.get_schema();

    std::cout << "database=" << conn.db << "\n";
    std::cout << "tables=" << schema.size() << "\n";

    for(const Table &table : schema) {
      std::cout << "table " << table.schema << "." << table.name << "\n";
      std::cout << "  columns=" << table.columns.size() << "\n";

      for(const Column &column : table.columns) {
        std::cout << "    " << column.position << " " << column.name
                  << " type=" << type_to_string(column.type)
                  << " nullable=" << (column.nullable ? "true" : "false")
                  << " auto_increment="
                  << (column.auto_increment ? "true" : "false");

        if(column.default_value.has_value()) {
          std::cout << " default=" << *column.default_value;
        }

        std::cout << "\n";
      }

      if(table.primary_key.has_value()) {
        std::cout << "  primary_key=";
        for(size_t i = 0; i < table.primary_key->column_names.size(); ++i) {
          if(i > 0) {
            std::cout << ",";
          }
          std::cout << table.primary_key->column_names[i];
        }
        std::cout << "\n";
      }

      std::cout << "  indexes=" << table.indexes.size() << "\n";
      for(const Index &idx : table.indexes) {
        std::cout << "    " << idx.name
                  << " unique=" << (idx.unique ? "true" : "false")
                  << " type=" << idx.type << " cols=";

        for(size_t i = 0; i < idx.column_names.size(); ++i) {
          if(i > 0) {
            std::cout << ",";
          }
          std::cout << idx.column_names[i];
        }

        std::cout << "\n";
      }

      std::cout << "  foreign_keys=" << table.foreign_keys.size() << "\n";
      for(const ForeignKey &fk : table.foreign_keys) {
        std::cout << "    " << fk.name << " cols=";
        for(size_t i = 0; i < fk.column_names.size(); ++i) {
          if(i > 0) {
            std::cout << ",";
          }
          std::cout << fk.column_names[i];
        }

        std::cout << " ref=" << fk.referenced_table << "(";
        for(size_t i = 0; i < fk.referenced_columns.size(); ++i) {
          if(i > 0) {
            std::cout << ",";
          }
          std::cout << fk.referenced_columns[i];
        }
        std::cout << ")"
                  << " on_delete=" << fk.on_delete
                  << " on_update=" << fk.on_update << "\n";
      }
    }

    return 0;
  } catch(const std::exception &e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
}
