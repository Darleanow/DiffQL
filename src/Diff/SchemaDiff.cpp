#include "DiffQL/Diff/SchemaDiff.hpp"

#include <algorithm>
#include <cctype>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace {
std::string lower(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return s;
}

std::string table_key(const std::string &schema, const std::string &table)
{
  return lower(schema) + "." + lower(table);
}

std::string column_key(const std::string &column)
{
  return lower(column);
}

std::string check_key(const std::string &name)
{
  return lower(name);
}

std::string canonical_type_label(const CanonicalType &type)
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

bool same_canonical_type(const CanonicalType &a, const CanonicalType &b)
{
  return a.base == b.base && a.length == b.length &&
         a.precision == b.precision && a.scale == b.scale;
}

bool same_optional(
    const std::optional<std::string> &a, const std::optional<std::string> &b
)
{
  if(a.has_value() != b.has_value())
    return false;
  if(!a.has_value())
    return true;
  return *a == *b;
}

int rename_score(const Column &old_col, const Column &new_col)
{
  int score = 0;

  if(old_col.type.base == new_col.type.base)
    score += 4;
  if(old_col.nullable == new_col.nullable)
    score += 1;
  if(old_col.auto_increment == new_col.auto_increment)
    score += 1;
  if(same_optional(old_col.default_value, new_col.default_value))
    score += 1;

  if(same_canonical_type(old_col.type, new_col.type)) {
    score += 1;
  }

  return score;
}

bool potentially_lossy_type_change(const Column &old_col, const Column &new_col)
{
  const CanonicalType::BaseType old_type = old_col.type.base;
  const CanonicalType::BaseType new_type = new_col.type.base;

  if(old_type == new_type) {
    if((old_type == CanonicalType::VARCHAR || old_type == CanonicalType::CHAR
       ) &&
       old_col.type.length.has_value() && new_col.type.length.has_value() &&
       *new_col.type.length < *old_col.type.length) {
      return true;
    }

    if(old_type == CanonicalType::DECIMAL &&
       old_col.type.precision.has_value() &&
       new_col.type.precision.has_value() &&
       *new_col.type.precision < *old_col.type.precision) {
      return true;
    }

    if(old_type == CanonicalType::DECIMAL && old_col.type.scale.has_value() &&
       new_col.type.scale.has_value() &&
       *new_col.type.scale < *old_col.type.scale) {
      return true;
    }

    return false;
  }

  const std::unordered_set<CanonicalType::BaseType> numeric_types {
      CanonicalType::SMALLINT, CanonicalType::INTEGER, CanonicalType::BIGINT,
      CanonicalType::DECIMAL,  CanonicalType::FLOAT,   CanonicalType::DOUBLE
  };

  if(numeric_types.count(old_type) != 0 && numeric_types.count(new_type) != 0) {
    auto rank = [](CanonicalType::BaseType t) {
      switch(t) {
      case CanonicalType::SMALLINT:
        return 1;
      case CanonicalType::INTEGER:
        return 2;
      case CanonicalType::BIGINT:
        return 3;
      case CanonicalType::DECIMAL:
        return 4;
      case CanonicalType::FLOAT:
        return 5;
      case CanonicalType::DOUBLE:
        return 6;
      default:
        return 0;
      }
    };

    return rank(new_type) < rank(old_type);
  }

  return true;
}

} // namespace

