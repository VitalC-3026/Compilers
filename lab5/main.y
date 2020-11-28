%{
    #include "common.h"
    #include "pch.h"
    TreeNode* root;
    int yylex();
    extern void yyerror(const char*);
%}

%token  ASG ADDASG MINASG MULASG DIVASG MODASG ADDASGO MINASGO
%token  DOT REF POI NOT
%token  ADD SUB MUL DIV MOD
%token  EQU GT LT GTQ LTQ NEQ
%token  AND OR
%token  LBRACE RBRACE LPAREN RPAREN
%token  ID
%token  DEC OCT HEX
%token  CHAR BOOL STRING
%token  D_BOOL D_INT D_CHAR D_STRING
%token  CONST STRUCT IF ELSE WHILE FOR RETURN CONTINUE BREAK
%token  PRINTF SCANCF
%token  SEMICOLON COMMA

%right  ASG ADDASG ASG ADDASG MINASG MULASG DIVASG
%left   AND OR
%left   EQU GT LT GTQ LTQ NEQ
%left   ADD SUB
%left   MUL DIV MOD
%left   REF NOT
%left   DOT POI


%%

program 
: statements    { root = new TreeNode(0, NODE_Prog); root->addChild($1); }
;

statements
: statement { $$ = $1; }
| statements statement { $$ = $1; $$->addSibling($2); }
;

statement
: SEMICOLON { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_SKIP); }
| declaration SEMICOLON { $$ = $1; }
| assignment SEMICOLON  { $$ = $1; }
| arithmetic SEMICOLON  { $$ = $1; }
| jump SEMICOLON { $$ = $1; }
| loop
| control
;

idlist
: idlist COMMA ID ASG expr  {   $$ = $1; 
                                TreeNode* node = new TreeNode(lineno, NODE_Stmt); node->setStatementType(STMT_ASIG);
                                node->setAssignmentType(ADDASIG); node->addChild($3); node->addChild($5);
                                $$->addChild(node);
                            }
| idlist COMMA ID   {   $$ = $1; 
                        $$->addChild($3);
                    }
| ID ASG expr   {   $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_DECL);
                    TreeNode* node = new TreeNode(lineno, NODE_Stmt); node->setStatementType(STMT_ASIG);
                    node->setAssignmentType(ADDASIG); node->addChild($1); node->addChild($3);
                    $$->addChild(node);
                }
| ID            {   $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_DECL);
                    $$->addChild($1);
                }
;

declaration
: type idlist   {   $$ = setType($2, $1, 0);}
| CONST type idlist {   $$ = setType($3, $2, 1);}
;

type
: D_BOOL { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType($1); }
| D_INT { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType($1); }
| D_CHAR { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType($1); }
| D_STRING { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType($1); }
;

loop
: FOR LBRACE forcon RBRACE LPAREN statements RPAREN { if(checkFor($3, $6)) {
                                                              $$ = new TreeNode(lineno, NODE_Stmt);
                                                              $$->addChild($3);
                                                              $$->addChild($6);
                                                              $$->setStatementType(STMT_FOR);
                                                          } else {
                                                              yyerror("FOR error, check failed!");
                                                          }
                                                          
                                                        }
| WHILE LBRACE expr RBRACE LPAREN statements RPAREN     { if(checkWhile($3, $6)) {
                                                              $$ = new TreeNode(lineno, NODE_Stmt);
                                                              $$->addChild($3);
                                                              $$->addChild($6);
                                                              $$->setStatementType(STMT_WHILE);
                                                          } else {
                                                              yyerror("WHILE error, check failed!");
                                                          }
                                                            
                                                        }
;

forcon
: statement SEMICOLON arithmetic SEMICOLON assignment {   if(checkIfCon($1, $3, $5)) {
                                                                $$ = new TreeNode(lineno, NODE_Stmt);
                                                                $$->addChild($1);
                                                                $$->addChild($3);
                                                                $$->addChild($5);
                                                            } else {
                                                                yyerror("FOR CON error, check failed!");
                                                            }

                                                        }
;

control
: IF LBRACE expr RBRACE LPAREN statements RPAREN    {   if(checkIf($3, $6)) {
                                                            $$ = new TreeNode(lineno, NODE_Stmt);
                                                            $$->addChild($3);
                                                            $$->addChild($6);
                                                            $$->setStatementType(STMT_IF);
                                                        } else {
                                                            yyerror("IF error, check failed!");
                                                        }
                                                            
                                                    }
| IF LBRACE expr RBRACE LPAREN statements RPAREN ELSE LPAREN statements RPAREN  {   if(checkIf($3, $6, $10)) {
                                                                                    $$ = new TreeNode(lineno, NODE_Stmt);
                                                                                    $$->addChild($3);
                                                                                    $$->addChild($6);
                                                                                    $$->addChild($10);
                                                                                    $$->setStatementType(STMT_IF);
                                                                                    } else {
                                                                                        yyerror("IF error, check failed!");
                                                                                    }
                                                                                        
                                                                                }
;

jump
: BREAK { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_BREAK); }
| CONTINUE { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_CONTINUE); }
| RETURN  expr { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_RETURN); $$->addChild($2);}
| RETURN { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_RETURN); }
;

