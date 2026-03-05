#include "DiffQL/Connectors/PostGreSQL/Connector.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <sys/wait.h>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
constexpr char        FIELD_SEPARATOR = 0x1f;

constexpr const char *QUERY_TABLES = R"SQL(
SELECT n.nspname, c.relname
FROM pg_class c
JOIN pg_namespace n ON n.oid = c.relnamespace
WHERE c.relkind IN ('r','p')
  AND n.nspname NOT IN ('pg_catalog','information_schema')
ORDER BY n.nspname, c.relname;
)SQL";

constexpr const char *QUERY_COLUMNS = R"SQL(
SELECT n.nspname,
       c.relname,
       a.attnum::text,
       a.attname,
       pg_catalog.format_type(a.atttypid, a.atttypmod),
       CASE WHEN a.attnotnull THEN 'false' ELSE 'true' END,
       COALESCE(pg_get_expr(ad.adbin, ad.adrelid), '')
FROM pg_attribute a
JOIN pg_class c ON c.oid = a.attrelid
JOIN pg_namespace n ON n.oid = c.relnamespace
LEFT JOIN pg_attrdef ad ON ad.adrelid = a.attrelid AND ad.adnum = a.attnum
WHERE c.relkind IN ('r','p')
  AND a.attnum > 0
  AND NOT a.attisdropped
  AND n.nspname NOT IN ('pg_catalog','information_schema')
ORDER BY n.nspname, c.relname, a.attnum;
)SQL";

constexpr const char *QUERY_PRIMARY_KEYS = R"SQL(
SELECT n.nspname,
       c.relname,
       con.conname,
       a.attname,
       ord.idx::text
FROM pg_constraint con
JOIN pg_class c ON c.oid = con.conrelid
JOIN pg_namespace n ON n.oid = c.relnamespace
JOIN LATERAL unnest(con.conkey) WITH ORDINALITY AS ord(attnum, idx) ON true
JOIN pg_attribute a ON a.attrelid = con.conrelid AND a.attnum = ord.attnum
WHERE con.contype = 'p'
  AND n.nspname NOT IN ('pg_catalog','information_schema')
ORDER BY n.nspname, c.relname, ord.idx;
)SQL";

constexpr const char *QUERY_FOREIGN_KEYS = R"SQL(
SELECT n.nspname,
       c.relname,
       con.conname,
       fn.nspname,
       fc.relname,
       a.attname,
       af.attname,
       ord.idx::text,
       con.confdeltype::text,
       con.confupdtype::text
FROM pg_constraint con
JOIN pg_class c ON c.oid = con.conrelid
JOIN pg_namespace n ON n.oid = c.relnamespace
JOIN pg_class fc ON fc.oid = con.confrelid
JOIN pg_namespace fn ON fn.oid = fc.relnamespace
JOIN LATERAL unnest(con.conkey) WITH ORDINALITY AS ord(attnum, idx) ON true
JOIN pg_attribute a ON a.attrelid = con.conrelid AND a.attnum = ord.attnum
JOIN pg_attribute af ON af.attrelid = con.confrelid AND af.attnum = con.confkey[ord.idx]
WHERE con.contype = 'f'
  AND n.nspname NOT IN ('pg_catalog','information_schema')
ORDER BY n.nspname, c.relname, con.conname, ord.idx;
)SQL";

constexpr const char *QUERY_INDEXES = R"SQL(
SELECT n.nspname,
       c.relname,
       ic.relname,
       CASE WHEN ix.indisunique THEN 'true' ELSE 'false' END,
       am.amname,
       COALESCE(string_agg(a.attname, ',' ORDER BY k.ord), '')
FROM pg_index ix
JOIN pg_class c ON c.oid = ix.indrelid
JOIN pg_namespace n ON n.oid = c.relnamespace
JOIN pg_class ic ON ic.oid = ix.indexrelid
JOIN pg_am am ON am.oid = ic.relam
LEFT JOIN LATERAL unnest(ix.indkey) WITH ORDINALITY AS k(attnum, ord) ON k.attnum > 0
LEFT JOIN pg_attribute a ON a.attrelid = c.oid AND a.attnum = k.attnum
WHERE n.nspname NOT IN ('pg_catalog','information_schema')
  AND c.relkind IN ('r','p')
  AND NOT ix.indisprimary
