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
constexpr char FIELD_SEP = 0x1f;

std::string trim(const std::string &s)
{
  size_t a = 0;
  size_t b = s.size();
  while(a < b && std::isspace(static_cast<unsigned char>(s[a])) != 0) ++a;
  while(b > a && std::isspace(static_cast<unsigned char>(s[b - 1])) != 0) --b;
  return s.substr(a, b - a);
}

std::string lower(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return s;
}

std::string upper(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
    return static_cast<char>(std::toupper(c));
  });
  return s;
}

std::vector<std::string> split(const std::string &s, char sep)
{
  std::vector<std::string> out;
  size_t start = 0;
  for(size_t i = 0; i < s.size(); ++i) {
    if(s[i] == sep) {
      out.emplace_back(s.substr(start, i - start));
      start = i + 1;
    }
  }
  out.emplace_back(s.substr(start));
  return out;
}

bool starts_with_ci(const std::string &s, const std::string &prefix)
{
  if(prefix.size() > s.size()) return false;
  for(size_t i = 0; i < prefix.size(); ++i) {
    if(std::tolower(static_cast<unsigned char>(s[i])) !=
       std::tolower(static_cast<unsigned char>(prefix[i]))) return false;
  }
  return true;
}

std::string sanitize_dump_sql(const std::string &dump_sql)
{
  std::string out;
  for(const std::string &line : split(dump_sql, '\n')) {
    std::string l = trim(line);
    if(starts_with_ci(l, "SET transaction_timeout")) continue;
    out += line;
    out.push_back('\n');
  }
  return out;
}

std::string shell_quote(const std::string &s)
{
  std::string out;
  out.reserve(s.size() + 2);
  out.push_back('\'');
  for(char c : s) {
    if(c == '\'') out += "'\\''";
    else out.push_back(c);
  }
  out.push_back('\'');
  return out;
}

int normalize_status(int status)
{
  if(status == -1) return -1;
  if(WIFEXITED(status)) return WEXITSTATUS(status);
  if(WIFSIGNALED(status)) return 128 + WTERMSIG(status);
  return status;
}

std::string env_or_default(const char *name, const std::string &fallback)
{
  const char *value = std::getenv(name);
  if(value == nullptr || std::string(value).empty()) return fallback;
  return std::string(value);
}

std::string action_from_code(const std::string &code)
{
  if(code == "a") return "NO ACTION";
  if(code == "r") return "RESTRICT";
  if(code == "c") return "CASCADE";
  if(code == "n") return "SET NULL";
  if(code == "d") return "SET DEFAULT";
  return "NO ACTION";
}

std::string make_db_identifier()
{
  auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch())
                 .count();
  return "diffql_tmp_" + std::to_string(now);
}

std::filesystem::path make_tmp_file(const std::string &prefix)
{
  auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch())
                 .count();
  return std::filesystem::temp_directory_path() /
         (prefix + std::to_string(now) + ".sql");
}

std::string conn_prefix(const PostgreSQLConn &conn)
{
  std::string prefix;
  if(!conn.passwd.empty()) prefix += "PGPASSWORD=" + shell_quote(conn.passwd) + " ";
  return prefix;
}

std::string conn_opts(const PostgreSQLConn &conn)
{
  std::string host = conn.host.empty() ? "localhost" : conn.host;
  std::string port = conn.port.empty() ? "5432" : conn.port;
  return " -h " + shell_quote(host) + " -p " + shell_quote(port) +
         " -U " + shell_quote(conn.user);
}

int run_status_inner(const std::string &inner)
{
  std::string cmd = "bash -lc " + shell_quote(inner);
  return normalize_status(std::system(cmd.c_str()));
}

