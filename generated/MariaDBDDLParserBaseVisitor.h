
// Generated from MariaDBDDLParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "MariaDBDDLParserVisitor.h"


/**
 * This class provides an empty implementation of MariaDBDDLParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MariaDBDDLParserBaseVisitor : public MariaDBDDLParserVisitor {
public:

  virtual std::any visitScript(MariaDBDDLParser::ScriptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(MariaDBDDLParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateTable(MariaDBDDLParser::CreateTableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfNotExists(MariaDBDDLParser::IfNotExistsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTableElement(MariaDBDDLParser::TableElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitColumnDefinition(MariaDBDDLParser::ColumnDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotNull(MariaDBDDLParser::NotNullContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullable(MariaDBDDLParser::NullableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefaultVal(MariaDBDDLParser::DefaultValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAutoIncrement(MariaDBDDLParser::AutoIncrementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInlinePrimaryKey(MariaDBDDLParser::InlinePrimaryKeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInlineUnique(MariaDBDDLParser::InlineUniqueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCommentMod(MariaDBDDLParser::CommentModContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnsignedMod(MariaDBDDLParser::UnsignedModContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitZerofillMod(MariaDBDDLParser::ZerofillModContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollateMod(MariaDBDDLParser::CollateModContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCheckMod(MariaDBDDLParser::CheckModContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefaultValue(MariaDBDDLParser::DefaultValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntDataType(MariaDBDDLParser::IntDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecimalDataType(MariaDBDDLParser::DecimalDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatDataType(MariaDBDDLParser::FloatDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoubleDataType(MariaDBDDLParser::DoubleDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarcharDataType(MariaDBDDLParser::VarcharDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCharDataType(MariaDBDDLParser::CharDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTextDataType(MariaDBDDLParser::TextDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTinyTextDataType(MariaDBDDLParser::TinyTextDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMediumTextDataType(MariaDBDDLParser::MediumTextDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLongTextDataType(MariaDBDDLParser::LongTextDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlobDataType(MariaDBDDLParser::BlobDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTinyBlobDataType(MariaDBDDLParser::TinyBlobDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMediumBlobDataType(MariaDBDDLParser::MediumBlobDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLongBlobDataType(MariaDBDDLParser::LongBlobDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDateDataType(MariaDBDDLParser::DateDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDatetimeDataType(MariaDBDDLParser::DatetimeDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTimestampDataType(MariaDBDDLParser::TimestampDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTimeDataType(MariaDBDDLParser::TimeDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBooleanDataType(MariaDBDDLParser::BooleanDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJsonDataType(MariaDBDDLParser::JsonDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTinyintDataType(MariaDBDDLParser::TinyintDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumDataType(MariaDBDDLParser::EnumDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntType(MariaDBDDLParser::IntTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDimension(MariaDBDDLParser::TypeDimensionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypePrecision(MariaDBDDLParser::TypePrecisionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumValues(MariaDBDDLParser::EnumValuesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryKeyConstraint(MariaDBDDLParser::PrimaryKeyConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUniqueKeyConstraint(MariaDBDDLParser::UniqueKeyConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndexConstraint(MariaDBDDLParser::IndexConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForeignKeyConstraint(MariaDBDDLParser::ForeignKeyConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCheckConstraint(MariaDBDDLParser::CheckConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstraintName(MariaDBDDLParser::ConstraintNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndexName(MariaDBDDLParser::IndexNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndexColumnNames(MariaDBDDLParser::IndexColumnNamesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReferenceActions(MariaDBDDLParser::ReferenceActionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOnDelete(MariaDBDDLParser::OnDeleteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOnUpdate(MariaDBDDLParser::OnUpdateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReferenceAction(MariaDBDDLParser::ReferenceActionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTableOptions(MariaDBDDLParser::TableOptionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEngineOption(MariaDBDDLParser::EngineOptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCharsetOption(MariaDBDDLParser::CharsetOptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollateOption(MariaDBDDLParser::CollateOptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAutoIncrOption(MariaDBDDLParser::AutoIncrOptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCommentOption(MariaDBDDLParser::CommentOptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDropTable(MariaDBDDLParser::DropTableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfExists(MariaDBDDLParser::IfExistsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateIndex(MariaDBDDLParser::CreateIndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDropIndex(MariaDBDDLParser::DropIndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAlterTable(MariaDBDDLParser::AlterTableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddColumn(MariaDBDDLParser::AddColumnContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDropColumn(MariaDBDDLParser::DropColumnContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModifyColumn(MariaDBDDLParser::ModifyColumnContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddConstraint(MariaDBDDLParser::AddConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDropPrimaryKey(MariaDBDDLParser::DropPrimaryKeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDropForeignKey(MariaDBDDLParser::DropForeignKeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDropIndexAlt(MariaDBDDLParser::DropIndexAltContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRenameTable(MariaDBDDLParser::RenameTableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreateDatabase(MariaDBDDLParser::CreateDatabaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUseDatabase(MariaDBDDLParser::UseDatabaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetStatement(MariaDBDDLParser::SetStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLockStatement(MariaDBDDLParser::LockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnlockStatement(MariaDBDDLParser::UnlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertStatement(MariaDBDDLParser::InsertStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(MariaDBDDLParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTableName(MariaDBDDLParser::TableNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitColumnName(MariaDBDDLParser::ColumnNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollationName(MariaDBDDLParser::CollationNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(MariaDBDDLParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonReservedKeyword(MariaDBDDLParser::NonReservedKeywordContext *ctx) override {
    return visitChildren(ctx);
  }


};

