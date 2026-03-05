#include "DiffQL/Connectors/PostGreSQL/Connector.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
std::string trim(const std::string &s)
{
  size_t a = 0;
  size_t b = s.size();
  while(a < b && std::isspace(static_cast<unsigned char>(s[a])) != 0) ++a;
  while(b > a && std::isspace(static_cast<unsigned char>(s[b - 1])) != 0) --b;
  return s.substr(a, b - a);
}

std::string normalize_statement_lead(std::string s)
{
  while(true) {
    s = trim(s);
    if(s.empty()) return s;

    if(s[0] == '\\') {
      size_t nl = s.find('\n');
      if(nl == std::string::npos) return "";
      s = s.substr(nl + 1);
      continue;
    }

    if(s.size() >= 2 && s[0] == '-' && s[1] == '-') {
      size_t nl = s.find('\n');
      if(nl == std::string::npos) return "";
      s = s.substr(nl + 1);
      continue;
    }

    break;
  }

  return s;
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

bool starts_with_ci(const std::string &s, const std::string &prefix)
{
  if(prefix.size() > s.size()) return false;
  for(size_t i = 0; i < prefix.size(); ++i) {
    if(std::tolower(static_cast<unsigned char>(s[i])) !=
       std::tolower(static_cast<unsigned char>(prefix[i]))) return false;
  }
  return true;
}

size_t skip_spaces(const std::string &s, size_t pos)
{
  while(pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos])) != 0) ++pos;
  return pos;
}

