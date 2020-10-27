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
#ifndef YYSTYPE
#define YYSTYPE double 
#endif

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


lines	:	lines expr ';' { printf("%f\n", $2 ); }
        |	lines '\n'
        |
        ;

expr    :   expr ADD expr   { $$ = $1 + $3; }
        |   expr SUB expr   { $$ = $1 - $3; }
        |   expr MUL expr   { $$ = $1 * $3; }
        |   expr DIV expr   { $$ = $1 / $3; }
        |   LB expr RB    { $$ = $2; }
        |   SUB expr %prec UMINUS   { $$ = -$2; }
        |   NUMBER  { $$ = $1; }
        ;

// NUMBER  :	'0'	{ $$ = 0.0; }
//         |	'1'	{ $$ = 1.0; }
//         |	'2'	{ $$ = 2.0; }
//         |	'3'	{ $$ = 3.0; }
//         |	'4'	{ $$ = 4.0; }
//         |	'5'	{ $$ = 5.0; }
//         |	'6'	{ $$ = 6.0; }
//         |	'7'	{ $$ = 7.0; }
//         |	'8'	{ $$ = 8.0; }
//         |	'9'	{ $$ = 9.0; }
//         ;	
	
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
            //     t = getchar();
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
            yylval = 0;
            while(isdigit(t)) {
                t = t - '0';
                yylval = yylval * 10 + t;
                t = getchar();
            }
            ungetc(t, stdin);
            return NUMBER;
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
