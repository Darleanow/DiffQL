
// Generated from MariaDBDDLParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "MariaDBDDLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MariaDBDDLParser.
 */
class  MariaDBDDLParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MariaDBDDLParser.
   */
    virtual std::any visitScript(MariaDBDDLParser::ScriptContext *context) = 0;

    virtual std::any visitStatement(MariaDBDDLParser::StatementContext *context) = 0;

    virtual std::any visitCreateTable(MariaDBDDLParser::CreateTableContext *context) = 0;

    virtual std::any visitIfNotExists(MariaDBDDLParser::IfNotExistsContext *context) = 0;

    virtual std::any visitTableElement(MariaDBDDLParser::TableElementContext *context) = 0;

    virtual std::any visitColumnDefinition(MariaDBDDLParser::ColumnDefinitionContext *context) = 0;

    virtual std::any visitNotNull(MariaDBDDLParser::NotNullContext *context) = 0;

    virtual std::any visitNullable(MariaDBDDLParser::NullableContext *context) = 0;

    virtual std::any visitDefaultVal(MariaDBDDLParser::DefaultValContext *context) = 0;

    virtual std::any visitAutoIncrement(MariaDBDDLParser::AutoIncrementContext *context) = 0;

    virtual std::any visitInlinePrimaryKey(MariaDBDDLParser::InlinePrimaryKeyContext *context) = 0;

    virtual std::any visitInlineUnique(MariaDBDDLParser::InlineUniqueContext *context) = 0;

    virtual std::any visitCommentMod(MariaDBDDLParser::CommentModContext *context) = 0;

    virtual std::any visitUnsignedMod(MariaDBDDLParser::UnsignedModContext *context) = 0;

    virtual std::any visitZerofillMod(MariaDBDDLParser::ZerofillModContext *context) = 0;

    virtual std::any visitCollateMod(MariaDBDDLParser::CollateModContext *context) = 0;

    virtual std::any visitCheckMod(MariaDBDDLParser::CheckModContext *context) = 0;

    virtual std::any visitDefaultValue(MariaDBDDLParser::DefaultValueContext *context) = 0;

    virtual std::any visitIntDataType(MariaDBDDLParser::IntDataTypeContext *context) = 0;

    virtual std::any visitDecimalDataType(MariaDBDDLParser::DecimalDataTypeContext *context) = 0;

    virtual std::any visitFloatDataType(MariaDBDDLParser::FloatDataTypeContext *context) = 0;

    virtual std::any visitDoubleDataType(MariaDBDDLParser::DoubleDataTypeContext *context) = 0;

    virtual std::any visitVarcharDataType(MariaDBDDLParser::VarcharDataTypeContext *context) = 0;

    virtual std::any visitCharDataType(MariaDBDDLParser::CharDataTypeContext *context) = 0;

    virtual std::any visitTextDataType(MariaDBDDLParser::TextDataTypeContext *context) = 0;

    virtual std::any visitTinyTextDataType(MariaDBDDLParser::TinyTextDataTypeContext *context) = 0;

    virtual std::any visitMediumTextDataType(MariaDBDDLParser::MediumTextDataTypeContext *context) = 0;

    virtual std::any visitLongTextDataType(MariaDBDDLParser::LongTextDataTypeContext *context) = 0;

    virtual std::any visitBlobDataType(MariaDBDDLParser::BlobDataTypeContext *context) = 0;

    virtual std::any visitTinyBlobDataType(MariaDBDDLParser::TinyBlobDataTypeContext *context) = 0;

    virtual std::any visitMediumBlobDataType(MariaDBDDLParser::MediumBlobDataTypeContext *context) = 0;

    virtual std::any visitLongBlobDataType(MariaDBDDLParser::LongBlobDataTypeContext *context) = 0;

    virtual std::any visitDateDataType(MariaDBDDLParser::DateDataTypeContext *context) = 0;

    virtual std::any visitDatetimeDataType(MariaDBDDLParser::DatetimeDataTypeContext *context) = 0;

    virtual std::any visitTimestampDataType(MariaDBDDLParser::TimestampDataTypeContext *context) = 0;

    virtual std::any visitTimeDataType(MariaDBDDLParser::TimeDataTypeContext *context) = 0;

    virtual std::any visitBooleanDataType(MariaDBDDLParser::BooleanDataTypeContext *context) = 0;

    virtual std::any visitJsonDataType(MariaDBDDLParser::JsonDataTypeContext *context) = 0;

    virtual std::any visitTinyintDataType(MariaDBDDLParser::TinyintDataTypeContext *context) = 0;

    virtual std::any visitEnumDataType(MariaDBDDLParser::EnumDataTypeContext *context) = 0;

    virtual std::any visitIntType(MariaDBDDLParser::IntTypeContext *context) = 0;

    virtual std::any visitTypeDimension(MariaDBDDLParser::TypeDimensionContext *context) = 0;

    virtual std::any visitTypePrecision(MariaDBDDLParser::TypePrecisionContext *context) = 0;

    virtual std::any visitEnumValues(MariaDBDDLParser::EnumValuesContext *context) = 0;

    virtual std::any visitPrimaryKeyConstraint(MariaDBDDLParser::PrimaryKeyConstraintContext *context) = 0;

    virtual std::any visitUniqueKeyConstraint(MariaDBDDLParser::UniqueKeyConstraintContext *context) = 0;

    virtual std::any visitIndexConstraint(MariaDBDDLParser::IndexConstraintContext *context) = 0;

    virtual std::any visitForeignKeyConstraint(MariaDBDDLParser::ForeignKeyConstraintContext *context) = 0;

    virtual std::any visitCheckConstraint(MariaDBDDLParser::CheckConstraintContext *context) = 0;

    virtual std::any visitConstraintName(MariaDBDDLParser::ConstraintNameContext *context) = 0;

    virtual std::any visitIndexName(MariaDBDDLParser::IndexNameContext *context) = 0;

    virtual std::any visitIndexColumnNames(MariaDBDDLParser::IndexColumnNamesContext *context) = 0;

    virtual std::any visitReferenceActions(MariaDBDDLParser::ReferenceActionsContext *context) = 0;

    virtual std::any visitOnDelete(MariaDBDDLParser::OnDeleteContext *context) = 0;

    virtual std::any visitOnUpdate(MariaDBDDLParser::OnUpdateContext *context) = 0;

    virtual std::any visitReferenceAction(MariaDBDDLParser::ReferenceActionContext *context) = 0;

    virtual std::any visitTableOptions(MariaDBDDLParser::TableOptionsContext *context) = 0;

    virtual std::any visitEngineOption(MariaDBDDLParser::EngineOptionContext *context) = 0;

    virtual std::any visitCharsetOption(MariaDBDDLParser::CharsetOptionContext *context) = 0;

    virtual std::any visitCollateOption(MariaDBDDLParser::CollateOptionContext *context) = 0;

    virtual std::any visitAutoIncrOption(MariaDBDDLParser::AutoIncrOptionContext *context) = 0;

    virtual std::any visitCommentOption(MariaDBDDLParser::CommentOptionContext *context) = 0;

    virtual std::any visitDropTable(MariaDBDDLParser::DropTableContext *context) = 0;

    virtual std::any visitIfExists(MariaDBDDLParser::IfExistsContext *context) = 0;

    virtual std::any visitCreateIndex(MariaDBDDLParser::CreateIndexContext *context) = 0;

    virtual std::any visitDropIndex(MariaDBDDLParser::DropIndexContext *context) = 0;

    virtual std::any visitAlterTable(MariaDBDDLParser::AlterTableContext *context) = 0;

    virtual std::any visitAddColumn(MariaDBDDLParser::AddColumnContext *context) = 0;

    virtual std::any visitDropColumn(MariaDBDDLParser::DropColumnContext *context) = 0;

    virtual std::any visitModifyColumn(MariaDBDDLParser::ModifyColumnContext *context) = 0;

    virtual std::any visitAddConstraint(MariaDBDDLParser::AddConstraintContext *context) = 0;

    virtual std::any visitDropPrimaryKey(MariaDBDDLParser::DropPrimaryKeyContext *context) = 0;

    virtual std::any visitDropForeignKey(MariaDBDDLParser::DropForeignKeyContext *context) = 0;

    virtual std::any visitDropIndexAlt(MariaDBDDLParser::DropIndexAltContext *context) = 0;

    virtual std::any visitRenameTable(MariaDBDDLParser::RenameTableContext *context) = 0;

    virtual std::any visitCreateDatabase(MariaDBDDLParser::CreateDatabaseContext *context) = 0;

    virtual std::any visitUseDatabase(MariaDBDDLParser::UseDatabaseContext *context) = 0;

    virtual std::any visitSetStatement(MariaDBDDLParser::SetStatementContext *context) = 0;

    virtual std::any visitLockStatement(MariaDBDDLParser::LockStatementContext *context) = 0;

    virtual std::any visitUnlockStatement(MariaDBDDLParser::UnlockStatementContext *context) = 0;

    virtual std::any visitInsertStatement(MariaDBDDLParser::InsertStatementContext *context) = 0;

    virtual std::any visitExpression(MariaDBDDLParser::ExpressionContext *context) = 0;

    virtual std::any visitTableName(MariaDBDDLParser::TableNameContext *context) = 0;

    virtual std::any visitColumnName(MariaDBDDLParser::ColumnNameContext *context) = 0;

    virtual std::any visitCollationName(MariaDBDDLParser::CollationNameContext *context) = 0;

    virtual std::any visitIdentifier(MariaDBDDLParser::IdentifierContext *context) = 0;

    virtual std::any visitNonReservedKeyword(MariaDBDDLParser::NonReservedKeywordContext *context) = 0;


};

