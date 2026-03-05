
// Generated from MariaDBDDLLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  MariaDBDDLLexer : public antlr4::Lexer {
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

  explicit MariaDBDDLLexer(antlr4::CharStream *input);

  ~MariaDBDDLLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

