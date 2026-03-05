
// Generated from MariaDBDDLParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  MariaDBDDLParser : public antlr4::Parser {
public:
  enum {
    ADD = 1, ALTER = 2, AUTO_INCREMENT = 3, BIGINT = 4, BLOB = 5, BOOLEAN = 6, 
    CASCADE = 7, CHAR = 8, CHARACTER = 9, CHARSET = 10, CHECK = 11, COLLATE = 12, 
    COLUMN = 13, COMMENT = 14, CONSTRAINT = 15, CREATE = 16, DATABASE = 17, 
    DATE = 18, DATETIME = 19, DECIMAL = 20, DEFAULT = 21, DELETE = 22, DOUBLE = 23, 
    DROP = 24, ENGINE = 25, ENUM = 26, EXISTS = 27, FLOAT = 28, FOREIGN = 29, 
    IF = 30, INDEX = 31, INSERT = 32, INT = 33, INTEGER = 34, INTO = 35, 
    JSON = 36, KEY = 37, LOCK = 38, LONGBLOB = 39, LONGTEXT = 40, MEDIUMBLOB = 41, 
    MEDIUMINT = 42, MEDIUMTEXT = 43, MODIFY = 44, NOT = 45, NULL_ = 46, 
    ON = 47, PRIMARY = 48, REFERENCES = 49, RENAME = 50, RESTRICT = 51, 
    SET = 52, ACTION = 53, SIGNED = 54, SMALLINT = 55, TABLE = 56, TABLES = 57, 
    TEXT = 58, TIME = 59, TIMESTAMP = 60, TINYBLOB = 61, TINYINT = 62, TINYTEXT = 63, 
    TO = 64, UNIQUE = 65, UNLOCK = 66, UNSIGNED = 67, UPDATE = 68, USE = 69, 
    VALUES = 70, VARCHAR = 71, WRITE = 72, READ = 73, ZEROFILL = 74, NO = 75, 
    LPAREN = 76, RPAREN = 77, COMMA = 78, SEMI = 79, DOT = 80, EQ = 81, 
    BACKTICK = 82, STRING_LITERAL = 83, NUMERIC_LITERAL = 84, BACKTICK_ID = 85, 
    ID = 86, LINE_COMMENT = 87, BLOCK_COMMENT = 88, CONDITIONAL_COMMENT = 89, 
    WS = 90, ANY = 91
  };

  enum {
    RuleScript = 0, RuleStatement = 1, RuleCreateTable = 2, RuleIfNotExists = 3, 
    RuleTableElement = 4, RuleColumnDefinition = 5, RuleColumnModifier = 6, 
    RuleDefaultValue = 7, RuleDataType = 8, RuleIntType = 9, RuleTypeDimension = 10, 
    RuleTypePrecision = 11, RuleEnumValues = 12, RuleTableConstraint = 13, 
    RuleConstraintName = 14, RuleIndexName = 15, RuleIndexColumnNames = 16, 
    RuleReferenceActions = 17, RuleOnDelete = 18, RuleOnUpdate = 19, RuleReferenceAction = 20, 
    RuleTableOptions = 21, RuleTableOption = 22, RuleDropTable = 23, RuleIfExists = 24, 
    RuleCreateIndex = 25, RuleDropIndex = 26, RuleAlterTable = 27, RuleAlterAction = 28, 
    RuleCreateDatabase = 29, RuleUseDatabase = 30, RuleSetStatement = 31, 
    RuleLockStatement = 32, RuleUnlockStatement = 33, RuleInsertStatement = 34, 
    RuleExpression = 35, RuleTableName = 36, RuleColumnName = 37, RuleCollationName = 38, 
    RuleIdentifier = 39, RuleNonReservedKeyword = 40
  };

  explicit MariaDBDDLParser(antlr4::TokenStream *input);

  MariaDBDDLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~MariaDBDDLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ScriptContext;
  class StatementContext;
  class CreateTableContext;
  class IfNotExistsContext;
  class TableElementContext;
  class ColumnDefinitionContext;
  class ColumnModifierContext;
  class DefaultValueContext;
  class DataTypeContext;
  class IntTypeContext;
  class TypeDimensionContext;
  class TypePrecisionContext;
  class EnumValuesContext;
  class TableConstraintContext;
  class ConstraintNameContext;
  class IndexNameContext;
  class IndexColumnNamesContext;
  class ReferenceActionsContext;
  class OnDeleteContext;
  class OnUpdateContext;
  class ReferenceActionContext;
  class TableOptionsContext;
  class TableOptionContext;
  class DropTableContext;
  class IfExistsContext;
  class CreateIndexContext;
  class DropIndexContext;
  class AlterTableContext;
  class AlterActionContext;
  class CreateDatabaseContext;
  class UseDatabaseContext;
  class SetStatementContext;
  class LockStatementContext;
  class UnlockStatementContext;
  class InsertStatementContext;
  class ExpressionContext;
  class TableNameContext;
  class ColumnNameContext;
  class CollationNameContext;
  class IdentifierContext;
  class NonReservedKeywordContext; 

  class  ScriptContext : public antlr4::ParserRuleContext {
  public:
    ScriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScriptContext* script();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CreateTableContext *createTable();
    antlr4::tree::TerminalNode *SEMI();
    DropTableContext *dropTable();
    CreateIndexContext *createIndex();
    DropIndexContext *dropIndex();
    AlterTableContext *alterTable();
    CreateDatabaseContext *createDatabase();
    UseDatabaseContext *useDatabase();
    SetStatementContext *setStatement();
    LockStatementContext *lockStatement();
    UnlockStatementContext *unlockStatement();
    InsertStatementContext *insertStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  CreateTableContext : public antlr4::ParserRuleContext {
  public:
    CreateTableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *TABLE();
    TableNameContext *tableName();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<TableElementContext *> tableElement();
    TableElementContext* tableElement(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    IfNotExistsContext *ifNotExists();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    TableOptionsContext *tableOptions();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateTableContext* createTable();

  class  IfNotExistsContext : public antlr4::ParserRuleContext {
  public:
    IfNotExistsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *EXISTS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfNotExistsContext* ifNotExists();

  class  TableElementContext : public antlr4::ParserRuleContext {
  public:
    TableElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColumnDefinitionContext *columnDefinition();
    TableConstraintContext *tableConstraint();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TableElementContext* tableElement();

  class  ColumnDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ColumnDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColumnNameContext *columnName();
    DataTypeContext *dataType();
    std::vector<ColumnModifierContext *> columnModifier();
    ColumnModifierContext* columnModifier(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ColumnDefinitionContext* columnDefinition();

  class  ColumnModifierContext : public antlr4::ParserRuleContext {
  public:
    ColumnModifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ColumnModifierContext() = default;
    void copyFrom(ColumnModifierContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CheckModContext : public ColumnModifierContext {
  public:
    CheckModContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *CHECK();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DefaultValContext : public ColumnModifierContext {
  public:
    DefaultValContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *DEFAULT();
    DefaultValueContext *defaultValue();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NullableContext : public ColumnModifierContext {
  public:
    NullableContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *NULL_();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CommentModContext : public ColumnModifierContext {
  public:
    CommentModContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *COMMENT();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotNullContext : public ColumnModifierContext {
  public:
    NotNullContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *NULL_();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CollateModContext : public ColumnModifierContext {
  public:
    CollateModContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *COLLATE();
    CollationNameContext *collationName();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AutoIncrementContext : public ColumnModifierContext {
  public:
    AutoIncrementContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *AUTO_INCREMENT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InlinePrimaryKeyContext : public ColumnModifierContext {
  public:
    InlinePrimaryKeyContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *PRIMARY();
    antlr4::tree::TerminalNode *KEY();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ZerofillModContext : public ColumnModifierContext {
  public:
    ZerofillModContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *ZEROFILL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InlineUniqueContext : public ColumnModifierContext {
  public:
    InlineUniqueContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *UNIQUE();
    antlr4::tree::TerminalNode *KEY();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnsignedModContext : public ColumnModifierContext {
  public:
    UnsignedModContext(ColumnModifierContext *ctx);

    antlr4::tree::TerminalNode *UNSIGNED();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ColumnModifierContext* columnModifier();

  class  DefaultValueContext : public antlr4::ParserRuleContext {
  public:
    DefaultValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *NUMERIC_LITERAL();
    antlr4::tree::TerminalNode *NULL_();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DefaultValueContext* defaultValue();

  class  DataTypeContext : public antlr4::ParserRuleContext {
  public:
    DataTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    DataTypeContext() = default;
    void copyFrom(DataTypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TinyBlobDataTypeContext : public DataTypeContext {
  public:
    TinyBlobDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *TINYBLOB();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DateDataTypeContext : public DataTypeContext {
  public:
    DateDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *DATE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DatetimeDataTypeContext : public DataTypeContext {
  public:
    DatetimeDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *DATETIME();
    TypeDimensionContext *typeDimension();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FloatDataTypeContext : public DataTypeContext {
  public:
    FloatDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *FLOAT();
    TypeDimensionContext *typeDimension();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MediumBlobDataTypeContext : public DataTypeContext {
  public:
    MediumBlobDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *MEDIUMBLOB();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlobDataTypeContext : public DataTypeContext {
  public:
    BlobDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *BLOB();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntDataTypeContext : public DataTypeContext {
  public:
    IntDataTypeContext(DataTypeContext *ctx);

    IntTypeContext *intType();
    TypeDimensionContext *typeDimension();
    antlr4::tree::TerminalNode *UNSIGNED();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EnumDataTypeContext : public DataTypeContext {
  public:
    EnumDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *LPAREN();
    EnumValuesContext *enumValues();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VarcharDataTypeContext : public DataTypeContext {
  public:
    VarcharDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *VARCHAR();
    TypeDimensionContext *typeDimension();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  JsonDataTypeContext : public DataTypeContext {
  public:
    JsonDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *JSON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LongTextDataTypeContext : public DataTypeContext {
  public:
    LongTextDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *LONGTEXT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TinyintDataTypeContext : public DataTypeContext {
  public:
    TinyintDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *TINYINT();
    TypeDimensionContext *typeDimension();
    antlr4::tree::TerminalNode *UNSIGNED();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TinyTextDataTypeContext : public DataTypeContext {
  public:
    TinyTextDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *TINYTEXT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BooleanDataTypeContext : public DataTypeContext {
  public:
    BooleanDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *BOOLEAN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MediumTextDataTypeContext : public DataTypeContext {
  public:
    MediumTextDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *MEDIUMTEXT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TimestampDataTypeContext : public DataTypeContext {
  public:
    TimestampDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *TIMESTAMP();
    TypeDimensionContext *typeDimension();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TextDataTypeContext : public DataTypeContext {
  public:
    TextDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *TEXT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DecimalDataTypeContext : public DataTypeContext {
  public:
    DecimalDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *DECIMAL();
    TypePrecisionContext *typePrecision();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CharDataTypeContext : public DataTypeContext {
  public:
    CharDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *CHAR();
    TypeDimensionContext *typeDimension();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DoubleDataTypeContext : public DataTypeContext {
  public:
    DoubleDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *DOUBLE();
    TypeDimensionContext *typeDimension();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LongBlobDataTypeContext : public DataTypeContext {
  public:
    LongBlobDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *LONGBLOB();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TimeDataTypeContext : public DataTypeContext {
  public:
    TimeDataTypeContext(DataTypeContext *ctx);

    antlr4::tree::TerminalNode *TIME();
    TypeDimensionContext *typeDimension();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  DataTypeContext* dataType();

  class  IntTypeContext : public antlr4::ParserRuleContext {
  public:
    IntTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *BIGINT();
    antlr4::tree::TerminalNode *SMALLINT();
    antlr4::tree::TerminalNode *MEDIUMINT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntTypeContext* intType();

  class  TypeDimensionContext : public antlr4::ParserRuleContext {
  public:
    TypeDimensionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *NUMERIC_LITERAL();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeDimensionContext* typeDimension();

  class  TypePrecisionContext : public antlr4::ParserRuleContext {
  public:
    TypePrecisionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> NUMERIC_LITERAL();
    antlr4::tree::TerminalNode* NUMERIC_LITERAL(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypePrecisionContext* typePrecision();

  class  EnumValuesContext : public antlr4::ParserRuleContext {
  public:
    EnumValuesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumValuesContext* enumValues();

  class  TableConstraintContext : public antlr4::ParserRuleContext {
  public:
    TableConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TableConstraintContext() = default;
    void copyFrom(TableConstraintContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ForeignKeyConstraintContext : public TableConstraintContext {
  public:
    ForeignKeyConstraintContext(TableConstraintContext *ctx);

    antlr4::tree::TerminalNode *FOREIGN();
    antlr4::tree::TerminalNode *KEY();
    std::vector<antlr4::tree::TerminalNode *> LPAREN();
    antlr4::tree::TerminalNode* LPAREN(size_t i);
    std::vector<IndexColumnNamesContext *> indexColumnNames();
    IndexColumnNamesContext* indexColumnNames(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RPAREN();
    antlr4::tree::TerminalNode* RPAREN(size_t i);
    antlr4::tree::TerminalNode *REFERENCES();
    TableNameContext *tableName();
    ConstraintNameContext *constraintName();
    IndexNameContext *indexName();
    ReferenceActionsContext *referenceActions();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IndexConstraintContext : public TableConstraintContext {
  public:
    IndexConstraintContext(TableConstraintContext *ctx);

    antlr4::tree::TerminalNode *KEY();
    IndexNameContext *indexName();
    antlr4::tree::TerminalNode *LPAREN();
    IndexColumnNamesContext *indexColumnNames();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UniqueKeyConstraintContext : public TableConstraintContext {
  public:
    UniqueKeyConstraintContext(TableConstraintContext *ctx);

    antlr4::tree::TerminalNode *UNIQUE();
    antlr4::tree::TerminalNode *LPAREN();
    IndexColumnNamesContext *indexColumnNames();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *KEY();
    IndexNameContext *indexName();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PrimaryKeyConstraintContext : public TableConstraintContext {
  public:
    PrimaryKeyConstraintContext(TableConstraintContext *ctx);

    antlr4::tree::TerminalNode *PRIMARY();
    antlr4::tree::TerminalNode *KEY();
    antlr4::tree::TerminalNode *LPAREN();
    IndexColumnNamesContext *indexColumnNames();
    antlr4::tree::TerminalNode *RPAREN();
    IndexNameContext *indexName();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CheckConstraintContext : public TableConstraintContext {
  public:
    CheckConstraintContext(TableConstraintContext *ctx);

    antlr4::tree::TerminalNode *CHECK();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    ConstraintNameContext *constraintName();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TableConstraintContext* tableConstraint();

  class  ConstraintNameContext : public antlr4::ParserRuleContext {
  public:
    ConstraintNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONSTRAINT();
    IdentifierContext *identifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstraintNameContext* constraintName();

  class  IndexNameContext : public antlr4::ParserRuleContext {
  public:
    IndexNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndexNameContext* indexName();

  class  IndexColumnNamesContext : public antlr4::ParserRuleContext {
  public:
    IndexColumnNamesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ColumnNameContext *> columnName();
    ColumnNameContext* columnName(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndexColumnNamesContext* indexColumnNames();

  class  ReferenceActionsContext : public antlr4::ParserRuleContext {
  public:
    ReferenceActionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OnDeleteContext *onDelete();
    OnUpdateContext *onUpdate();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReferenceActionsContext* referenceActions();

  class  OnDeleteContext : public antlr4::ParserRuleContext {
  public:
    OnDeleteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ON();
    antlr4::tree::TerminalNode *DELETE();
    ReferenceActionContext *referenceAction();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OnDeleteContext* onDelete();

  class  OnUpdateContext : public antlr4::ParserRuleContext {
  public:
    OnUpdateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ON();
    antlr4::tree::TerminalNode *UPDATE();
    ReferenceActionContext *referenceAction();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OnUpdateContext* onUpdate();

  class  ReferenceActionContext : public antlr4::ParserRuleContext {
  public:
    ReferenceActionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CASCADE();
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *NULL_();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *RESTRICT();
    antlr4::tree::TerminalNode *NO();
    antlr4::tree::TerminalNode *ACTION();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReferenceActionContext* referenceAction();

  class  TableOptionsContext : public antlr4::ParserRuleContext {
  public:
    TableOptionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TableOptionContext *> tableOption();
    TableOptionContext* tableOption(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TableOptionsContext* tableOptions();

  class  TableOptionContext : public antlr4::ParserRuleContext {
  public:
    TableOptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TableOptionContext() = default;
    void copyFrom(TableOptionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EngineOptionContext : public TableOptionContext {
  public:
    EngineOptionContext(TableOptionContext *ctx);

    antlr4::tree::TerminalNode *ENGINE();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *EQ();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CharsetOptionContext : public TableOptionContext {
  public:
    CharsetOptionContext(TableOptionContext *ctx);

    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *CHARSET();
    antlr4::tree::TerminalNode *CHARACTER();
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *EQ();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AutoIncrOptionContext : public TableOptionContext {
  public:
    AutoIncrOptionContext(TableOptionContext *ctx);

    antlr4::tree::TerminalNode *AUTO_INCREMENT();
    antlr4::tree::TerminalNode *NUMERIC_LITERAL();
    antlr4::tree::TerminalNode *EQ();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CommentOptionContext : public TableOptionContext {
  public:
    CommentOptionContext(TableOptionContext *ctx);

    antlr4::tree::TerminalNode *COMMENT();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *EQ();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CollateOptionContext : public TableOptionContext {
  public:
    CollateOptionContext(TableOptionContext *ctx);

    antlr4::tree::TerminalNode *COLLATE();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *EQ();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TableOptionContext* tableOption();

  class  DropTableContext : public antlr4::ParserRuleContext {
  public:
    DropTableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DROP();
    antlr4::tree::TerminalNode *TABLE();
    TableNameContext *tableName();
    IfExistsContext *ifExists();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropTableContext* dropTable();

  class  IfExistsContext : public antlr4::ParserRuleContext {
  public:
    IfExistsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *EXISTS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfExistsContext* ifExists();

  class  CreateIndexContext : public antlr4::ParserRuleContext {
  public:
    CreateIndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *INDEX();
    IndexNameContext *indexName();
    antlr4::tree::TerminalNode *ON();
    TableNameContext *tableName();
    antlr4::tree::TerminalNode *LPAREN();
    IndexColumnNamesContext *indexColumnNames();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *UNIQUE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateIndexContext* createIndex();

  class  DropIndexContext : public antlr4::ParserRuleContext {
  public:
    DropIndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DROP();
    antlr4::tree::TerminalNode *INDEX();
    IndexNameContext *indexName();
    antlr4::tree::TerminalNode *ON();
    TableNameContext *tableName();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropIndexContext* dropIndex();

  class  AlterTableContext : public antlr4::ParserRuleContext {
  public:
    AlterTableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ALTER();
    antlr4::tree::TerminalNode *TABLE();
    TableNameContext *tableName();
    std::vector<AlterActionContext *> alterAction();
    AlterActionContext* alterAction(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AlterTableContext* alterTable();

  class  AlterActionContext : public antlr4::ParserRuleContext {
  public:
    AlterActionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AlterActionContext() = default;
    void copyFrom(AlterActionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AddColumnContext : public AlterActionContext {
  public:
    AddColumnContext(AlterActionContext *ctx);

    antlr4::tree::TerminalNode *ADD();
    ColumnDefinitionContext *columnDefinition();
    antlr4::tree::TerminalNode *COLUMN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DropForeignKeyContext : public AlterActionContext {
  public:
    DropForeignKeyContext(AlterActionContext *ctx);

    antlr4::tree::TerminalNode *DROP();
    antlr4::tree::TerminalNode *FOREIGN();
    antlr4::tree::TerminalNode *KEY();
    IdentifierContext *identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DropIndexAltContext : public AlterActionContext {
  public:
    DropIndexAltContext(AlterActionContext *ctx);

    antlr4::tree::TerminalNode *DROP();
    antlr4::tree::TerminalNode *INDEX();
    IdentifierContext *identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddConstraintContext : public AlterActionContext {
  public:
    AddConstraintContext(AlterActionContext *ctx);

    antlr4::tree::TerminalNode *ADD();
    TableConstraintContext *tableConstraint();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DropPrimaryKeyContext : public AlterActionContext {
  public:
    DropPrimaryKeyContext(AlterActionContext *ctx);

    antlr4::tree::TerminalNode *DROP();
    antlr4::tree::TerminalNode *PRIMARY();
    antlr4::tree::TerminalNode *KEY();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RenameTableContext : public AlterActionContext {
  public:
    RenameTableContext(AlterActionContext *ctx);

    antlr4::tree::TerminalNode *RENAME();
    antlr4::tree::TerminalNode *TO();
    TableNameContext *tableName();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DropColumnContext : public AlterActionContext {
  public:
    DropColumnContext(AlterActionContext *ctx);

    antlr4::tree::TerminalNode *DROP();
    ColumnNameContext *columnName();
    antlr4::tree::TerminalNode *COLUMN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ModifyColumnContext : public AlterActionContext {
  public:
    ModifyColumnContext(AlterActionContext *ctx);

    antlr4::tree::TerminalNode *MODIFY();
    ColumnDefinitionContext *columnDefinition();
    antlr4::tree::TerminalNode *COLUMN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AlterActionContext* alterAction();

  class  CreateDatabaseContext : public antlr4::ParserRuleContext {
  public:
    CreateDatabaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *DATABASE();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    IfNotExistsContext *ifNotExists();
    antlr4::tree::TerminalNode *CHARSET();
    antlr4::tree::TerminalNode *CHARACTER();
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *EQ();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateDatabaseContext* createDatabase();

  class  UseDatabaseContext : public antlr4::ParserRuleContext {
  public:
    UseDatabaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *USE();
    IdentifierContext *identifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UseDatabaseContext* useDatabase();

  class  SetStatementContext : public antlr4::ParserRuleContext {
  public:
    SetStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET();
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetStatementContext* setStatement();

  class  LockStatementContext : public antlr4::ParserRuleContext {
  public:
    LockStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOCK();
    antlr4::tree::TerminalNode *TABLES();
    TableNameContext *tableName();
    antlr4::tree::TerminalNode *WRITE();
    antlr4::tree::TerminalNode *READ();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LockStatementContext* lockStatement();

  class  UnlockStatementContext : public antlr4::ParserRuleContext {
  public:
    UnlockStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNLOCK();
    antlr4::tree::TerminalNode *TABLES();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnlockStatementContext* unlockStatement();

  class  InsertStatementContext : public antlr4::ParserRuleContext {
  public:
    InsertStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    antlr4::tree::TerminalNode *INTO();
    TableNameContext *tableName();
    antlr4::tree::TerminalNode *VALUES();
    antlr4::tree::TerminalNode *LPAREN();
    IndexColumnNamesContext *indexColumnNames();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertStatementContext* insertStatement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> RPAREN();
    antlr4::tree::TerminalNode* RPAREN(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  TableNameContext : public antlr4::ParserRuleContext {
  public:
    TableNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *DOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TableNameContext* tableName();

  class  ColumnNameContext : public antlr4::ParserRuleContext {
  public:
    ColumnNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ColumnNameContext* columnName();

  class  CollationNameContext : public antlr4::ParserRuleContext {
  public:
    CollationNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *STRING_LITERAL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CollationNameContext* collationName();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *BACKTICK_ID();
    NonReservedKeywordContext *nonReservedKeyword();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  NonReservedKeywordContext : public antlr4::ParserRuleContext {
  public:
    NonReservedKeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ACTION();
    antlr4::tree::TerminalNode *CASCADE();
    antlr4::tree::TerminalNode *CHARSET();
    antlr4::tree::TerminalNode *CHARACTER();
    antlr4::tree::TerminalNode *COLLATE();
    antlr4::tree::TerminalNode *COLUMN();
    antlr4::tree::TerminalNode *COMMENT();
    antlr4::tree::TerminalNode *DATABASE();
    antlr4::tree::TerminalNode *ENGINE();
    antlr4::tree::TerminalNode *EXISTS();
    antlr4::tree::TerminalNode *KEY();
    antlr4::tree::TerminalNode *LOCK();
    antlr4::tree::TerminalNode *NO();
    antlr4::tree::TerminalNode *READ();
    antlr4::tree::TerminalNode *RENAME();
    antlr4::tree::TerminalNode *RESTRICT();
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *SIGNED();
    antlr4::tree::TerminalNode *TABLES();
    antlr4::tree::TerminalNode *TO();
    antlr4::tree::TerminalNode *UNLOCK();
    antlr4::tree::TerminalNode *UNSIGNED();
    antlr4::tree::TerminalNode *VALUES();
    antlr4::tree::TerminalNode *WRITE();
    antlr4::tree::TerminalNode *ZEROFILL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NonReservedKeywordContext* nonReservedKeyword();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