GROUP BY n.nspname, c.relname, ic.relname, ix.indisunique, am.amname
ORDER BY n.nspname, c.relname, ic.relname;
)SQL";

constexpr const char *QUERY_CHECKS = R"SQL(
SELECT n.nspname,
       c.relname,
       con.conname,
       pg_get_constraintdef(con.oid)
FROM pg_constraint con
JOIN pg_class c ON c.oid = con.conrelid
JOIN pg_namespace n ON n.oid = c.relnamespace
WHERE con.contype = 'c'
  AND n.nspname NOT IN ('pg_catalog','information_schema')
ORDER BY n.nspname, c.relname, con.conname;
)SQL";

struct CatalogState
{
  std::vector<Table>                      tables;
  std::unordered_map<std::string, size_t> table_index;
};

struct TemporaryFile
{
  std::filesystem::path path;

  explicit TemporaryFile(std::filesystem::path file_path)
      : path(std::move(file_path))
  {
  }

  ~TemporaryFile()
  {
    if(path.empty()) {
      return;
    }
    std::error_code ec;
    std::filesystem::remove(path, ec);
  }

  TemporaryFile(const TemporaryFile &)            = delete;
  TemporaryFile &operator=(const TemporaryFile &) = delete;

  TemporaryFile(TemporaryFile &&other) noexcept : path(std::move(other.path))
  {
    other.path.clear();
  }

  TemporaryFile &operator=(TemporaryFile &&other) noexcept
  {
    if(this == &other) {
      return *this;
    }
    std::error_code ec;
    std::filesystem::remove(path, ec);
    path = std::move(other.path);
    other.path.clear();
    return *this;
  }
};

struct TempDbGuard
{
  PostgreSQLConn conn;
  std::string    dbname;
  bool           enabled = true;

  ~TempDbGuard();
};

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

std::string to_upper(std::string value)
{
  std::transform(
      value.begin(), value.end(), value.begin(),
      [](unsigned char c) { return static_cast<char>(std::toupper(c)); }
  );
  return value;
}

bool iequals(const std::string &a, const std::string &b)
{
  return to_lower(a) == to_lower(b);
}

std::vector<std::string> split(const std::string &value, char sep)
{
  std::vector<std::string> out;
  size_t                   start = 0;

  for(size_t i = 0; i < value.size(); ++i) {
    if(value[i] != sep) {
      continue;
    }
    out.emplace_back(value.substr(start, i - start));
    start = i + 1;
  }

  out.emplace_back(value.substr(start));
  return out;
}

bool starts_with_case_insensitive(
    const std::string &value, const std::string &prefix
)
{
  if(prefix.size() > value.size()) {
    return false;
  }

  for(size_t i = 0; i < prefix.size(); ++i) {
    if(std::tolower(static_cast<unsigned char>(value[i])) !=
       std::tolower(static_cast<unsigned char>(prefix[i]))) {
      return false;
    }
  }

  return true;
}

std::string sanitize_dump_sql(const std::string &dump_sql)
{
  std::string sanitized;

  for(const std::string &line : split(dump_sql, '\n')) {
    if(starts_with_case_insensitive(trim(line), "SET transaction_timeout")) {
      continue;
    }
    sanitized += line;
    sanitized.push_back('\n');
  }

  return sanitized;
}

std::string shell_quote(const std::string &value)
{
  std::string out;
  out.reserve(value.size() + 2);
  out.push_back('\'');

  for(char c : value) {
    if(c == '\'') {
      out += "'\\''";
    } else {
      out.push_back(c);
    }
  }

  out.push_back('\'');
  return out;
}

int normalize_status(int status)
{
  if(status == -1) {
    return -1;
  }
  if(WIFEXITED(status)) {
    return WEXITSTATUS(status);
  }
  if(WIFSIGNALED(status)) {
    return 128 + WTERMSIG(status);
  }
  return status;
}

std::string env_or_default(const char *name, const std::string &fallback)
{
  const char *value = std::getenv(name);
  if(value == nullptr || std::string(value).empty()) {
    return fallback;
  }
  return std::string(value);
}

std::string connection_env_prefix(const PostgreSQLConn &conn)
{
  if(conn.passwd.empty()) {
    return {};
  }
  return "PGPASSWORD=" + shell_quote(conn.passwd) + " ";
}

