#include "DiffQL/MigrationGenerator/PostgreSQLMigrationGenerator.hpp"

#include <algorithm>
#include <sstream>
#include <unordered_map>

std::string PostgreSQLMigrationGenerator::database_name() const { return "PostgreSQL"; }
std::string PostgreSQLMigrationGenerator::identifier_quote() const { return "\""; }

std::string PostgreSQLMigrationGenerator::type_to_sql(const CanonicalType &type) const
{
  std::ostringstream os;

  switch(type.base) {
    case CanonicalType::INTEGER:    os << "INTEGER"; break;
    case CanonicalType::BIGINT:     os << "BIGINT"; break;
    case CanonicalType::SMALLINT:   os << "SMALLINT"; break;
    case CanonicalType::TINYINT:    os << "SMALLINT"; break;  // PostgreSQL doesn't have TINYINT
    case CanonicalType::MEDIUMINT:  os << "INTEGER"; break;   // PostgreSQL doesn't have MEDIUMINT
    case CanonicalType::VARCHAR:
      os << "VARCHAR";
      if(type.length) os << "(" << *type.length << ")";
      else os << "(255)";  // Default length
      break;
    case CanonicalType::TEXT:       os << "TEXT"; break;
    case CanonicalType::MEDIUMTEXT: os << "TEXT"; break;  // PostgreSQL uses TEXT for all
    case CanonicalType::LONGTEXT:   os << "TEXT"; break;
    case CanonicalType::CHAR:
      os << "CHAR";
      if(type.length) os << "(" << *type.length << ")";
      break;
    case CanonicalType::DECIMAL:
      os << "NUMERIC";
      if(type.precision) {
        os << "(" << *type.precision;
        if(type.scale) os << "," << *type.scale;
        os << ")";
      }
      break;
    case CanonicalType::FLOAT:      os << "REAL"; break;
    case CanonicalType::DOUBLE:     os << "DOUBLE PRECISION"; break;
    case CanonicalType::DATE:       os << "DATE"; break;
    case CanonicalType::DATETIME:   os << "TIMESTAMP"; break;
    case CanonicalType::TIMESTAMP:  os << "TIMESTAMP"; break;
    case CanonicalType::TIME:       os << "TIME"; break;
    case CanonicalType::BOOLEAN:    os << "BOOLEAN"; break;
    case CanonicalType::BLOB:       os << "BYTEA"; break;
    case CanonicalType::JSON:       os << "JSONB"; break;
    case CanonicalType::ENUM:       os << "VARCHAR(255)"; break;  // Use VARCHAR as fallback
  }

  return os.str();
}

