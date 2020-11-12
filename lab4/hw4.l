%option noyywrap
%option yylineno
%top{
    #include <map>
    #include <cmath>
    #include <iomanip>
    #include <string>
    #include <utility>
    #include <fstream>
    using namespace std;
}

%{
    map<string, int> symbolTable;
    int level = 0, lines = 0, spec = 0;
%}
ASSIG       "="
SEMICOLON   ";"
LBRACE      "{"
RBRACE      "}"
LPAREN      "("
RPAREN      ")"
LBRACK      "["
RBRACK      "]"
INT         int
CONST       const
IF          if
ELSE        else
SWITCH      switch
CASE        case
DEFAULT     default
FOR         for
WHILE       while
DO          do
BREAK       break
CONTINUE    continue
RETURN      return
ID          [a-zA-Z_][0-9a-zA-Z_]*
DECIMAL     ([1-9][0-9]*|0)
HEXADECIMAL (0x|0X)[0-9A-Fa-f]+
OCTAL       (0)[0-7]+
BINARY      [0-1]*

commentbegin "/*"
commentelement .|\n
commentend "*/"
%x COMMENT
commentline "//".*

line        \n
char        .

%%
"="         { yyout << std::right << setw(12) << "ASSIG" << setw(12) << yytext << endl; }
"+="         { yyout << std::right << setw(12) << "ADDASGN" << setw(12) << yytext << endl; }
"-="         { yyout << std::right << setw(12) << "MINASGN" << setw(12) << yytext << endl; }
"*="         { yyout << std::right << setw(12) << "MULASGN" << setw(12) << yytext << endl; }
"/="         { yyout << std::right << setw(12) << "DIVASGN" << setw(12) << yytext << endl; }

"&"         { yyout << std::right << setw(12) << "QUO" << setw(12) << yytext << endl; }
"!"         { yyout << std::right << setw(12) << "NOT" << setw(12) << yytext << endl; }
"->"        { yyout << std::right << setw(12) << "ARROW" << setw(12) << yytext << endl; }
"++"        { yyout << std::right << setw(12) << "SADD" << setw(12) << yytext << endl; }
"--"        { yyout << std::right << setw(12) << "SMIN" << setw(12) << yytext << endl; }

"+"         { yyout << std::right << setw(12) << "ADD" << setw(12) << yytext << endl; }
"-"         { yyout << std::right << setw(12) << "MIN" << setw(12) << yytext << endl; }
"*"         { yyout << std::right << setw(12) << "MUL" << setw(12) << yytext << endl; }
"/"        { yyout << std::right << setw(12) << "DIV" << setw(12) << yytext << endl; }
"%"         { yyout << std::right << setw(12) << "MOD" << setw(12) << yytext << endl; }

"<="        { yyout << std::right << setw(12) << "SE" << setw(12) << yytext << endl; }
">="        { yyout << std::right << setw(12) << "GE" << setw(12) << yytext << endl; }
">"         { yyout << std::right << setw(12) << "GT" << setw(12) << yytext << endl; }
"<"         { yyout << std::right << setw(12) << "ST" << setw(12) << yytext << endl; }

"=="        { yyout << std::right << setw(12) << "EQUAL" << setw(12) << yytext << endl; }
"!="        { yyout << std::right << setw(12) << "NEQUAL" << setw(12) << yytext << endl; }

"&&"        { yyout << std::right << setw(12) << "AND" << setw(12) << yytext << endl; }
"||"        { yyout << std::right << setw(12) << "OR" << setw(12) << yytext << endl; }

{SEMICOLON} { yyout << std::right << setw(12) << "SEMICOL" << setw(12) << yytext << endl; }
{LBRACE}    { level++; yyout << std::right << setw(12) << "LBRACE" << setw(12) << yytext << endl; }
{RBRACE}    { level--; yyout << std::right << setw(12) << "RBRACE" << setw(12) << yytext << endl; }
{LPAREN}    { yyout << std::right << setw(12) << "LPAREN" << setw(12) << yytext << endl; }
{RPAREN}    { yyout << std::right << setw(12) << "RPAREN" << setw(12) << yytext << endl; }
{LBRACK}    { yyout << std::right << setw(12) << "LBRACK" << setw(12) << yytext << endl; }
{RBRACK}    { yyout << std::right << setw(12) << "RBRACK" << setw(12) << yytext << endl; }

