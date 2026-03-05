
// Generated from MariaDBDDLParser.g4 by ANTLR 4.13.2


#include "MariaDBDDLParserVisitor.h"

#include "MariaDBDDLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MariaDBDDLParserStaticData final {
  MariaDBDDLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MariaDBDDLParserStaticData(const MariaDBDDLParserStaticData&) = delete;
  MariaDBDDLParserStaticData(MariaDBDDLParserStaticData&&) = delete;
  MariaDBDDLParserStaticData& operator=(const MariaDBDDLParserStaticData&) = delete;
  MariaDBDDLParserStaticData& operator=(MariaDBDDLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mariadbddlparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<MariaDBDDLParserStaticData> mariadbddlparserParserStaticData = nullptr;

void mariadbddlparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mariadbddlparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(mariadbddlparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MariaDBDDLParserStaticData>(
    std::vector<std::string>{
      "script", "statement", "createTable", "ifNotExists", "tableElement", 
      "columnDefinition", "columnModifier", "defaultValue", "dataType", 
      "intType", "typeDimension", "typePrecision", "enumValues", "tableConstraint", 
      "constraintName", "indexName", "indexColumnNames", "referenceActions", 
      "onDelete", "onUpdate", "referenceAction", "tableOptions", "tableOption", 
      "dropTable", "ifExists", "createIndex", "dropIndex", "alterTable", 
      "alterAction", "createDatabase", "useDatabase", "setStatement", "lockStatement", 
      "unlockStatement", "insertStatement", "expression", "tableName", "columnName", 
      "collationName", "identifier", "nonReservedKeyword"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "'('", "')'", "','", "';'", "'.'", 
      "'='", "'`'"
    },
    std::vector<std::string>{
      "", "ADD", "ALTER", "AUTO_INCREMENT", "BIGINT", "BLOB", "BOOLEAN", 
      "CASCADE", "CHAR", "CHARACTER", "CHARSET", "CHECK", "COLLATE", "COLUMN", 
      "COMMENT", "CONSTRAINT", "CREATE", "DATABASE", "DATE", "DATETIME", 
      "DECIMAL", "DEFAULT", "DELETE", "DOUBLE", "DROP", "ENGINE", "ENUM", 
      "EXISTS", "FLOAT", "FOREIGN", "IF", "INDEX", "INSERT", "INT", "INTEGER", 
      "INTO", "JSON", "KEY", "LOCK", "LONGBLOB", "LONGTEXT", "MEDIUMBLOB", 
      "MEDIUMINT", "MEDIUMTEXT", "MODIFY", "NOT", "NULL_", "ON", "PRIMARY", 
      "REFERENCES", "RENAME", "RESTRICT", "SET", "ACTION", "SIGNED", "SMALLINT", 
      "TABLE", "TABLES", "TEXT", "TIME", "TIMESTAMP", "TINYBLOB", "TINYINT", 
      "TINYTEXT", "TO", "UNIQUE", "UNLOCK", "UNSIGNED", "UPDATE", "USE", 
      "VALUES", "VARCHAR", "WRITE", "READ", "ZEROFILL", "NO", "LPAREN", 
      "RPAREN", "COMMA", "SEMI", "DOT", "EQ", "BACKTICK", "STRING_LITERAL", 
      "NUMERIC_LITERAL", "BACKTICK_ID", "ID", "LINE_COMMENT", "BLOCK_COMMENT", 
      "CONDITIONAL_COMMENT", "WS", "ANY"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,91,554,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,1,0,5,0,84,8,0,10,
  	0,12,0,87,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,3,1,125,8,1,1,2,1,2,1,2,3,2,130,8,2,1,2,1,2,1,2,1,2,
  	1,2,5,2,137,8,2,10,2,12,2,140,9,2,1,2,1,2,3,2,144,8,2,1,3,1,3,1,3,1,3,
  	1,4,1,4,3,4,152,8,4,1,5,1,5,1,5,5,5,157,8,5,10,5,12,5,160,9,5,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,172,8,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,6,3,6,185,8,6,1,7,1,7,1,8,1,8,3,8,191,8,8,1,8,3,8,194,
  	8,8,1,8,1,8,3,8,198,8,8,1,8,1,8,3,8,202,8,8,1,8,1,8,3,8,206,8,8,1,8,1,
  	8,1,8,1,8,3,8,212,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,
  	225,8,8,1,8,1,8,3,8,229,8,8,1,8,1,8,3,8,233,8,8,1,8,1,8,1,8,1,8,3,8,239,
  	8,8,1,8,3,8,242,8,8,1,8,1,8,1,8,1,8,1,8,3,8,249,8,8,1,9,1,9,1,10,1,10,
  	1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,5,12,266,8,12,
  	10,12,12,12,269,9,12,1,13,1,13,1,13,3,13,274,8,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,3,13,282,8,13,1,13,3,13,285,8,13,1,13,1,13,1,13,1,13,1,13,1,
  	13,1,13,1,13,1,13,1,13,1,13,3,13,298,8,13,1,13,1,13,1,13,3,13,303,8,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,314,8,13,1,13,3,13,
  	317,8,13,1,13,1,13,1,13,1,13,1,13,3,13,324,8,13,1,14,1,14,1,14,1,15,1,
  	15,1,16,1,16,1,16,5,16,334,8,16,10,16,12,16,337,9,16,1,17,1,17,3,17,341,
  	8,17,1,17,1,17,3,17,345,8,17,3,17,347,8,17,1,18,1,18,1,18,1,18,1,19,1,
  	19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,365,8,20,1,
  	21,4,21,368,8,21,11,21,12,21,369,1,22,1,22,3,22,374,8,22,1,22,1,22,3,
  	22,378,8,22,1,22,1,22,1,22,3,22,383,8,22,1,22,3,22,386,8,22,1,22,1,22,
  	1,22,3,22,391,8,22,1,22,1,22,1,22,3,22,396,8,22,1,22,1,22,1,22,3,22,401,
  	8,22,1,22,3,22,404,8,22,1,23,1,23,1,23,3,23,409,8,23,1,23,1,23,1,24,1,
  	24,1,24,1,25,1,25,3,25,418,8,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,
  	25,1,26,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,5,27,440,
  	8,27,10,27,12,27,443,9,27,1,28,1,28,3,28,447,8,28,1,28,1,28,1,28,3,28,
  	452,8,28,1,28,1,28,1,28,3,28,457,8,28,1,28,1,28,1,28,1,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,3,28,475,8,28,1,29,1,
  	29,1,29,3,29,480,8,29,1,29,1,29,3,29,484,8,29,1,29,1,29,1,29,3,29,489,
  	8,29,1,29,3,29,492,8,29,1,29,3,29,495,8,29,1,30,1,30,1,30,1,31,1,31,5,
  	31,502,8,31,10,31,12,31,505,9,31,1,32,1,32,1,32,1,32,1,32,1,33,1,33,1,
  	33,1,34,1,34,1,34,1,34,1,34,1,34,1,34,3,34,522,8,34,1,34,1,34,5,34,526,
  	8,34,10,34,12,34,529,9,34,1,35,4,35,532,8,35,11,35,12,35,533,1,36,1,36,
  	1,36,3,36,539,8,36,1,37,1,37,1,38,1,38,3,38,545,8,38,1,39,1,39,1,39,3,
  	39,550,8,39,1,40,1,40,1,40,2,503,527,0,41,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,
  	68,70,72,74,76,78,80,0,6,2,0,46,46,83,84,4,0,4,4,33,34,42,42,55,55,1,
  	0,79,79,1,0,72,73,1,0,77,77,13,0,7,7,9,10,12,14,17,17,25,25,27,27,37,
  	38,50,54,57,57,64,64,66,67,70,70,72,75,630,0,85,1,0,0,0,2,124,1,0,0,0,
  	4,126,1,0,0,0,6,145,1,0,0,0,8,151,1,0,0,0,10,153,1,0,0,0,12,184,1,0,0,
  	0,14,186,1,0,0,0,16,248,1,0,0,0,18,250,1,0,0,0,20,252,1,0,0,0,22,256,
  	1,0,0,0,24,262,1,0,0,0,26,323,1,0,0,0,28,325,1,0,0,0,30,328,1,0,0,0,32,
  	330,1,0,0,0,34,346,1,0,0,0,36,348,1,0,0,0,38,352,1,0,0,0,40,364,1,0,0,
  	0,42,367,1,0,0,0,44,403,1,0,0,0,46,405,1,0,0,0,48,412,1,0,0,0,50,415,
  	1,0,0,0,52,427,1,0,0,0,54,433,1,0,0,0,56,474,1,0,0,0,58,476,1,0,0,0,60,
  	496,1,0,0,0,62,499,1,0,0,0,64,506,1,0,0,0,66,511,1,0,0,0,68,514,1,0,0,
  	0,70,531,1,0,0,0,72,535,1,0,0,0,74,540,1,0,0,0,76,544,1,0,0,0,78,549,
  	1,0,0,0,80,551,1,0,0,0,82,84,3,2,1,0,83,82,1,0,0,0,84,87,1,0,0,0,85,83,
  	1,0,0,0,85,86,1,0,0,0,86,88,1,0,0,0,87,85,1,0,0,0,88,89,5,0,0,1,89,1,
  	1,0,0,0,90,91,3,4,2,0,91,92,5,79,0,0,92,125,1,0,0,0,93,94,3,46,23,0,94,
  	95,5,79,0,0,95,125,1,0,0,0,96,97,3,50,25,0,97,98,5,79,0,0,98,125,1,0,
  	0,0,99,100,3,52,26,0,100,101,5,79,0,0,101,125,1,0,0,0,102,103,3,54,27,
  	0,103,104,5,79,0,0,104,125,1,0,0,0,105,106,3,58,29,0,106,107,5,79,0,0,
  	107,125,1,0,0,0,108,109,3,60,30,0,109,110,5,79,0,0,110,125,1,0,0,0,111,
  	112,3,62,31,0,112,113,5,79,0,0,113,125,1,0,0,0,114,115,3,64,32,0,115,
  	116,5,79,0,0,116,125,1,0,0,0,117,118,3,66,33,0,118,119,5,79,0,0,119,125,
  	1,0,0,0,120,121,3,68,34,0,121,122,5,79,0,0,122,125,1,0,0,0,123,125,5,
  	79,0,0,124,90,1,0,0,0,124,93,1,0,0,0,124,96,1,0,0,0,124,99,1,0,0,0,124,
  	102,1,0,0,0,124,105,1,0,0,0,124,108,1,0,0,0,124,111,1,0,0,0,124,114,1,
  	0,0,0,124,117,1,0,0,0,124,120,1,0,0,0,124,123,1,0,0,0,125,3,1,0,0,0,126,
  	127,5,16,0,0,127,129,5,56,0,0,128,130,3,6,3,0,129,128,1,0,0,0,129,130,
  	1,0,0,0,130,131,1,0,0,0,131,132,3,72,36,0,132,133,5,76,0,0,133,138,3,
  	8,4,0,134,135,5,78,0,0,135,137,3,8,4,0,136,134,1,0,0,0,137,140,1,0,0,
  	0,138,136,1,0,0,0,138,139,1,0,0,0,139,141,1,0,0,0,140,138,1,0,0,0,141,
  	143,5,77,0,0,142,144,3,42,21,0,143,142,1,0,0,0,143,144,1,0,0,0,144,5,
  	1,0,0,0,145,146,5,30,0,0,146,147,5,45,0,0,147,148,5,27,0,0,148,7,1,0,
  	0,0,149,152,3,10,5,0,150,152,3,26,13,0,151,149,1,0,0,0,151,150,1,0,0,
  	0,152,9,1,0,0,0,153,154,3,74,37,0,154,158,3,16,8,0,155,157,3,12,6,0,156,
  	155,1,0,0,0,157,160,1,0,0,0,158,156,1,0,0,0,158,159,1,0,0,0,159,11,1,
  	0,0,0,160,158,1,0,0,0,161,162,5,45,0,0,162,185,5,46,0,0,163,185,5,46,
  	0,0,164,165,5,21,0,0,165,185,3,14,7,0,166,185,5,3,0,0,167,168,5,48,0,
  	0,168,185,5,37,0,0,169,171,5,65,0,0,170,172,5,37,0,0,171,170,1,0,0,0,
  	171,172,1,0,0,0,172,185,1,0,0,0,173,174,5,14,0,0,174,185,5,83,0,0,175,
  	185,5,67,0,0,176,185,5,74,0,0,177,178,5,12,0,0,178,185,3,76,38,0,179,
  	180,5,11,0,0,180,181,5,76,0,0,181,182,3,70,35,0,182,183,5,77,0,0,183,
  	185,1,0,0,0,184,161,1,0,0,0,184,163,1,0,0,0,184,164,1,0,0,0,184,166,1,
  	0,0,0,184,167,1,0,0,0,184,169,1,0,0,0,184,173,1,0,0,0,184,175,1,0,0,0,
  	184,176,1,0,0,0,184,177,1,0,0,0,184,179,1,0,0,0,185,13,1,0,0,0,186,187,
  	7,0,0,0,187,15,1,0,0,0,188,190,3,18,9,0,189,191,3,20,10,0,190,189,1,0,
  	0,0,190,191,1,0,0,0,191,193,1,0,0,0,192,194,5,67,0,0,193,192,1,0,0,0,
  	193,194,1,0,0,0,194,249,1,0,0,0,195,197,5,20,0,0,196,198,3,22,11,0,197,
  	196,1,0,0,0,197,198,1,0,0,0,198,249,1,0,0,0,199,201,5,28,0,0,200,202,
  	3,20,10,0,201,200,1,0,0,0,201,202,1,0,0,0,202,249,1,0,0,0,203,205,5,23,
  	0,0,204,206,3,20,10,0,205,204,1,0,0,0,205,206,1,0,0,0,206,249,1,0,0,0,
  	207,208,5,71,0,0,208,249,3,20,10,0,209,211,5,8,0,0,210,212,3,20,10,0,
  	211,210,1,0,0,0,211,212,1,0,0,0,212,249,1,0,0,0,213,249,5,58,0,0,214,
  	249,5,63,0,0,215,249,5,43,0,0,216,249,5,40,0,0,217,249,5,5,0,0,218,249,
  	5,61,0,0,219,249,5,41,0,0,220,249,5,39,0,0,221,249,5,18,0,0,222,224,5,
  	19,0,0,223,225,3,20,10,0,224,223,1,0,0,0,224,225,1,0,0,0,225,249,1,0,
  	0,0,226,228,5,60,0,0,227,229,3,20,10,0,228,227,1,0,0,0,228,229,1,0,0,
  	0,229,249,1,0,0,0,230,232,5,59,0,0,231,233,3,20,10,0,232,231,1,0,0,0,
  	232,233,1,0,0,0,233,249,1,0,0,0,234,249,5,6,0,0,235,249,5,36,0,0,236,
  	238,5,62,0,0,237,239,3,20,10,0,238,237,1,0,0,0,238,239,1,0,0,0,239,241,
  	1,0,0,0,240,242,5,67,0,0,241,240,1,0,0,0,241,242,1,0,0,0,242,249,1,0,
  	0,0,243,244,5,26,0,0,244,245,5,76,0,0,245,246,3,24,12,0,246,247,5,77,
  	0,0,247,249,1,0,0,0,248,188,1,0,0,0,248,195,1,0,0,0,248,199,1,0,0,0,248,
  	203,1,0,0,0,248,207,1,0,0,0,248,209,1,0,0,0,248,213,1,0,0,0,248,214,1,
  	0,0,0,248,215,1,0,0,0,248,216,1,0,0,0,248,217,1,0,0,0,248,218,1,0,0,0,
  	248,219,1,0,0,0,248,220,1,0,0,0,248,221,1,0,0,0,248,222,1,0,0,0,248,226,
  	1,0,0,0,248,230,1,0,0,0,248,234,1,0,0,0,248,235,1,0,0,0,248,236,1,0,0,
  	0,248,243,1,0,0,0,249,17,1,0,0,0,250,251,7,1,0,0,251,19,1,0,0,0,252,253,
  	5,76,0,0,253,254,5,84,0,0,254,255,5,77,0,0,255,21,1,0,0,0,256,257,5,76,
  	0,0,257,258,5,84,0,0,258,259,5,78,0,0,259,260,5,84,0,0,260,261,5,77,0,
  	0,261,23,1,0,0,0,262,267,5,83,0,0,263,264,5,78,0,0,264,266,5,83,0,0,265,
  	263,1,0,0,0,266,269,1,0,0,0,267,265,1,0,0,0,267,268,1,0,0,0,268,25,1,
  	0,0,0,269,267,1,0,0,0,270,271,5,48,0,0,271,273,5,37,0,0,272,274,3,30,
  	15,0,273,272,1,0,0,0,273,274,1,0,0,0,274,275,1,0,0,0,275,276,5,76,0,0,
  	276,277,3,32,16,0,277,278,5,77,0,0,278,324,1,0,0,0,279,281,5,65,0,0,280,
  	282,5,37,0,0,281,280,1,0,0,0,281,282,1,0,0,0,282,284,1,0,0,0,283,285,
  	3,30,15,0,284,283,1,0,0,0,284,285,1,0,0,0,285,286,1,0,0,0,286,287,5,76,
  	0,0,287,288,3,32,16,0,288,289,5,77,0,0,289,324,1,0,0,0,290,291,5,37,0,
  	0,291,292,3,30,15,0,292,293,5,76,0,0,293,294,3,32,16,0,294,295,5,77,0,
  	0,295,324,1,0,0,0,296,298,3,28,14,0,297,296,1,0,0,0,297,298,1,0,0,0,298,
  	299,1,0,0,0,299,300,5,29,0,0,300,302,5,37,0,0,301,303,3,30,15,0,302,301,
  	1,0,0,0,302,303,1,0,0,0,303,304,1,0,0,0,304,305,5,76,0,0,305,306,3,32,
  	16,0,306,307,5,77,0,0,307,308,5,49,0,0,308,309,3,72,36,0,309,310,5,76,
  	0,0,310,311,3,32,16,0,311,313,5,77,0,0,312,314,3,34,17,0,313,312,1,0,
  	0,0,313,314,1,0,0,0,314,324,1,0,0,0,315,317,3,28,14,0,316,315,1,0,0,0,
  	316,317,1,0,0,0,317,318,1,0,0,0,318,319,5,11,0,0,319,320,5,76,0,0,320,
  	321,3,70,35,0,321,322,5,77,0,0,322,324,1,0,0,0,323,270,1,0,0,0,323,279,
  	1,0,0,0,323,290,1,0,0,0,323,297,1,0,0,0,323,316,1,0,0,0,324,27,1,0,0,
  	0,325,326,5,15,0,0,326,327,3,78,39,0,327,29,1,0,0,0,328,329,3,78,39,0,
  	329,31,1,0,0,0,330,335,3,74,37,0,331,332,5,78,0,0,332,334,3,74,37,0,333,
  	331,1,0,0,0,334,337,1,0,0,0,335,333,1,0,0,0,335,336,1,0,0,0,336,33,1,
  	0,0,0,337,335,1,0,0,0,338,340,3,36,18,0,339,341,3,38,19,0,340,339,1,0,
  	0,0,340,341,1,0,0,0,341,347,1,0,0,0,342,344,3,38,19,0,343,345,3,36,18,
  	0,344,343,1,0,0,0,344,345,1,0,0,0,345,347,1,0,0,0,346,338,1,0,0,0,346,
  	342,1,0,0,0,347,35,1,0,0,0,348,349,5,47,0,0,349,350,5,22,0,0,350,351,
  	3,40,20,0,351,37,1,0,0,0,352,353,5,47,0,0,353,354,5,68,0,0,354,355,3,
  	40,20,0,355,39,1,0,0,0,356,365,5,7,0,0,357,358,5,52,0,0,358,365,5,46,
  	0,0,359,360,5,52,0,0,360,365,5,21,0,0,361,365,5,51,0,0,362,363,5,75,0,
  	0,363,365,5,53,0,0,364,356,1,0,0,0,364,357,1,0,0,0,364,359,1,0,0,0,364,
  	361,1,0,0,0,364,362,1,0,0,0,365,41,1,0,0,0,366,368,3,44,22,0,367,366,
  	1,0,0,0,368,369,1,0,0,0,369,367,1,0,0,0,369,370,1,0,0,0,370,43,1,0,0,
  	0,371,373,5,25,0,0,372,374,5,81,0,0,373,372,1,0,0,0,373,374,1,0,0,0,374,
  	375,1,0,0,0,375,404,3,78,39,0,376,378,5,21,0,0,377,376,1,0,0,0,377,378,
  	1,0,0,0,378,382,1,0,0,0,379,383,5,10,0,0,380,381,5,9,0,0,381,383,5,52,
  	0,0,382,379,1,0,0,0,382,380,1,0,0,0,383,385,1,0,0,0,384,386,5,81,0,0,
  	385,384,1,0,0,0,385,386,1,0,0,0,386,387,1,0,0,0,387,404,3,78,39,0,388,
  	390,5,12,0,0,389,391,5,81,0,0,390,389,1,0,0,0,390,391,1,0,0,0,391,392,
  	1,0,0,0,392,404,3,78,39,0,393,395,5,3,0,0,394,396,5,81,0,0,395,394,1,
  	0,0,0,395,396,1,0,0,0,396,397,1,0,0,0,397,404,5,84,0,0,398,400,5,14,0,
  	0,399,401,5,81,0,0,400,399,1,0,0,0,400,401,1,0,0,0,401,402,1,0,0,0,402,
  	404,5,83,0,0,403,371,1,0,0,0,403,377,1,0,0,0,403,388,1,0,0,0,403,393,
  	1,0,0,0,403,398,1,0,0,0,404,45,1,0,0,0,405,406,5,24,0,0,406,408,5,56,
  	0,0,407,409,3,48,24,0,408,407,1,0,0,0,408,409,1,0,0,0,409,410,1,0,0,0,
  	410,411,3,72,36,0,411,47,1,0,0,0,412,413,5,30,0,0,413,414,5,27,0,0,414,
  	49,1,0,0,0,415,417,5,16,0,0,416,418,5,65,0,0,417,416,1,0,0,0,417,418,
  	1,0,0,0,418,419,1,0,0,0,419,420,5,31,0,0,420,421,3,30,15,0,421,422,5,
  	47,0,0,422,423,3,72,36,0,423,424,5,76,0,0,424,425,3,32,16,0,425,426,5,
  	77,0,0,426,51,1,0,0,0,427,428,5,24,0,0,428,429,5,31,0,0,429,430,3,30,
  	15,0,430,431,5,47,0,0,431,432,3,72,36,0,432,53,1,0,0,0,433,434,5,2,0,
  	0,434,435,5,56,0,0,435,436,3,72,36,0,436,441,3,56,28,0,437,438,5,78,0,
  	0,438,440,3,56,28,0,439,437,1,0,0,0,440,443,1,0,0,0,441,439,1,0,0,0,441,
  	442,1,0,0,0,442,55,1,0,0,0,443,441,1,0,0,0,444,446,5,1,0,0,445,447,5,
  	13,0,0,446,445,1,0,0,0,446,447,1,0,0,0,447,448,1,0,0,0,448,475,3,10,5,
  	0,449,451,5,24,0,0,450,452,5,13,0,0,451,450,1,0,0,0,451,452,1,0,0,0,452,
  	453,1,0,0,0,453,475,3,74,37,0,454,456,5,44,0,0,455,457,5,13,0,0,456,455,
  	1,0,0,0,456,457,1,0,0,0,457,458,1,0,0,0,458,475,3,10,5,0,459,460,5,1,
  	0,0,460,475,3,26,13,0,461,462,5,24,0,0,462,463,5,48,0,0,463,475,5,37,
  	0,0,464,465,5,24,0,0,465,466,5,29,0,0,466,467,5,37,0,0,467,475,3,78,39,
  	0,468,469,5,24,0,0,469,470,5,31,0,0,470,475,3,78,39,0,471,472,5,50,0,
  	0,472,473,5,64,0,0,473,475,3,72,36,0,474,444,1,0,0,0,474,449,1,0,0,0,
  	474,454,1,0,0,0,474,459,1,0,0,0,474,461,1,0,0,0,474,464,1,0,0,0,474,468,
  	1,0,0,0,474,471,1,0,0,0,475,57,1,0,0,0,476,477,5,16,0,0,477,479,5,17,
  	0,0,478,480,3,6,3,0,479,478,1,0,0,0,479,480,1,0,0,0,480,481,1,0,0,0,481,
  	494,3,78,39,0,482,484,5,21,0,0,483,482,1,0,0,0,483,484,1,0,0,0,484,488,
  	1,0,0,0,485,489,5,10,0,0,486,487,5,9,0,0,487,489,5,52,0,0,488,485,1,0,
  	0,0,488,486,1,0,0,0,489,491,1,0,0,0,490,492,5,81,0,0,491,490,1,0,0,0,
  	491,492,1,0,0,0,492,493,1,0,0,0,493,495,3,78,39,0,494,483,1,0,0,0,494,
  	495,1,0,0,0,495,59,1,0,0,0,496,497,5,69,0,0,497,498,3,78,39,0,498,61,
  	1,0,0,0,499,503,5,52,0,0,500,502,8,2,0,0,501,500,1,0,0,0,502,505,1,0,
  	0,0,503,504,1,0,0,0,503,501,1,0,0,0,504,63,1,0,0,0,505,503,1,0,0,0,506,
  	507,5,38,0,0,507,508,5,57,0,0,508,509,3,72,36,0,509,510,7,3,0,0,510,65,
  	1,0,0,0,511,512,5,66,0,0,512,513,5,57,0,0,513,67,1,0,0,0,514,515,5,32,
  	0,0,515,516,5,35,0,0,516,521,3,72,36,0,517,518,5,76,0,0,518,519,3,32,
  	16,0,519,520,5,77,0,0,520,522,1,0,0,0,521,517,1,0,0,0,521,522,1,0,0,0,
  	522,523,1,0,0,0,523,527,5,70,0,0,524,526,8,2,0,0,525,524,1,0,0,0,526,
  	529,1,0,0,0,527,528,1,0,0,0,527,525,1,0,0,0,528,69,1,0,0,0,529,527,1,
  	0,0,0,530,532,8,4,0,0,531,530,1,0,0,0,532,533,1,0,0,0,533,531,1,0,0,0,
  	533,534,1,0,0,0,534,71,1,0,0,0,535,538,3,78,39,0,536,537,5,80,0,0,537,
  	539,3,78,39,0,538,536,1,0,0,0,538,539,1,0,0,0,539,73,1,0,0,0,540,541,
  	3,78,39,0,541,75,1,0,0,0,542,545,3,78,39,0,543,545,5,83,0,0,544,542,1,
  	0,0,0,544,543,1,0,0,0,545,77,1,0,0,0,546,550,5,86,0,0,547,550,5,85,0,
  	0,548,550,3,80,40,0,549,546,1,0,0,0,549,547,1,0,0,0,549,548,1,0,0,0,550,
  	79,1,0,0,0,551,552,7,5,0,0,552,81,1,0,0,0,63,85,124,129,138,143,151,158,
  	171,184,190,193,197,201,205,211,224,228,232,238,241,248,267,273,281,284,
  	297,302,313,316,323,335,340,344,346,364,369,373,377,382,385,390,395,400,
  	403,408,417,441,446,451,456,474,479,483,488,491,494,503,521,527,533,538,
  	544,549
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mariadbddlparserParserStaticData = std::move(staticData);
}

}

MariaDBDDLParser::MariaDBDDLParser(TokenStream *input) : MariaDBDDLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MariaDBDDLParser::MariaDBDDLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MariaDBDDLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *mariadbddlparserParserStaticData->atn, mariadbddlparserParserStaticData->decisionToDFA, mariadbddlparserParserStaticData->sharedContextCache, options);
}