std::string PostgreSQLMigrationGenerator::column_definition(
    const Column &col,
    bool for_create
) const
{
  std::ostringstream os;

  os << quote_identifier(col.name) << " ";

  // Use SERIAL types for auto_increment in CREATE statements
  if(col.auto_increment && for_create) {
    switch(col.type.base) {
      case CanonicalType::BIGINT:
        os << "BIGSERIAL";
        break;
      case CanonicalType::SMALLINT:
        os << "SMALLSERIAL";
        break;
      default:
        os << "SERIAL";
        break;
    }
  } else {
    os << type_to_sql(col.type);
  }

  if(!col.nullable)
    os << " NOT NULL";

  if(col.default_value && !col.auto_increment) {
    const auto &def = *col.default_value;
    // Convert MySQL-specific functions to PostgreSQL equivalents
    if(def == "CURRENT_TIMESTAMP") {
      os << " DEFAULT CURRENT_TIMESTAMP";
    } else if(def == "NULL") {
      os << " DEFAULT NULL";
    } else if(def.find('(') != std::string::npos) {
      // Function call, use as-is
      os << " DEFAULT " << def;
    } else {
      os << " DEFAULT '" << def << "'";
    }
  }

  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_create_table(const Table &table) const
{
  std::ostringstream os;

  os << "CREATE TABLE " << quote_identifier(table.name) << " (\n";

  // Columns
  for(size_t i = 0; i < table.columns.size(); ++i) {
    os << "  " << column_definition(table.columns[i], true);
    if(i < table.columns.size() - 1 || table.primary_key ||
       !table.foreign_keys.empty() || !table.checks.empty())
      os << ",";
    os << "\n";
  }

  // Primary Key
  if(table.primary_key) {
    os << "  PRIMARY KEY (" << join_columns(table.primary_key->column_names) << ")";
    if(!table.foreign_keys.empty() || !table.checks.empty())
      os << ",";
    os << "\n";
  }

  // Foreign Keys
  for(size_t i = 0; i < table.foreign_keys.size(); ++i) {
    const auto &fk = table.foreign_keys[i];
    os << "  CONSTRAINT " << quote_identifier(fk.name)
       << " FOREIGN KEY (" << join_columns(fk.column_names) << ")"
       << " REFERENCES " << quote_identifier(fk.referenced_table)
       << " (" << join_columns(fk.referenced_columns) << ")";

    if(!fk.on_delete.empty() && fk.on_delete != "NO ACTION")
      os << " ON DELETE " << fk.on_delete;
    if(!fk.on_update.empty() && fk.on_update != "NO ACTION")
      os << " ON UPDATE " << fk.on_update;

    if(i < table.foreign_keys.size() - 1 || !table.checks.empty())
      os << ",";
    os << "\n";
  }

  // Check Constraints
  for(size_t i = 0; i < table.checks.size(); ++i) {
    const auto &chk = table.checks[i];
    os << "  CONSTRAINT " << quote_identifier(chk.name)
       << " CHECK (" << chk.expression << ")";
    if(i < table.checks.size() - 1)
      os << ",";
    os << "\n";
  }

  os << ");\n";

  // Indexes (created separately)
  for(const auto &idx : table.indexes) {
    os << generate_add_index(table.name, idx);
  }

  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_drop_table(const std::string &table_name) const
{
  return "DROP TABLE IF EXISTS " + quote_identifier(table_name) + " CASCADE;\n";
}

std::string PostgreSQLMigrationGenerator::generate_add_column(
    const std::string &table_name,
    const Column      &column
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ADD COLUMN " << column_definition(column, false) << ";\n";

  // If auto_increment, we need to create a sequence and set it
  if(column.auto_increment) {
    std::string seq_name = table_name + "_" + column.name + "_seq";
    os << "CREATE SEQUENCE IF NOT EXISTS " << quote_identifier(seq_name) << ";\n";
    os << "ALTER TABLE " << quote_identifier(table_name)
       << " ALTER COLUMN " << quote_identifier(column.name)
       << " SET DEFAULT nextval('" << seq_name << "');\n";
  }

  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_drop_column(
    const std::string &table_name,
    const std::string &column_name
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " DROP COLUMN " << quote_identifier(column_name) << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_alter_column_type(
    const std::string &table_name,
    const Column      &new_column
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ALTER COLUMN " << quote_identifier(new_column.name)
     << " TYPE " << type_to_sql(new_column.type) << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_alter_column_nullable(
    const std::string &table_name,
    const std::string &column_name,
    bool nullable
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ALTER COLUMN " << quote_identifier(column_name);

  if(nullable)
    os << " DROP NOT NULL;\n";
  else
    os << " SET NOT NULL;\n";

  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_alter_column_default(
    const std::string                &table_name,
    const std::string                &column_name,
    const std::optional<std::string> &default_value
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ALTER COLUMN " << quote_identifier(column_name);

  if(default_value) {
    const auto &def = *default_value;
    if(def == "CURRENT_TIMESTAMP" || def == "NULL" ||
       def.find('(') != std::string::npos)
      os << " SET DEFAULT " << def;
    else
      os << " SET DEFAULT '" << def << "'";
  } else {
    os << " DROP DEFAULT";
  }

  os << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_modify_column(
    const std::string &table_name,
    const Column      &old_column,
    const Column      &new_column
) const
{
  std::ostringstream os;

  // PostgreSQL requires separate statements for each column attribute change
  if(old_column.type != new_column.type)
    os << generate_alter_column_type(table_name, new_column);

  if(old_column.nullable != new_column.nullable)
    os << generate_alter_column_nullable(table_name, new_column.name, new_column.nullable);

  if(old_column.default_value != new_column.default_value)
    os << generate_alter_column_default(table_name, new_column.name, new_column.default_value);

  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_add_primary_key(
    const std::string &table_name,
    const PrimaryKey  &pk
) const
{
  std::ostringstream os;
  std::string constraint_name = pk.constraint_name.value_or(table_name + "_pkey");

  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ADD CONSTRAINT " << quote_identifier(constraint_name)
     << " PRIMARY KEY (" << join_columns(pk.column_names) << ");\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_drop_primary_key(
    const std::string &table_name,
    const PrimaryKey  &pk
) const
{
  std::ostringstream os;
  std::string constraint_name = pk.constraint_name.value_or(table_name + "_pkey");

  os << "ALTER TABLE " << quote_identifier(table_name)
     << " DROP CONSTRAINT " << quote_identifier(constraint_name) << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_add_foreign_key(
    const std::string &table_name,
    const ForeignKey  &fk
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ADD CONSTRAINT " << quote_identifier(fk.name)
     << " FOREIGN KEY (" << join_columns(fk.column_names) << ")"
     << " REFERENCES " << quote_identifier(fk.referenced_table)
     << " (" << join_columns(fk.referenced_columns) << ")";

  if(!fk.on_delete.empty() && fk.on_delete != "NO ACTION")
    os << " ON DELETE " << fk.on_delete;
  if(!fk.on_update.empty() && fk.on_update != "NO ACTION")
    os << " ON UPDATE " << fk.on_update;

  os << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_drop_foreign_key(
    const std::string &table_name,
    const ForeignKey  &fk
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " DROP CONSTRAINT " << quote_identifier(fk.name) << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_add_index(
    const std::string &table_name,
    const Index       &index
) const
{
  std::ostringstream os;

  if(index.unique)
    os << "CREATE UNIQUE INDEX ";
  else
    os << "CREATE INDEX ";

  os << quote_identifier(index.name)
     << " ON " << quote_identifier(table_name)
     << " (" << join_columns(index.column_names) << ")";

  // PostgreSQL index types: btree, hash, gist, gin, spgist, brin
  if(!index.type.empty()) {
    std::string pg_type = index.type;
    // Convert common MySQL types to PostgreSQL equivalents
    if(pg_type == "BTREE") pg_type = "btree";
    else if(pg_type == "HASH") pg_type = "hash";

    os << " USING " << pg_type;
  }

  os << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_drop_index(
    const std::string &table_name,
    const Index       &index
) const
{
  std::ostringstream os;
  // PostgreSQL doesn't need table name for DROP INDEX
  os << "DROP INDEX IF EXISTS " << quote_identifier(index.name) << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_add_check(
    const std::string    &table_name,
    const CheckConstraint &check
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ADD CONSTRAINT " << quote_identifier(check.name)
     << " CHECK (" << check.expression << ");\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate_drop_check(
    const std::string    &table_name,
    const CheckConstraint &check
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " DROP CONSTRAINT " << quote_identifier(check.name) << ";\n";
  return os.str();
}

std::string PostgreSQLMigrationGenerator::generate(
    const SchemaDiff         &diff,
    const std::vector<Table> &source_schema,
    const std::vector<Table> &dest_schema
) const
{
  std::ostringstream script;

  // Build lookup maps for table details
  std::unordered_map<std::string, const Table *> dest_map;
  for(const auto &t : dest_schema)
    dest_map[t.name] = &t;

  script << "-- Migration script generated by DiffQL for PostgreSQL\n";
  script << "-- Generated at: " << __DATE__ << " " << __TIME__ << "\n";
  script << "-- ==================================================\n\n";
  script << "BEGIN;\n\n";

  // Process each table diff
  for(const auto &td : diff.table_diffs) {
    script << "-- Table: " << td.table_name << "\n";

    switch(td.action) {
      case DiffAction::DROPPED:
        script << generate_drop_table(td.table_name);
        break;

      case DiffAction::ADDED: {
        auto it = dest_map.find(td.table_name);
        if(it != dest_map.end())
          script << generate_create_table(*it->second);
        break;
      }

      case DiffAction::MODIFIED: {
        // Drop foreign keys first (to avoid constraint issues)
        for(const auto &fk_diff : td.fk_diffs) {
          if(fk_diff.action == DiffAction::DROPPED ||
             fk_diff.action == DiffAction::MODIFIED) {
            if(fk_diff.before)
              script << generate_drop_foreign_key(td.table_name, *fk_diff.before);
          }
        }

        // Drop indexes that are being removed or modified
        for(const auto &idx_diff : td.index_diffs) {
          if(idx_diff.action == DiffAction::DROPPED ||
             idx_diff.action == DiffAction::MODIFIED) {
            if(idx_diff.before)
              script << generate_drop_index(td.table_name, *idx_diff.before);
          }
        }

        // Drop check constraints
        for(const auto &chk_diff : td.check_diffs) {
          if(chk_diff.action == DiffAction::DROPPED ||
             chk_diff.action == DiffAction::MODIFIED) {
            if(chk_diff.before)
              script << generate_drop_check(td.table_name, *chk_diff.before);
          }
        }

        // Handle primary key changes (drop first if modified)
        if(td.pk_diff) {
          if(td.pk_diff->action == DiffAction::DROPPED ||
             td.pk_diff->action == DiffAction::MODIFIED) {
            if(td.pk_diff->before)
              script << generate_drop_primary_key(td.table_name, *td.pk_diff->before);
          }
        }

        // Column changes
        for(const auto &col_diff : td.column_diffs) {
          switch(col_diff.action) {
            case DiffAction::DROPPED:
              script << generate_drop_column(td.table_name, col_diff.name);
              break;
            case DiffAction::ADDED:
              if(col_diff.after)
                script << generate_add_column(td.table_name, *col_diff.after);
              break;
            case DiffAction::MODIFIED:
              if(col_diff.before && col_diff.after)
                script << generate_modify_column(td.table_name, *col_diff.before, *col_diff.after);
              break;
          }
        }

        // Add primary key
        if(td.pk_diff) {
          if(td.pk_diff->action == DiffAction::ADDED ||
             td.pk_diff->action == DiffAction::MODIFIED) {
            if(td.pk_diff->after)
              script << generate_add_primary_key(td.table_name, *td.pk_diff->after);
          }
        }

        // Add check constraints
        for(const auto &chk_diff : td.check_diffs) {
          if(chk_diff.action == DiffAction::ADDED ||
             chk_diff.action == DiffAction::MODIFIED) {
            if(chk_diff.after)
              script << generate_add_check(td.table_name, *chk_diff.after);
          }
        }

        // Add indexes
        for(const auto &idx_diff : td.index_diffs) {
          if(idx_diff.action == DiffAction::ADDED ||
             idx_diff.action == DiffAction::MODIFIED) {
            if(idx_diff.after)
              script << generate_add_index(td.table_name, *idx_diff.after);
          }
        }

        // Add foreign keys last
        for(const auto &fk_diff : td.fk_diffs) {
          if(fk_diff.action == DiffAction::ADDED ||
             fk_diff.action == DiffAction::MODIFIED) {
            if(fk_diff.after)
              script << generate_add_foreign_key(td.table_name, *fk_diff.after);
          }
        }

        break;
      }
    }

    script << "\n";
  }

  script << "COMMIT;\n";

  return script.str();
}