{INT}       { yyout << std::right << setw(12) << "INT" << setw(12) << yytext << endl; spec++; }
{CONST}     { yyout << std::right << setw(12) << "CONST" << setw(12) << yytext << endl; spec++; }
{IF}          { yyout << std::right << setw(12) << "IF" << setw(12) << yytext << endl; spec++; }
{ELSE}        { yyout << std::right << setw(12) << "ELSE" << setw(12) << yytext << endl; spec++; }
{SWITCH}      { yyout << std::right << setw(12) << "SWITCH" << setw(12) << yytext << endl; spec++; }
{CASE}        { yyout << std::right << setw(12) << "CASE" << setw(12) << yytext << endl; spec++; }
{DEFAULT}     { yyout << std::right << setw(12) << "DEFAULT" << setw(12) << yytext << endl; spec++; }
{FOR}         { yyout << std::right << setw(12) << "FOR" << setw(12) << yytext << endl; spec++; }
{WHILE}       { yyout << std::right << setw(12) << "WHILE" << setw(12) << yytext << endl; spec++; }
{DO}          { yyout << std::right << setw(12) << "DO" << setw(12) << yytext << endl; spec++; }
{BREAK}       { yyout << std::right << setw(12) << "BREAK" << setw(12) << yytext << endl; spec++; }
{CONTINUE}    { yyout << std::right << setw(12) << "CONTINUE" << setw(12) << yytext << endl; spec++; }
{RETURN}      { yyout << std::right << setw(12) << "RETURN" << setw(12) << yytext << endl; spec++; }

{ID}        {
                if (symbolTable.find(yytext) != symbolTable.end()) {
                    symbolTable[yytext] = level;
                    yyout << std::right << setw(12) << "ID" << setw(12) << yytext << setw(12) << level << endl;
                } else {
                    symbolTable[yytext] = level;
                    yyout << std::right << setw(12) << "ID" << setw(12) << yytext << setw(12) << level << endl;
                }
            }
{DECIMAL}   { yyout << std::right << setw(12) << "DEC" << setw(12) << yytext << setw(12)  << yytext << endl; }
{HEXADECIMAL}   {   yyout << std::right << setw(12) << "HEX" << setw(12) << yytext;
                    int num = 0;
                    for (int i = 2; i < strlen(yytext); i++) {
                        num += (yytext[i] - 48) * pow(16, strlen(yytext) - i - 1);
                    }
                    yyout << setw(12) << num << endl; }
{OCTAL}     { yyout << std::right << setw(12) << "OCT" << setw(12) << yytext;
              int num = 0;
              for (int i = 1; i < strlen(yytext); i++) {
                  num += (yytext[i] - 48) * pow(8, strlen(yytext) - i - 1);
              }
              yyout << setw(12) << num << endl; }
{BINARY}    { yyout << std::right << setw(12) << "BIN" << setw(12) << yytext;
              int num = 0;
              for (int i = 1; i < strlen(yytext); i++) {
                  num += (yytext[i] - 48) * pow(2, strlen(yytext) - i - 1);
              }
              yyout << setw(12) << yytext << endl; }
{line}      { lines++; }
{commentbegin} {BEGIN COMMENT;}
<COMMENT>{commentelement} {}
<COMMENT>{commentend} {BEGIN INITIAL;}
{commentline}   {lines--;}
%%

int main(){
    ifstream input("./testin");
    ofstream output("./testout");
    yyFlexLexer lexer(&input, &output);
    output << std::right << setw(12) << "Type" << setw(12) << "Attributes" << setw(12) << "Values" << endl;
    lexer.yylex();
    output << std::right << setw(12) << "LINES" << setw(12) << lines << endl;
    output << std::right << setw(12) << "KEY WORDS" << setw(12) << spec << endl;
    return 0;
}