bool is_ident_char(char c)
{
  return std::isalnum(static_cast<unsigned char>(c)) != 0 || c == '_' || c == '$';
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

std::optional<std::string> parse_identifier(const std::string &s, size_t &pos)
{
  pos = skip_spaces(s, pos);
  if(pos >= s.size()) return std::nullopt;

  if(s[pos] == '"') {
    ++pos;
    std::string out;
    while(pos < s.size()) {
      if(s[pos] == '"') {
        if(pos + 1 < s.size() && s[pos + 1] == '"') {
          out.push_back('"');
          pos += 2;
          continue;
        }
        ++pos;
        return out;
      }
      out.push_back(s[pos]);
      ++pos;
    }
    return std::nullopt;
  }

  size_t start = pos;
  while(pos < s.size() && is_ident_char(s[pos])) ++pos;
  if(start == pos) return std::nullopt;
  return s.substr(start, pos - start);
}

std::pair<std::string, std::string> parse_qualified_name(const std::string &s, size_t &pos)
{
  auto first = parse_identifier(s, pos);
  if(!first.has_value()) return {"public", ""};

  pos = skip_spaces(s, pos);
  if(pos < s.size() && s[pos] == '.') {
    ++pos;
    auto second = parse_identifier(s, pos);
    if(second.has_value()) return {*first, *second};
  }

  return {"public", *first};
}

std::pair<std::string, size_t> extract_paren(const std::string &s, size_t open_pos)
{
  if(open_pos >= s.size() || s[open_pos] != '(') return {"", std::string::npos};

  bool in_single = false;
  bool in_double = false;
  int depth = 0;

  for(size_t i = open_pos; i < s.size(); ++i) {
    const char c = s[i];
    if(in_single) {
      if(c == '\'' && i + 1 < s.size() && s[i + 1] == '\'') { ++i; continue; }
      if(c == '\'') in_single = false;
      continue;
    }
    if(in_double) {
      if(c == '"' && i + 1 < s.size() && s[i + 1] == '"') { ++i; continue; }
      if(c == '"') in_double = false;
      continue;
    }
    if(c == '\'') { in_single = true; continue; }
    if(c == '"') { in_double = true; continue; }
    if(c == '(') { ++depth; continue; }
    if(c == ')') {
      --depth;
      if(depth == 0) return {s.substr(open_pos + 1, i - open_pos - 1), i};
    }
  }

  return {"", std::string::npos};
}

std::vector<std::string> split_top_level_csv(const std::string &s)
{
  std::vector<std::string> out;
  bool in_single = false;
  bool in_double = false;
  int depth = 0;
  size_t start = 0;

  for(size_t i = 0; i < s.size(); ++i) {
    const char c = s[i];
    if(in_single) {
      if(c == '\'' && i + 1 < s.size() && s[i + 1] == '\'') { ++i; continue; }
      if(c == '\'') in_single = false;
      continue;
    }
    if(in_double) {
      if(c == '"' && i + 1 < s.size() && s[i + 1] == '"') { ++i; continue; }
      if(c == '"') in_double = false;
      continue;
    }
    if(c == '\'') { in_single = true; continue; }
    if(c == '"') { in_double = true; continue; }
    if(c == '(') { ++depth; continue; }
    if(c == ')') { if(depth > 0) --depth; continue; }
    if(c == ',' && depth == 0) {
      out.emplace_back(trim(s.substr(start, i - start)));
      start = i + 1;
    }
  }

  if(start < s.size()) out.emplace_back(trim(s.substr(start)));
  return out;
}

std::vector<std::string> split_sql_statements(const std::string &sql)
{
  std::vector<std::string> out;
  bool in_single = false;
  bool in_double = false;
  bool in_line = false;
  int block_depth = 0;
  std::string dollar;
  size_t start = 0;

  for(size_t i = 0; i < sql.size(); ++i) {
    if(in_line) {
      if(sql[i] == '\n') in_line = false;
      continue;
    }
    if(block_depth > 0) {
      if(i + 1 < sql.size() && sql[i] == '/' && sql[i + 1] == '*') { ++block_depth; ++i; continue; }
      if(i + 1 < sql.size() && sql[i] == '*' && sql[i + 1] == '/') { --block_depth; ++i; }
      continue;
    }
    if(!dollar.empty()) {
      if(i + dollar.size() <= sql.size() && sql.compare(i, dollar.size(), dollar) == 0) {
        i += dollar.size() - 1;
        dollar.clear();
      }
      continue;
    }
    if(in_single) {
      if(sql[i] == '\'' && i + 1 < sql.size() && sql[i + 1] == '\'') { ++i; continue; }
      if(sql[i] == '\'') in_single = false;
      continue;
    }
    if(in_double) {
      if(sql[i] == '"' && i + 1 < sql.size() && sql[i + 1] == '"') { ++i; continue; }
      if(sql[i] == '"') in_double = false;
      continue;
    }

    if(i + 1 < sql.size() && sql[i] == '-' && sql[i + 1] == '-') { in_line = true; ++i; continue; }
    if(i + 1 < sql.size() && sql[i] == '/' && sql[i + 1] == '*') { block_depth = 1; ++i; continue; }
    if(sql[i] == '\'') { in_single = true; continue; }
    if(sql[i] == '"') { in_double = true; continue; }

    if(sql[i] == '$') {
      size_t j = i + 1;
      while(j < sql.size() && is_ident_char(sql[j])) ++j;
      if(j < sql.size() && sql[j] == '$') {
        dollar = sql.substr(i, j - i + 1);
        i = j;
        continue;
      }
    }

    if(sql[i] == ';') {
      std::string stmt = trim(sql.substr(start, i - start));
      if(!stmt.empty()) out.emplace_back(std::move(stmt));
      start = i + 1;
    }
  }

  std::string tail = trim(sql.substr(start));
  if(!tail.empty()) out.emplace_back(std::move(tail));
  return out;
}

std::vector<std::string> parse_identifier_list(const std::string &inside)
{
  std::vector<std::string> out;
  for(const std::string &part : split_top_level_csv(inside)) {
    size_t p = 0;
    auto id = parse_identifier(part, p);
    if(id.has_value()) out.emplace_back(*id);
  }
  return out;
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

  if(t == "smallint" || t == "int2" || t == "smallserial") return {CanonicalType::SMALLINT, {}, {}, {}, raw};
  if(t == "bigint" || t == "int8" || t == "bigserial") return {CanonicalType::BIGINT, {}, {}, {}, raw};
  if(t == "integer" || t == "int" || t == "int4" || t == "serial") return {CanonicalType::INTEGER, {}, {}, {}, raw};
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

std::optional<Column> parse_column(const std::string &def, int position)
{
  size_t pos = 0;
  auto name = parse_identifier(def, pos);
  if(!name.has_value()) return std::nullopt;

  std::string rest = trim(def.substr(pos));
  if(rest.empty()) return std::nullopt;

  std::string lr = " " + lower(rest);
  size_t boundary = std::string::npos;
  for(const std::string &m : std::vector<std::string>{
          " default ", " not null", " null", " constraint", " primary key", " references", " unique", " check", " generated", " collate"}) {
    size_t i = lr.find(m);
    if(i != std::string::npos) {
      size_t actual = i == 0 ? 0 : i - 1;
      boundary = boundary == std::string::npos ? actual : std::min(boundary, actual);
    }
  }

  std::string raw_type = boundary == std::string::npos ? trim(rest) : trim(rest.substr(0, boundary));
  std::string attrs = boundary == std::string::npos ? "" : rest.substr(boundary);
  std::string la = lower(attrs);

  bool nullable = la.find("not null") == std::string::npos && la.find("primary key") == std::string::npos;
  std::optional<std::string> default_value;
  size_t d = la.find("default");
  if(d != std::string::npos) {
    size_t s = skip_spaces(attrs, d + 7);
    size_t e = attrs.size();
    for(const std::string &stop : std::vector<std::string>{
            " not null", " null", " constraint", " primary key", " references", " unique", " check", " generated", " collate"}) {
      size_t rel = lower(attrs.substr(s)).find(stop);
      if(rel != std::string::npos) e = std::min(e, s + rel);
    }
    std::string v = trim(attrs.substr(s, e - s));
    if(!v.empty()) default_value = v;
  }

  bool auto_increment = lower(raw_type).find("serial") != std::string::npos ||
                        (default_value.has_value() && lower(*default_value).find("nextval(") != std::string::npos);

  return Column{
      .name = *name,
      .type = map_type(raw_type),
      .nullable = nullable,
      .default_value = default_value,
      .auto_increment = auto_increment,
      .position = position,
      .source_dbms = "postgresql"};
}

void apply_primary_key(Table &t, const std::vector<std::string> &cols, const std::optional<std::string> &name)
{
  if(cols.empty()) return;
  t.primary_key = PrimaryKey{.column_names = cols, .constraint_name = name};
  for(const std::string &pk : cols) {
    for(Column &c : t.columns) {
      if(lower(c.name) == lower(pk)) c.nullable = false;
    }
  }
}

void apply_unique(Table &t, const std::vector<std::string> &cols, const std::optional<std::string> &name)
{
  if(cols.empty()) return;
  t.indexes.emplace_back(Index{
      .name = name.value_or(t.name + "_unique_" + std::to_string(t.indexes.size() + 1)),
      .column_names = cols,
      .unique = true,
      .type = "BTREE"});
}

std::pair<std::optional<std::string>, std::string> unwrap_constraint(const std::string &s)
{
  std::string t = trim(s);
  if(!starts_with_ci(t, "CONSTRAINT")) return {std::nullopt, t};

  size_t p = std::string("CONSTRAINT").size();
  auto name = parse_identifier(t, p);
  if(!name.has_value()) return {std::nullopt, t};
  return {*name, trim(t.substr(p))};
}

void apply_constraint(Table &t, const std::string &raw_clause, const std::optional<std::string> &name)
{
  std::string c = trim(raw_clause);
  std::string lc = lower(c);

  if(starts_with_ci(lc, "primary key")) {
    size_t o = c.find('(');
    if(o == std::string::npos) return;
    auto [inside, close] = extract_paren(c, o);
    if(close == std::string::npos) return;
    apply_primary_key(t, parse_identifier_list(inside), name);
    return;
  }

  if(starts_with_ci(lc, "unique")) {
    size_t o = c.find('(');
    if(o == std::string::npos) return;
    auto [inside, close] = extract_paren(c, o);
    if(close == std::string::npos) return;
    apply_unique(t, parse_identifier_list(inside), name);
  }
}

std::optional<Table> parse_create_table(const std::string &stmt)
{
  size_t p = std::string("CREATE TABLE").size();
  std::string ls = lower(stmt);

  size_t ine = ls.find("if not exists", p);
  if(ine != std::string::npos && ine == skip_spaces(ls, p)) p = ine + 13;

  auto [schema, table_name] = parse_qualified_name(stmt, p);
  if(table_name.empty()) return std::nullopt;

  size_t open = stmt.find('(', p);
  if(open == std::string::npos) return std::nullopt;

  auto [body, close] = extract_paren(stmt, open);
  if(close == std::string::npos) return std::nullopt;

  Table t{.name = table_name, .schema = schema, .columns = {}, .primary_key = std::nullopt, .foreign_keys = {}, .indexes = {}, .checks = {}};

  int position = 1;
  for(const std::string &item : split_top_level_csv(body)) {
    if(item.empty()) continue;

    std::string li = lower(item);
    if(starts_with_ci(li, "constraint") || starts_with_ci(li, "primary key") || starts_with_ci(li, "unique")) {
      auto [cn, clause] = unwrap_constraint(item);
      apply_constraint(t, clause, cn);
      continue;
    }

    auto col = parse_column(item, position);
    if(!col.has_value()) continue;

    if(li.find("primary key") != std::string::npos) {
      apply_primary_key(t, {col->name}, std::nullopt);
      col->nullable = false;
    }

    t.columns.push_back(*col);
    ++position;
  }

  return t;
}

std::string table_key(const std::string &schema, const std::string &table)
{
  return lower(schema) + "." + lower(table);
}

void parse_alter_table(const std::string &stmt,
                       std::unordered_map<std::string, size_t> &index,
                       std::vector<Table> &tables)
{
  size_t p = std::string("ALTER TABLE").size();
  std::string ls = lower(stmt);

  size_t ie = ls.find("if exists", p);
  if(ie != std::string::npos && ie == skip_spaces(ls, p)) p = ie + 9;

  size_t only = ls.find("only", p);
  if(only != std::string::npos && only == skip_spaces(ls, p)) p = only + 4;

  auto [schema, table_name] = parse_qualified_name(stmt, p);
  if(table_name.empty()) return;

  auto it = index.find(table_key(schema, table_name));
  if(it == index.end()) return;

  size_t alter_column = ls.find("alter column", p);
  if(alter_column != std::string::npos) {
    size_t col_pos = alter_column + std::string("alter column").size();
    auto col_name = parse_identifier(stmt, col_pos);
    if(col_name.has_value()) {
      size_t set_default = ls.find("set default", col_pos);
      if(set_default != std::string::npos) {
        std::string value = trim(stmt.substr(set_default + std::string("set default").size()));
        for(Column &col : tables[it->second].columns) {
          if(lower(col.name) == lower(*col_name)) {
            col.default_value = value.empty() ? std::optional<std::string>{}
                                              : std::optional<std::string>{value};
            if(lower(value).find("nextval(") != std::string::npos) {
              col.auto_increment = true;
            }
          }
        }
      }
    }
  }

  size_t add = ls.find("add", p);
  if(add == std::string::npos) return;

  std::string rest = trim(stmt.substr(add + 3));
  auto [cn, clause] = unwrap_constraint(rest);
  apply_constraint(tables[it->second], clause, cn);
}

void parse_create_index(const std::string &stmt,
                        std::unordered_map<std::string, size_t> &index,
                        std::vector<Table> &tables)
{
  size_t p = std::string("CREATE").size();
  std::string ls = lower(stmt);
  bool unique = false;

  if(starts_with_ci(trim(stmt.substr(p)), "UNIQUE")) {
    size_t u = ls.find("unique", p);
    if(u != std::string::npos) { p = u + 6; unique = true; }
  }

  size_t iidx = ls.find("index", p);
  if(iidx == std::string::npos) return;
  p = skip_spaces(stmt, iidx + 5);

  if(starts_with_ci(trim(stmt.substr(p)), "CONCURRENTLY")) {
    size_t c = ls.find("concurrently", p);
    if(c != std::string::npos) p = c + 12;
  }

  p = skip_spaces(stmt, p);
  if(starts_with_ci(trim(stmt.substr(p)), "IF NOT EXISTS")) {
    size_t ine = ls.find("if not exists", p);
    if(ine != std::string::npos) p = ine + 13;
  }

  auto index_name = parse_identifier(stmt, p);
  if(!index_name.has_value()) return;

  size_t on = ls.find("on", p);
  if(on == std::string::npos) return;
  p = skip_spaces(stmt, on + 2);

  if(starts_with_ci(trim(stmt.substr(p)), "ONLY")) {
    size_t only = ls.find("only", p);
    if(only != std::string::npos) p = only + 4;
  }

  auto [schema, table_name] = parse_qualified_name(stmt, p);
  if(table_name.empty()) return;

  auto it = index.find(table_key(schema, table_name));
  if(it == index.end()) return;

  std::string idx_type = "BTREE";
  size_t using_pos = ls.find("using", p);
  size_t open = stmt.find('(', p);
  if(using_pos != std::string::npos && (open == std::string::npos || using_pos < open)) {
    size_t mp = using_pos + 5;
    auto method = parse_identifier(stmt, mp);
    if(method.has_value()) idx_type = upper(*method);
  }

  if(open == std::string::npos) return;
  auto [inside, close] = extract_paren(stmt, open);
  if(close == std::string::npos) return;

  tables[it->second].indexes.emplace_back(Index{
      .name = *index_name,
      .column_names = parse_identifier_list(inside),
      .unique = unique,
      .type = idx_type});
}
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
      std::chrono::system_clock::now().time_since_epoch()).count();

  std::filesystem::path path = std::filesystem::temp_directory_path() /
                               ("diffql_pg_" + std::to_string(now_ms) + ".sql");

  std::string host = m_conn_object.host.empty() ? "localhost" : m_conn_object.host;
  std::string port = m_conn_object.port.empty() ? "5432" : m_conn_object.port;

  const char *env_pg_dump = std::getenv("DIFFQL_PG_DUMP_BIN");
  std::string pg_dump_bin = (env_pg_dump == nullptr || std::string(env_pg_dump).empty())
                                ? "pg_dump"
                                : std::string(env_pg_dump);

  std::string cmd;
  if(!m_conn_object.passwd.empty()) cmd += "PGPASSWORD=" + shell_quote(m_conn_object.passwd) + " ";
  cmd += shell_quote(pg_dump_bin) + " --schema-only --no-owner --no-privileges --no-comments";
  cmd += " -h " + shell_quote(host);
  cmd += " -p " + shell_quote(port);
  cmd += " -U " + shell_quote(m_conn_object.user);
  cmd += " -f " + shell_quote(path.string());
  cmd += " " + shell_quote(m_conn_object.db);

  if(std::system(cmd.c_str()) != 0) throw std::runtime_error("pg_dump failed");

  std::ifstream file(path);
  if(!file.is_open()) throw std::runtime_error("unable to open PostgreSQL dump file");
  return file;
}

std::vector<Table> PostgreSQLConnector::parse(std::istream &input) const
{
  std::string sql((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  std::vector<std::string> statements = split_sql_statements(sql);

  std::vector<Table> tables;
  std::unordered_map<std::string, size_t> index;

  for(const std::string &raw : statements) {
    std::string s = normalize_statement_lead(raw);
    if(s.empty()) continue;

    if(starts_with_ci(s, "CREATE TABLE")) {
      auto t = parse_create_table(s);
      if(!t.has_value()) continue;

      std::string key = table_key(t->schema, t->name);
      auto it = index.find(key);
      if(it == index.end()) {
        index[key] = tables.size();
        tables.push_back(*t);
      } else {
        tables[it->second] = *t;
      }
      continue;
    }

    if(starts_with_ci(s, "ALTER TABLE")) {
      parse_alter_table(s, index, tables);
      continue;
    }

    if(starts_with_ci(s, "CREATE INDEX") || starts_with_ci(s, "CREATE UNIQUE INDEX")) {
      parse_create_index(s, index, tables);
    }
  }

  return tables;
}
