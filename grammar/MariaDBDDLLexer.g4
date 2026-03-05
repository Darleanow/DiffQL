lexer grammar MariaDBDDLLexer;

// Keywords (case-insensitive via fragment)

ADD         : A D D ;
ALTER       : A L T E R ;
AUTO_INCREMENT : A U T O '_' I N C R E M E N T ;
BIGINT      : B I G I N T ;
BLOB        : B L O B ;
BOOLEAN     : B O O L E A N ;
CASCADE     : C A S C A D E ;
CHAR        : C H A R ;
CHARACTER   : C H A R A C T E R ;
CHARSET     : C H A R S E T ;
CHECK       : C H E C K ;
COLLATE     : C O L L A T E ;
COLUMN      : C O L U M N ;
COMMENT     : C O M M E N T ;
CONSTRAINT  : C O N S T R A I N T ;
CREATE      : C R E A T E ;
DATABASE    : D A T A B A S E ;
DATE        : D A T E ;
DATETIME    : D A T E T I M E ;
DECIMAL     : D E C I M A L ;
DEFAULT     : D E F A U L T ;
DELETE      : D E L E T E ;
DOUBLE      : D O U B L E ;
DROP        : D R O P ;
ENGINE      : E N G I N E ;
ENUM        : E N U M ;
EXISTS      : E X I S T S ;
FLOAT       : F L O A T ;
FOREIGN     : F O R E I G N ;
IF          : I F ;
INDEX       : I N D E X ;
INSERT      : I N S E R T ;
INT         : I N T ;
INTEGER     : I N T E G E R ;
INTO        : I N T O ;
JSON        : J S O N ;
KEY         : K E Y ;
LOCK        : L O C K ;
LONGBLOB    : L O N G B L O B ;
LONGTEXT    : L O N G T E X T ;
MEDIUMBLOB  : M E D I U M B L O B ;
MEDIUMINT   : M E D I U M I N T ;
MEDIUMTEXT  : M E D I U M T E X T ;
MODIFY      : M O D I F Y ;
NOT         : N O T ;
NULL_       : N U L L ;
ON          : O N ;
PRIMARY     : P R I M A R Y ;
REFERENCES  : R E F E R E N C E S ;
RENAME      : R E N A M E ;
RESTRICT    : R E S T R I C T ;
SET         : S E T ;
ACTION      : A C T I O N ;
SIGNED      : S I G N E D ;
SMALLINT    : S M A L L I N T ;
TABLE       : T A B L E ;
TABLES      : T A B L E S ;
TEXT        : T E X T ;
TIME        : T I M E ;
TIMESTAMP   : T I M E S T A M P ;
TINYBLOB    : T I N Y B L O B ;
TINYINT     : T I N Y I N T ;
TINYTEXT    : T I N Y T E X T ;
TO          : T O ;
UNIQUE      : U N I Q U E ;
UNLOCK      : U N L O C K ;
UNSIGNED    : U N S I G N E D ;
UPDATE      : U P D A T E ;
USE         : U S E ;
VALUES      : V A L U E S ;
VARCHAR     : V A R C H A R ;
WRITE       : W R I T E ;
READ        : R E A D ;
ZEROFILL    : Z E R O F I L L ;
NO          : N O ;

// Symbols

LPAREN      : '(' ;
RPAREN      : ')' ;
COMMA       : ',' ;
SEMI        : ';' ;
DOT         : '.' ;
EQ          : '=' ;
BACKTICK    : '`' ;

// Literals

STRING_LITERAL
    : '\'' ( ~('\'' | '\\') | '\\' . | '\'\'' )* '\''
    ;

NUMERIC_LITERAL
    : '-'? [0-9]+ ( '.' [0-9]+ )?
    ;

// Identifiers

BACKTICK_ID
    : '`' ( ~'`' | '``' )+ '`'
    ;

ID  : [a-zA-Z_] [a-zA-Z0-9_]* ;

// Skip

LINE_COMMENT
    : '--' ~[\r\n]* -> skip
    ;

BLOCK_COMMENT
    : '/*' .*? '*/' -> skip
    ;

CONDITIONAL_COMMENT
    : '/*!' .*? '*/' -> skip
    ;

WS  : [ \t\r\n]+ -> skip ;

// Catch-all for anything else
ANY : . -> skip ;

// Case-insensitive fragments

fragment A : [aA]; fragment B : [bB]; fragment C : [cC]; fragment D : [dD];
fragment E : [eE]; fragment F : [fF]; fragment G : [gG]; fragment H : [hH];
fragment I : [iI]; fragment J : [jJ]; fragment K : [kK]; fragment L : [lL];
fragment M : [mM]; fragment N : [nN]; fragment O : [oO]; fragment P : [pP];
fragment Q : [qQ]; fragment R : [rR]; fragment S : [sS]; fragment T : [tT];
fragment U : [uU]; fragment V : [vV]; fragment W : [wW]; fragment X : [xX];
fragment Y : [yY]; fragment Z : [zZ];
