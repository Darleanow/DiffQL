#include "DiffQL/Connectors/MariaDB/Connector.hpp"
#include "DiffQL/DiffEngine/DiffEngine.hpp"
#include "DiffQL/MigrationGenerator/MariaDBMigrationGenerator.hpp"
#include "DiffQL/MigrationGenerator/PostgreSQLMigrationGenerator.hpp"
#include "DiffQL/Parser/DDLVisitor.hpp"
#include "DiffQL/UI/DiffViewer.hpp"
#include "MariaDBDDLLexer.h"
#include "MariaDBDDLParser.h"

#include <antlr4-runtime.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

static std::vector<Table> parse_sql_file(const std::string &path)
{
  std::ifstream file(path);
  if(!file.is_open()) {
    std::cerr << "Error: cannot open file: " << path << "\n";
    return {};
  }

  std::ostringstream ss;
  ss << file.rdbuf();
  std::string sql = ss.str();

  antlr4::ANTLRInputStream  input(sql);
  MariaDBDDLLexer           lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  MariaDBDDLParser          parser(&tokens);
  parser.removeErrorListeners();

  auto      *tree = parser.script();
  DDLVisitor visitor;
  visitor.visit(tree);

  return visitor.tables();
}

static const char *action_str(DiffAction a)
{
  switch(a) {
    case DiffAction::ADDED:    return "ADDED";
    case DiffAction::DROPPED:  return "DROPPED";
    case DiffAction::MODIFIED: return "MODIFIED";
  }
  return "?";
}

static const char *type_str(CanonicalType::BaseType t)
{
  switch(t) {
    case CanonicalType::INTEGER:    return "INT";
    case CanonicalType::BIGINT:     return "BIGINT";
    case CanonicalType::SMALLINT:   return "SMALLINT";
    case CanonicalType::TINYINT:    return "TINYINT";
    case CanonicalType::MEDIUMINT:  return "MEDIUMINT";
    case CanonicalType::VARCHAR:    return "VARCHAR";
    case CanonicalType::TEXT:       return "TEXT";
    case CanonicalType::MEDIUMTEXT: return "MEDIUMTEXT";
    case CanonicalType::LONGTEXT:   return "LONGTEXT";
    case CanonicalType::CHAR:       return "CHAR";
    case CanonicalType::DECIMAL:    return "DECIMAL";
    case CanonicalType::FLOAT:      return "FLOAT";
    case CanonicalType::DOUBLE:     return "DOUBLE";
    case CanonicalType::DATE:       return "DATE";
    case CanonicalType::DATETIME:   return "DATETIME";
    case CanonicalType::TIMESTAMP:  return "TIMESTAMP";
    case CanonicalType::TIME:       return "TIME";
    case CanonicalType::BOOLEAN:    return "BOOLEAN";
    case CanonicalType::BLOB:       return "BLOB";
    case CanonicalType::JSON:       return "JSON";
    case CanonicalType::ENUM:       return "ENUM";
  }
  return "?";
}

static std::string fmt_type(const CanonicalType &t)
{
  std::ostringstream os;
  os << type_str(t.base);
  if(t.length)    os << "(" << *t.length << ")";
  if(t.precision) os << "(" << *t.precision << (t.scale ? "," + std::to_string(*t.scale) : "") << ")";
  return os.str();
}

static void dump_column_detail(const ElementDiff<Column> &d)
{
  std::cout << "    Column [" << action_str(d.action) << "] " << d.name;

  if(d.action == DiffAction::MODIFIED && d.before && d.after) {
    const auto &b = *d.before;
    const auto &a = *d.after;
    std::string details;

    if(b.type != a.type)
      details += " type: " + fmt_type(b.type) + " -> " + fmt_type(a.type);
    if(b.nullable != a.nullable)
      details += std::string(" nullable: ") + (b.nullable ? "YES" : "NO") + " -> " + (a.nullable ? "YES" : "NO");
    if(b.auto_increment != a.auto_increment)
      details += std::string(" auto_increment: ") + (b.auto_increment ? "YES" : "NO") + " -> " + (a.auto_increment ? "YES" : "NO");
    if(b.default_value != a.default_value)
      details += " default: " + b.default_value.value_or("NULL") + " -> " + a.default_value.value_or("NULL");

    if(!details.empty())
      std::cout << " —" << details;
  }

  std::cout << "\n";
}

