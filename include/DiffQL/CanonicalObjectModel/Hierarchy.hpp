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
    VARCHAR,
    TEXT,
    CHAR,
    DECIMAL,
    FLOAT,
    DOUBLE,
    DATE,
    DATETIME,
    TIMESTAMP,
    BOOLEAN,
    BLOB,
    JSON
  };

  BaseType           base;
  std::optional<int> length;
  std::optional<int> precision;
  std::optional<int> scale;
  std::string        raw_type; // Debug purposes
};

struct Column
{
  std::string                name;
  CanonicalType              type;
  bool                       nullable;
  std::optional<std::string> default_value;
  bool                       auto_increment;
  int                        position; // Table order

  std::string                source_dbms; // MariaDB, etc...
};

struct PrimaryKey
{
  std::vector<std::string>   column_names;
  std::optional<std::string> constraint_name;
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
