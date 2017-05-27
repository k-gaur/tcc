#ifndef VARDEF_H_INCLUDED
#define VARDEF_H_INCLUDED

extern char *_file; //contains source file name

//Miscelleneous macros
#define VERSION 1.3
#define FALSE 0
#define TRUE 1
#define SHIFT 1
#define REDUCE 2
#define ACCEPT 3
#define COMPILER 5
#define USER 6
#define WSPACE 50
#define NEWLINE 51
#define ASSNOTACCREG 91
#define ASSACCREG 92
#define STRCPY 93
#define STRCAT 94
#define STRCMP 95
#define JUMP 96
#define PUSHVAL 97
#define PUSHADDR 98
#define ILLEGAL 99
#define LABEL 99
#define UMINUS 100
#define TABSIZE 256
#define ISALPHA(i) (('a'<=i && i<='z') || ('A'<=i && i<='Z'))
#define ISNUM(i) ('0'<=i && i<='9')

//Non terminal codes
#define INVAR 18
#define OUTVAR 17
#define STMT 16
#define LOOPSTMT 15
#define LOGOP 14
#define ALOP 13
#define RELOP 12
#define OP 11
#define EXPRS 10
#define EXPRP 9
#define CONDSTMT 8
#define CONST 7
#define TYPE 6
#define ID 5
#define IDNAME 4
#define IDTYPE 3
#define INITSTMT 2
#define SUBPROG 1
#define PROG 0

//Token codes
#define NOTOP 41
#define DOLLAR 40
#define ENTER 39
#define EXIT 38
#define ENDOP 37
#define COLON 36
#define INTCONST 35
#define INT 34
#define CHAR 33
#define STR 32
#define REAL 31
#define COMOP 30
#define IDENTIFIER 29
#define LB 28
#define RB 27
#define ASSOP 26
#define SUBOP 25
#define STRCONST 24
#define CHARCONST 23
#define REALCONST 22
#define IF 21
#define FI 20
#define ELSE 19
#define LP 18
#define RP 17
#define LTROP 16
#define GTROP 15
#define LTEOP 14
#define GTEOP 13
#define EQLOP 12
#define NEQOP 11
#define ADDOP 10
#define MULOP 9
#define DIVOP 8
#define MODOP 7
#define XOROP 6
#define ANDOP 5
#define OROP 4
#define LOOP 3
#define POOL 2
#define PRINT 1
#define SCAN 0

//Semantic error codes
#define SEMDECL 0
#define SEMDECL2 1
#define SEMDECL3 2
#define SEMDECL4 3
#define SEMDECL5 4
#define SEMUNDEF 5
#define SEMTYPE 6
#define SEMTYPE2 7
#define SEMTYPE3 8
#define SEMINVALIDARRAY 9
#define SEMINVALIDVAR 10
#define SEMUMINUSARR 11
#define SEMMINUSZERO 12

//Error definitions
#define ERRMAIN0 "error: wrong input\ntype \"tcc -h\" for help\n"
#define ERRMAIN1 "error: file '%s' does not exist\ntype \"tcc -h\" for help\n"
#define ERRLEX "%s: lexical error at line %d: illegal symbol '%s' is used\n"
#define ERRPARSE "%s: syntax error at line %d: '%s' is not allowed here\n"
#define ERRSEMDECL "%s: semantic error at line %d: redeclaration of variable '%s' occurs\n"
#define ERRSEMDECL2 "%s: semantic error at line %d: Invalid size limit is provided\n"
#define ERRSEMDECL3 "%s: semantic error at line %d: Size limit cannot be applied on 'real' types \n"
#define ERRSEMDECL4 "%s: semantic error at line %d: At declaration, Index value for array '%s' must be constant \n"
#define ERRSEMDECL5 "%s: semantic error at line %d: Value assigned to variable '%s' is not constant \n"
#define ERRSEMUNDEF "%s: semantic error at line %d: variable '%s' is not defined\n"
#define ERRSEMTYPE "%s: semantic error at line %d: incompatible type assignment to variable '%s' (expected '%s' type instead of '%s' type)\n"
#define ERRSEMTYPE2 "%s: semantic error at line %d: incompatible operands used for '%s'\n"
#define ERRSEMTYPE3 "%s: semantic error at line %d: operation '%s' is not allowed on string types\n"
#define WARSEMTYPE "%s: warning at line %d: narrow type conversion ('%s' to '%s') for variable '%s' occurs\n"
#define ERRSEMINVALIDARRAY "%s: semantic error at line %d: variable '%s' is not an array but used like an array\n"
#define ERRSEMINVALIDVAR "%s: semantic error at line %d: variable '%s' is an array but used like a non-array\n"
#define ERRSEMUMINUSARR "%s: semantic error at line %d: unary minus opration is not allowed on string constant '%s'\n"
#define ERRSEMMINUSZERO "%s: semantic error at line %d: Invalid constant '-0' is used\n"

//Phase dump definition
#define DUMP "\n----------------------------------------------------------------------------------------------------\n"

#endif // VARDEF_H_INCLUDED