std::pair<int, std::string> run_capture_inner(const std::string &inner)
{
  std::string cmd = "bash -lc " + shell_quote(inner);
  FILE *pipe = popen(cmd.c_str(), "r");
  if(pipe == nullptr) throw std::runtime_error("failed to run command");

  std::string output;
  char        buf[4096];
  while(fgets(buf, static_cast<int>(sizeof(buf)), pipe) != nullptr) {
    output += buf;
  }

  int status = normalize_status(pclose(pipe));
  return {status, output};
}

std::vector<std::vector<std::string>> query_rows(const PostgreSQLConn &conn,
                                                 const std::string &db,
                                                 const std::string &sql)
{
  std::filesystem::path sql_file = make_tmp_file("diffql_query_");
  {
    std::ofstream out(sql_file);
    if(!out.is_open()) throw std::runtime_error("unable to create query file");
    out << sql;
  }

  std::string psql_bin = env_or_default("DIFFQL_PSQL_BIN", "psql");
  std::string inner = conn_prefix(conn) + shell_quote(psql_bin) +
                      " -X -A -t -F $'\\x1f'" +
                      conn_opts(conn) +
                      " -d " + shell_quote(db) +
                      " -f " + shell_quote(sql_file.string());

  auto [status, output] = run_capture_inner(inner);
  std::error_code ec;
  std::filesystem::remove(sql_file, ec);

  if(status != 0) throw std::runtime_error("psql query failed");

  std::vector<std::vector<std::string>> rows;
  for(const std::string &line_raw : split(output, '\n')) {
    std::string line = trim(line_raw);
    if(line.empty()) continue;
    rows.emplace_back(split(line, FIELD_SEP));
  }

  return rows;
}

CanonicalType map_type(const std::string &raw)
{
  std::string t = lower(trim(raw));
  auto one_number = [&](int &n) -> bool {
    size_t o = t.find('(');
    size_t c = t.find(')', o == std::string::npos ? 0 : o + 1);
    if(o == std::string::npos || c == std::string::npos || c <= o + 1) return false;
    try {
      n = std::stoi(trim(t.substr(o + 1, c - o - 1)));
      return true;
    } catch(...) {
      return false;
    }
  };

  if(t == "smallint" || t == "int2") return {CanonicalType::SMALLINT, {}, {}, {}, raw};
  if(t == "bigint" || t == "int8") return {CanonicalType::BIGINT, {}, {}, {}, raw};
  if(t == "integer" || t == "int" || t == "int4") return {CanonicalType::INTEGER, {}, {}, {}, raw};
  if(t.find("character varying") == 0 || t.find("varchar") == 0) {
    int n = 0;
    if(one_number(n)) return {CanonicalType::VARCHAR, n, {}, {}, raw};
    return {CanonicalType::VARCHAR, {}, {}, {}, raw};
  }
  if(t.find("character") == 0 || t.find("char") == 0) {
    int n = 0;
    if(one_number(n)) return {CanonicalType::CHAR, n, {}, {}, raw};
    return {CanonicalType::CHAR, {}, {}, {}, raw};
  }
  if(t == "text") return {CanonicalType::TEXT, {}, {}, {}, raw};
  if(t.find("numeric") == 0 || t.find("decimal") == 0) return {CanonicalType::DECIMAL, {}, {}, {}, raw};
  if(t == "real" || t == "float4") return {CanonicalType::FLOAT, {}, {}, {}, raw};
  if(t == "double precision" || t == "float8") return {CanonicalType::DOUBLE, {}, {}, {}, raw};
  if(t == "date") return {CanonicalType::DATE, {}, {}, {}, raw};
  if(t.find("timestamp") == 0 || t == "timestamptz") return {CanonicalType::TIMESTAMP, {}, {}, {}, raw};
  if(t == "boolean" || t == "bool") return {CanonicalType::BOOLEAN, {}, {}, {}, raw};
  if(t == "bytea") return {CanonicalType::BLOB, {}, {}, {}, raw};
  if(t == "json" || t == "jsonb") return {CanonicalType::JSON, {}, {}, {}, raw};
  return {CanonicalType::TEXT, {}, {}, {}, raw};
}