assignment
:
| ID ASG expr       {   if(checkAsg($1, 0)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| ID ADDASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ADDASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| ID MINASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MINASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| ID MULASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MULASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| ID DIVASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(DIVASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| ID MODASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MODASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| ADDASGO ID        {   if(checkAsg($2, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ADDASIGO);
                            $$->addChild($2);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| MINASGO ID        {   if(checkAsg($2, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MINASIGO);
                            $$->addChild($2);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| ID ADDASGO        {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ADDASIGO);
                            $$->addChild($1);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
| ID MINASGO        {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MINASIGO);
                            $$->addChild($1);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                    }
;

expr
: expr ADD expr { $$ = addOperatorNode($1, $3, OP_ADD, lineno);}
| expr MIN expr { $$ = addOperatorNode($1, $3, OP_MIN, lineno);}
| expr MUL expr { $$ = addOperatorNode($1, $3, OP_MUL, lineno);}
| expr DIV expr { $$ = addOperatorNode($1, $3, OP_DIV, lineno);}
| expr MOD expr { $$ = addOperatorNode($1, $3, OP_MOD, lineno);}
| expr AND expr { $$ = addOperatorNode($1, $3, OP_AND, lineno);}
| expr OR  expr { $$ = addOperatorNode($1, $3, OP_OR, lineno);}
| expr GT  expr { $$ = addOperatorNode($1, $3, OP_GT, lineno);}
| expr GTQ expr { $$ = addOperatorNode($1, $3, OP_GTQ, lineno);}
| expr LT  expr { $$ = addOperatorNode($1, $3, OP_LT, lineno);}
| expr LTQ expr { $$ = addOperatorNode($1, $3, OP_LTQ, lineno);}
| expr NEQ expr { $$ = addOperatorNode($1, $3, OP_NEQ, lineno);}
| expr EQU expr { $$ = addOperatorNode($1, $3, OP_EQU, lineno);}
| NOT  expr     { if($1->getNodeType() == NODE_Var || $1->getNodeType() == NODE_Const) {
                    if ($1->getDeclType() != D_STRING) {
                        TreeNode* node = new TreeNode(lineno, NODE_Op);
                        node->setOperatorType(OP_NOT);
                        node->addChild($2);
                        $$ = node;
                    }
                  } else {
                      yyerror("NOT Type error, this node is a string.");
                  }
                }
| ADD  expr     { $$ = $2;}
| MIN  expr     { if($2->getNodeType() == NODE_Var && $2->getDeclType() == D_INT) {
                    int value = $2->getIntValue();
                    $2->setIntValue(-value);
                    $$ = $2;
                  } else {
                      yyerror("UMINUS Type error, this node is not an integer.");
                  }
                }
| REF  expr     { if($1->getNodeType() == NODE_Var || $1->getNodeType() == NODE_Const) {
                    if ($1->getIdentifier() != "") {
                        TreeNode* node = new TreeNode(lineno, NODE_Op);
                        node->setOperatorType(OP_REF);
                        node->addChild($2);
                        $$ = node;
                    }
                  } else {
                      yyerror("REF Type error, this node is not an identifier.");
                  }
                }    
| ID   { $$ = $1; }
| INTEGER   { $$ = $1; }
| CHAR  { $$ = $1; }
| STRING    { $$ = $1; }
;


%%

TreeNode* addOperatorNode(TreeNode* t1, TreeNode* t2, OperatorType op, int lineno)
{
    TreeNode* node = nullptr;
    if ((t1->getNodeType() == NODE_Const || t1->getNodeType() == NODE_Var) &&
        (t2->getNodeType() == NODE_Const || t2->getNodeType() == NODE_Var)) {
            // arithmetics type check
            TreeNode* node = new TreeNode(lineno, NODE_Op);
            node->setOperatorType(op);
            node->addChild(t1);
            node->addChild(t2);
    }
    return node;
}

bool checkFor(TreeNode* t1, TreeNode* t2)
{
    if(t1->getNodeType() != NODE_Stmt || t2->getNodeType() != NODE_Stmt) {
        return false;
    }
    return true;
}

bool checkIfCon(TreeNode* t1, TreeNode* t2, TreeNode* t3){
    if(t1->getStatementType() != STMT_ASIG && t1->getStatementType() != STMT_DECL) {
        return false;
    }
    if(t1->getStatementType() == STMT_ASIG) {
        // id should be declared before.
    }
    if(t2->getOperatorType() != OP_EQU && t2->getOperatorType() != OP_NEQ &&
        t2->getOperatorType() != OP_GT && t2->getOperatorType() != OP_GTQ &&
        t2->getOperatorType() != OP_LT && t2->getOperatorType() != OP_LTQ) {
            return false;
    }
}

bool checkWhile(TreeNode* t1, TreeNode* t2)
{
    if(t1->getNodeType() != NODE_Var && t1->getNodeType() != NODE_Const && t1->getNodeType != NODE_Op) {
        return false;
    }
    if(t2->getNodeType() != NODE_Stmt) {
        return false;
    }
    if(t1->getNodeType() != NODE_Var || t1->getNodeType() != NODE_Const) {
        if (t1->getDeclType() == D_STRING) {
            return false;
        }
    }
    return true;
}

bool checkIf(TreeNode* t1, TreeNode* t2, TreeNode* t3=nullptr)
{
    if (t1->getNodeType() != NODE_Var && t1->getNodeType() != NODE_Const && t1->getNodeType != NODE_Op) {
        return false;
    }
    if (t2->getNodeType() != NODE_Stmt) {
        return false;
    }
    if (t3 != nullptr && t3->getNodeType() != NODE_Stmt) {
        return false;
    }
    if (t1->getNodeType() != NODE_Var || t1->getNodeType() != NODE_Const) {
        if (t1->getDeclType() == D_STRING) {
            return false;
        }
    }
    return true;
}

bool checkAsg(TreeNode* t1, bool i)
{
    if (t1->getNodeType() != NODE_Var) {
        return false;
    }
    if (i) {
        if (t1->getDeclType() != D_INT) {
            return false;
        }
    }
    // id check
    if (1) {}
    return true;
}

TreeNode* setType(TreeNode* idlist, TreeNode* type, bool ifConst) {
    if(ifConst){
        // iterate nodes to set type and const
    } else {

    }
    return idlist;
}