#include "DiffQL/MigrationGenerator/MariaDBMigrationGenerator.hpp"

#include <algorithm>
#include <sstream>
#include <unordered_map>

std::string MariaDBMigrationGenerator::database_name() const { return "MariaDB"; }
std::string MariaDBMigrationGenerator::identifier_quote() const { return "`"; }

std::string MariaDBMigrationGenerator::type_to_sql(const CanonicalType &type) const
{
  std::ostringstream os;

  switch(type.base) {
    case CanonicalType::INTEGER:    os << "INT"; break;
    case CanonicalType::BIGINT:     os << "BIGINT"; break;
    case CanonicalType::SMALLINT:   os << "SMALLINT"; break;
    case CanonicalType::TINYINT:    os << "TINYINT"; break;
    case CanonicalType::MEDIUMINT:  os << "MEDIUMINT"; break;
    case CanonicalType::VARCHAR:
      os << "VARCHAR";
      if(type.length) os << "(" << *type.length << ")";
      else os << "(255)";  // Default length
      break;
    case CanonicalType::TEXT:       os << "TEXT"; break;
    case CanonicalType::MEDIUMTEXT: os << "MEDIUMTEXT"; break;
    case CanonicalType::LONGTEXT:   os << "LONGTEXT"; break;
    case CanonicalType::CHAR:
      os << "CHAR";
      if(type.length) os << "(" << *type.length << ")";
      break;
    case CanonicalType::DECIMAL:
      os << "DECIMAL";
      if(type.precision) {
        os << "(" << *type.precision;
        if(type.scale) os << "," << *type.scale;
        os << ")";
      }
      break;
    case CanonicalType::FLOAT:      os << "FLOAT"; break;
    case CanonicalType::DOUBLE:     os << "DOUBLE"; break;
    case CanonicalType::DATE:       os << "DATE"; break;
    case CanonicalType::DATETIME:   os << "DATETIME"; break;
    case CanonicalType::TIMESTAMP:  os << "TIMESTAMP"; break;
    case CanonicalType::TIME:       os << "TIME"; break;
    case CanonicalType::BOOLEAN:    os << "TINYINT(1)"; break;
    case CanonicalType::BLOB:       os << "BLOB"; break;
    case CanonicalType::JSON:       os << "JSON"; break;
    case CanonicalType::ENUM:       os << "VARCHAR(255)"; break;  // Fallback for ENUM
  }

  return os.str();
}

std::string MariaDBMigrationGenerator::column_definition(const Column &col) const
{
  std::ostringstream os;

  os << quote_identifier(col.name) << " " << type_to_sql(col.type);

  if(!col.nullable)
    os << " NOT NULL";

  if(col.auto_increment)
    os << " AUTO_INCREMENT";

  if(col.default_value) {
    const auto &def = *col.default_value;
    // Check if it's a function call or keyword
    if(def == "CURRENT_TIMESTAMP" || def == "NULL" ||
       def.find('(') != std::string::npos)
      os << " DEFAULT " << def;
    else
      os << " DEFAULT '" << def << "'";
  }

  return os.str();
}

