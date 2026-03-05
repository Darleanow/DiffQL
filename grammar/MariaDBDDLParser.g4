parser grammar MariaDBDDLParser;

options { tokenVocab = MariaDBDDLLexer; }

// Entry point

script
    : statement* EOF
    ;

statement
    : createTable SEMI
    | dropTable SEMI
    | createIndex SEMI
    | dropIndex SEMI
    | alterTable SEMI
    | createDatabase SEMI
    | useDatabase SEMI
    | setStatement SEMI
    | lockStatement SEMI
    | unlockStatement SEMI
    | insertStatement SEMI
    | SEMI
    ;

// CREATE TABLE

createTable
    : CREATE TABLE ifNotExists? tableName
      LPAREN tableElement (COMMA tableElement)* RPAREN
      tableOptions?
    ;

ifNotExists
    : IF NOT EXISTS
    ;

tableElement
    : columnDefinition
    | tableConstraint
    ;

columnDefinition
    : columnName dataType columnModifier*
    ;

columnModifier
    : NOT NULL_                                   # notNull
    | NULL_                                       # nullable
    | DEFAULT defaultValue                        # defaultVal
    | AUTO_INCREMENT                              # autoIncrement
    | PRIMARY KEY                                 # inlinePrimaryKey
    | UNIQUE (KEY)?                               # inlineUnique
    | COMMENT STRING_LITERAL                      # commentMod
    | UNSIGNED                                    # unsignedMod
    | ZEROFILL                                    # zerofillMod
    | COLLATE collationName                       # collateMod
    | CHECK LPAREN expression RPAREN              # checkMod
    ;

defaultValue
    : STRING_LITERAL
    | NUMERIC_LITERAL
    | NULL_
    ;

// Data types

dataType
    : intType typeDimension? UNSIGNED?            # intDataType
    | DECIMAL typePrecision?                      # decimalDataType
    | FLOAT typeDimension?                        # floatDataType
    | DOUBLE typeDimension?                       # doubleDataType
    | VARCHAR typeDimension                       # varcharDataType
    | CHAR typeDimension?                         # charDataType
    | TEXT                                        # textDataType
    | TINYTEXT                                    # tinyTextDataType
    | MEDIUMTEXT                                  # mediumTextDataType
    | LONGTEXT                                    # longTextDataType
    | BLOB                                        # blobDataType
    | TINYBLOB                                    # tinyBlobDataType
    | MEDIUMBLOB                                  # mediumBlobDataType
    | LONGBLOB                                    # longBlobDataType
    | DATE                                        # dateDataType
    | DATETIME typeDimension?                     # datetimeDataType
    | TIMESTAMP typeDimension?                    # timestampDataType
    | TIME typeDimension?                         # timeDataType
    | BOOLEAN                                     # booleanDataType
    | JSON                                        # jsonDataType
    | TINYINT typeDimension? UNSIGNED?            # tinyintDataType
    | ENUM LPAREN enumValues RPAREN               # enumDataType
    ;

intType
    : INT
    | INTEGER
    | BIGINT
    | SMALLINT
    | MEDIUMINT
    ;

typeDimension
    : LPAREN NUMERIC_LITERAL RPAREN
    ;

typePrecision
    : LPAREN NUMERIC_LITERAL COMMA NUMERIC_LITERAL RPAREN
    ;

enumValues
    : STRING_LITERAL (COMMA STRING_LITERAL)*
    ;

// Table constraints

tableConstraint
    : PRIMARY KEY indexName? LPAREN indexColumnNames RPAREN                                   # primaryKeyConstraint
    | UNIQUE KEY? indexName? LPAREN indexColumnNames RPAREN                                   # uniqueKeyConstraint
    | KEY indexName LPAREN indexColumnNames RPAREN                                            # indexConstraint
    | constraintName? FOREIGN KEY indexName? LPAREN indexColumnNames RPAREN
      REFERENCES tableName LPAREN indexColumnNames RPAREN referenceActions?                   # foreignKeyConstraint
    | constraintName? CHECK LPAREN expression RPAREN                                          # checkConstraint
    ;

constraintName
    : CONSTRAINT identifier
    ;

indexName
    : identifier
    ;

indexColumnNames
    : columnName (COMMA columnName)*
    ;

referenceActions
    : onDelete onUpdate?
    | onUpdate onDelete?
    ;

onDelete
    : ON DELETE referenceAction
    ;

onUpdate
    : ON UPDATE referenceAction
    ;

referenceAction
    : CASCADE
    | SET NULL_
    | SET DEFAULT
    | RESTRICT
    | NO ACTION
    ;

// Table options

tableOptions
    : tableOption+
    ;

tableOption
    : ENGINE EQ? identifier                       # engineOption
    | DEFAULT? (CHARSET | CHARACTER SET) EQ? identifier   # charsetOption
    | COLLATE EQ? identifier                      # collateOption
    | AUTO_INCREMENT EQ? NUMERIC_LITERAL          # autoIncrOption
    | COMMENT EQ? STRING_LITERAL                  # commentOption
    ;

// DROP TABLE

dropTable
    : DROP TABLE ifExists? tableName
    ;

ifExists
    : IF EXISTS
    ;

// CREATE / DROP INDEX

createIndex
    : CREATE UNIQUE? INDEX indexName ON tableName LPAREN indexColumnNames RPAREN
    ;

dropIndex
    : DROP INDEX indexName ON tableName
    ;

// ALTER TABLE

alterTable
    : ALTER TABLE tableName alterAction (COMMA alterAction)*
    ;

alterAction
    : ADD COLUMN? columnDefinition                                           # addColumn
    | DROP COLUMN? columnName                                                # dropColumn
    | MODIFY COLUMN? columnDefinition                                        # modifyColumn
    | ADD tableConstraint                                                    # addConstraint
    | DROP PRIMARY KEY                                                       # dropPrimaryKey
    | DROP FOREIGN KEY identifier                                            # dropForeignKey
    | DROP INDEX identifier                                                  # dropIndexAlt
    | RENAME TO tableName                                                    # renameTable
    ;

// Misc statements (skipped)

createDatabase
    : CREATE DATABASE ifNotExists? identifier (DEFAULT? (CHARSET | CHARACTER SET) EQ? identifier)?
    ;

useDatabase
    : USE identifier
    ;

setStatement
    : SET (~SEMI)*?
    ;

lockStatement
    : LOCK TABLES tableName (WRITE | READ)
    ;

unlockStatement
    : UNLOCK TABLES
    ;

insertStatement
    : INSERT INTO tableName (LPAREN indexColumnNames RPAREN)? VALUES (~SEMI)*?
    ;

// Expression (generic, for CHECK constraints) 

expression
    : ~(RPAREN)+
    ;

// Identifiers

tableName
    : identifier (DOT identifier)?
    ;

columnName
    : identifier
    ;

collationName
    : identifier
    | STRING_LITERAL
    ;

identifier
    : ID
    | BACKTICK_ID
    | nonReservedKeyword
    ;

nonReservedKeyword
    : ACTION | CASCADE | CHARSET | CHARACTER | COLLATE | COLUMN | COMMENT
    | DATABASE | ENGINE | EXISTS | KEY | LOCK | NO | READ | RENAME
    | RESTRICT | SET | SIGNED | TABLES | TO | UNLOCK | UNSIGNED | VALUES
    | WRITE | ZEROFILL
    ;
