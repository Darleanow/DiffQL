#pragma once
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

enum class DiffAction
{
  ADDED,
  DROPPED,
  MODIFIED
};

template <typename T>
struct ElementDiff
{
  DiffAction       action;
  std::string      name;
  std::optional<T> before;
  std::optional<T> after;
};

struct TableDiff
{
  DiffAction                                action;
  std::string                               table_name;
  std::optional<std::string>                new_name;

  std::vector<ElementDiff<Column>>          column_diffs;
  std::optional<ElementDiff<PrimaryKey>>    pk_diff;
  std::vector<ElementDiff<ForeignKey>>      fk_diffs;
  std::vector<ElementDiff<Index>>           index_diffs;
  std::vector<ElementDiff<CheckConstraint>> check_diffs;
};

struct SchemaDiff
{
  std::vector<TableDiff> table_diffs;
};

// Called when two tables look like renames (orig_name, dest_name, similarity 0..1).
// Return true to treat as rename/modification, false to treat as drop+add.
using RenameCallback = std::function<bool(const std::string &, const std::string &, float)>;

class DiffEngine
{
public:
  DiffEngine(
      const std::vector<Table> &schema_origin,
      const std::vector<Table> &schema_dest
  );

  void set_rename_callback(RenameCallback cb);

  const SchemaDiff &compare_schemas();

protected:
  float jaro_winkler(const std::string &s1, const std::string &s2) const;

private:
  std::vector<Table> m_schema_origin;
  std::vector<Table> m_schema_dest;
  SchemaDiff         m_diff;
  RenameCallback     m_rename_callback;

  std::unordered_map<std::string, std::string> detect_table_renames(
      const std::vector<const Table *> &only_origin,
      const std::vector<const Table *> &only_dest,
      std::vector<std::pair<const Table *, const Table *>> &out_pairs);

  std::vector<ForeignKey> normalize_fk_references(
      const std::vector<ForeignKey> &fks,
      const std::unordered_map<std::string, std::string> &renames) const;

  std::vector<ElementDiff<ForeignKey>> diff_foreign_keys(
      const std::vector<ForeignKey> &origins,
      const std::vector<ForeignKey> &dests) const;

  std::unordered_map<std::string, std::string> detect_table_renames(
      const std::vector<const Table *> &only_origin,
      const std::vector<const Table *> &only_dest,
      std::vector<std::pair<const Table *, const Table *>> &out_pairs);

  std::vector<ForeignKey> normalize_fk_references(
      const std::vector<ForeignKey> &fks,
      const std::unordered_map<std::string, std::string> &renames) const;

  std::vector<ElementDiff<ForeignKey>> diff_foreign_keys(
      const std::vector<ForeignKey> &origins,
      const std::vector<ForeignKey> &dests) const;

  std::optional<TableDiff> compare_tables(
      const Table &origin,
      const Table &dest,
      const std::unordered_map<std::string, std::string> &renames = {}) const;

  template <typename T>
  std::vector<ElementDiff<T>> diff_elements(
      const std::vector<T> &origins,
      const std::vector<T> &dests) const;
};
