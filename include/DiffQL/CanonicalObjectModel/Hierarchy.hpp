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

  bool operator==(const CanonicalType &o) const
  {
    return base == o.base && length == o.length
           && precision == o.precision && scale == o.scale;
  }
  bool operator!=(const CanonicalType &o) const { return !(*this == o); }
};

struct Column
{
  std::string                name;
  CanonicalType              type;
  bool                       nullable;
  bool                       auto_increment;
  std::optional<std::string> default_value;

  std::string source_dbms;

  bool operator==(const Column &o) const
  {
    return name == o.name && type == o.type && nullable == o.nullable
           && auto_increment == o.auto_increment
           && default_value == o.default_value;
  }
  bool operator!=(const Column &o) const { return !(*this == o); }
};

struct PrimaryKey
{
  std::optional<std::string> constraint_name;
  std::vector<std::string>   column_names;

  bool operator==(const PrimaryKey &o) const
  {
    return column_names == o.column_names;
  }
  bool operator!=(const PrimaryKey &o) const { return !(*this == o); }
};

struct ForeignKey
{
  std::string              name;
  std::vector<std::string> column_names;
  std::string              referenced_table;
  std::vector<std::string> referenced_columns;
  std::string              on_delete;
  std::string              on_update;

  bool operator==(const ForeignKey &o) const
  {
    return name == o.name && column_names == o.column_names
           && referenced_table == o.referenced_table
           && referenced_columns == o.referenced_columns
           && on_delete == o.on_delete && on_update == o.on_update;
  }
  bool operator!=(const ForeignKey &o) const { return !(*this == o); }
};

struct Index
{
  std::string              name;
  std::vector<std::string> column_names;
  bool                     unique;
  std::string              type;

  bool operator==(const Index &o) const
  {
    return name == o.name && column_names == o.column_names
           && unique == o.unique && type == o.type;
  }
  bool operator!=(const Index &o) const { return !(*this == o); }
};

struct CheckConstraint
{
  std::string name;
  std::string expression;

  bool operator==(const CheckConstraint &o) const
  {
    return name == o.name && expression == o.expression;
  }
  bool operator!=(const CheckConstraint &o) const { return !(*this == o); }
};

struct Table
{
  std::string                  name;
  std::string                  schema;
  std::vector<Column>          columns;
  std::optional<PrimaryKey>    primary_key;
  std::vector<ForeignKey>      foreign_keys;
  std::vector<Index>           indexes;
  std::vector<CheckConstraint> checks;
};
