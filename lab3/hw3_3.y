%{
/*
hw3.y
YACC 
Date: 2020/10/21
Juanyun Mai <1811499@mail.nankai.edu.cn>
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifndef YYSTYPE
#define YYSTYPE int
#endif


struct item {
    char identifier[50];
    int value;
};
int last = 0;
struct item id_table[1000];
char idStr[50];
int cmpstr(const char* s1, const char* s2);
int yylex();
extern int yyparse(); 
FILE* yyin;
void yyerror(const char* s);

%}

%token ADD
%token SUB
%token MUL
%token DIV
%token UMINUS
%token LB
%token RB
%token ID
%token EQ
%token NUMBER


%left ADD SUB
%left MUL DIV
%right UMINUS EQ


%%


lines	:	lines expr ';' { printf("%d\n", $2 ); }
        |   lines stmt ';' { printf("%d\n", $2 ); }
        |	lines '\n'
        |
        ;

stmt    :   ID EQ expr  { $$ = $3; id_table[$1].value = $3; }
        |
        ;

expr    :   expr ADD expr   { $$ = $1 + $3; }
        |   expr SUB expr   { $$ = $1 - $3; }
        |   expr MUL expr   { $$ = $1 * $3; }
        |   expr DIV expr   { $$ = $1 / $3; }
        |   LB expr RB    { $$ = $2; }
        |   UMINUS expr   { $$ = -$2; }
        |   NUMBER  { $$ = $1; }
        |   ID      { $$ = id_table[$1].value; }
        ;


	
%%	
	
// programs section	

int cmpstr(const char* s1, const char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int i;
    if (len1 != len2) {
        return 0;
    }
    for (i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            return 0;
        }
    }
    return 1;
}

int yylex()	
{	
    // place your token retrieving code here
    int t;
    while (1) {
        t = getchar();
        if (t == ' ' || t == '\t' || t == '\n')
            ;
        else if (t == '+') {
            return ADD;
        }
        else if (t == '-') {
            ungetc(t, stdin);
            ungetc(t, stdin);
            t = getchar();
            // 如果-前面是数字的话，那么一定是SUB.
            // 如果-前面什么都没有|有运算符|有括号，那么就是UMINUS.
            if (isdigit(t)) {
                return SUB;
            }
            else {
                t = getchar();
                return UMINUS;
            }
        }
        else if (t == '*') {
            return MUL;
        }
        else if (t == '/') {
            return DIV;
        }
        else if (t == '(') {
            return LB;
        }
        else if (t == ')') {
            return RB;
        }
        else if (t == '=') {
            return EQ;
        }
        else if (isdigit(t)) {
            yylval = 0;
            while(isdigit(t)) {
                yylval = yylval * 10 + t - '0';
                t = getchar();
            }
            ungetc(t, stdin);
            return NUMBER;
        }
        else if ((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z') || t == '_') {
            int idx = 0;
            while((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z') 
            || (t >= '0' && t <= '9') || t == '_' ) {
                idStr[idx] = t;
                idx++;
                t = getchar();
            }
            idStr[idx] = '\0';
            ungetc(t, stdin);
            int i;
            for (i = 0; i < last; i++) {
                if (cmpstr(id_table[i].identifier, idStr)) {
                    yylval = i;
                    return ID;
                }
            }
            
            if (last < 1000) {
                struct item temp;
                for (int i = 0; i <= idx && i < 50; i++) {
                    temp.identifier[i] = idStr[i];
                }
                temp.value = 0;
                id_table[last] = temp;
                yylval = last;
                last++;
            }
            else {
                char err[50] = "NO Place For New Identifier!";
                yyerror(err);
            }
            
            
            return ID;
        }
        else {
            return t;
        }
    }		
}	
	
int main(void)	
{	
    yyin = stdin;	
    do {	
        yyparse();	
    } while (!feof(yyin));	
    return 0;	
}	

void yyerror(const char* s) {	
    fprintf (stderr, "Parse error: %s\n", s);	
    exit (1);	
}	