std::string connection_cli_options(const PostgreSQLConn &conn)
{
  const std::string host = conn.host.empty() ? "localhost" : conn.host;
  const std::string port = conn.port.empty() ? "5432" : conn.port;

  return " -h " + shell_quote(host) + " -p " + shell_quote(port) + " -U " +
         shell_quote(conn.user);
}

int run_status_command(const std::string &inner_command)
{
  const std::string command = "bash -lc " + shell_quote(inner_command);
  return normalize_status(std::system(command.c_str()));
}

std::pair<int, std::string> run_capture_command(const std::string &inner_command
)
{
  const std::string command = "bash -lc " + shell_quote(inner_command);
  FILE             *pipe    = popen(command.c_str(), "r");
  if(pipe == nullptr) {
    throw std::runtime_error("failed to run command");
  }

  std::string output;
  char        buffer[4096];
  while(fgets(buffer, static_cast<int>(sizeof(buffer)), pipe) != nullptr) {
    output += buffer;
  }

  const int status = normalize_status(pclose(pipe));
  return {status, output};
}

std::filesystem::path make_temp_sql_file(const std::string &prefix)
{
  const auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch()
  )
                          .count();

  return std::filesystem::temp_directory_path() /
         (prefix + std::to_string(now_ms) + ".sql");
}

std::string make_temp_database_name()
{
  const auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch()
  )
                          .count();

  return "diffql_tmp_" + std::to_string(now_ms);
}

std::optional<int> to_int(const std::string &value)
{
  try {
    return std::stoi(value);
  } catch(...) {
    return std::nullopt;
  }
}

std::string action_from_code(const std::string &code)
{
  if(code == "a") {
    return "NO ACTION";
  }
  if(code == "r") {
    return "RESTRICT";
  }
  if(code == "c") {
    return "CASCADE";
  }
  if(code == "n") {
    return "SET NULL";
  }
  if(code == "d") {
    return "SET DEFAULT";
  }
  return "NO ACTION";
}

