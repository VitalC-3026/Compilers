%{
    #include "common.h"
    TreeNode* root;
    extern int lineno;
    int yylex();
    void yyerror(const char*);
%}

expr    : ID   { $$ = $1; }
        | INTEGER { $$ = $1; }
        | CHAR { $$ = $1; }
        | STRING { $$ = $1; }
        ;
