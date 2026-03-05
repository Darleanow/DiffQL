#include "DiffQL/Parser/DDLVisitor.hpp"

std::vector<Table> &DDLVisitor::tables()
{
  return m_tables;
}

std::string
    DDLVisitor::extractIdentifier(MariaDBDDLParser::IdentifierContext *ctx)
{
  if(ctx->BACKTICK_ID()) {
    // Strip surrounding backticks
    auto text = ctx->BACKTICK_ID()->getText();
    return text.substr(1, text.size() - 2);
  }

  if(ctx->ID()) {
    return ctx->ID()->getText();
  }

  // nonReservedKeyword
  return ctx->getText();
}

std::string
    DDLVisitor::extractIdentifier(MariaDBDDLParser::ColumnNameContext *ctx)
{
  return extractIdentifier(ctx->identifier());
}

std::string
    DDLVisitor::extractIdentifier(MariaDBDDLParser::TableNameContext *ctx)
{
  auto ids = ctx->identifier();
  if(ids.size() == 2) {
    return extractIdentifier(ids[0]) + "." + extractIdentifier(ids[1]);
  }
  return extractIdentifier(ids[0]);
}

std::optional<int>
    DDLVisitor::extractDimension(MariaDBDDLParser::TypeDimensionContext *ctx)
{
  if(!ctx) {
    return std::nullopt;
  }
  return std::stoi(ctx->NUMERIC_LITERAL()->getText());
}

std::any DDLVisitor::visitCreateTable(MariaDBDDLParser::CreateTableContext *ctx)
{
  m_current_table = Table();

  auto table_name = ctx->tableName();
  auto ids        = table_name->identifier();

  if(ids.size() == 2) {
    m_current_table.schema = extractIdentifier(ids[0]);
    m_current_table.name   = extractIdentifier(ids[1]);
  } else {
    m_current_table.name = extractIdentifier(ids[0]);
  }

  // Visit all table elements (columns + constraints)
  for(auto *elem : ctx->tableElement()) {
    visit(elem);
  }

  m_tables.push_back(m_current_table);
  return {};
}

std::any DDLVisitor::visitColumnDefinition(
    MariaDBDDLParser::ColumnDefinitionContext *ctx
)
{
  m_current_column = Column {
      .name           = extractIdentifier(ctx->columnName()),
      .type           = {},
      .nullable       = true, // default
      .auto_increment = false,
      .default_value  = std::nullopt,
      .source_dbms    = "MariaDB",
  };

  // Visit dataType
  visit(ctx->dataType());

  // Visit modifiers
  for(auto *mod : ctx->columnModifier()) {
    visit(mod);
  }

  m_current_table.columns.push_back(m_current_column);
  return {};
}

std::any DDLVisitor::visitNotNull(MariaDBDDLParser::NotNullContext * /*ctx*/)
{
  m_current_column.nullable = false;
  return {};
}

std::any DDLVisitor::visitNullable(MariaDBDDLParser::NullableContext * /*ctx*/)
{
  m_current_column.nullable = true;
  return {};
}

std::any DDLVisitor::visitDefaultVal(MariaDBDDLParser::DefaultValContext *ctx)
{
  auto *dval = ctx->defaultValue();
  if(dval->NULL_()) {
    m_current_column.default_value = "NULL";
  } else {
    m_current_column.default_value = dval->getText();
  }
  return {};
}

std::any DDLVisitor::visitAutoIncrement(
    MariaDBDDLParser::AutoIncrementContext * /*ctx*/
)
{
  m_current_column.auto_increment = true;
  return {};
}

std::any DDLVisitor::visitIntDataType(MariaDBDDLParser::IntDataTypeContext *ctx)
{
  auto *int_kw = ctx->intType();
  if(int_kw->BIGINT()) {
    m_current_column.type.base = CanonicalType::BIGINT;
  } else if(int_kw->SMALLINT()) {
    m_current_column.type.base = CanonicalType::SMALLINT;
  } else if(int_kw->MEDIUMINT()) {
    m_current_column.type.base = CanonicalType::MEDIUMINT;
  } else {
    m_current_column.type.base = CanonicalType::INTEGER;
  }

  m_current_column.type.length = extractDimension(ctx->typeDimension());
  return {};
}

