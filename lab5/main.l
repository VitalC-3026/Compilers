%option nounput
%{
/*
 * lab5
 * Lex
 * Data: 2020/11/19
 * Juanyun Mai
*/

#include "common.h"
#include "type.h"
#include "main.tab.h" 
using std::cerr;
using std::cout;
using std::endl;
int lineno = 1, level = 0, ifFor = 0;
extern void yyerror(const char*);
extern map<string, stack<idAttr>> identifierTable;

int checkRange(string id, int level) {
    int idx = -1;
    if(identifierTable.find(id) != identifierTable.end()){
        stack<idAttr> s = identifierTable.find(id)->second;
        while(!s.empty()) {           
            if(s.top().level <= level) {
                // fputs("exists! use before\n", yyout);
                // cout << s.size() << endl;
                idx = s.top().id;
                break;
            }
            s.pop();
        }
    }
    return idx;
}

void createIntNode(int lineno, RadixType radix){
    TreeNode* node = new TreeNode(lineno, NODE_Const);
    node->setDeclType(D_INT);
    node->setRadixType(radix);
    switch (radix){
        case DECIMAL: {
            node->setIntValue(atoi(yytext));
            // cout << "ID value: INT" << atoi(yytext) << endl;
            break;
        }
        case OCTAL: {
            int num = 0;
            for (int i = 1; i < strlen(yytext); i++) {
                num += (int)yytext[i] * pow(8, (strlen(yytext) - i - 1));
            }
            node->setIntValue(num);
            // cout << "ID value: INT" << num << endl;
            break;
        }
        case HEXA: {
            int num = 0;
            for (int i = 2; i < strlen(yytext); i++) {
                char c = yytext[i];
                int tmp;
                if (c >= '0' && c <= '9') {
                    tmp = c - '0';
                } else if (c >= 'a' && c <= 'f') {
                    tmp = c - 'a';
                } else if (c >= 'A' && c <= 'F') {
                    tmp = c - 'A';
                } else {
                    yyerror("Unexpected integer!");
                    break;
                }
                num += tmp * pow(16, (strlen(yytext) - i - 1));
            }
            node->setIntValue(num);
            // cout << "ID value: INT" << num << endl;
            break;
        }
        default:
            break;
    }
    yylval = node;
}
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
CHAR \'.?\'
STRING \".*\"


%%

{commentbegin} {BEGIN COMMENT;}
<COMMENT>{commentelement} {}
<COMMENT>{commentend} {BEGIN INITIAL;}
{commentline}   {} /*do nothing*/


"bool"  return T_BOOL;
"int"   return T_INT; 
"char"  return T_CHAR; 
"string" return T_STRING;
"void"  return T_VOID;
"main"  return MAIN;
"const"  return CONST;
"struct" return STRUCT;
"if"    return IF;
"else"  return ELSE;
"while" return WHILE;
"for"   { ifFor = 1; return FOR;}
"return" return RETURN;
"continue" return CONTINUE;
"break" return BREAK;
"printf" return PRINTF;
"scanf" return SCANF;

"="     return ASG;
"+="    return ADDASG;
"-="    return MINASG;
"*="    return MULASG;
"/="    return DIVASG;
"%="    return MODASG;
"++"    return ADDASGO;
"--"    return MINASGO;

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

"("     {   
            // if(ifFor == 1) {   
            //     cout << "LBRACE" << ifFor << " " << level << endl; 
            //     level++;
            // } 
            return LBRACE; }
")"     {   
            return RBRACE; 
        }
"{"     {   cout << "LPAREN" << level << endl; 
            level++;
            // if(ifFor == 0){   
            //     cout << "LPAREN" << ifFor << " " << level << endl; 
            //     level++; 
            // } 
            return LPAREN;
        }
"}"     {
            ifFor = 0;
            --level; 
            cout << lineno << "RPAREN" << level << endl;
            return RPAREN; 
        }
";"     return SEMICOLON;
","     return COMMA;

{ID}    {
            if (identifierTable.find(yytext) != identifierTable.end()){
                // cout << yytext << " exists!" << endl;
                stack<idAttr> s = identifierTable.find(yytext)->second;
                int id = -1;
                while(!s.empty()) {
                    // cout << s.top().level << " " << level;
                    if(s.top().level <= level) {
                        // cout << yytext << " use before" << endl;
                        //fputs("exists! use before ID@", yyout);
                        // cout << s.size() << endl;
                        id = s.top().id;
                        //fputs(to_string(id).c_str(),yyout);
                        break;
                    }
                    s.pop();
                }
                TreeNode* node = new TreeNode(lineno, NODE_Var);
                if (id != -1) {
                    node->setFormerNodeId(id);
                } // else {
                //     cout << "exists! higher level!"<<endl;
                //     fputs("exists! higher level\n", yyout);
                //     // idAttr attr;
                //     // attr.level = level;
                //     // attr.id = node->getNodeId();
                //     // s.push(attr);
                //     // identifierTable[yytext] = s;
                // }
                node->setIdentifier((string) yytext);
                // cout << "ID@" << node->getNodeId() << " level" << level;
                yylval = node;
                
            } else {
                // cout << yytext << " doesn't exist!" << endl;
                // fputs("nonexists!\n", yyout);
                TreeNode* node = new TreeNode(lineno, NODE_Var);
                string identifier = (string) yytext;
                node->setIdentifier(identifier);
                yylval = node;
            }
            return ID;
        }
{DEC}   {
            createIntNode(lineno, DECIMAL);
            return INTEGER;
        }
{OCT}   {
            createIntNode(lineno, OCTAL);
            return INTEGER;
        }
{HEX}   {
            createIntNode(lineno, HEXA);
            return INTEGER;
        }
{CHAR}  {
            TreeNode* node = new TreeNode(lineno, NODE_Const);
            node->setDeclType(D_CHAR);
            node->setCharValue(yytext[1]);
            yylval = node;
            // cout << "ID value: CHAR" << yytext[1] << endl;
            return CHAR;
        }
{STRING} {
            TreeNode* node = new TreeNode(lineno, NODE_Const);
            node->setDeclType(D_STRING);
            node->setStringValue((string)yytext);
            yylval = node;
            // cout << "ID value: STRING" << yytext << endl;
            return STRING;
        }

{WHITESPACE}    /*do nothing*/

{EOL}   { lineno++; }

.       {
            cerr << "[line "<< lineno <<" ] unknown character:" << yytext << endl;
        }
