#pragma once
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/DiffEngine/DiffEngine.hpp"
#include <string>
#include <vector>

class MigrationGenerator
{
public:
  virtual ~MigrationGenerator() = default;

  virtual std::string generate(
      const SchemaDiff         &diff,
      const std::vector<Table> &source_schema,
      const std::vector<Table> &dest_schema
  ) const = 0;

  virtual std::string database_name() const = 0;

protected:
  virtual std::string generate_create_table(const Table &table) const = 0;
  virtual std::string generate_drop_table(const std::string &table_name) const = 0;

  virtual std::string generate_add_column(
      const std::string &table_name,
      const Column      &column
  ) const = 0;

  virtual std::string generate_drop_column(
      const std::string &table_name,
      const std::string &column_name
  ) const = 0;

  virtual std::string generate_modify_column(
      const std::string &table_name,
      const Column      &old_column,
      const Column      &new_column
  ) const = 0;

  virtual std::string generate_add_primary_key(
      const std::string &table_name,
      const PrimaryKey  &pk
  ) const = 0;

  virtual std::string generate_drop_primary_key(
      const std::string &table_name,
      const PrimaryKey  &pk
  ) const = 0;

  virtual std::string generate_add_foreign_key(
      const std::string &table_name,
      const ForeignKey  &fk
  ) const = 0;

  virtual std::string generate_drop_foreign_key(
      const std::string &table_name,
      const ForeignKey  &fk
  ) const = 0;

  virtual std::string generate_add_index(
      const std::string &table_name,
      const Index       &index
  ) const = 0;

  virtual std::string generate_drop_index(
      const std::string &table_name,
      const Index       &index
  ) const = 0;

  virtual std::string generate_add_check(
      const std::string     &table_name,
      const CheckConstraint &check
  ) const = 0;

  virtual std::string generate_drop_check(
      const std::string     &table_name,
      const CheckConstraint &check
  ) const = 0;

  virtual std::string type_to_sql(const CanonicalType &type) const = 0;
  virtual std::string identifier_quote() const = 0;

  std::string quote_identifier(const std::string &name) const;
  std::string join_columns(const std::vector<std::string> &cols) const;
};
