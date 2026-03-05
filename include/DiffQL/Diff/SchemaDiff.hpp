#pragma once

#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include <string>
#include <vector>

struct DiffTableRef
{
  std::string schema;
  std::string table;
};

struct DiffColumnRef
{
  std::string schema;
  std::string table;
  std::string column;
};

struct DiffColumnRename
{
  std::string schema;
  std::string table;
  std::string old_name;
  std::string new_name;
  int         score;
};

struct DiffColumnTypeChange
{
  std::string schema;
  std::string table;
  std::string column;
  std::string old_type;
  std::string new_type;
  bool        potentially_lossy;
};

struct DiffCheckChange
{
  std::string schema;
  std::string table;
  std::string check_name;
  std::string old_expression;
  std::string new_expression;
};

struct DiffWarning
{
  std::string category;
  std::string message;
};

struct SchemaDiffResult
{
  std::vector<DiffTableRef>        added_tables;
  std::vector<DiffTableRef>        removed_tables;

  std::vector<DiffColumnRef>       added_columns;
  std::vector<DiffColumnRef>       removed_columns;
  std::vector<DiffColumnRename>    renamed_columns;
  std::vector<DiffColumnTypeChange> type_changes;

  std::vector<DiffCheckChange>     added_checks;
  std::vector<DiffCheckChange>     removed_checks;
  std::vector<DiffCheckChange>     modified_checks;

  std::vector<DiffWarning>         warnings;
};

SchemaDiffResult diff_schemas(const std::vector<Table> &source,
                              const std::vector<Table> &target);

std::string      diff_report_markdown(const SchemaDiffResult &result);