MariaDBDDLParser::~MariaDBDDLParser() {
  delete _interpreter;
}

const atn::ATN& MariaDBDDLParser::getATN() const {
  return *mariadbddlparserParserStaticData->atn;
}

std::string MariaDBDDLParser::getGrammarFileName() const {
  return "MariaDBDDLParser.g4";
}

const std::vector<std::string>& MariaDBDDLParser::getRuleNames() const {
  return mariadbddlparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& MariaDBDDLParser::getVocabulary() const {
  return mariadbddlparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MariaDBDDLParser::getSerializedATN() const {
  return mariadbddlparserParserStaticData->serializedATN;
}


//----------------- ScriptContext ------------------------------------------------------------------

MariaDBDDLParser::ScriptContext::ScriptContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::ScriptContext::EOF() {
  return getToken(MariaDBDDLParser::EOF, 0);
}

std::vector<MariaDBDDLParser::StatementContext *> MariaDBDDLParser::ScriptContext::statement() {
  return getRuleContexts<MariaDBDDLParser::StatementContext>();
}

MariaDBDDLParser::StatementContext* MariaDBDDLParser::ScriptContext::statement(size_t i) {
  return getRuleContext<MariaDBDDLParser::StatementContext>(i);
}


size_t MariaDBDDLParser::ScriptContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleScript;
}


std::any MariaDBDDLParser::ScriptContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitScript(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::ScriptContext* MariaDBDDLParser::script() {
  ScriptContext *_localctx = _tracker.createInstance<ScriptContext>(_ctx, getState());
  enterRule(_localctx, 0, MariaDBDDLParser::RuleScript);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503878817087492) != 0) || ((((_la - 66) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 66)) & 8201) != 0)) {
      setState(82);
      statement();
      setState(87);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(88);
    match(MariaDBDDLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

MariaDBDDLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MariaDBDDLParser::CreateTableContext* MariaDBDDLParser::StatementContext::createTable() {
  return getRuleContext<MariaDBDDLParser::CreateTableContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::StatementContext::SEMI() {
  return getToken(MariaDBDDLParser::SEMI, 0);
}

MariaDBDDLParser::DropTableContext* MariaDBDDLParser::StatementContext::dropTable() {
  return getRuleContext<MariaDBDDLParser::DropTableContext>(0);
}

MariaDBDDLParser::CreateIndexContext* MariaDBDDLParser::StatementContext::createIndex() {
  return getRuleContext<MariaDBDDLParser::CreateIndexContext>(0);
}

MariaDBDDLParser::DropIndexContext* MariaDBDDLParser::StatementContext::dropIndex() {
  return getRuleContext<MariaDBDDLParser::DropIndexContext>(0);
}

MariaDBDDLParser::AlterTableContext* MariaDBDDLParser::StatementContext::alterTable() {
  return getRuleContext<MariaDBDDLParser::AlterTableContext>(0);
}

MariaDBDDLParser::CreateDatabaseContext* MariaDBDDLParser::StatementContext::createDatabase() {
  return getRuleContext<MariaDBDDLParser::CreateDatabaseContext>(0);
}

MariaDBDDLParser::UseDatabaseContext* MariaDBDDLParser::StatementContext::useDatabase() {
  return getRuleContext<MariaDBDDLParser::UseDatabaseContext>(0);
}

MariaDBDDLParser::SetStatementContext* MariaDBDDLParser::StatementContext::setStatement() {
  return getRuleContext<MariaDBDDLParser::SetStatementContext>(0);
}

MariaDBDDLParser::LockStatementContext* MariaDBDDLParser::StatementContext::lockStatement() {
  return getRuleContext<MariaDBDDLParser::LockStatementContext>(0);
}

MariaDBDDLParser::UnlockStatementContext* MariaDBDDLParser::StatementContext::unlockStatement() {
  return getRuleContext<MariaDBDDLParser::UnlockStatementContext>(0);
}

MariaDBDDLParser::InsertStatementContext* MariaDBDDLParser::StatementContext::insertStatement() {
  return getRuleContext<MariaDBDDLParser::InsertStatementContext>(0);
}


size_t MariaDBDDLParser::StatementContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleStatement;
}


std::any MariaDBDDLParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::StatementContext* MariaDBDDLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, MariaDBDDLParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(124);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(90);
      createTable();
      setState(91);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(93);
      dropTable();
      setState(94);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(96);
      createIndex();
      setState(97);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(99);
      dropIndex();
      setState(100);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(102);
      alterTable();
      setState(103);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(105);
      createDatabase();
      setState(106);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(108);
      useDatabase();
      setState(109);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(111);
      setStatement();
      setState(112);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(114);
      lockStatement();
      setState(115);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(117);
      unlockStatement();
      setState(118);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(120);
      insertStatement();
      setState(121);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(123);
      match(MariaDBDDLParser::SEMI);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateTableContext ------------------------------------------------------------------

MariaDBDDLParser::CreateTableContext::CreateTableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::CreateTableContext::CREATE() {
  return getToken(MariaDBDDLParser::CREATE, 0);
}

tree::TerminalNode* MariaDBDDLParser::CreateTableContext::TABLE() {
  return getToken(MariaDBDDLParser::TABLE, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::CreateTableContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CreateTableContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

std::vector<MariaDBDDLParser::TableElementContext *> MariaDBDDLParser::CreateTableContext::tableElement() {
  return getRuleContexts<MariaDBDDLParser::TableElementContext>();
}

MariaDBDDLParser::TableElementContext* MariaDBDDLParser::CreateTableContext::tableElement(size_t i) {
  return getRuleContext<MariaDBDDLParser::TableElementContext>(i);
}

tree::TerminalNode* MariaDBDDLParser::CreateTableContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

MariaDBDDLParser::IfNotExistsContext* MariaDBDDLParser::CreateTableContext::ifNotExists() {
  return getRuleContext<MariaDBDDLParser::IfNotExistsContext>(0);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::CreateTableContext::COMMA() {
  return getTokens(MariaDBDDLParser::COMMA);
}

tree::TerminalNode* MariaDBDDLParser::CreateTableContext::COMMA(size_t i) {
  return getToken(MariaDBDDLParser::COMMA, i);
}

MariaDBDDLParser::TableOptionsContext* MariaDBDDLParser::CreateTableContext::tableOptions() {
  return getRuleContext<MariaDBDDLParser::TableOptionsContext>(0);
}


size_t MariaDBDDLParser::CreateTableContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleCreateTable;
}


std::any MariaDBDDLParser::CreateTableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCreateTable(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::CreateTableContext* MariaDBDDLParser::createTable() {
  CreateTableContext *_localctx = _tracker.createInstance<CreateTableContext>(_ctx, getState());
  enterRule(_localctx, 4, MariaDBDDLParser::RuleCreateTable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    match(MariaDBDDLParser::CREATE);
    setState(127);
    match(MariaDBDDLParser::TABLE);
    setState(129);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MariaDBDDLParser::IF) {
      setState(128);
      ifNotExists();
    }
    setState(131);
    tableName();
    setState(132);
    match(MariaDBDDLParser::LPAREN);
    setState(133);
    tableElement();
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MariaDBDDLParser::COMMA) {
      setState(134);
      match(MariaDBDDLParser::COMMA);
      setState(135);
      tableElement();
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(141);
    match(MariaDBDDLParser::RPAREN);
    setState(143);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 35673608) != 0)) {
      setState(142);
      tableOptions();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfNotExistsContext ------------------------------------------------------------------

MariaDBDDLParser::IfNotExistsContext::IfNotExistsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::IfNotExistsContext::IF() {
  return getToken(MariaDBDDLParser::IF, 0);
}

tree::TerminalNode* MariaDBDDLParser::IfNotExistsContext::NOT() {
  return getToken(MariaDBDDLParser::NOT, 0);
}

tree::TerminalNode* MariaDBDDLParser::IfNotExistsContext::EXISTS() {
  return getToken(MariaDBDDLParser::EXISTS, 0);
}


size_t MariaDBDDLParser::IfNotExistsContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleIfNotExists;
}


std::any MariaDBDDLParser::IfNotExistsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitIfNotExists(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::IfNotExistsContext* MariaDBDDLParser::ifNotExists() {
  IfNotExistsContext *_localctx = _tracker.createInstance<IfNotExistsContext>(_ctx, getState());
  enterRule(_localctx, 6, MariaDBDDLParser::RuleIfNotExists);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(MariaDBDDLParser::IF);
    setState(146);
    match(MariaDBDDLParser::NOT);
    setState(147);
    match(MariaDBDDLParser::EXISTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableElementContext ------------------------------------------------------------------

MariaDBDDLParser::TableElementContext::TableElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MariaDBDDLParser::ColumnDefinitionContext* MariaDBDDLParser::TableElementContext::columnDefinition() {
  return getRuleContext<MariaDBDDLParser::ColumnDefinitionContext>(0);
}

MariaDBDDLParser::TableConstraintContext* MariaDBDDLParser::TableElementContext::tableConstraint() {
  return getRuleContext<MariaDBDDLParser::TableConstraintContext>(0);
}


size_t MariaDBDDLParser::TableElementContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleTableElement;
}


std::any MariaDBDDLParser::TableElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTableElement(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::TableElementContext* MariaDBDDLParser::tableElement() {
  TableElementContext *_localctx = _tracker.createInstance<TableElementContext>(_ctx, getState());
  enterRule(_localctx, 8, MariaDBDDLParser::RuleTableElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(151);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(149);
      columnDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(150);
      tableConstraint();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnDefinitionContext ------------------------------------------------------------------

MariaDBDDLParser::ColumnDefinitionContext::ColumnDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MariaDBDDLParser::ColumnNameContext* MariaDBDDLParser::ColumnDefinitionContext::columnName() {
  return getRuleContext<MariaDBDDLParser::ColumnNameContext>(0);
}

MariaDBDDLParser::DataTypeContext* MariaDBDDLParser::ColumnDefinitionContext::dataType() {
  return getRuleContext<MariaDBDDLParser::DataTypeContext>(0);
}

std::vector<MariaDBDDLParser::ColumnModifierContext *> MariaDBDDLParser::ColumnDefinitionContext::columnModifier() {
  return getRuleContexts<MariaDBDDLParser::ColumnModifierContext>();
}

MariaDBDDLParser::ColumnModifierContext* MariaDBDDLParser::ColumnDefinitionContext::columnModifier(size_t i) {
  return getRuleContext<MariaDBDDLParser::ColumnModifierContext>(i);
}


size_t MariaDBDDLParser::ColumnDefinitionContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleColumnDefinition;
}


std::any MariaDBDDLParser::ColumnDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitColumnDefinition(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::ColumnDefinitionContext* MariaDBDDLParser::columnDefinition() {
  ColumnDefinitionContext *_localctx = _tracker.createInstance<ColumnDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 10, MariaDBDDLParser::RuleColumnDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    columnName();
    setState(154);
    dataType();
    setState(158);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 387028095096840) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 517) != 0)) {
      setState(155);
      columnModifier();
      setState(160);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnModifierContext ------------------------------------------------------------------

MariaDBDDLParser::ColumnModifierContext::ColumnModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MariaDBDDLParser::ColumnModifierContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleColumnModifier;
}

void MariaDBDDLParser::ColumnModifierContext::copyFrom(ColumnModifierContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CheckModContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::CheckModContext::CHECK() {
  return getToken(MariaDBDDLParser::CHECK, 0);
}

tree::TerminalNode* MariaDBDDLParser::CheckModContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

MariaDBDDLParser::ExpressionContext* MariaDBDDLParser::CheckModContext::expression() {
  return getRuleContext<MariaDBDDLParser::ExpressionContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CheckModContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

MariaDBDDLParser::CheckModContext::CheckModContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::CheckModContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCheckMod(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefaultValContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DefaultValContext::DEFAULT() {
  return getToken(MariaDBDDLParser::DEFAULT, 0);
}

MariaDBDDLParser::DefaultValueContext* MariaDBDDLParser::DefaultValContext::defaultValue() {
  return getRuleContext<MariaDBDDLParser::DefaultValueContext>(0);
}

MariaDBDDLParser::DefaultValContext::DefaultValContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DefaultValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDefaultVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NullableContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::NullableContext::NULL_() {
  return getToken(MariaDBDDLParser::NULL_, 0);
}

MariaDBDDLParser::NullableContext::NullableContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::NullableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitNullable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CommentModContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::CommentModContext::COMMENT() {
  return getToken(MariaDBDDLParser::COMMENT, 0);
}

tree::TerminalNode* MariaDBDDLParser::CommentModContext::STRING_LITERAL() {
  return getToken(MariaDBDDLParser::STRING_LITERAL, 0);
}

MariaDBDDLParser::CommentModContext::CommentModContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::CommentModContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCommentMod(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotNullContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::NotNullContext::NOT() {
  return getToken(MariaDBDDLParser::NOT, 0);
}

tree::TerminalNode* MariaDBDDLParser::NotNullContext::NULL_() {
  return getToken(MariaDBDDLParser::NULL_, 0);
}

MariaDBDDLParser::NotNullContext::NotNullContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::NotNullContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitNotNull(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CollateModContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::CollateModContext::COLLATE() {
  return getToken(MariaDBDDLParser::COLLATE, 0);
}

MariaDBDDLParser::CollationNameContext* MariaDBDDLParser::CollateModContext::collationName() {
  return getRuleContext<MariaDBDDLParser::CollationNameContext>(0);
}

MariaDBDDLParser::CollateModContext::CollateModContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::CollateModContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCollateMod(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AutoIncrementContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::AutoIncrementContext::AUTO_INCREMENT() {
  return getToken(MariaDBDDLParser::AUTO_INCREMENT, 0);
}

MariaDBDDLParser::AutoIncrementContext::AutoIncrementContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::AutoIncrementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitAutoIncrement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InlinePrimaryKeyContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::InlinePrimaryKeyContext::PRIMARY() {
  return getToken(MariaDBDDLParser::PRIMARY, 0);
}

tree::TerminalNode* MariaDBDDLParser::InlinePrimaryKeyContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

MariaDBDDLParser::InlinePrimaryKeyContext::InlinePrimaryKeyContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::InlinePrimaryKeyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitInlinePrimaryKey(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ZerofillModContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::ZerofillModContext::ZEROFILL() {
  return getToken(MariaDBDDLParser::ZEROFILL, 0);
}

MariaDBDDLParser::ZerofillModContext::ZerofillModContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::ZerofillModContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitZerofillMod(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InlineUniqueContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::InlineUniqueContext::UNIQUE() {
  return getToken(MariaDBDDLParser::UNIQUE, 0);
}

tree::TerminalNode* MariaDBDDLParser::InlineUniqueContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

MariaDBDDLParser::InlineUniqueContext::InlineUniqueContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::InlineUniqueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitInlineUnique(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnsignedModContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::UnsignedModContext::UNSIGNED() {
  return getToken(MariaDBDDLParser::UNSIGNED, 0);
}

MariaDBDDLParser::UnsignedModContext::UnsignedModContext(ColumnModifierContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::UnsignedModContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitUnsignedMod(this);
  else
    return visitor->visitChildren(this);
}
MariaDBDDLParser::ColumnModifierContext* MariaDBDDLParser::columnModifier() {
  ColumnModifierContext *_localctx = _tracker.createInstance<ColumnModifierContext>(_ctx, getState());
  enterRule(_localctx, 12, MariaDBDDLParser::RuleColumnModifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(184);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MariaDBDDLParser::NOT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::NotNullContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(161);
        match(MariaDBDDLParser::NOT);
        setState(162);
        match(MariaDBDDLParser::NULL_);
        break;
      }

      case MariaDBDDLParser::NULL_: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::NullableContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(163);
        match(MariaDBDDLParser::NULL_);
        break;
      }

      case MariaDBDDLParser::DEFAULT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::DefaultValContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(164);
        match(MariaDBDDLParser::DEFAULT);
        setState(165);
        defaultValue();
        break;
      }

      case MariaDBDDLParser::AUTO_INCREMENT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::AutoIncrementContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(166);
        match(MariaDBDDLParser::AUTO_INCREMENT);
        break;
      }

      case MariaDBDDLParser::PRIMARY: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::InlinePrimaryKeyContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(167);
        match(MariaDBDDLParser::PRIMARY);
        setState(168);
        match(MariaDBDDLParser::KEY);
        break;
      }

      case MariaDBDDLParser::UNIQUE: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::InlineUniqueContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(169);
        match(MariaDBDDLParser::UNIQUE);
        setState(171);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::KEY) {
          setState(170);
          match(MariaDBDDLParser::KEY);
        }
        break;
      }

      case MariaDBDDLParser::COMMENT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::CommentModContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(173);
        match(MariaDBDDLParser::COMMENT);
        setState(174);
        match(MariaDBDDLParser::STRING_LITERAL);
        break;
      }

      case MariaDBDDLParser::UNSIGNED: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::UnsignedModContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(175);
        match(MariaDBDDLParser::UNSIGNED);
        break;
      }

      case MariaDBDDLParser::ZEROFILL: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::ZerofillModContext>(_localctx);
        enterOuterAlt(_localctx, 9);
        setState(176);
        match(MariaDBDDLParser::ZEROFILL);
        break;
      }

      case MariaDBDDLParser::COLLATE: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::CollateModContext>(_localctx);
        enterOuterAlt(_localctx, 10);
        setState(177);
        match(MariaDBDDLParser::COLLATE);
        setState(178);
        collationName();
        break;
      }

      case MariaDBDDLParser::CHECK: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::CheckModContext>(_localctx);
        enterOuterAlt(_localctx, 11);
        setState(179);
        match(MariaDBDDLParser::CHECK);
        setState(180);
        match(MariaDBDDLParser::LPAREN);
        setState(181);
        expression();
        setState(182);
        match(MariaDBDDLParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefaultValueContext ------------------------------------------------------------------

MariaDBDDLParser::DefaultValueContext::DefaultValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::DefaultValueContext::STRING_LITERAL() {
  return getToken(MariaDBDDLParser::STRING_LITERAL, 0);
}

tree::TerminalNode* MariaDBDDLParser::DefaultValueContext::NUMERIC_LITERAL() {
  return getToken(MariaDBDDLParser::NUMERIC_LITERAL, 0);
}

tree::TerminalNode* MariaDBDDLParser::DefaultValueContext::NULL_() {
  return getToken(MariaDBDDLParser::NULL_, 0);
}


size_t MariaDBDDLParser::DefaultValueContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleDefaultValue;
}


std::any MariaDBDDLParser::DefaultValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDefaultValue(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::DefaultValueContext* MariaDBDDLParser::defaultValue() {
  DefaultValueContext *_localctx = _tracker.createInstance<DefaultValueContext>(_ctx, getState());
  enterRule(_localctx, 14, MariaDBDDLParser::RuleDefaultValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    _la = _input->LA(1);
    if (!(((((_la - 46) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 46)) & 412316860417) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataTypeContext ------------------------------------------------------------------

MariaDBDDLParser::DataTypeContext::DataTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MariaDBDDLParser::DataTypeContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleDataType;
}

void MariaDBDDLParser::DataTypeContext::copyFrom(DataTypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TinyBlobDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::TinyBlobDataTypeContext::TINYBLOB() {
  return getToken(MariaDBDDLParser::TINYBLOB, 0);
}

MariaDBDDLParser::TinyBlobDataTypeContext::TinyBlobDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::TinyBlobDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTinyBlobDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DateDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DateDataTypeContext::DATE() {
  return getToken(MariaDBDDLParser::DATE, 0);
}

MariaDBDDLParser::DateDataTypeContext::DateDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DateDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDateDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DatetimeDataTypeContext::DATETIME() {
  return getToken(MariaDBDDLParser::DATETIME, 0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::DatetimeDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

MariaDBDDLParser::DatetimeDataTypeContext::DatetimeDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DatetimeDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDatetimeDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FloatDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::FloatDataTypeContext::FLOAT() {
  return getToken(MariaDBDDLParser::FLOAT, 0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::FloatDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

MariaDBDDLParser::FloatDataTypeContext::FloatDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::FloatDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitFloatDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MediumBlobDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::MediumBlobDataTypeContext::MEDIUMBLOB() {
  return getToken(MariaDBDDLParser::MEDIUMBLOB, 0);
}

MariaDBDDLParser::MediumBlobDataTypeContext::MediumBlobDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::MediumBlobDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitMediumBlobDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlobDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::BlobDataTypeContext::BLOB() {
  return getToken(MariaDBDDLParser::BLOB, 0);
}

MariaDBDDLParser::BlobDataTypeContext::BlobDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::BlobDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitBlobDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntDataTypeContext ------------------------------------------------------------------

MariaDBDDLParser::IntTypeContext* MariaDBDDLParser::IntDataTypeContext::intType() {
  return getRuleContext<MariaDBDDLParser::IntTypeContext>(0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::IntDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::IntDataTypeContext::UNSIGNED() {
  return getToken(MariaDBDDLParser::UNSIGNED, 0);
}

MariaDBDDLParser::IntDataTypeContext::IntDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::IntDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitIntDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EnumDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::EnumDataTypeContext::ENUM() {
  return getToken(MariaDBDDLParser::ENUM, 0);
}

tree::TerminalNode* MariaDBDDLParser::EnumDataTypeContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

MariaDBDDLParser::EnumValuesContext* MariaDBDDLParser::EnumDataTypeContext::enumValues() {
  return getRuleContext<MariaDBDDLParser::EnumValuesContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::EnumDataTypeContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

MariaDBDDLParser::EnumDataTypeContext::EnumDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::EnumDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitEnumDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarcharDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::VarcharDataTypeContext::VARCHAR() {
  return getToken(MariaDBDDLParser::VARCHAR, 0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::VarcharDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

MariaDBDDLParser::VarcharDataTypeContext::VarcharDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::VarcharDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitVarcharDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- JsonDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::JsonDataTypeContext::JSON() {
  return getToken(MariaDBDDLParser::JSON, 0);
}

MariaDBDDLParser::JsonDataTypeContext::JsonDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::JsonDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitJsonDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LongTextDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::LongTextDataTypeContext::LONGTEXT() {
  return getToken(MariaDBDDLParser::LONGTEXT, 0);
}

MariaDBDDLParser::LongTextDataTypeContext::LongTextDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::LongTextDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitLongTextDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TinyintDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::TinyintDataTypeContext::TINYINT() {
  return getToken(MariaDBDDLParser::TINYINT, 0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::TinyintDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::TinyintDataTypeContext::UNSIGNED() {
  return getToken(MariaDBDDLParser::UNSIGNED, 0);
}

MariaDBDDLParser::TinyintDataTypeContext::TinyintDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::TinyintDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTinyintDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TinyTextDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::TinyTextDataTypeContext::TINYTEXT() {
  return getToken(MariaDBDDLParser::TINYTEXT, 0);
}

MariaDBDDLParser::TinyTextDataTypeContext::TinyTextDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::TinyTextDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTinyTextDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleanDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::BooleanDataTypeContext::BOOLEAN() {
  return getToken(MariaDBDDLParser::BOOLEAN, 0);
}

MariaDBDDLParser::BooleanDataTypeContext::BooleanDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::BooleanDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitBooleanDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MediumTextDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::MediumTextDataTypeContext::MEDIUMTEXT() {
  return getToken(MariaDBDDLParser::MEDIUMTEXT, 0);
}

MariaDBDDLParser::MediumTextDataTypeContext::MediumTextDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::MediumTextDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitMediumTextDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TimestampDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::TimestampDataTypeContext::TIMESTAMP() {
  return getToken(MariaDBDDLParser::TIMESTAMP, 0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::TimestampDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

MariaDBDDLParser::TimestampDataTypeContext::TimestampDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::TimestampDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTimestampDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TextDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::TextDataTypeContext::TEXT() {
  return getToken(MariaDBDDLParser::TEXT, 0);
}

MariaDBDDLParser::TextDataTypeContext::TextDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::TextDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTextDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DecimalDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DecimalDataTypeContext::DECIMAL() {
  return getToken(MariaDBDDLParser::DECIMAL, 0);
}

MariaDBDDLParser::TypePrecisionContext* MariaDBDDLParser::DecimalDataTypeContext::typePrecision() {
  return getRuleContext<MariaDBDDLParser::TypePrecisionContext>(0);
}

MariaDBDDLParser::DecimalDataTypeContext::DecimalDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DecimalDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDecimalDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CharDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::CharDataTypeContext::CHAR() {
  return getToken(MariaDBDDLParser::CHAR, 0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::CharDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

MariaDBDDLParser::CharDataTypeContext::CharDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::CharDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCharDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoubleDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DoubleDataTypeContext::DOUBLE() {
  return getToken(MariaDBDDLParser::DOUBLE, 0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::DoubleDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

MariaDBDDLParser::DoubleDataTypeContext::DoubleDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DoubleDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDoubleDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LongBlobDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::LongBlobDataTypeContext::LONGBLOB() {
  return getToken(MariaDBDDLParser::LONGBLOB, 0);
}

MariaDBDDLParser::LongBlobDataTypeContext::LongBlobDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::LongBlobDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitLongBlobDataType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TimeDataTypeContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::TimeDataTypeContext::TIME() {
  return getToken(MariaDBDDLParser::TIME, 0);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::TimeDataTypeContext::typeDimension() {
  return getRuleContext<MariaDBDDLParser::TypeDimensionContext>(0);
}

MariaDBDDLParser::TimeDataTypeContext::TimeDataTypeContext(DataTypeContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::TimeDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTimeDataType(this);
  else
    return visitor->visitChildren(this);
}
MariaDBDDLParser::DataTypeContext* MariaDBDDLParser::dataType() {
  DataTypeContext *_localctx = _tracker.createInstance<DataTypeContext>(_ctx, getState());
  enterRule(_localctx, 16, MariaDBDDLParser::RuleDataType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(248);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MariaDBDDLParser::BIGINT:
      case MariaDBDDLParser::INT:
      case MariaDBDDLParser::INTEGER:
      case MariaDBDDLParser::MEDIUMINT:
      case MariaDBDDLParser::SMALLINT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::IntDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(188);
        intType();
        setState(190);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(189);
          typeDimension();
        }
        setState(193);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          setState(192);
          match(MariaDBDDLParser::UNSIGNED);
          break;
        }

        default:
          break;
        }
        break;
      }

      case MariaDBDDLParser::DECIMAL: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::DecimalDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(195);
        match(MariaDBDDLParser::DECIMAL);
        setState(197);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(196);
          typePrecision();
        }
        break;
      }

      case MariaDBDDLParser::FLOAT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::FloatDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(199);
        match(MariaDBDDLParser::FLOAT);
        setState(201);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(200);
          typeDimension();
        }
        break;
      }

      case MariaDBDDLParser::DOUBLE: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::DoubleDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(203);
        match(MariaDBDDLParser::DOUBLE);
        setState(205);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(204);
          typeDimension();
        }
        break;
      }

      case MariaDBDDLParser::VARCHAR: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::VarcharDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(207);
        match(MariaDBDDLParser::VARCHAR);
        setState(208);
        typeDimension();
        break;
      }

      case MariaDBDDLParser::CHAR: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::CharDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(209);
        match(MariaDBDDLParser::CHAR);
        setState(211);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(210);
          typeDimension();
        }
        break;
      }

      case MariaDBDDLParser::TEXT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::TextDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(213);
        match(MariaDBDDLParser::TEXT);
        break;
      }

      case MariaDBDDLParser::TINYTEXT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::TinyTextDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(214);
        match(MariaDBDDLParser::TINYTEXT);
        break;
      }

      case MariaDBDDLParser::MEDIUMTEXT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::MediumTextDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 9);
        setState(215);
        match(MariaDBDDLParser::MEDIUMTEXT);
        break;
      }

      case MariaDBDDLParser::LONGTEXT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::LongTextDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 10);
        setState(216);
        match(MariaDBDDLParser::LONGTEXT);
        break;
      }

      case MariaDBDDLParser::BLOB: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::BlobDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 11);
        setState(217);
        match(MariaDBDDLParser::BLOB);
        break;
      }

      case MariaDBDDLParser::TINYBLOB: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::TinyBlobDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 12);
        setState(218);
        match(MariaDBDDLParser::TINYBLOB);
        break;
      }

      case MariaDBDDLParser::MEDIUMBLOB: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::MediumBlobDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 13);
        setState(219);
        match(MariaDBDDLParser::MEDIUMBLOB);
        break;
      }

      case MariaDBDDLParser::LONGBLOB: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::LongBlobDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 14);
        setState(220);
        match(MariaDBDDLParser::LONGBLOB);
        break;
      }

      case MariaDBDDLParser::DATE: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::DateDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 15);
        setState(221);
        match(MariaDBDDLParser::DATE);
        break;
      }

      case MariaDBDDLParser::DATETIME: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::DatetimeDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 16);
        setState(222);
        match(MariaDBDDLParser::DATETIME);
        setState(224);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(223);
          typeDimension();
        }
        break;
      }

      case MariaDBDDLParser::TIMESTAMP: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::TimestampDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 17);
        setState(226);
        match(MariaDBDDLParser::TIMESTAMP);
        setState(228);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(227);
          typeDimension();
        }
        break;
      }

      case MariaDBDDLParser::TIME: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::TimeDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 18);
        setState(230);
        match(MariaDBDDLParser::TIME);
        setState(232);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(231);
          typeDimension();
        }
        break;
      }

      case MariaDBDDLParser::BOOLEAN: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::BooleanDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 19);
        setState(234);
        match(MariaDBDDLParser::BOOLEAN);
        break;
      }

      case MariaDBDDLParser::JSON: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::JsonDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 20);
        setState(235);
        match(MariaDBDDLParser::JSON);
        break;
      }

      case MariaDBDDLParser::TINYINT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::TinyintDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 21);
        setState(236);
        match(MariaDBDDLParser::TINYINT);
        setState(238);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::LPAREN) {
          setState(237);
          typeDimension();
        }
        setState(241);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
        case 1: {
          setState(240);
          match(MariaDBDDLParser::UNSIGNED);
          break;
        }

        default:
          break;
        }
        break;
      }

      case MariaDBDDLParser::ENUM: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::EnumDataTypeContext>(_localctx);
        enterOuterAlt(_localctx, 22);
        setState(243);
        match(MariaDBDDLParser::ENUM);
        setState(244);
        match(MariaDBDDLParser::LPAREN);
        setState(245);
        enumValues();
        setState(246);
        match(MariaDBDDLParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntTypeContext ------------------------------------------------------------------

MariaDBDDLParser::IntTypeContext::IntTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::IntTypeContext::INT() {
  return getToken(MariaDBDDLParser::INT, 0);
}

tree::TerminalNode* MariaDBDDLParser::IntTypeContext::INTEGER() {
  return getToken(MariaDBDDLParser::INTEGER, 0);
}

tree::TerminalNode* MariaDBDDLParser::IntTypeContext::BIGINT() {
  return getToken(MariaDBDDLParser::BIGINT, 0);
}

tree::TerminalNode* MariaDBDDLParser::IntTypeContext::SMALLINT() {
  return getToken(MariaDBDDLParser::SMALLINT, 0);
}

tree::TerminalNode* MariaDBDDLParser::IntTypeContext::MEDIUMINT() {
  return getToken(MariaDBDDLParser::MEDIUMINT, 0);
}


size_t MariaDBDDLParser::IntTypeContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleIntType;
}


