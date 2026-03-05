#pragma once
#include <optional>
#include <string>
#include <vector>

struct CanonicalType
{
  enum BaseType
  {
    INTEGER,
    BIGINT,
    SMALLINT,
    TINYINT,
    MEDIUMINT,
    VARCHAR,
    TEXT,
    MEDIUMTEXT,
    LONGTEXT,
    CHAR,
    DECIMAL,
    FLOAT,
    DOUBLE,
    DATE,
    DATETIME,
    TIMESTAMP,
    TIME,
    BOOLEAN,
    BLOB,
    JSON,
    ENUM
  };

  BaseType           base;
  std::optional<int> length;
  std::optional<int> precision;
  std::optional<int> scale;
};

struct Column
{
  std::string                name;
  CanonicalType              type;
  bool                       nullable;
  bool                       auto_increment;
  std::optional<std::string> default_value;

  std::string source_dbms; // MariaDB, etc...
};

struct PrimaryKey
{
  std::optional<std::string> constraint_name;
  std::vector<std::string>   column_names;
};

struct ForeignKey
{
  std::string              name;
  std::vector<std::string> column_names;
  std::string              referenced_table;
  std::vector<std::string> referenced_columns;
  std::string              on_delete;
  std::string              on_update;
};

struct Index
{
  std::string              name;
  std::vector<std::string> column_names;
  bool                     unique;
  std::string              type; // BTREE, HASH....
};

struct CheckConstraint
{
  std::string name;
  std::string expression; // for instance, "age >= 18"
};

struct Table
{
  std::string                  name;
  std::string                  schema; // public, dbo, default if empty
  std::vector<Column>          columns;
  std::optional<PrimaryKey>    primary_key;
  std::vector<ForeignKey>      foreign_keys;
  std::vector<Index>           indexes;
  std::vector<CheckConstraint> checks;
};
