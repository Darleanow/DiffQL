#pragma once

#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "MariaDBDDLParserBaseVisitor.h"
#include <vector>

class DDLVisitor : public MariaDBDDLParserBaseVisitor
{
public:
  std::vector<Table> &tables();

  std::any visitCreateTable(MariaDBDDLParser::CreateTableContext *ctx) override;
  std::any visitColumnDefinition(
      MariaDBDDLParser::ColumnDefinitionContext *ctx
  ) override;

  // Column modifiers
  std::any visitNotNull(MariaDBDDLParser::NotNullContext *ctx) override;
  std::any visitNullable(MariaDBDDLParser::NullableContext *ctx) override;
  std::any visitDefaultVal(MariaDBDDLParser::DefaultValContext *ctx) override;
  std::any
      visitAutoIncrement(MariaDBDDLParser::AutoIncrementContext *ctx) override;

  // Data types
  std::any visitIntDataType(MariaDBDDLParser::IntDataTypeContext *ctx) override;
  std::any visitDecimalDataType(
      MariaDBDDLParser::DecimalDataTypeContext *ctx
  ) override;
  std::any
      visitFloatDataType(MariaDBDDLParser::FloatDataTypeContext *ctx) override;
  std::any visitDoubleDataType(
      MariaDBDDLParser::DoubleDataTypeContext *ctx
  ) override;
  std::any visitVarcharDataType(
      MariaDBDDLParser::VarcharDataTypeContext *ctx
  ) override;
  std::any
      visitCharDataType(MariaDBDDLParser::CharDataTypeContext *ctx) override;
  std::any
      visitTextDataType(MariaDBDDLParser::TextDataTypeContext *ctx) override;
  std::any visitMediumTextDataType(
      MariaDBDDLParser::MediumTextDataTypeContext *ctx
  ) override;
  std::any visitLongTextDataType(
      MariaDBDDLParser::LongTextDataTypeContext *ctx
  ) override;
  std::any visitTinyTextDataType(
      MariaDBDDLParser::TinyTextDataTypeContext *ctx
  ) override;
  std::any
      visitBlobDataType(MariaDBDDLParser::BlobDataTypeContext *ctx) override;
  std::any
      visitDateDataType(MariaDBDDLParser::DateDataTypeContext *ctx) override;
  std::any visitDatetimeDataType(
      MariaDBDDLParser::DatetimeDataTypeContext *ctx
  ) override;
  std::any visitTimestampDataType(
      MariaDBDDLParser::TimestampDataTypeContext *ctx
  ) override;
  std::any
      visitTimeDataType(MariaDBDDLParser::TimeDataTypeContext *ctx) override;
  std::any visitBooleanDataType(
      MariaDBDDLParser::BooleanDataTypeContext *ctx
  ) override;
  std::any
      visitJsonDataType(MariaDBDDLParser::JsonDataTypeContext *ctx) override;
  std::any visitTinyintDataType(
      MariaDBDDLParser::TinyintDataTypeContext *ctx
  ) override;
  std::any
      visitEnumDataType(MariaDBDDLParser::EnumDataTypeContext *ctx) override;

  // Table constraints
  std::any visitPrimaryKeyConstraint(
      MariaDBDDLParser::PrimaryKeyConstraintContext *ctx
  ) override;
  std::any visitUniqueKeyConstraint(
      MariaDBDDLParser::UniqueKeyConstraintContext *ctx
  ) override;
  std::any visitIndexConstraint(
      MariaDBDDLParser::IndexConstraintContext *ctx
  ) override;
  std::any visitForeignKeyConstraint(
      MariaDBDDLParser::ForeignKeyConstraintContext *ctx
  ) override;
  std::any visitCheckConstraint(
      MariaDBDDLParser::CheckConstraintContext *ctx
  ) override;

private:
  std::vector<Table> m_tables;

  // Temp state during table parsing
  Table       m_current_table;
  Column      m_current_column;

  std::string extractIdentifier(MariaDBDDLParser::IdentifierContext *ctx);
  std::string extractIdentifier(MariaDBDDLParser::ColumnNameContext *ctx);
  std::string extractIdentifier(MariaDBDDLParser::TableNameContext *ctx);

  std::optional<int>
      extractDimension(MariaDBDDLParser::TypeDimensionContext *ctx);
};