template <typename T>
static void dump_diffs(const char *label, const std::vector<ElementDiff<T>> &diffs)
{
  for(const auto &d : diffs)
    std::cout << "    " << label << " [" << action_str(d.action) << "] " << d.name << "\n";
}

static void dump_schema_diff(const SchemaDiff &diff)
{
  std::cout << "\n=== Schema Diff ===\n\n";

  for(const auto &td : diff.table_diffs) {
    std::cout << "[" << action_str(td.action) << "] Table: " << td.table_name << "\n";

    if(td.action == DiffAction::MODIFIED) {
      for(const auto &cd : td.column_diffs) dump_column_detail(cd);
      dump_diffs("ForeignKey", td.fk_diffs);
      dump_diffs("Index",      td.index_diffs);
      dump_diffs("Check",      td.check_diffs);

      if(td.pk_diff)
        std::cout << "    PrimaryKey [" << action_str(td.pk_diff->action) << "] "
                  << td.pk_diff->name << "\n";
    }

    std::cout << "\n";
  }

  std::cout << "Total: " << diff.table_diffs.size() << " table diff(s)\n";
}

// ─── TUI mode ────────────────────────────────────────────────────────────────

static int run_tui(const char *origin_path, const char *dest_path)
{
  DiffQL::UI::run_tui_mode(origin_path, dest_path, parse_sql_file);
  return 0;
}

// ─── Default DB mode ─────────────────────────────────────────────────────────

static int run_db_mode()
{
  MariaDBConn connect_origin {
      .host   = "localhost",
      .user   = "root",
      .passwd = "toor",
      .db     = "nation"
  };
  MariaDBConnector connector_origin(connect_origin);
  auto             schema_origin = connector_origin.get_schema();

  MariaDBConn connect_dest {
      .host   = "localhost",
      .user   = "root",
      .passwd = "toor",
      .db     = "nation2",
      .port   = std::optional<int>(3307)
  };
  MariaDBConnector connector_dest(connect_dest);
  auto             schema_dest = connector_dest.get_schema();

  DiffEngine  engine(schema_origin, schema_dest);
  const auto &diff = engine.compare_schemas();

  dump_schema_diff(diff);

  // Generate migration scripts
  std::cout << "\n Generate Migration Script\n";
  std::cout << "Select target database:\n";
  std::cout << "  1. MariaDB\n";
  std::cout << "  2. PostgreSQL\n";
  std::cout << "Choice [1/2]: ";

  std::string choice;
  std::getline(std::cin, choice);

  std::unique_ptr<MigrationGenerator> generator;
  std::string                         output_file;

  if(choice == "2") {
    generator   = std::make_unique<PostgreSQLMigrationGenerator>();
    output_file = "migration_postgresql.sql";
  } else {
    generator   = std::make_unique<MariaDBMigrationGenerator>();
    output_file = "migration_mariadb.sql";
  }

  std::string script = generator->generate(diff, schema_origin, schema_dest);

  std::cout << "\n" << script;

  std::ofstream out(output_file);
  if(out) {
    out << script;
    std::cout << "\nMigration script saved to: " << output_file << "\n";
  } else {
    std::cerr << "\nFailed to save migration script to file.\n";
  }

  return 0;
}

// ─── Entry point ─────────────────────────────────────────────────────────────

static void print_usage(const char *prog)
{
  std::cerr << "Usage:\n"
            << "  " << prog << "                              # DB diff (default)\n"
            << "  " << prog << " --tui <origin.sql> <dest.sql>  # TUI diff viewer\n";
}

int main(int argc, char **argv)
{
  if(argc == 4 && std::string(argv[1]) == "--tui")
    return run_tui(argv[2], argv[3]);

  if(argc > 1) {
    print_usage(argv[0]);
    return 1;
  }

  return run_db_mode();
}