std::any DDLVisitor::visitDecimalDataType(
    MariaDBDDLParser::DecimalDataTypeContext *ctx
)
{
  m_current_column.type.base = CanonicalType::DECIMAL;
  if(ctx->typePrecision()) {
    auto nums                       = ctx->typePrecision()->NUMERIC_LITERAL();
    m_current_column.type.precision = std::stoi(nums[0]->getText());
    m_current_column.type.scale     = std::stoi(nums[1]->getText());
  }
  return {};
}

std::any
    DDLVisitor::visitFloatDataType(MariaDBDDLParser::FloatDataTypeContext *ctx)
{
  m_current_column.type.base   = CanonicalType::FLOAT;
  m_current_column.type.length = extractDimension(ctx->typeDimension());
  return {};
}

std::any DDLVisitor::visitDoubleDataType(
    MariaDBDDLParser::DoubleDataTypeContext *ctx
)
{
  m_current_column.type.base   = CanonicalType::DOUBLE;
  m_current_column.type.length = extractDimension(ctx->typeDimension());
  return {};
}

std::any DDLVisitor::visitVarcharDataType(
    MariaDBDDLParser::VarcharDataTypeContext *ctx
)
{
  m_current_column.type.base   = CanonicalType::VARCHAR;
  m_current_column.type.length = extractDimension(ctx->typeDimension());
  return {};
}

std::any
    DDLVisitor::visitCharDataType(MariaDBDDLParser::CharDataTypeContext *ctx)
{
  m_current_column.type.base   = CanonicalType::CHAR;
  m_current_column.type.length = extractDimension(ctx->typeDimension());
  return {};
}

std::any DDLVisitor::
    visitTextDataType(MariaDBDDLParser::TextDataTypeContext * /*ctx*/)
{
  m_current_column.type.base = CanonicalType::TEXT;
  return {};
}

std::any DDLVisitor::visitMediumTextDataType(
    MariaDBDDLParser::MediumTextDataTypeContext * /*ctx*/
)
{
  m_current_column.type.base = CanonicalType::MEDIUMTEXT;
  return {};
}

std::any DDLVisitor::visitLongTextDataType(
    MariaDBDDLParser::LongTextDataTypeContext * /*ctx*/
)
{
  m_current_column.type.base = CanonicalType::LONGTEXT;
  return {};
}

std::any DDLVisitor::visitTinyTextDataType(
    MariaDBDDLParser::TinyTextDataTypeContext * /*ctx*/
)
{
  m_current_column.type.base = CanonicalType::TINYTEXT;
  return {};
}

std::any DDLVisitor::
    visitBlobDataType(MariaDBDDLParser::BlobDataTypeContext * /*ctx*/)
{
  m_current_column.type.base = CanonicalType::BLOB;
  return {};
}

std::any DDLVisitor::
    visitDateDataType(MariaDBDDLParser::DateDataTypeContext * /*ctx*/)
{
  m_current_column.type.base = CanonicalType::DATE;
  return {};
}

std::any DDLVisitor::visitDatetimeDataType(
    MariaDBDDLParser::DatetimeDataTypeContext * /*ctx*/
)
{
  m_current_column.type.base = CanonicalType::DATETIME;
  return {};
}

std::any DDLVisitor::visitTimestampDataType(
    MariaDBDDLParser::TimestampDataTypeContext * /*ctx*/
)
{
  m_current_column.type.base = CanonicalType::TIMESTAMP;
  return {};
}

std::any DDLVisitor::
    visitTimeDataType(MariaDBDDLParser::TimeDataTypeContext * /*ctx*/)
{
  m_current_column.type.base = CanonicalType::TIME;
  return {};
}

std::any DDLVisitor::visitBooleanDataType(
    MariaDBDDLParser::BooleanDataTypeContext * /*ctx*/
)
{
  m_current_column.type.base = CanonicalType::BOOLEAN;
  return {};
}

