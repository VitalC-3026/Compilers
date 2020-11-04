%option noyywrap
%option yylineno
%top{
    #include <map>
    #include <iomanip>
    #include <string>
    #include <utility>
    using namespace std;
}

%{
    map<string, int> symbolTable;
    symbolTable["int"] = -1;
    symbolTable["while"] = -1;
%}

ID      [a-zA-Z_][0-9a-zA-Z_]*
NUMBER  [1-9][0-9]*
line    \n
char    .

%%

{ID}        {
                if (symbolTable.find(yytext) != symbolTable.end()) {
                    if (symbolTable[yytext] == -1) {
                        cout << "ID\t" << yytext << "\t" << "Reserved Word" << endl;
                    }
                    
                } else {
                    std::cout << "Identifier not found" << endl;
                }
            }
{NUMBER}    { cout << "NUMBER\t" << yytext << "\t" << symbolTable[yytext] << endl; }
{line}      { cout << setw(8) << yylineno << endl; }

%%

int main(){
    yyFlexLexer lexer;
    lexer.yylex();
    return 0;
}