std::string MariaDBMigrationGenerator::generate_create_table(const Table &table) const
{
  std::ostringstream os;

  os << "CREATE TABLE " << quote_identifier(table.name) << " (\n";

  // Columns
  for(size_t i = 0; i < table.columns.size(); ++i) {
    os << "  " << column_definition(table.columns[i]);
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

    if(!fk.on_delete.empty() && fk.on_delete != "RESTRICT")
      os << " ON DELETE " << fk.on_delete;
    if(!fk.on_update.empty() && fk.on_update != "RESTRICT")
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

std::string MariaDBMigrationGenerator::generate_drop_table(const std::string &table_name) const
{
  return "DROP TABLE IF EXISTS " + quote_identifier(table_name) + ";\n";
}

std::string MariaDBMigrationGenerator::generate_add_column(
    const std::string &table_name,
    const Column      &column
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ADD COLUMN " << column_definition(column) << ";\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_drop_column(
    const std::string &table_name,
    const std::string &column_name
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " DROP COLUMN " << quote_identifier(column_name) << ";\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_modify_column(
    const std::string &table_name,
    const Column      &old_column,
    const Column      &new_column
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " MODIFY COLUMN " << column_definition(new_column) << ";\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_add_primary_key(
    const std::string &table_name,
    const PrimaryKey  &pk
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " ADD PRIMARY KEY (" << join_columns(pk.column_names) << ");\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_drop_primary_key(
    const std::string &table_name,
    const PrimaryKey  &pk
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " DROP PRIMARY KEY;\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_add_foreign_key(
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

  if(!fk.on_delete.empty() && fk.on_delete != "RESTRICT")
    os << " ON DELETE " << fk.on_delete;
  if(!fk.on_update.empty() && fk.on_update != "RESTRICT")
    os << " ON UPDATE " << fk.on_update;

  os << ";\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_drop_foreign_key(
    const std::string &table_name,
    const ForeignKey  &fk
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " DROP FOREIGN KEY " << quote_identifier(fk.name) << ";\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_add_index(
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

  if(!index.type.empty() && index.type != "BTREE")
    os << " USING " << index.type;

  os << ";\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_drop_index(
    const std::string &table_name,
    const Index       &index
) const
{
  std::ostringstream os;
  os << "DROP INDEX " << quote_identifier(index.name)
     << " ON " << quote_identifier(table_name) << ";\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate_add_check(
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

std::string MariaDBMigrationGenerator::generate_drop_check(
    const std::string    &table_name,
    const CheckConstraint &check
) const
{
  std::ostringstream os;
  os << "ALTER TABLE " << quote_identifier(table_name)
     << " DROP CONSTRAINT " << quote_identifier(check.name) << ";\n";
  return os.str();
}

std::string MariaDBMigrationGenerator::generate(
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

  script << "-- Migration script generated by DiffQL for MariaDB\n";
  script << "-- Generated at: " << __DATE__ << " " << __TIME__ << "\n";
  script << "-- ==================================================\n\n";

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

        // Detect special case: PK change with AUTO_INCREMENT column being added
        // In MariaDB, AUTO_INCREMENT column MUST be a key, so we need to combine
        // DROP PK + ADD AUTO_INCREMENT COLUMN + ADD PK in a single ALTER statement
        bool needs_combined_pk_change = false;
        const Column *auto_inc_column = nullptr;

        if(td.pk_diff &&
           (td.pk_diff->action == DiffAction::MODIFIED ||
            td.pk_diff->action == DiffAction::DROPPED)) {
          // Check if we're adding a new AUTO_INCREMENT column
          for(const auto &col_diff : td.column_diffs) {
            if(col_diff.action == DiffAction::ADDED && col_diff.after &&
               col_diff.after->auto_increment) {
              needs_combined_pk_change = true;
              auto_inc_column          = &(*col_diff.after);
              break;
            }
          }
        }

        if(needs_combined_pk_change && auto_inc_column && td.pk_diff->after) {
          // Generate combined ALTER TABLE statement for MariaDB
          script << "ALTER TABLE " << quote_identifier(td.table_name)
                 << " DROP PRIMARY KEY,\n"
                 << "  ADD COLUMN " << column_definition(*auto_inc_column) << " FIRST,\n"
                 << "  ADD PRIMARY KEY (" << join_columns(td.pk_diff->after->column_names) << ");\n";

          // Process remaining column changes (non-AUTO_INCREMENT adds)
          for(const auto &col_diff : td.column_diffs) {
            if(col_diff.action == DiffAction::DROPPED) {
              script << generate_drop_column(td.table_name, col_diff.name);
            } else if(col_diff.action == DiffAction::ADDED && col_diff.after) {
              // Skip the AUTO_INCREMENT column we already added
              if(!col_diff.after->auto_increment)
                script << generate_add_column(td.table_name, *col_diff.after);
            } else if(col_diff.action == DiffAction::MODIFIED &&
                      col_diff.before && col_diff.after) {
              script << generate_modify_column(td.table_name, *col_diff.before, *col_diff.after);
            }
          }
        } else {
          // Standard handling: separate statements

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

        // Rename table if name changed
        if(td.new_name) {
          script << "RENAME TABLE " << quote_identifier(td.table_name)
                 << " TO " << quote_identifier(*td.new_name) << ";\n";
        }

        break;
      }
    }

    script << "\n";
  }

  return script.str();
}