CanonicalType map_type(const std::string &raw)
{
  const std::string normalized = to_lower(trim(raw));

  auto              parse_length = [&](int &value) -> bool {
    const size_t open = normalized.find('(');
    const size_t close =
        normalized.find(')', open == std::string::npos ? 0 : open + 1);
    if(open == std::string::npos || close == std::string::npos ||
       close <= open + 1) {
      return false;
    }

    const std::optional<int> parsed =
        to_int(trim(normalized.substr(open + 1, close - open - 1)));
    if(!parsed.has_value()) {
      return false;
    }

    value = *parsed;
    return true;
  };

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
    int length = 0;
    if(parse_length(length)) {
      return {CanonicalType::VARCHAR, length, {}, {}, raw};
    }
    return {CanonicalType::VARCHAR, {}, {}, {}, raw};
  }

  if(normalized.find("character") == 0 || normalized.find("char") == 0) {
    int length = 0;
    if(parse_length(length)) {
      return {CanonicalType::CHAR, length, {}, {}, raw};
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

std::string table_key(const std::string &schema, const std::string &table)
{
  return to_lower(schema) + "." + to_lower(table);
}

std::vector<std::vector<std::string>> query_rows(
    const PostgreSQLConn &conn, const std::string &db, const std::string &sql
)
{
  TemporaryFile query_file(make_temp_sql_file("diffql_query_"));

  {
    std::ofstream out(query_file.path);
    if(!out.is_open()) {
      throw std::runtime_error("unable to create query file");
    }
    out << sql;
  }

  const std::string psql_bin = env_or_default("DIFFQL_PSQL_BIN", "psql");
  const std::string command =
      connection_env_prefix(conn) + shell_quote(psql_bin) +
      " -X -A -t -F $'\\x1f'" + connection_cli_options(conn) + " -d " +
      shell_quote(db) + " -f " + shell_quote(query_file.path.string());

  const auto [status, output] = run_capture_command(command);
  if(status != 0) {
    throw std::runtime_error("psql query failed");
  }

  std::vector<std::vector<std::string>> rows;
  for(const std::string &raw_line : split(output, '\n')) {
    const std::string line = trim(raw_line);
    if(line.empty()) {
      continue;
    }
    rows.push_back(split(line, FIELD_SEPARATOR));
  }

  return rows;
}

class CatalogLoader
{
public:
  CatalogLoader(const PostgreSQLConn &conn, std::string db)
      : conn_(conn),
        db_(std::move(db))
  {
  }

  std::vector<Table> load()
  {
    load_tables();
    load_columns();
    load_primary_keys();
    load_foreign_keys();
    load_indexes();
    load_checks();
    return std::move(state_.tables);
  }

private:
  const PostgreSQLConn                 &conn_;
  std::string                           db_;
  CatalogState                          state_;

  std::vector<std::vector<std::string>> rows(const std::string &sql) const
  {
    return query_rows(conn_, db_, sql);
  }

  Table *find_table(const std::string &schema, const std::string &table)
  {
    const auto it = state_.table_index.find(table_key(schema, table));
    if(it == state_.table_index.end()) {
      return nullptr;
    }
    return &state_.tables[it->second];
  }

  void load_tables()
  {
    for(const auto &row : rows(QUERY_TABLES)) {
      if(row.size() < 2) {
        continue;
      }

      Table table {
          .name         = row[1],
          .schema       = row[0],
          .columns      = {},
          .primary_key  = std::nullopt,
          .foreign_keys = {},
          .indexes      = {},
          .checks       = {}
      };

      state_.table_index[table_key(table.schema, table.name)] =
          state_.tables.size();
      state_.tables.push_back(std::move(table));
    }
  }

  void load_columns()
  {
    for(const auto &row : rows(QUERY_COLUMNS)) {
      if(row.size() < 7) {
        continue;
      }

      Table *table = find_table(row[0], row[1]);
      if(table == nullptr) {
        continue;
      }

      const std::optional<int> position = to_int(row[2]);
      if(!position.has_value()) {
        continue;
      }

      std::optional<std::string> default_value;
      if(!row[6].empty()) {
        default_value = row[6];
      }

      const bool is_auto_increment =
          default_value.has_value() &&
          to_lower(*default_value).find("nextval(") != std::string::npos;

      table->columns.push_back(Column {
          .name           = row[3],
          .type           = map_type(row[4]),
          .nullable       = (row[5] == "true"),
          .default_value  = default_value,
          .auto_increment = is_auto_increment,
          .position       = *position,
          .source_dbms    = "postgresql"
      });
    }
  }

  void load_primary_keys()
  {
    for(const auto &row : rows(QUERY_PRIMARY_KEYS)) {
      if(row.size() < 5) {
        continue;
      }

      Table *table = find_table(row[0], row[1]);
      if(table == nullptr) {
        continue;
      }

      if(!table->primary_key.has_value()) {
        table->primary_key =
            PrimaryKey {.column_names = {}, .constraint_name = row[2]};
      }

      table->primary_key->column_names.push_back(row[3]);

      for(Column &column : table->columns) {
        if(iequals(column.name, row[3])) {
          column.nullable = false;
        }
      }
    }
  }

  void load_foreign_keys()
  {
    for(const auto &row : rows(QUERY_FOREIGN_KEYS)) {
      if(row.size() < 10) {
        continue;
      }

      Table *table = find_table(row[0], row[1]);
      if(table == nullptr) {
        continue;
      }

      size_t fk_index = table->foreign_keys.size();
      for(size_t i = 0; i < table->foreign_keys.size(); ++i) {
        if(table->foreign_keys[i].name == row[2]) {
          fk_index = i;
          break;
        }
      }

      if(fk_index == table->foreign_keys.size()) {
        const std::string referenced_table =
            row[3] == "public" ? row[4] : row[3] + "." + row[4];

        table->foreign_keys.push_back(ForeignKey {
            .name               = row[2],
            .column_names       = {},
            .referenced_table   = referenced_table,
            .referenced_columns = {},
            .on_delete          = action_from_code(row[8]),
            .on_update          = action_from_code(row[9])
        });

        fk_index = table->foreign_keys.size() - 1;
      }

      table->foreign_keys[fk_index].column_names.push_back(row[5]);
      table->foreign_keys[fk_index].referenced_columns.push_back(row[6]);
    }
  }

  void load_indexes()
  {
    for(const auto &row : rows(QUERY_INDEXES)) {
      if(row.size() < 6) {
        continue;
      }

      Table *table = find_table(row[0], row[1]);
      if(table == nullptr) {
        continue;
      }

      std::vector<std::string> columns;
      if(!row[5].empty()) {
        columns = split(row[5], ',');
      }

      table->indexes.push_back(Index {
          .name         = row[2],
          .column_names = columns,
          .unique       = (row[3] == "true"),
          .type         = to_upper(row[4])
      });
    }
  }

  void load_checks()
  {
    for(const auto &row : rows(QUERY_CHECKS)) {
      if(row.size() < 4) {
        continue;
      }

      Table *table = find_table(row[0], row[1]);
      if(table == nullptr) {
        continue;
      }

      table->checks.push_back(
          CheckConstraint {.name = row[2], .expression = row[3]}
      );
    }
  }
};

std::vector<Table>
    introspect_schema(const PostgreSQLConn &conn, const std::string &db)
{
  CatalogLoader loader(conn, db);
  return loader.load();
}

TempDbGuard::~TempDbGuard()
{
  if(!enabled) {
    return;
  }

  const std::string dropdb_bin = env_or_default("DIFFQL_DROPDB_BIN", "dropdb");
  const std::string command =
      connection_env_prefix(conn) + shell_quote(dropdb_bin) +
      connection_cli_options(conn) + " --if-exists " + shell_quote(dbname);

  run_status_command(command);
}

} // namespace

PostgreSQLConnector::PostgreSQLConnector(PostgreSQLConn conn_object)
    : m_conn_object(std::move(conn_object))
{
}

std::vector<Table> PostgreSQLConnector::get_schema()
{
  std::ifstream file = dump();
  return parse(file);
}

std::ifstream PostgreSQLConnector::dump() const
{
  const std::filesystem::path dump_path = make_temp_sql_file("diffql_pg_");

  const std::string           pg_dump_bin =
      env_or_default("DIFFQL_PG_DUMP_BIN", "pg_dump");
  const std::string command =
      connection_env_prefix(m_conn_object) + shell_quote(pg_dump_bin) +
      " --schema-only --no-owner --no-privileges --no-comments" +
      connection_cli_options(m_conn_object) + " -f " +
      shell_quote(dump_path.string()) + " " + shell_quote(m_conn_object.db);

  if(run_status_command(command) != 0) {
    throw std::runtime_error("pg_dump failed");
  }

  std::ifstream file(dump_path);
  if(!file.is_open()) {
    throw std::runtime_error("unable to open PostgreSQL dump file");
  }

  std::error_code ec;
  std::filesystem::remove(dump_path, ec);

  return file;
}

std::vector<Table> PostgreSQLConnector::parse(std::istream &input) const
{
  std::string dump_sql(
      (std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>()
  );

  if(dump_sql.empty()) {
    return {};
  }

  const std::string sanitized_dump = sanitize_dump_sql(dump_sql);

  TemporaryFile     restore_file(make_temp_sql_file("diffql_restore_"));
  {
    std::ofstream out(restore_file.path);
    if(!out.is_open()) {
      throw std::runtime_error("unable to create restore file");
    }
    out << sanitized_dump;
  }

  const std::string temp_db = make_temp_database_name();
  TempDbGuard       guard {m_conn_object, temp_db, true};

  const std::string createdb_bin =
      env_or_default("DIFFQL_CREATEDB_BIN", "createdb");
  const std::string create_db_command =
      connection_env_prefix(m_conn_object) + shell_quote(createdb_bin) +
      connection_cli_options(m_conn_object) + " " + shell_quote(temp_db);

  if(run_status_command(create_db_command) != 0) {
    throw std::runtime_error("createdb failed");
  }

  const std::string psql_bin = env_or_default("DIFFQL_PSQL_BIN", "psql");
  const std::string restore_command =
      connection_env_prefix(m_conn_object) + shell_quote(psql_bin) +
      " -X -q -v ON_ERROR_STOP=1" + connection_cli_options(m_conn_object) +
      " -d " + shell_quote(temp_db) + " -f " +
      shell_quote(restore_file.path.string()) + " >/dev/null";

  if(run_status_command(restore_command) != 0) {
    throw std::runtime_error("restore dump failed");
  }

  return introspect_schema(m_conn_object, temp_db);
}