std::string table_key(const std::string &schema, const std::string &table)
{
  return lower(schema) + "." + lower(table);
}

std::vector<Table> introspect_schema(const PostgreSQLConn &conn, const std::string &db)
{
  std::vector<Table> tables;
  std::unordered_map<std::string, size_t> index;

  const std::string q_tables = R"SQL(
SELECT n.nspname, c.relname
FROM pg_class c
JOIN pg_namespace n ON n.oid = c.relnamespace
WHERE c.relkind IN ('r','p')
  AND n.nspname NOT IN ('pg_catalog','information_schema')
ORDER BY n.nspname, c.relname;
)SQL";

  for(const auto &row : query_rows(conn, db, q_tables)) {
    if(row.size() < 2) continue;
    Table t{.name = row[1], .schema = row[0], .columns = {}, .primary_key = std::nullopt, .foreign_keys = {}, .indexes = {}, .checks = {}};
    index[table_key(t.schema, t.name)] = tables.size();
    tables.push_back(std::move(t));
  }

  const std::string q_columns = R"SQL(
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

  for(const auto &row : query_rows(conn, db, q_columns)) {
    if(row.size() < 7) continue;
    auto it = index.find(table_key(row[0], row[1]));
    if(it == index.end()) continue;

    int position = 0;
    try {
      position = std::stoi(row[2]);
    } catch(...) {
      continue;
    }

    std::optional<std::string> def;
    if(!row[6].empty()) def = row[6];

    bool auto_inc = def.has_value() && lower(*def).find("nextval(") != std::string::npos;

    tables[it->second].columns.push_back(Column{
        .name = row[3],
        .type = map_type(row[4]),
        .nullable = (row[5] == "true"),
        .default_value = def,
        .auto_increment = auto_inc,
        .position = position,
        .source_dbms = "postgresql"});
  }

  const std::string q_pk = R"SQL(
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

  for(const auto &row : query_rows(conn, db, q_pk)) {
    if(row.size() < 5) continue;
    auto it = index.find(table_key(row[0], row[1]));
    if(it == index.end()) continue;

    Table &t = tables[it->second];
    if(!t.primary_key.has_value()) {
      t.primary_key = PrimaryKey{.column_names = {}, .constraint_name = row[2]};
    }
    t.primary_key->column_names.push_back(row[3]);

    for(Column &c : t.columns) {
      if(lower(c.name) == lower(row[3])) c.nullable = false;
    }
  }

  const std::string q_fk = R"SQL(
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

  for(const auto &row : query_rows(conn, db, q_fk)) {
    if(row.size() < 10) continue;
    auto it = index.find(table_key(row[0], row[1]));
    if(it == index.end()) continue;

    Table &t = tables[it->second];
    size_t fk_idx = t.foreign_keys.size();
    for(size_t i = 0; i < t.foreign_keys.size(); ++i) {
      if(t.foreign_keys[i].name == row[2]) {
        fk_idx = i;
        break;
      }
    }

    if(fk_idx == t.foreign_keys.size()) {
      std::string ref_table = row[3] == "public" ? row[4] : row[3] + "." + row[4];
      t.foreign_keys.push_back(ForeignKey{
          .name = row[2],
          .column_names = {},
          .referenced_table = ref_table,
          .referenced_columns = {},
          .on_delete = action_from_code(row[8]),
          .on_update = action_from_code(row[9])});
    }

    t.foreign_keys[fk_idx].column_names.push_back(row[5]);
    t.foreign_keys[fk_idx].referenced_columns.push_back(row[6]);
  }

  const std::string q_indexes = R"SQL(
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

  for(const auto &row : query_rows(conn, db, q_indexes)) {
    if(row.size() < 6) continue;
    auto it = index.find(table_key(row[0], row[1]));
    if(it == index.end()) continue;

    std::vector<std::string> cols;
    if(!row[5].empty()) cols = split(row[5], ',');

    tables[it->second].indexes.push_back(Index{
        .name = row[2],
        .column_names = cols,
        .unique = (row[3] == "true"),
        .type = upper(row[4])});
  }

  const std::string q_checks = R"SQL(
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

  for(const auto &row : query_rows(conn, db, q_checks)) {
    if(row.size() < 4) continue;
    auto it = index.find(table_key(row[0], row[1]));
    if(it == index.end()) continue;

    tables[it->second].checks.push_back(CheckConstraint{
        .name = row[2],
        .expression = row[3]});
  }

  return tables;
}