SchemaDiffResult diff_schemas(
    const std::vector<Table> &source, const std::vector<Table> &target
)
{
  SchemaDiffResult                               result;

  std::unordered_map<std::string, const Table *> source_tables;
  std::unordered_map<std::string, const Table *> target_tables;

  for(const Table &t : source)
    source_tables[table_key(t.schema, t.name)] = &t;
  for(const Table &t : target)
    target_tables[table_key(t.schema, t.name)] = &t;

  for(const auto &[key, table] : source_tables) {
    if(target_tables.find(key) == target_tables.end()) {
      result.removed_tables.push_back({table->schema, table->name});
      result.warnings.push_back(
          {"destructive", "DROP TABLE " + table->schema + "." + table->name}
      );
    }
  }

  for(const auto &[key, table] : target_tables) {
    if(source_tables.find(key) == source_tables.end()) {
      result.added_tables.push_back({table->schema, table->name});
    }
  }

  for(const auto &[key, old_table] : source_tables) {
    auto it_target = target_tables.find(key);
    if(it_target == target_tables.end())
      continue;

    const Table *new_table = it_target->second;

    std::unordered_map<std::string, const Column *> old_cols;
    std::unordered_map<std::string, const Column *> new_cols;

    for(const Column &c : old_table->columns)
      old_cols[column_key(c.name)] = &c;
    for(const Column &c : new_table->columns)
      new_cols[column_key(c.name)] = &c;

    std::vector<const Column *> removed;
    std::vector<const Column *> added;

    for(const auto &[ck, c] : old_cols) {
      auto it_new = new_cols.find(ck);
      if(it_new == new_cols.end()) {
        removed.push_back(c);
      } else {
        const Column *nc = it_new->second;
        if(!same_canonical_type(c->type, nc->type)) {
          bool              risky    = potentially_lossy_type_change(*c, *nc);
          const std::string old_type = canonical_type_label(c->type);
          const std::string new_type = canonical_type_label(nc->type);
          result.type_changes.push_back(
              {old_table->schema, old_table->name, c->name, old_type, new_type,
               risky}
          );

          if(risky) {
            result.warnings.push_back(
                {"type_change", "Potentially lossy ALTER TYPE on " +
                                    old_table->schema + "." + old_table->name +
                                    "." + c->name + " (" + old_type + " -> " +
                                    new_type + ")"}
            );
          }
        }
      }
    }

    for(const auto &[ck, c] : new_cols) {
      if(old_cols.find(ck) == old_cols.end()) {
        added.push_back(c);
      }
    }

    std::vector<bool> removed_used(removed.size(), false);
    std::vector<bool> added_used(added.size(), false);

    while(true) {
      int best_score = -1;
      int best_i     = -1;
      int best_j     = -1;

      for(size_t i = 0; i < removed.size(); ++i) {
        if(removed_used[i])
          continue;
        for(size_t j = 0; j < added.size(); ++j) {
          if(added_used[j])
            continue;
          int s = rename_score(*removed[i], *added[j]);
          if(s > best_score) {
            best_score = s;
            best_i     = static_cast<int>(i);
            best_j     = static_cast<int>(j);
          }
        }
      }

      if(best_score < 6 || best_i < 0 || best_j < 0)
        break;

      removed_used[static_cast<size_t>(best_i)] = true;
      added_used[static_cast<size_t>(best_j)]   = true;

      result.renamed_columns.push_back(
          {old_table->schema, old_table->name,
           removed[static_cast<size_t>(best_i)]->name,
           added[static_cast<size_t>(best_j)]->name, best_score}
      );
    }

    for(size_t i = 0; i < removed.size(); ++i) {
      if(removed_used[i])
        continue;
      result.removed_columns.push_back(
          {old_table->schema, old_table->name, removed[i]->name}
      );
      result.warnings.push_back(
          {"destructive", "DROP COLUMN " + old_table->schema + "." +
                              old_table->name + "." + removed[i]->name}
      );
    }

    for(size_t j = 0; j < added.size(); ++j) {
      if(added_used[j])
        continue;
      result.added_columns.push_back(
          {new_table->schema, new_table->name, added[j]->name}
      );
    }

    std::unordered_map<std::string, std::string> old_checks;
    std::unordered_map<std::string, std::string> new_checks;

    for(const CheckConstraint &c : old_table->checks)
      old_checks[check_key(c.name)] = c.expression;
    for(const CheckConstraint &c : new_table->checks)
      new_checks[check_key(c.name)] = c.expression;

    for(const CheckConstraint &c : old_table->checks) {
      std::string ck     = check_key(c.name);
      auto        it_new = new_checks.find(ck);
      if(it_new == new_checks.end()) {
        result.removed_checks.push_back(
            {old_table->schema, old_table->name, c.name, c.expression, ""}
        );
      } else if(it_new->second != c.expression) {
        result.modified_checks.push_back(
            {old_table->schema, old_table->name, c.name, c.expression,
             it_new->second}
        );
      }
    }

    for(const CheckConstraint &c : new_table->checks) {
      std::string ck = check_key(c.name);
      if(old_checks.find(ck) == old_checks.end()) {
        result.added_checks.push_back(
            {new_table->schema, new_table->name, c.name, "", c.expression}
        );
      }
    }
  }

  return result;
}

std::string diff_report_markdown(const SchemaDiffResult &result)
{
  std::ostringstream out;

  out << "# Schema Diff Report\n\n";

  out << "## Table Changes\n";
  out << "- Added tables: " << result.added_tables.size() << "\n";
  for(const auto &t : result.added_tables)
    out << "  - + " << t.schema << "." << t.table << "\n";
  out << "- Removed tables: " << result.removed_tables.size() << "\n";
  for(const auto &t : result.removed_tables)
    out << "  - - " << t.schema << "." << t.table << "\n";
  out << "\n";

  out << "## Column Changes\n";
  out << "- Renamed columns: " << result.renamed_columns.size() << "\n";
  for(const auto &r : result.renamed_columns) {
    out << "  - ~ " << r.schema << "." << r.table << "." << r.old_name << " -> "
        << r.new_name << " (score=" << r.score << ")\n";
  }
  out << "- Added columns: " << result.added_columns.size() << "\n";
  for(const auto &c : result.added_columns)
    out << "  - + " << c.schema << "." << c.table << "." << c.column << "\n";
  out << "- Removed columns: " << result.removed_columns.size() << "\n";
  for(const auto &c : result.removed_columns)
    out << "  - - " << c.schema << "." << c.table << "." << c.column << "\n";
  out << "\n";

  out << "## Type Changes\n";
  out << "- Type changes: " << result.type_changes.size() << "\n";
  for(const auto &c : result.type_changes) {
    out << "  - * " << c.schema << "." << c.table << "." << c.column << " : "
        << c.old_type << " -> " << c.new_type;
    if(c.potentially_lossy)
      out << " [RISK]";
    out << "\n";
  }
  out << "\n";

  out << "## CHECK Changes\n";
  out << "- Added CHECK: " << result.added_checks.size() << "\n";
  for(const auto &c : result.added_checks) {
    out << "  - + " << c.schema << "." << c.table << "." << c.check_name
        << " => " << c.new_expression << "\n";
  }
  out << "- Removed CHECK: " << result.removed_checks.size() << "\n";
  for(const auto &c : result.removed_checks) {
    out << "  - - " << c.schema << "." << c.table << "." << c.check_name
        << " => " << c.old_expression << "\n";
  }
  out << "- Modified CHECK: " << result.modified_checks.size() << "\n";
  for(const auto &c : result.modified_checks) {
    out << "  - ~ " << c.schema << "." << c.table << "." << c.check_name
        << " => " << c.old_expression << " -> " << c.new_expression << "\n";
  }
  out << "\n";

  out << "## Warnings\n";
  out << "- Total warnings: " << result.warnings.size() << "\n";
  for(const auto &w : result.warnings) {
    out << "  - [" << w.category << "] " << w.message << "\n";
  }

  return out.str();
}
