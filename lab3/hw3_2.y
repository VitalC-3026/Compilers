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
#define YYSTYPE char*
#endif

char idStr[50];
char numStr[50];
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
%token NUMBER

%left ADD SUB
%left MUL DIV
%right UMINUS

%%


lines	:	lines expr ';' { printf("%s\n", $2 ); }
        |	lines '\n'
        |
        ;

expr    :   expr ADD expr   { $$ = (char*) malloc(50*sizeof(char)); strcpy($$, $1); strcat($$, $3); strcat($$, "+ "); }
        |   expr SUB expr   { $$ = (char*) malloc(50*sizeof(char)); strcpy($$, $1); strcat($$, $3); strcat($$, "- "); }
        |   expr MUL expr   { $$ = (char*) malloc(50*sizeof(char)); strcpy($$, $1); strcat($$, $3); strcat($$, "* "); }
        |   expr DIV expr   { $$ = (char*) malloc(50*sizeof(char)); strcpy($$, $1); strcat($$, $3); strcat($$, "/ "); }
        |   LB expr RB    { $$ = (char*) malloc(50*sizeof(char)); strcpy($$, $2); }
        |   SUB expr %prec UMINUS   { $$ = (char*) malloc(50*sizeof(char)); strcpy($$, "0"); strcat($$, $2); }
        |   NUMBER  { $$ = (char*) malloc(50*sizeof(char)); strcpy($$, $1); strcat($$, " ");}
        |   ID      { $$ = (char*) malloc(50*sizeof(char)); strcpy($$, $1); strcat($$, " ");}
        ;

	
%%	
	
// programs section	
	
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
            return SUB;
            // ungetc(t, stdin);
            // ungetc(t, stdin);
            // t = getchar();
            // // 如果-前面是数字的话，那么一定是SUB.
            // // 如果-前面什么都没有|有运算符|有括号，那么就是UMINUS.
            // if (isdigit(t)) {
            //     return SUB;
            // }
            // else {
            //     t = getchar();
            //     return UMINUS;
            // }
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
        else if (isdigit(t)) {
            int idx = 0;
            while(isdigit(t)) {
                numStr[idx] = t;
                idx++;
                t = getchar();
            }
            ungetc(t, stdin);
            numStr[idx] = '\0';
            yylval = numStr;
            return NUMBER;
        }
        else if ((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z')) {
            int idx = 0;
            while((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z') 
            || (t >= '0' && t <= '9') || t == '_' ) {
                idStr[idx] = t;
                idx++;
                t = getchar();
            }
            idStr[idx] = '\0';
            yylval = idStr;
            ungetc(t, stdin);
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
