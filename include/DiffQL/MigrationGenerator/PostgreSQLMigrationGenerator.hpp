#pragma once
#include "DiffQL/MigrationGenerator/MigrationGenerator.hpp"

/**
 * @brief Migration script generator for PostgreSQL databases.
 *
 * Generates ALTER TABLE statements using PostgreSQL syntax:
 * - Uses double quotes (") for identifier quoting
 * - Uses ALTER COLUMN for column changes
 * - Supports PostgreSQL-specific data types (SERIAL, TEXT, etc.)
 */
class PostgreSQLMigrationGenerator : public MigrationGenerator
{
public:
  std::string generate(
      const SchemaDiff         &diff,
      const std::vector<Table> &source_schema,
      const std::vector<Table> &dest_schema
  ) const override;

  std::string database_name() const override;

protected:
  std::string generate_create_table(const Table &table) const override;
  std::string generate_drop_table(const std::string &table_name) const override;

  std::string generate_add_column(
      const std::string &table_name,
      const Column      &column
  ) const override;

  std::string generate_drop_column(
      const std::string &table_name,
      const std::string &column_name
  ) const override;

  std::string generate_modify_column(
      const std::string &table_name,
      const Column      &old_column,
      const Column      &new_column
  ) const override;

  std::string generate_add_primary_key(
      const std::string &table_name,
      const PrimaryKey  &pk
  ) const override;

  std::string generate_drop_primary_key(
      const std::string &table_name,
      const PrimaryKey  &pk
  ) const override;

  std::string generate_add_foreign_key(
      const std::string &table_name,
      const ForeignKey  &fk
  ) const override;

  std::string generate_drop_foreign_key(
      const std::string &table_name,
      const ForeignKey  &fk
  ) const override;

  std::string generate_add_index(
      const std::string &table_name,
      const Index       &index
  ) const override;

  std::string generate_drop_index(
      const std::string &table_name,
      const Index       &index
  ) const override;

  std::string generate_add_check(
      const std::string    &table_name,
      const CheckConstraint &check
  ) const override;

  std::string generate_drop_check(
      const std::string    &table_name,
      const CheckConstraint &check
  ) const override;

  std::string type_to_sql(const CanonicalType &type) const override;

  std::string identifier_quote() const override;

private:
  std::string column_definition(const Column &col, bool for_create = true) const;

  // PostgreSQL requires separate statements for some column alterations
  std::string generate_alter_column_type(
      const std::string &table_name,
      const Column      &new_column
  ) const;

  std::string generate_alter_column_nullable(
      const std::string &table_name,
      const std::string &column_name,
      bool nullable
  ) const;

  std::string generate_alter_column_default(
      const std::string                &table_name,
      const std::string                &column_name,
      const std::optional<std::string> &default_value
  ) const;
};