std::any MariaDBDDLParser::IntTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitIntType(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::IntTypeContext* MariaDBDDLParser::intType() {
  IntTypeContext *_localctx = _tracker.createInstance<IntTypeContext>(_ctx, getState());
  enterRule(_localctx, 18, MariaDBDDLParser::RuleIntType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36033220835278864) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDimensionContext ------------------------------------------------------------------

MariaDBDDLParser::TypeDimensionContext::TypeDimensionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::TypeDimensionContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

tree::TerminalNode* MariaDBDDLParser::TypeDimensionContext::NUMERIC_LITERAL() {
  return getToken(MariaDBDDLParser::NUMERIC_LITERAL, 0);
}

tree::TerminalNode* MariaDBDDLParser::TypeDimensionContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}


size_t MariaDBDDLParser::TypeDimensionContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleTypeDimension;
}


std::any MariaDBDDLParser::TypeDimensionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTypeDimension(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::TypeDimensionContext* MariaDBDDLParser::typeDimension() {
  TypeDimensionContext *_localctx = _tracker.createInstance<TypeDimensionContext>(_ctx, getState());
  enterRule(_localctx, 20, MariaDBDDLParser::RuleTypeDimension);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    match(MariaDBDDLParser::LPAREN);
    setState(253);
    match(MariaDBDDLParser::NUMERIC_LITERAL);
    setState(254);
    match(MariaDBDDLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypePrecisionContext ------------------------------------------------------------------

MariaDBDDLParser::TypePrecisionContext::TypePrecisionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::TypePrecisionContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::TypePrecisionContext::NUMERIC_LITERAL() {
  return getTokens(MariaDBDDLParser::NUMERIC_LITERAL);
}

tree::TerminalNode* MariaDBDDLParser::TypePrecisionContext::NUMERIC_LITERAL(size_t i) {
  return getToken(MariaDBDDLParser::NUMERIC_LITERAL, i);
}

tree::TerminalNode* MariaDBDDLParser::TypePrecisionContext::COMMA() {
  return getToken(MariaDBDDLParser::COMMA, 0);
}

tree::TerminalNode* MariaDBDDLParser::TypePrecisionContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}


size_t MariaDBDDLParser::TypePrecisionContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleTypePrecision;
}


std::any MariaDBDDLParser::TypePrecisionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTypePrecision(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::TypePrecisionContext* MariaDBDDLParser::typePrecision() {
  TypePrecisionContext *_localctx = _tracker.createInstance<TypePrecisionContext>(_ctx, getState());
  enterRule(_localctx, 22, MariaDBDDLParser::RuleTypePrecision);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
    match(MariaDBDDLParser::LPAREN);
    setState(257);
    match(MariaDBDDLParser::NUMERIC_LITERAL);
    setState(258);
    match(MariaDBDDLParser::COMMA);
    setState(259);
    match(MariaDBDDLParser::NUMERIC_LITERAL);
    setState(260);
    match(MariaDBDDLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumValuesContext ------------------------------------------------------------------

MariaDBDDLParser::EnumValuesContext::EnumValuesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::EnumValuesContext::STRING_LITERAL() {
  return getTokens(MariaDBDDLParser::STRING_LITERAL);
}

tree::TerminalNode* MariaDBDDLParser::EnumValuesContext::STRING_LITERAL(size_t i) {
  return getToken(MariaDBDDLParser::STRING_LITERAL, i);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::EnumValuesContext::COMMA() {
  return getTokens(MariaDBDDLParser::COMMA);
}

tree::TerminalNode* MariaDBDDLParser::EnumValuesContext::COMMA(size_t i) {
  return getToken(MariaDBDDLParser::COMMA, i);
}


size_t MariaDBDDLParser::EnumValuesContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleEnumValues;
}


std::any MariaDBDDLParser::EnumValuesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitEnumValues(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::EnumValuesContext* MariaDBDDLParser::enumValues() {
  EnumValuesContext *_localctx = _tracker.createInstance<EnumValuesContext>(_ctx, getState());
  enterRule(_localctx, 24, MariaDBDDLParser::RuleEnumValues);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    match(MariaDBDDLParser::STRING_LITERAL);
    setState(267);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MariaDBDDLParser::COMMA) {
      setState(263);
      match(MariaDBDDLParser::COMMA);
      setState(264);
      match(MariaDBDDLParser::STRING_LITERAL);
      setState(269);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableConstraintContext ------------------------------------------------------------------

MariaDBDDLParser::TableConstraintContext::TableConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MariaDBDDLParser::TableConstraintContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleTableConstraint;
}

void MariaDBDDLParser::TableConstraintContext::copyFrom(TableConstraintContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ForeignKeyConstraintContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::ForeignKeyConstraintContext::FOREIGN() {
  return getToken(MariaDBDDLParser::FOREIGN, 0);
}

tree::TerminalNode* MariaDBDDLParser::ForeignKeyConstraintContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::ForeignKeyConstraintContext::LPAREN() {
  return getTokens(MariaDBDDLParser::LPAREN);
}

tree::TerminalNode* MariaDBDDLParser::ForeignKeyConstraintContext::LPAREN(size_t i) {
  return getToken(MariaDBDDLParser::LPAREN, i);
}

std::vector<MariaDBDDLParser::IndexColumnNamesContext *> MariaDBDDLParser::ForeignKeyConstraintContext::indexColumnNames() {
  return getRuleContexts<MariaDBDDLParser::IndexColumnNamesContext>();
}

MariaDBDDLParser::IndexColumnNamesContext* MariaDBDDLParser::ForeignKeyConstraintContext::indexColumnNames(size_t i) {
  return getRuleContext<MariaDBDDLParser::IndexColumnNamesContext>(i);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::ForeignKeyConstraintContext::RPAREN() {
  return getTokens(MariaDBDDLParser::RPAREN);
}

tree::TerminalNode* MariaDBDDLParser::ForeignKeyConstraintContext::RPAREN(size_t i) {
  return getToken(MariaDBDDLParser::RPAREN, i);
}

tree::TerminalNode* MariaDBDDLParser::ForeignKeyConstraintContext::REFERENCES() {
  return getToken(MariaDBDDLParser::REFERENCES, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::ForeignKeyConstraintContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}

MariaDBDDLParser::ConstraintNameContext* MariaDBDDLParser::ForeignKeyConstraintContext::constraintName() {
  return getRuleContext<MariaDBDDLParser::ConstraintNameContext>(0);
}

MariaDBDDLParser::IndexNameContext* MariaDBDDLParser::ForeignKeyConstraintContext::indexName() {
  return getRuleContext<MariaDBDDLParser::IndexNameContext>(0);
}

MariaDBDDLParser::ReferenceActionsContext* MariaDBDDLParser::ForeignKeyConstraintContext::referenceActions() {
  return getRuleContext<MariaDBDDLParser::ReferenceActionsContext>(0);
}

MariaDBDDLParser::ForeignKeyConstraintContext::ForeignKeyConstraintContext(TableConstraintContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::ForeignKeyConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitForeignKeyConstraint(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IndexConstraintContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::IndexConstraintContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

MariaDBDDLParser::IndexNameContext* MariaDBDDLParser::IndexConstraintContext::indexName() {
  return getRuleContext<MariaDBDDLParser::IndexNameContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::IndexConstraintContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

MariaDBDDLParser::IndexColumnNamesContext* MariaDBDDLParser::IndexConstraintContext::indexColumnNames() {
  return getRuleContext<MariaDBDDLParser::IndexColumnNamesContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::IndexConstraintContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

MariaDBDDLParser::IndexConstraintContext::IndexConstraintContext(TableConstraintContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::IndexConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitIndexConstraint(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UniqueKeyConstraintContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::UniqueKeyConstraintContext::UNIQUE() {
  return getToken(MariaDBDDLParser::UNIQUE, 0);
}

tree::TerminalNode* MariaDBDDLParser::UniqueKeyConstraintContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

MariaDBDDLParser::IndexColumnNamesContext* MariaDBDDLParser::UniqueKeyConstraintContext::indexColumnNames() {
  return getRuleContext<MariaDBDDLParser::IndexColumnNamesContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::UniqueKeyConstraintContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

tree::TerminalNode* MariaDBDDLParser::UniqueKeyConstraintContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

MariaDBDDLParser::IndexNameContext* MariaDBDDLParser::UniqueKeyConstraintContext::indexName() {
  return getRuleContext<MariaDBDDLParser::IndexNameContext>(0);
}

MariaDBDDLParser::UniqueKeyConstraintContext::UniqueKeyConstraintContext(TableConstraintContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::UniqueKeyConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitUniqueKeyConstraint(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryKeyConstraintContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::PrimaryKeyConstraintContext::PRIMARY() {
  return getToken(MariaDBDDLParser::PRIMARY, 0);
}

tree::TerminalNode* MariaDBDDLParser::PrimaryKeyConstraintContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

tree::TerminalNode* MariaDBDDLParser::PrimaryKeyConstraintContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

MariaDBDDLParser::IndexColumnNamesContext* MariaDBDDLParser::PrimaryKeyConstraintContext::indexColumnNames() {
  return getRuleContext<MariaDBDDLParser::IndexColumnNamesContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::PrimaryKeyConstraintContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

MariaDBDDLParser::IndexNameContext* MariaDBDDLParser::PrimaryKeyConstraintContext::indexName() {
  return getRuleContext<MariaDBDDLParser::IndexNameContext>(0);
}

MariaDBDDLParser::PrimaryKeyConstraintContext::PrimaryKeyConstraintContext(TableConstraintContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::PrimaryKeyConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryKeyConstraint(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CheckConstraintContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::CheckConstraintContext::CHECK() {
  return getToken(MariaDBDDLParser::CHECK, 0);
}

tree::TerminalNode* MariaDBDDLParser::CheckConstraintContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

MariaDBDDLParser::ExpressionContext* MariaDBDDLParser::CheckConstraintContext::expression() {
  return getRuleContext<MariaDBDDLParser::ExpressionContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CheckConstraintContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

MariaDBDDLParser::ConstraintNameContext* MariaDBDDLParser::CheckConstraintContext::constraintName() {
  return getRuleContext<MariaDBDDLParser::ConstraintNameContext>(0);
}

MariaDBDDLParser::CheckConstraintContext::CheckConstraintContext(TableConstraintContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::CheckConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCheckConstraint(this);
  else
    return visitor->visitChildren(this);
}
MariaDBDDLParser::TableConstraintContext* MariaDBDDLParser::tableConstraint() {
  TableConstraintContext *_localctx = _tracker.createInstance<TableConstraintContext>(_ctx, getState());
  enterRule(_localctx, 26, MariaDBDDLParser::RuleTableConstraint);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(323);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::PrimaryKeyConstraintContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(270);
      match(MariaDBDDLParser::PRIMARY);
      setState(271);
      match(MariaDBDDLParser::KEY);
      setState(273);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 179018497672771200) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & 6295373) != 0)) {
        setState(272);
        indexName();
      }
      setState(275);
      match(MariaDBDDLParser::LPAREN);
      setState(276);
      indexColumnNames();
      setState(277);
      match(MariaDBDDLParser::RPAREN);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::UniqueKeyConstraintContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(279);
      match(MariaDBDDLParser::UNIQUE);
      setState(281);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
      case 1: {
        setState(280);
        match(MariaDBDDLParser::KEY);
        break;
      }

      default:
        break;
      }
      setState(284);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 179018497672771200) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & 6295373) != 0)) {
        setState(283);
        indexName();
      }
      setState(286);
      match(MariaDBDDLParser::LPAREN);
      setState(287);
      indexColumnNames();
      setState(288);
      match(MariaDBDDLParser::RPAREN);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::IndexConstraintContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(290);
      match(MariaDBDDLParser::KEY);
      setState(291);
      indexName();
      setState(292);
      match(MariaDBDDLParser::LPAREN);
      setState(293);
      indexColumnNames();
      setState(294);
      match(MariaDBDDLParser::RPAREN);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::ForeignKeyConstraintContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(297);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MariaDBDDLParser::CONSTRAINT) {
        setState(296);
        constraintName();
      }
      setState(299);
      match(MariaDBDDLParser::FOREIGN);
      setState(300);
      match(MariaDBDDLParser::KEY);
      setState(302);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 179018497672771200) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & 6295373) != 0)) {
        setState(301);
        indexName();
      }
      setState(304);
      match(MariaDBDDLParser::LPAREN);
      setState(305);
      indexColumnNames();
      setState(306);
      match(MariaDBDDLParser::RPAREN);
      setState(307);
      match(MariaDBDDLParser::REFERENCES);
      setState(308);
      tableName();
      setState(309);
      match(MariaDBDDLParser::LPAREN);
      setState(310);
      indexColumnNames();
      setState(311);
      match(MariaDBDDLParser::RPAREN);
      setState(313);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MariaDBDDLParser::ON) {
        setState(312);
        referenceActions();
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::CheckConstraintContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(316);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MariaDBDDLParser::CONSTRAINT) {
        setState(315);
        constraintName();
      }
      setState(318);
      match(MariaDBDDLParser::CHECK);
      setState(319);
      match(MariaDBDDLParser::LPAREN);
      setState(320);
      expression();
      setState(321);
      match(MariaDBDDLParser::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintNameContext ------------------------------------------------------------------

MariaDBDDLParser::ConstraintNameContext::ConstraintNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::ConstraintNameContext::CONSTRAINT() {
  return getToken(MariaDBDDLParser::CONSTRAINT, 0);
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::ConstraintNameContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}


size_t MariaDBDDLParser::ConstraintNameContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleConstraintName;
}


std::any MariaDBDDLParser::ConstraintNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitConstraintName(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::ConstraintNameContext* MariaDBDDLParser::constraintName() {
  ConstraintNameContext *_localctx = _tracker.createInstance<ConstraintNameContext>(_ctx, getState());
  enterRule(_localctx, 28, MariaDBDDLParser::RuleConstraintName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    match(MariaDBDDLParser::CONSTRAINT);
    setState(326);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexNameContext ------------------------------------------------------------------

MariaDBDDLParser::IndexNameContext::IndexNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::IndexNameContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}


size_t MariaDBDDLParser::IndexNameContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleIndexName;
}


std::any MariaDBDDLParser::IndexNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitIndexName(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::IndexNameContext* MariaDBDDLParser::indexName() {
  IndexNameContext *_localctx = _tracker.createInstance<IndexNameContext>(_ctx, getState());
  enterRule(_localctx, 30, MariaDBDDLParser::RuleIndexName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(328);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexColumnNamesContext ------------------------------------------------------------------

MariaDBDDLParser::IndexColumnNamesContext::IndexColumnNamesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MariaDBDDLParser::ColumnNameContext *> MariaDBDDLParser::IndexColumnNamesContext::columnName() {
  return getRuleContexts<MariaDBDDLParser::ColumnNameContext>();
}

MariaDBDDLParser::ColumnNameContext* MariaDBDDLParser::IndexColumnNamesContext::columnName(size_t i) {
  return getRuleContext<MariaDBDDLParser::ColumnNameContext>(i);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::IndexColumnNamesContext::COMMA() {
  return getTokens(MariaDBDDLParser::COMMA);
}

tree::TerminalNode* MariaDBDDLParser::IndexColumnNamesContext::COMMA(size_t i) {
  return getToken(MariaDBDDLParser::COMMA, i);
}


size_t MariaDBDDLParser::IndexColumnNamesContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleIndexColumnNames;
}


std::any MariaDBDDLParser::IndexColumnNamesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitIndexColumnNames(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::IndexColumnNamesContext* MariaDBDDLParser::indexColumnNames() {
  IndexColumnNamesContext *_localctx = _tracker.createInstance<IndexColumnNamesContext>(_ctx, getState());
  enterRule(_localctx, 32, MariaDBDDLParser::RuleIndexColumnNames);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(330);
    columnName();
    setState(335);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MariaDBDDLParser::COMMA) {
      setState(331);
      match(MariaDBDDLParser::COMMA);
      setState(332);
      columnName();
      setState(337);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReferenceActionsContext ------------------------------------------------------------------

MariaDBDDLParser::ReferenceActionsContext::ReferenceActionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MariaDBDDLParser::OnDeleteContext* MariaDBDDLParser::ReferenceActionsContext::onDelete() {
  return getRuleContext<MariaDBDDLParser::OnDeleteContext>(0);
}

MariaDBDDLParser::OnUpdateContext* MariaDBDDLParser::ReferenceActionsContext::onUpdate() {
  return getRuleContext<MariaDBDDLParser::OnUpdateContext>(0);
}


size_t MariaDBDDLParser::ReferenceActionsContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleReferenceActions;
}


std::any MariaDBDDLParser::ReferenceActionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitReferenceActions(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::ReferenceActionsContext* MariaDBDDLParser::referenceActions() {
  ReferenceActionsContext *_localctx = _tracker.createInstance<ReferenceActionsContext>(_ctx, getState());
  enterRule(_localctx, 34, MariaDBDDLParser::RuleReferenceActions);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(346);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(338);
      onDelete();
      setState(340);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MariaDBDDLParser::ON) {
        setState(339);
        onUpdate();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(342);
      onUpdate();
      setState(344);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MariaDBDDLParser::ON) {
        setState(343);
        onDelete();
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OnDeleteContext ------------------------------------------------------------------

MariaDBDDLParser::OnDeleteContext::OnDeleteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::OnDeleteContext::ON() {
  return getToken(MariaDBDDLParser::ON, 0);
}

tree::TerminalNode* MariaDBDDLParser::OnDeleteContext::DELETE() {
  return getToken(MariaDBDDLParser::DELETE, 0);
}

MariaDBDDLParser::ReferenceActionContext* MariaDBDDLParser::OnDeleteContext::referenceAction() {
  return getRuleContext<MariaDBDDLParser::ReferenceActionContext>(0);
}


size_t MariaDBDDLParser::OnDeleteContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleOnDelete;
}


std::any MariaDBDDLParser::OnDeleteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitOnDelete(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::OnDeleteContext* MariaDBDDLParser::onDelete() {
  OnDeleteContext *_localctx = _tracker.createInstance<OnDeleteContext>(_ctx, getState());
  enterRule(_localctx, 36, MariaDBDDLParser::RuleOnDelete);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(348);
    match(MariaDBDDLParser::ON);
    setState(349);
    match(MariaDBDDLParser::DELETE);
    setState(350);
    referenceAction();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OnUpdateContext ------------------------------------------------------------------

MariaDBDDLParser::OnUpdateContext::OnUpdateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::OnUpdateContext::ON() {
  return getToken(MariaDBDDLParser::ON, 0);
}

tree::TerminalNode* MariaDBDDLParser::OnUpdateContext::UPDATE() {
  return getToken(MariaDBDDLParser::UPDATE, 0);
}

MariaDBDDLParser::ReferenceActionContext* MariaDBDDLParser::OnUpdateContext::referenceAction() {
  return getRuleContext<MariaDBDDLParser::ReferenceActionContext>(0);
}


size_t MariaDBDDLParser::OnUpdateContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleOnUpdate;
}


std::any MariaDBDDLParser::OnUpdateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitOnUpdate(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::OnUpdateContext* MariaDBDDLParser::onUpdate() {
  OnUpdateContext *_localctx = _tracker.createInstance<OnUpdateContext>(_ctx, getState());
  enterRule(_localctx, 38, MariaDBDDLParser::RuleOnUpdate);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    match(MariaDBDDLParser::ON);
    setState(353);
    match(MariaDBDDLParser::UPDATE);
    setState(354);
    referenceAction();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReferenceActionContext ------------------------------------------------------------------

MariaDBDDLParser::ReferenceActionContext::ReferenceActionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::ReferenceActionContext::CASCADE() {
  return getToken(MariaDBDDLParser::CASCADE, 0);
}

tree::TerminalNode* MariaDBDDLParser::ReferenceActionContext::SET() {
  return getToken(MariaDBDDLParser::SET, 0);
}

tree::TerminalNode* MariaDBDDLParser::ReferenceActionContext::NULL_() {
  return getToken(MariaDBDDLParser::NULL_, 0);
}

tree::TerminalNode* MariaDBDDLParser::ReferenceActionContext::DEFAULT() {
  return getToken(MariaDBDDLParser::DEFAULT, 0);
}

tree::TerminalNode* MariaDBDDLParser::ReferenceActionContext::RESTRICT() {
  return getToken(MariaDBDDLParser::RESTRICT, 0);
}

tree::TerminalNode* MariaDBDDLParser::ReferenceActionContext::NO() {
  return getToken(MariaDBDDLParser::NO, 0);
}

tree::TerminalNode* MariaDBDDLParser::ReferenceActionContext::ACTION() {
  return getToken(MariaDBDDLParser::ACTION, 0);
}


size_t MariaDBDDLParser::ReferenceActionContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleReferenceAction;
}


std::any MariaDBDDLParser::ReferenceActionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitReferenceAction(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::ReferenceActionContext* MariaDBDDLParser::referenceAction() {
  ReferenceActionContext *_localctx = _tracker.createInstance<ReferenceActionContext>(_ctx, getState());
  enterRule(_localctx, 40, MariaDBDDLParser::RuleReferenceAction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(364);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(356);
      match(MariaDBDDLParser::CASCADE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(357);
      match(MariaDBDDLParser::SET);
      setState(358);
      match(MariaDBDDLParser::NULL_);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(359);
      match(MariaDBDDLParser::SET);
      setState(360);
      match(MariaDBDDLParser::DEFAULT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(361);
      match(MariaDBDDLParser::RESTRICT);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(362);
      match(MariaDBDDLParser::NO);
      setState(363);
      match(MariaDBDDLParser::ACTION);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableOptionsContext ------------------------------------------------------------------

MariaDBDDLParser::TableOptionsContext::TableOptionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MariaDBDDLParser::TableOptionContext *> MariaDBDDLParser::TableOptionsContext::tableOption() {
  return getRuleContexts<MariaDBDDLParser::TableOptionContext>();
}

MariaDBDDLParser::TableOptionContext* MariaDBDDLParser::TableOptionsContext::tableOption(size_t i) {
  return getRuleContext<MariaDBDDLParser::TableOptionContext>(i);
}


size_t MariaDBDDLParser::TableOptionsContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleTableOptions;
}


std::any MariaDBDDLParser::TableOptionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTableOptions(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::TableOptionsContext* MariaDBDDLParser::tableOptions() {
  TableOptionsContext *_localctx = _tracker.createInstance<TableOptionsContext>(_ctx, getState());
  enterRule(_localctx, 42, MariaDBDDLParser::RuleTableOptions);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(367); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(366);
      tableOption();
      setState(369); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 35673608) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableOptionContext ------------------------------------------------------------------

MariaDBDDLParser::TableOptionContext::TableOptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MariaDBDDLParser::TableOptionContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleTableOption;
}

void MariaDBDDLParser::TableOptionContext::copyFrom(TableOptionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EngineOptionContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::EngineOptionContext::ENGINE() {
  return getToken(MariaDBDDLParser::ENGINE, 0);
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::EngineOptionContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::EngineOptionContext::EQ() {
  return getToken(MariaDBDDLParser::EQ, 0);
}

MariaDBDDLParser::EngineOptionContext::EngineOptionContext(TableOptionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::EngineOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitEngineOption(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CharsetOptionContext ------------------------------------------------------------------

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::CharsetOptionContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CharsetOptionContext::CHARSET() {
  return getToken(MariaDBDDLParser::CHARSET, 0);
}

tree::TerminalNode* MariaDBDDLParser::CharsetOptionContext::CHARACTER() {
  return getToken(MariaDBDDLParser::CHARACTER, 0);
}

tree::TerminalNode* MariaDBDDLParser::CharsetOptionContext::SET() {
  return getToken(MariaDBDDLParser::SET, 0);
}

tree::TerminalNode* MariaDBDDLParser::CharsetOptionContext::DEFAULT() {
  return getToken(MariaDBDDLParser::DEFAULT, 0);
}

tree::TerminalNode* MariaDBDDLParser::CharsetOptionContext::EQ() {
  return getToken(MariaDBDDLParser::EQ, 0);
}

MariaDBDDLParser::CharsetOptionContext::CharsetOptionContext(TableOptionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::CharsetOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCharsetOption(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AutoIncrOptionContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::AutoIncrOptionContext::AUTO_INCREMENT() {
  return getToken(MariaDBDDLParser::AUTO_INCREMENT, 0);
}

tree::TerminalNode* MariaDBDDLParser::AutoIncrOptionContext::NUMERIC_LITERAL() {
  return getToken(MariaDBDDLParser::NUMERIC_LITERAL, 0);
}

tree::TerminalNode* MariaDBDDLParser::AutoIncrOptionContext::EQ() {
  return getToken(MariaDBDDLParser::EQ, 0);
}

MariaDBDDLParser::AutoIncrOptionContext::AutoIncrOptionContext(TableOptionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::AutoIncrOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitAutoIncrOption(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CommentOptionContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::CommentOptionContext::COMMENT() {
  return getToken(MariaDBDDLParser::COMMENT, 0);
}

tree::TerminalNode* MariaDBDDLParser::CommentOptionContext::STRING_LITERAL() {
  return getToken(MariaDBDDLParser::STRING_LITERAL, 0);
}

tree::TerminalNode* MariaDBDDLParser::CommentOptionContext::EQ() {
  return getToken(MariaDBDDLParser::EQ, 0);
}

MariaDBDDLParser::CommentOptionContext::CommentOptionContext(TableOptionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::CommentOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCommentOption(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CollateOptionContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::CollateOptionContext::COLLATE() {
  return getToken(MariaDBDDLParser::COLLATE, 0);
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::CollateOptionContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CollateOptionContext::EQ() {
  return getToken(MariaDBDDLParser::EQ, 0);
}

MariaDBDDLParser::CollateOptionContext::CollateOptionContext(TableOptionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::CollateOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCollateOption(this);
  else
    return visitor->visitChildren(this);
}
MariaDBDDLParser::TableOptionContext* MariaDBDDLParser::tableOption() {
  TableOptionContext *_localctx = _tracker.createInstance<TableOptionContext>(_ctx, getState());
  enterRule(_localctx, 44, MariaDBDDLParser::RuleTableOption);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(403);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MariaDBDDLParser::ENGINE: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::EngineOptionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(371);
        match(MariaDBDDLParser::ENGINE);
        setState(373);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::EQ) {
          setState(372);
          match(MariaDBDDLParser::EQ);
        }
        setState(375);
        identifier();
        break;
      }

      case MariaDBDDLParser::CHARACTER:
      case MariaDBDDLParser::CHARSET:
      case MariaDBDDLParser::DEFAULT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::CharsetOptionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(377);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::DEFAULT) {
          setState(376);
          match(MariaDBDDLParser::DEFAULT);
        }
        setState(382);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case MariaDBDDLParser::CHARSET: {
            setState(379);
            match(MariaDBDDLParser::CHARSET);
            break;
          }

          case MariaDBDDLParser::CHARACTER: {
            setState(380);
            match(MariaDBDDLParser::CHARACTER);
            setState(381);
            match(MariaDBDDLParser::SET);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(385);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::EQ) {
          setState(384);
          match(MariaDBDDLParser::EQ);
        }
        setState(387);
        identifier();
        break;
      }

      case MariaDBDDLParser::COLLATE: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::CollateOptionContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(388);
        match(MariaDBDDLParser::COLLATE);
        setState(390);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::EQ) {
          setState(389);
          match(MariaDBDDLParser::EQ);
        }
        setState(392);
        identifier();
        break;
      }

      case MariaDBDDLParser::AUTO_INCREMENT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::AutoIncrOptionContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(393);
        match(MariaDBDDLParser::AUTO_INCREMENT);
        setState(395);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::EQ) {
          setState(394);
          match(MariaDBDDLParser::EQ);
        }
        setState(397);
        match(MariaDBDDLParser::NUMERIC_LITERAL);
        break;
      }

      case MariaDBDDLParser::COMMENT: {
        _localctx = _tracker.createInstance<MariaDBDDLParser::CommentOptionContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(398);
        match(MariaDBDDLParser::COMMENT);
        setState(400);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MariaDBDDLParser::EQ) {
          setState(399);
          match(MariaDBDDLParser::EQ);
        }
        setState(402);
        match(MariaDBDDLParser::STRING_LITERAL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropTableContext ------------------------------------------------------------------

MariaDBDDLParser::DropTableContext::DropTableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::DropTableContext::DROP() {
  return getToken(MariaDBDDLParser::DROP, 0);
}

tree::TerminalNode* MariaDBDDLParser::DropTableContext::TABLE() {
  return getToken(MariaDBDDLParser::TABLE, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::DropTableContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}

MariaDBDDLParser::IfExistsContext* MariaDBDDLParser::DropTableContext::ifExists() {
  return getRuleContext<MariaDBDDLParser::IfExistsContext>(0);
}


size_t MariaDBDDLParser::DropTableContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleDropTable;
}


std::any MariaDBDDLParser::DropTableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDropTable(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::DropTableContext* MariaDBDDLParser::dropTable() {
  DropTableContext *_localctx = _tracker.createInstance<DropTableContext>(_ctx, getState());
  enterRule(_localctx, 46, MariaDBDDLParser::RuleDropTable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(405);
    match(MariaDBDDLParser::DROP);
    setState(406);
    match(MariaDBDDLParser::TABLE);
    setState(408);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MariaDBDDLParser::IF) {
      setState(407);
      ifExists();
    }
    setState(410);
    tableName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfExistsContext ------------------------------------------------------------------

MariaDBDDLParser::IfExistsContext::IfExistsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::IfExistsContext::IF() {
  return getToken(MariaDBDDLParser::IF, 0);
}

tree::TerminalNode* MariaDBDDLParser::IfExistsContext::EXISTS() {
  return getToken(MariaDBDDLParser::EXISTS, 0);
}


size_t MariaDBDDLParser::IfExistsContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleIfExists;
}


std::any MariaDBDDLParser::IfExistsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitIfExists(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::IfExistsContext* MariaDBDDLParser::ifExists() {
  IfExistsContext *_localctx = _tracker.createInstance<IfExistsContext>(_ctx, getState());
  enterRule(_localctx, 48, MariaDBDDLParser::RuleIfExists);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(412);
    match(MariaDBDDLParser::IF);
    setState(413);
    match(MariaDBDDLParser::EXISTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateIndexContext ------------------------------------------------------------------

MariaDBDDLParser::CreateIndexContext::CreateIndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::CreateIndexContext::CREATE() {
  return getToken(MariaDBDDLParser::CREATE, 0);
}

tree::TerminalNode* MariaDBDDLParser::CreateIndexContext::INDEX() {
  return getToken(MariaDBDDLParser::INDEX, 0);
}

MariaDBDDLParser::IndexNameContext* MariaDBDDLParser::CreateIndexContext::indexName() {
  return getRuleContext<MariaDBDDLParser::IndexNameContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CreateIndexContext::ON() {
  return getToken(MariaDBDDLParser::ON, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::CreateIndexContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CreateIndexContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

MariaDBDDLParser::IndexColumnNamesContext* MariaDBDDLParser::CreateIndexContext::indexColumnNames() {
  return getRuleContext<MariaDBDDLParser::IndexColumnNamesContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CreateIndexContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

tree::TerminalNode* MariaDBDDLParser::CreateIndexContext::UNIQUE() {
  return getToken(MariaDBDDLParser::UNIQUE, 0);
}


size_t MariaDBDDLParser::CreateIndexContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleCreateIndex;
}


std::any MariaDBDDLParser::CreateIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCreateIndex(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::CreateIndexContext* MariaDBDDLParser::createIndex() {
  CreateIndexContext *_localctx = _tracker.createInstance<CreateIndexContext>(_ctx, getState());
  enterRule(_localctx, 50, MariaDBDDLParser::RuleCreateIndex);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(415);
    match(MariaDBDDLParser::CREATE);
    setState(417);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MariaDBDDLParser::UNIQUE) {
      setState(416);
      match(MariaDBDDLParser::UNIQUE);
    }
    setState(419);
    match(MariaDBDDLParser::INDEX);
    setState(420);
    indexName();
    setState(421);
    match(MariaDBDDLParser::ON);
    setState(422);
    tableName();
    setState(423);
    match(MariaDBDDLParser::LPAREN);
    setState(424);
    indexColumnNames();
    setState(425);
    match(MariaDBDDLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropIndexContext ------------------------------------------------------------------

MariaDBDDLParser::DropIndexContext::DropIndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::DropIndexContext::DROP() {
  return getToken(MariaDBDDLParser::DROP, 0);
}

tree::TerminalNode* MariaDBDDLParser::DropIndexContext::INDEX() {
  return getToken(MariaDBDDLParser::INDEX, 0);
}

MariaDBDDLParser::IndexNameContext* MariaDBDDLParser::DropIndexContext::indexName() {
  return getRuleContext<MariaDBDDLParser::IndexNameContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::DropIndexContext::ON() {
  return getToken(MariaDBDDLParser::ON, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::DropIndexContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}


size_t MariaDBDDLParser::DropIndexContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleDropIndex;
}


std::any MariaDBDDLParser::DropIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDropIndex(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::DropIndexContext* MariaDBDDLParser::dropIndex() {
  DropIndexContext *_localctx = _tracker.createInstance<DropIndexContext>(_ctx, getState());
  enterRule(_localctx, 52, MariaDBDDLParser::RuleDropIndex);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    match(MariaDBDDLParser::DROP);
    setState(428);
    match(MariaDBDDLParser::INDEX);
    setState(429);
    indexName();
    setState(430);
    match(MariaDBDDLParser::ON);
    setState(431);
    tableName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlterTableContext ------------------------------------------------------------------

MariaDBDDLParser::AlterTableContext::AlterTableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::AlterTableContext::ALTER() {
  return getToken(MariaDBDDLParser::ALTER, 0);
}

tree::TerminalNode* MariaDBDDLParser::AlterTableContext::TABLE() {
  return getToken(MariaDBDDLParser::TABLE, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::AlterTableContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}

std::vector<MariaDBDDLParser::AlterActionContext *> MariaDBDDLParser::AlterTableContext::alterAction() {
  return getRuleContexts<MariaDBDDLParser::AlterActionContext>();
}

MariaDBDDLParser::AlterActionContext* MariaDBDDLParser::AlterTableContext::alterAction(size_t i) {
  return getRuleContext<MariaDBDDLParser::AlterActionContext>(i);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::AlterTableContext::COMMA() {
  return getTokens(MariaDBDDLParser::COMMA);
}

tree::TerminalNode* MariaDBDDLParser::AlterTableContext::COMMA(size_t i) {
  return getToken(MariaDBDDLParser::COMMA, i);
}


size_t MariaDBDDLParser::AlterTableContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleAlterTable;
}


std::any MariaDBDDLParser::AlterTableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitAlterTable(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::AlterTableContext* MariaDBDDLParser::alterTable() {
  AlterTableContext *_localctx = _tracker.createInstance<AlterTableContext>(_ctx, getState());
  enterRule(_localctx, 54, MariaDBDDLParser::RuleAlterTable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(433);
    match(MariaDBDDLParser::ALTER);
    setState(434);
    match(MariaDBDDLParser::TABLE);
    setState(435);
    tableName();
    setState(436);
    alterAction();
    setState(441);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MariaDBDDLParser::COMMA) {
      setState(437);
      match(MariaDBDDLParser::COMMA);
      setState(438);
      alterAction();
      setState(443);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlterActionContext ------------------------------------------------------------------

MariaDBDDLParser::AlterActionContext::AlterActionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MariaDBDDLParser::AlterActionContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleAlterAction;
}

void MariaDBDDLParser::AlterActionContext::copyFrom(AlterActionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AddColumnContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::AddColumnContext::ADD() {
  return getToken(MariaDBDDLParser::ADD, 0);
}

MariaDBDDLParser::ColumnDefinitionContext* MariaDBDDLParser::AddColumnContext::columnDefinition() {
  return getRuleContext<MariaDBDDLParser::ColumnDefinitionContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::AddColumnContext::COLUMN() {
  return getToken(MariaDBDDLParser::COLUMN, 0);
}

MariaDBDDLParser::AddColumnContext::AddColumnContext(AlterActionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::AddColumnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitAddColumn(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropForeignKeyContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DropForeignKeyContext::DROP() {
  return getToken(MariaDBDDLParser::DROP, 0);
}

tree::TerminalNode* MariaDBDDLParser::DropForeignKeyContext::FOREIGN() {
  return getToken(MariaDBDDLParser::FOREIGN, 0);
}

tree::TerminalNode* MariaDBDDLParser::DropForeignKeyContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::DropForeignKeyContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}

MariaDBDDLParser::DropForeignKeyContext::DropForeignKeyContext(AlterActionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DropForeignKeyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDropForeignKey(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropIndexAltContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DropIndexAltContext::DROP() {
  return getToken(MariaDBDDLParser::DROP, 0);
}

tree::TerminalNode* MariaDBDDLParser::DropIndexAltContext::INDEX() {
  return getToken(MariaDBDDLParser::INDEX, 0);
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::DropIndexAltContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}

MariaDBDDLParser::DropIndexAltContext::DropIndexAltContext(AlterActionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DropIndexAltContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDropIndexAlt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddConstraintContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::AddConstraintContext::ADD() {
  return getToken(MariaDBDDLParser::ADD, 0);
}

MariaDBDDLParser::TableConstraintContext* MariaDBDDLParser::AddConstraintContext::tableConstraint() {
  return getRuleContext<MariaDBDDLParser::TableConstraintContext>(0);
}

MariaDBDDLParser::AddConstraintContext::AddConstraintContext(AlterActionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::AddConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitAddConstraint(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropPrimaryKeyContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DropPrimaryKeyContext::DROP() {
  return getToken(MariaDBDDLParser::DROP, 0);
}

tree::TerminalNode* MariaDBDDLParser::DropPrimaryKeyContext::PRIMARY() {
  return getToken(MariaDBDDLParser::PRIMARY, 0);
}

tree::TerminalNode* MariaDBDDLParser::DropPrimaryKeyContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

MariaDBDDLParser::DropPrimaryKeyContext::DropPrimaryKeyContext(AlterActionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DropPrimaryKeyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDropPrimaryKey(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RenameTableContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::RenameTableContext::RENAME() {
  return getToken(MariaDBDDLParser::RENAME, 0);
}

tree::TerminalNode* MariaDBDDLParser::RenameTableContext::TO() {
  return getToken(MariaDBDDLParser::TO, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::RenameTableContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}

MariaDBDDLParser::RenameTableContext::RenameTableContext(AlterActionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::RenameTableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitRenameTable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropColumnContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::DropColumnContext::DROP() {
  return getToken(MariaDBDDLParser::DROP, 0);
}

MariaDBDDLParser::ColumnNameContext* MariaDBDDLParser::DropColumnContext::columnName() {
  return getRuleContext<MariaDBDDLParser::ColumnNameContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::DropColumnContext::COLUMN() {
  return getToken(MariaDBDDLParser::COLUMN, 0);
}

MariaDBDDLParser::DropColumnContext::DropColumnContext(AlterActionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::DropColumnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitDropColumn(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ModifyColumnContext ------------------------------------------------------------------

tree::TerminalNode* MariaDBDDLParser::ModifyColumnContext::MODIFY() {
  return getToken(MariaDBDDLParser::MODIFY, 0);
}

MariaDBDDLParser::ColumnDefinitionContext* MariaDBDDLParser::ModifyColumnContext::columnDefinition() {
  return getRuleContext<MariaDBDDLParser::ColumnDefinitionContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::ModifyColumnContext::COLUMN() {
  return getToken(MariaDBDDLParser::COLUMN, 0);
}

MariaDBDDLParser::ModifyColumnContext::ModifyColumnContext(AlterActionContext *ctx) { copyFrom(ctx); }


std::any MariaDBDDLParser::ModifyColumnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitModifyColumn(this);
  else
    return visitor->visitChildren(this);
}
MariaDBDDLParser::AlterActionContext* MariaDBDDLParser::alterAction() {
  AlterActionContext *_localctx = _tracker.createInstance<AlterActionContext>(_ctx, getState());
  enterRule(_localctx, 56, MariaDBDDLParser::RuleAlterAction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(474);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::AddColumnContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(444);
      match(MariaDBDDLParser::ADD);
      setState(446);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
      case 1: {
        setState(445);
        match(MariaDBDDLParser::COLUMN);
        break;
      }

      default:
        break;
      }
      setState(448);
      columnDefinition();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::DropColumnContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(449);
      match(MariaDBDDLParser::DROP);
      setState(451);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
      case 1: {
        setState(450);
        match(MariaDBDDLParser::COLUMN);
        break;
      }

      default:
        break;
      }
      setState(453);
      columnName();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::ModifyColumnContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(454);
      match(MariaDBDDLParser::MODIFY);
      setState(456);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
      case 1: {
        setState(455);
        match(MariaDBDDLParser::COLUMN);
        break;
      }

      default:
        break;
      }
      setState(458);
      columnDefinition();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::AddConstraintContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(459);
      match(MariaDBDDLParser::ADD);
      setState(460);
      tableConstraint();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::DropPrimaryKeyContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(461);
      match(MariaDBDDLParser::DROP);
      setState(462);
      match(MariaDBDDLParser::PRIMARY);
      setState(463);
      match(MariaDBDDLParser::KEY);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::DropForeignKeyContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(464);
      match(MariaDBDDLParser::DROP);
      setState(465);
      match(MariaDBDDLParser::FOREIGN);
      setState(466);
      match(MariaDBDDLParser::KEY);
      setState(467);
      identifier();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::DropIndexAltContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(468);
      match(MariaDBDDLParser::DROP);
      setState(469);
      match(MariaDBDDLParser::INDEX);
      setState(470);
      identifier();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<MariaDBDDLParser::RenameTableContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(471);
      match(MariaDBDDLParser::RENAME);
      setState(472);
      match(MariaDBDDLParser::TO);
      setState(473);
      tableName();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateDatabaseContext ------------------------------------------------------------------

MariaDBDDLParser::CreateDatabaseContext::CreateDatabaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::CreateDatabaseContext::CREATE() {
  return getToken(MariaDBDDLParser::CREATE, 0);
}

tree::TerminalNode* MariaDBDDLParser::CreateDatabaseContext::DATABASE() {
  return getToken(MariaDBDDLParser::DATABASE, 0);
}

std::vector<MariaDBDDLParser::IdentifierContext *> MariaDBDDLParser::CreateDatabaseContext::identifier() {
  return getRuleContexts<MariaDBDDLParser::IdentifierContext>();
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::CreateDatabaseContext::identifier(size_t i) {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(i);
}

MariaDBDDLParser::IfNotExistsContext* MariaDBDDLParser::CreateDatabaseContext::ifNotExists() {
  return getRuleContext<MariaDBDDLParser::IfNotExistsContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CreateDatabaseContext::CHARSET() {
  return getToken(MariaDBDDLParser::CHARSET, 0);
}

tree::TerminalNode* MariaDBDDLParser::CreateDatabaseContext::CHARACTER() {
  return getToken(MariaDBDDLParser::CHARACTER, 0);
}

tree::TerminalNode* MariaDBDDLParser::CreateDatabaseContext::SET() {
  return getToken(MariaDBDDLParser::SET, 0);
}

tree::TerminalNode* MariaDBDDLParser::CreateDatabaseContext::DEFAULT() {
  return getToken(MariaDBDDLParser::DEFAULT, 0);
}

tree::TerminalNode* MariaDBDDLParser::CreateDatabaseContext::EQ() {
  return getToken(MariaDBDDLParser::EQ, 0);
}


size_t MariaDBDDLParser::CreateDatabaseContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleCreateDatabase;
}


std::any MariaDBDDLParser::CreateDatabaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCreateDatabase(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::CreateDatabaseContext* MariaDBDDLParser::createDatabase() {
  CreateDatabaseContext *_localctx = _tracker.createInstance<CreateDatabaseContext>(_ctx, getState());
  enterRule(_localctx, 58, MariaDBDDLParser::RuleCreateDatabase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(476);
    match(MariaDBDDLParser::CREATE);
    setState(477);
    match(MariaDBDDLParser::DATABASE);
    setState(479);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MariaDBDDLParser::IF) {
      setState(478);
      ifNotExists();
    }
    setState(481);
    identifier();
    setState(494);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2098688) != 0)) {
      setState(483);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MariaDBDDLParser::DEFAULT) {
        setState(482);
        match(MariaDBDDLParser::DEFAULT);
      }
      setState(488);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case MariaDBDDLParser::CHARSET: {
          setState(485);
          match(MariaDBDDLParser::CHARSET);
          break;
        }

        case MariaDBDDLParser::CHARACTER: {
          setState(486);
          match(MariaDBDDLParser::CHARACTER);
          setState(487);
          match(MariaDBDDLParser::SET);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(491);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MariaDBDDLParser::EQ) {
        setState(490);
        match(MariaDBDDLParser::EQ);
      }
      setState(493);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UseDatabaseContext ------------------------------------------------------------------

MariaDBDDLParser::UseDatabaseContext::UseDatabaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::UseDatabaseContext::USE() {
  return getToken(MariaDBDDLParser::USE, 0);
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::UseDatabaseContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}


size_t MariaDBDDLParser::UseDatabaseContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleUseDatabase;
}


std::any MariaDBDDLParser::UseDatabaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitUseDatabase(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::UseDatabaseContext* MariaDBDDLParser::useDatabase() {
  UseDatabaseContext *_localctx = _tracker.createInstance<UseDatabaseContext>(_ctx, getState());
  enterRule(_localctx, 60, MariaDBDDLParser::RuleUseDatabase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(496);
    match(MariaDBDDLParser::USE);
    setState(497);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetStatementContext ------------------------------------------------------------------

MariaDBDDLParser::SetStatementContext::SetStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::SetStatementContext::SET() {
  return getToken(MariaDBDDLParser::SET, 0);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::SetStatementContext::SEMI() {
  return getTokens(MariaDBDDLParser::SEMI);
}

tree::TerminalNode* MariaDBDDLParser::SetStatementContext::SEMI(size_t i) {
  return getToken(MariaDBDDLParser::SEMI, i);
}


size_t MariaDBDDLParser::SetStatementContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleSetStatement;
}


std::any MariaDBDDLParser::SetStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitSetStatement(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::SetStatementContext* MariaDBDDLParser::setStatement() {
  SetStatementContext *_localctx = _tracker.createInstance<SetStatementContext>(_ctx, getState());
  enterRule(_localctx, 62, MariaDBDDLParser::RuleSetStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(499);
    match(MariaDBDDLParser::SET);
    setState(503);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(500);
        _la = _input->LA(1);
        if (_la == 0 || _la == Token::EOF || (_la == MariaDBDDLParser::SEMI)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        } 
      }
      setState(505);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LockStatementContext ------------------------------------------------------------------

MariaDBDDLParser::LockStatementContext::LockStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::LockStatementContext::LOCK() {
  return getToken(MariaDBDDLParser::LOCK, 0);
}

tree::TerminalNode* MariaDBDDLParser::LockStatementContext::TABLES() {
  return getToken(MariaDBDDLParser::TABLES, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::LockStatementContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::LockStatementContext::WRITE() {
  return getToken(MariaDBDDLParser::WRITE, 0);
}

tree::TerminalNode* MariaDBDDLParser::LockStatementContext::READ() {
  return getToken(MariaDBDDLParser::READ, 0);
}


size_t MariaDBDDLParser::LockStatementContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleLockStatement;
}


std::any MariaDBDDLParser::LockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitLockStatement(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::LockStatementContext* MariaDBDDLParser::lockStatement() {
  LockStatementContext *_localctx = _tracker.createInstance<LockStatementContext>(_ctx, getState());
  enterRule(_localctx, 64, MariaDBDDLParser::RuleLockStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(506);
    match(MariaDBDDLParser::LOCK);
    setState(507);
    match(MariaDBDDLParser::TABLES);
    setState(508);
    tableName();
    setState(509);
    _la = _input->LA(1);
    if (!(_la == MariaDBDDLParser::WRITE

    || _la == MariaDBDDLParser::READ)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnlockStatementContext ------------------------------------------------------------------

MariaDBDDLParser::UnlockStatementContext::UnlockStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::UnlockStatementContext::UNLOCK() {
  return getToken(MariaDBDDLParser::UNLOCK, 0);
}

tree::TerminalNode* MariaDBDDLParser::UnlockStatementContext::TABLES() {
  return getToken(MariaDBDDLParser::TABLES, 0);
}


size_t MariaDBDDLParser::UnlockStatementContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleUnlockStatement;
}


std::any MariaDBDDLParser::UnlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitUnlockStatement(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::UnlockStatementContext* MariaDBDDLParser::unlockStatement() {
  UnlockStatementContext *_localctx = _tracker.createInstance<UnlockStatementContext>(_ctx, getState());
  enterRule(_localctx, 66, MariaDBDDLParser::RuleUnlockStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(511);
    match(MariaDBDDLParser::UNLOCK);
    setState(512);
    match(MariaDBDDLParser::TABLES);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertStatementContext ------------------------------------------------------------------

MariaDBDDLParser::InsertStatementContext::InsertStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::InsertStatementContext::INSERT() {
  return getToken(MariaDBDDLParser::INSERT, 0);
}

tree::TerminalNode* MariaDBDDLParser::InsertStatementContext::INTO() {
  return getToken(MariaDBDDLParser::INTO, 0);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::InsertStatementContext::tableName() {
  return getRuleContext<MariaDBDDLParser::TableNameContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::InsertStatementContext::VALUES() {
  return getToken(MariaDBDDLParser::VALUES, 0);
}

tree::TerminalNode* MariaDBDDLParser::InsertStatementContext::LPAREN() {
  return getToken(MariaDBDDLParser::LPAREN, 0);
}

MariaDBDDLParser::IndexColumnNamesContext* MariaDBDDLParser::InsertStatementContext::indexColumnNames() {
  return getRuleContext<MariaDBDDLParser::IndexColumnNamesContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::InsertStatementContext::RPAREN() {
  return getToken(MariaDBDDLParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::InsertStatementContext::SEMI() {
  return getTokens(MariaDBDDLParser::SEMI);
}

tree::TerminalNode* MariaDBDDLParser::InsertStatementContext::SEMI(size_t i) {
  return getToken(MariaDBDDLParser::SEMI, i);
}


size_t MariaDBDDLParser::InsertStatementContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleInsertStatement;
}


std::any MariaDBDDLParser::InsertStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitInsertStatement(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::InsertStatementContext* MariaDBDDLParser::insertStatement() {
  InsertStatementContext *_localctx = _tracker.createInstance<InsertStatementContext>(_ctx, getState());
  enterRule(_localctx, 68, MariaDBDDLParser::RuleInsertStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(514);
    match(MariaDBDDLParser::INSERT);
    setState(515);
    match(MariaDBDDLParser::INTO);
    setState(516);
    tableName();
    setState(521);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MariaDBDDLParser::LPAREN) {
      setState(517);
      match(MariaDBDDLParser::LPAREN);
      setState(518);
      indexColumnNames();
      setState(519);
      match(MariaDBDDLParser::RPAREN);
    }
    setState(523);
    match(MariaDBDDLParser::VALUES);
    setState(527);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(524);
        _la = _input->LA(1);
        if (_la == 0 || _la == Token::EOF || (_la == MariaDBDDLParser::SEMI)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        } 
      }
      setState(529);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

MariaDBDDLParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MariaDBDDLParser::ExpressionContext::RPAREN() {
  return getTokens(MariaDBDDLParser::RPAREN);
}

tree::TerminalNode* MariaDBDDLParser::ExpressionContext::RPAREN(size_t i) {
  return getToken(MariaDBDDLParser::RPAREN, i);
}


size_t MariaDBDDLParser::ExpressionContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleExpression;
}


std::any MariaDBDDLParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::ExpressionContext* MariaDBDDLParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 70, MariaDBDDLParser::RuleExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(531); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(530);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == MariaDBDDLParser::RPAREN)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(533); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 268427263) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableNameContext ------------------------------------------------------------------

MariaDBDDLParser::TableNameContext::TableNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MariaDBDDLParser::IdentifierContext *> MariaDBDDLParser::TableNameContext::identifier() {
  return getRuleContexts<MariaDBDDLParser::IdentifierContext>();
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::TableNameContext::identifier(size_t i) {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(i);
}

tree::TerminalNode* MariaDBDDLParser::TableNameContext::DOT() {
  return getToken(MariaDBDDLParser::DOT, 0);
}


size_t MariaDBDDLParser::TableNameContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleTableName;
}


std::any MariaDBDDLParser::TableNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitTableName(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::TableNameContext* MariaDBDDLParser::tableName() {
  TableNameContext *_localctx = _tracker.createInstance<TableNameContext>(_ctx, getState());
  enterRule(_localctx, 72, MariaDBDDLParser::RuleTableName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(535);
    identifier();
    setState(538);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MariaDBDDLParser::DOT) {
      setState(536);
      match(MariaDBDDLParser::DOT);
      setState(537);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnNameContext ------------------------------------------------------------------

MariaDBDDLParser::ColumnNameContext::ColumnNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::ColumnNameContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}


size_t MariaDBDDLParser::ColumnNameContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleColumnName;
}


std::any MariaDBDDLParser::ColumnNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitColumnName(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::ColumnNameContext* MariaDBDDLParser::columnName() {
  ColumnNameContext *_localctx = _tracker.createInstance<ColumnNameContext>(_ctx, getState());
  enterRule(_localctx, 74, MariaDBDDLParser::RuleColumnName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(540);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CollationNameContext ------------------------------------------------------------------

MariaDBDDLParser::CollationNameContext::CollationNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::CollationNameContext::identifier() {
  return getRuleContext<MariaDBDDLParser::IdentifierContext>(0);
}

tree::TerminalNode* MariaDBDDLParser::CollationNameContext::STRING_LITERAL() {
  return getToken(MariaDBDDLParser::STRING_LITERAL, 0);
}


size_t MariaDBDDLParser::CollationNameContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleCollationName;
}


std::any MariaDBDDLParser::CollationNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitCollationName(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::CollationNameContext* MariaDBDDLParser::collationName() {
  CollationNameContext *_localctx = _tracker.createInstance<CollationNameContext>(_ctx, getState());
  enterRule(_localctx, 76, MariaDBDDLParser::RuleCollationName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(544);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MariaDBDDLParser::CASCADE:
      case MariaDBDDLParser::CHARACTER:
      case MariaDBDDLParser::CHARSET:
      case MariaDBDDLParser::COLLATE:
      case MariaDBDDLParser::COLUMN:
      case MariaDBDDLParser::COMMENT:
      case MariaDBDDLParser::DATABASE:
      case MariaDBDDLParser::ENGINE:
      case MariaDBDDLParser::EXISTS:
      case MariaDBDDLParser::KEY:
      case MariaDBDDLParser::LOCK:
      case MariaDBDDLParser::RENAME:
      case MariaDBDDLParser::RESTRICT:
      case MariaDBDDLParser::SET:
      case MariaDBDDLParser::ACTION:
      case MariaDBDDLParser::SIGNED:
      case MariaDBDDLParser::TABLES:
      case MariaDBDDLParser::TO:
      case MariaDBDDLParser::UNLOCK:
      case MariaDBDDLParser::UNSIGNED:
      case MariaDBDDLParser::VALUES:
      case MariaDBDDLParser::WRITE:
      case MariaDBDDLParser::READ:
      case MariaDBDDLParser::ZEROFILL:
      case MariaDBDDLParser::NO:
      case MariaDBDDLParser::BACKTICK_ID:
      case MariaDBDDLParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(542);
        identifier();
        break;
      }

      case MariaDBDDLParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(543);
        match(MariaDBDDLParser::STRING_LITERAL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

MariaDBDDLParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::IdentifierContext::ID() {
  return getToken(MariaDBDDLParser::ID, 0);
}

tree::TerminalNode* MariaDBDDLParser::IdentifierContext::BACKTICK_ID() {
  return getToken(MariaDBDDLParser::BACKTICK_ID, 0);
}

MariaDBDDLParser::NonReservedKeywordContext* MariaDBDDLParser::IdentifierContext::nonReservedKeyword() {
  return getRuleContext<MariaDBDDLParser::NonReservedKeywordContext>(0);
}


size_t MariaDBDDLParser::IdentifierContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleIdentifier;
}


std::any MariaDBDDLParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::IdentifierContext* MariaDBDDLParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 78, MariaDBDDLParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(549);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MariaDBDDLParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(546);
        match(MariaDBDDLParser::ID);
        break;
      }

      case MariaDBDDLParser::BACKTICK_ID: {
        enterOuterAlt(_localctx, 2);
        setState(547);
        match(MariaDBDDLParser::BACKTICK_ID);
        break;
      }

      case MariaDBDDLParser::CASCADE:
      case MariaDBDDLParser::CHARACTER:
      case MariaDBDDLParser::CHARSET:
      case MariaDBDDLParser::COLLATE:
      case MariaDBDDLParser::COLUMN:
      case MariaDBDDLParser::COMMENT:
      case MariaDBDDLParser::DATABASE:
      case MariaDBDDLParser::ENGINE:
      case MariaDBDDLParser::EXISTS:
      case MariaDBDDLParser::KEY:
      case MariaDBDDLParser::LOCK:
      case MariaDBDDLParser::RENAME:
      case MariaDBDDLParser::RESTRICT:
      case MariaDBDDLParser::SET:
      case MariaDBDDLParser::ACTION:
      case MariaDBDDLParser::SIGNED:
      case MariaDBDDLParser::TABLES:
      case MariaDBDDLParser::TO:
      case MariaDBDDLParser::UNLOCK:
      case MariaDBDDLParser::UNSIGNED:
      case MariaDBDDLParser::VALUES:
      case MariaDBDDLParser::WRITE:
      case MariaDBDDLParser::READ:
      case MariaDBDDLParser::ZEROFILL:
      case MariaDBDDLParser::NO: {
        enterOuterAlt(_localctx, 3);
        setState(548);
        nonReservedKeyword();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NonReservedKeywordContext ------------------------------------------------------------------

MariaDBDDLParser::NonReservedKeywordContext::NonReservedKeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::ACTION() {
  return getToken(MariaDBDDLParser::ACTION, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::CASCADE() {
  return getToken(MariaDBDDLParser::CASCADE, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::CHARSET() {
  return getToken(MariaDBDDLParser::CHARSET, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::CHARACTER() {
  return getToken(MariaDBDDLParser::CHARACTER, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::COLLATE() {
  return getToken(MariaDBDDLParser::COLLATE, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::COLUMN() {
  return getToken(MariaDBDDLParser::COLUMN, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::COMMENT() {
  return getToken(MariaDBDDLParser::COMMENT, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::DATABASE() {
  return getToken(MariaDBDDLParser::DATABASE, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::ENGINE() {
  return getToken(MariaDBDDLParser::ENGINE, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::EXISTS() {
  return getToken(MariaDBDDLParser::EXISTS, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::KEY() {
  return getToken(MariaDBDDLParser::KEY, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::LOCK() {
  return getToken(MariaDBDDLParser::LOCK, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::NO() {
  return getToken(MariaDBDDLParser::NO, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::READ() {
  return getToken(MariaDBDDLParser::READ, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::RENAME() {
  return getToken(MariaDBDDLParser::RENAME, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::RESTRICT() {
  return getToken(MariaDBDDLParser::RESTRICT, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::SET() {
  return getToken(MariaDBDDLParser::SET, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::SIGNED() {
  return getToken(MariaDBDDLParser::SIGNED, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::TABLES() {
  return getToken(MariaDBDDLParser::TABLES, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::TO() {
  return getToken(MariaDBDDLParser::TO, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::UNLOCK() {
  return getToken(MariaDBDDLParser::UNLOCK, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::UNSIGNED() {
  return getToken(MariaDBDDLParser::UNSIGNED, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::VALUES() {
  return getToken(MariaDBDDLParser::VALUES, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::WRITE() {
  return getToken(MariaDBDDLParser::WRITE, 0);
}

tree::TerminalNode* MariaDBDDLParser::NonReservedKeywordContext::ZEROFILL() {
  return getToken(MariaDBDDLParser::ZEROFILL, 0);
}


size_t MariaDBDDLParser::NonReservedKeywordContext::getRuleIndex() const {
  return MariaDBDDLParser::RuleNonReservedKeyword;
}


std::any MariaDBDDLParser::NonReservedKeywordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MariaDBDDLParserVisitor*>(visitor))
    return parserVisitor->visitNonReservedKeyword(this);
  else
    return visitor->visitChildren(this);
}

MariaDBDDLParser::NonReservedKeywordContext* MariaDBDDLParser::nonReservedKeyword() {
  NonReservedKeywordContext *_localctx = _tracker.createInstance<NonReservedKeywordContext>(_ctx, getState());
  enterRule(_localctx, 80, MariaDBDDLParser::RuleNonReservedKeyword);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(551);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 179018497672771200) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 3917) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void MariaDBDDLParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mariadbddlparserParserInitialize();
#else
  ::antlr4::internal::call_once(mariadbddlparserParserOnceFlag, mariadbddlparserParserInitialize);
#endif
}
