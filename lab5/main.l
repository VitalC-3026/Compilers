%option noyywrap
%{
/*
 * lab5
 * Lex
 * Data: 2020/11/19
 * Juanyun Mai
*/

#include "common.h"
int lineno = 1; 

%}

commentbegin "/*"
commentelement .|\n
commentend "*/"
%x COMMENT
commentline "//"[^\n]*
EOL	(\r\n|\r|\n)
WHITESPACE [[:blank:]]

ID  [_a-zA-Z][a-zA-Z_0-9]*
DEC [1-9]?[0-9]*
OCT 0[0-7]+
HEX 0x[0-9a-fA-F]+
INTEGER {DEC}|{OCT}|{HEX}
CHAR \'.?\'
STRING \".*\"

%%

{commentbegin} {BEGIN COMMENT;}
<COMMENT>{commentelement} {}
<COMMENT>{commentend} {BEGIN INITIAL;}
{commentline}   /*do nothing*/
{EOL}   { lineno++; }
{WHITESPACE}    /*do nothing*/

"bool"  return BOOL;
"int"   return INT; 
"char"  return CHAR; 
"string" return STRING;
"const" return CONST; 
"struct" return STRUCT;
"if"    return IF;
"else"  return ELSE;
"while" return WHILE;
"for"   return FOR;
"return" return RETURN;
"continue" return CONTINUE;
"break" return BREAK;
"printf" return PRINTF
"scanf" return SCANF;

"="     return ASG;
"+="    return ADDASG;
"-="    return MINASG;
"*="    return MULASG;
"/="    return DIVASG;

"."     return DOT;
"&"     return REF;
"->"    return POI;
"!"     return NOT;

"+"     return ADD;
"-"     return MIN;
"*"     return MUL;
"/"     return DIV;
"%"     return MOD;

"=="    return EQU;
">"     return GT;
"<"     return LT;
">="    return GTQ;
"<="    return LTQ;
"!="    return NEQ;

"&&"    return AND;
"||"    return OR;

"("     return LBRACE;
")"     return RBRACE;
"{"     return LPAREN;
"}"     return RPAREN;
";"     return SEMICOLON;

{ID}    {
            TreeNode* Node_ID = new TreeNode(Type_ID);
        }


{CHAR}
{STRING}