struct TempDbGuard
{
  PostgreSQLConn conn;
  std::string    dbname;
  bool           enabled = true;

  ~TempDbGuard()
  {
    if(!enabled) return;
    std::string dropdb_bin = env_or_default("DIFFQL_DROPDB_BIN", "dropdb");
    std::string inner = conn_prefix(conn) + shell_quote(dropdb_bin) +
                        conn_opts(conn) +
                        " --if-exists " + shell_quote(dbname);
    run_status_inner(inner);
  }
};

} 

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
  const auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();

  std::filesystem::path path =
      std::filesystem::temp_directory_path() /
      ("diffql_pg_" + std::to_string(now_ms) + ".sql");

  std::string pg_dump_bin = env_or_default("DIFFQL_PG_DUMP_BIN", "pg_dump");
  std::string inner = conn_prefix(m_conn_object) + shell_quote(pg_dump_bin) +
                      " --schema-only --no-owner --no-privileges --no-comments" +
                      conn_opts(m_conn_object) +
                      " -f " + shell_quote(path.string()) +
                      " " + shell_quote(m_conn_object.db);

  if(run_status_inner(inner) != 0) throw std::runtime_error("pg_dump failed");

  std::ifstream file(path);
  if(!file.is_open()) throw std::runtime_error("unable to open PostgreSQL dump file");
  return file;
}

std::vector<Table> PostgreSQLConnector::parse(std::istream &input) const
{
  std::string dump_sql((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  if(dump_sql.empty()) return {};
  dump_sql = sanitize_dump_sql(dump_sql);

  std::filesystem::path restore_file = make_tmp_file("diffql_restore_");
  {
    std::ofstream out(restore_file);
    if(!out.is_open()) throw std::runtime_error("unable to create restore file");
    out << dump_sql;
  }

  std::string tmp_db = make_db_identifier();
  TempDbGuard guard{m_conn_object, tmp_db, true};

  std::string createdb_bin = env_or_default("DIFFQL_CREATEDB_BIN", "createdb");
  std::string create_cmd = conn_prefix(m_conn_object) + shell_quote(createdb_bin) +
                           conn_opts(m_conn_object) +
                           " " + shell_quote(tmp_db);

  if(run_status_inner(create_cmd) != 0) {
    std::error_code ec;
    std::filesystem::remove(restore_file, ec);
    throw std::runtime_error("createdb failed");
  }

  std::string psql_bin = env_or_default("DIFFQL_PSQL_BIN", "psql");
  std::string restore_cmd = conn_prefix(m_conn_object) + shell_quote(psql_bin) +
                            " -X -q -v ON_ERROR_STOP=1" +
                            conn_opts(m_conn_object) +
                            " -d " + shell_quote(tmp_db) +
                            " -f " + shell_quote(restore_file.string()) +
                            " >/dev/null";

  if(run_status_inner(restore_cmd) != 0) {
    std::error_code ec;
    std::filesystem::remove(restore_file, ec);
    throw std::runtime_error("restore dump failed");
  }

  std::vector<Table> result = introspect_schema(m_conn_object, tmp_db);

  std::error_code ec;
  std::filesystem::remove(restore_file, ec);

  return result;
}