std::any DDLVisitor::
    visitJsonDataType(MariaDBDDLParser::JsonDataTypeContext * /*ctx*/)
{
  m_current_column.type.base = CanonicalType::JSON;
  return {};
}

std::any DDLVisitor::visitTinyintDataType(
    MariaDBDDLParser::TinyintDataTypeContext *ctx
)
{
  m_current_column.type.base   = CanonicalType::TINYINT;
  m_current_column.type.length = extractDimension(ctx->typeDimension());
  return {};
}

std::any DDLVisitor::
    visitEnumDataType(MariaDBDDLParser::EnumDataTypeContext * /*ctx*/)
{
  m_current_column.type.base = CanonicalType::ENUM;
  return {};
}

std::any DDLVisitor::visitPrimaryKeyConstraint(
    MariaDBDDLParser::PrimaryKeyConstraintContext *ctx
)
{
  PrimaryKey pk;
  pk.constraint_name = "PRIMARY";

  if(ctx->indexName()) {
    pk.constraint_name = extractIdentifier(ctx->indexName()->identifier());
  }

  for(auto *col : ctx->indexColumnNames()->columnName()) {
    pk.column_names.push_back(extractIdentifier(col));
  }

  m_current_table.primary_key = pk;
  return {};
}

std::any DDLVisitor::visitUniqueKeyConstraint(
    MariaDBDDLParser::UniqueKeyConstraintContext *ctx
)
{
  Index idx;
  idx.unique = true;
  idx.type   = "BTREE";

  if(ctx->indexName()) {
    idx.name = extractIdentifier(ctx->indexName()->identifier());
  }

  for(auto *col : ctx->indexColumnNames()->columnName()) {
    idx.column_names.push_back(extractIdentifier(col));
  }

  m_current_table.indexes.push_back(idx);
  return {};
}

std::any DDLVisitor::visitIndexConstraint(
    MariaDBDDLParser::IndexConstraintContext *ctx
)
{
  Index idx;
  idx.unique = false;
  idx.type   = "BTREE";
  idx.name   = extractIdentifier(ctx->indexName()->identifier());

  for(auto *col : ctx->indexColumnNames()->columnName()) {
    idx.column_names.push_back(extractIdentifier(col));
  }

  m_current_table.indexes.push_back(idx);
  return {};
}

std::any DDLVisitor::visitForeignKeyConstraint(
    MariaDBDDLParser::ForeignKeyConstraintContext *ctx
)
{
  ForeignKey fk;

  // Constraint name
  if(ctx->constraintName()) {
    fk.name = extractIdentifier(ctx->constraintName()->identifier());
  }

  // FK columns
  auto fk_cols = ctx->indexColumnNames(0);
  for(auto *col : fk_cols->columnName()) {
    fk.column_names.push_back(extractIdentifier(col));
  }

  // Referenced table
  fk.referenced_table = extractIdentifier(ctx->tableName());

  // Referenced columns
  auto ref_cols = ctx->indexColumnNames(1);
  for(auto *col : ref_cols->columnName()) {
    fk.referenced_columns.push_back(extractIdentifier(col));
  }

  // Reference actions
  if(ctx->referenceActions()) {
    if(ctx->referenceActions()->onDelete()) {
      fk.on_delete =
          ctx->referenceActions()->onDelete()->referenceAction()->getText();
    }
    if(ctx->referenceActions()->onUpdate()) {
      fk.on_update =
          ctx->referenceActions()->onUpdate()->referenceAction()->getText();
    }
  }

  m_current_table.foreign_keys.push_back(fk);
  return {};
}

std::any DDLVisitor::visitCheckConstraint(
    MariaDBDDLParser::CheckConstraintContext *ctx
)
{
  CheckConstraint chk;

  if(ctx->constraintName()) {
    chk.name = extractIdentifier(ctx->constraintName()->identifier());
  }

  chk.expression = ctx->expression()->getText();

  m_current_table.checks.push_back(chk);
  return {};
}
