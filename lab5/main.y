%{
    #include "common.h"
    #include <cassert>
    extern TreeNode* root;
    int yylex();
    extern void yyerror(const char*);
    extern int lineno, level;
    extern FILE* yyout;
    extern map<string, stack<idAttr>> identifierTable;
    extern int checkRange(string id, int level);
    TreeNode* addOperatorNode(TreeNode* t1, TreeNode* t2, OperatorType op, int lineno);
    bool checkFor(TreeNode* t1, TreeNode* t2);
    bool checkIfCon(TreeNode* t1, TreeNode* t2, TreeNode* t3);
    bool checkWhile(TreeNode* t1, TreeNode* t2);
    bool checkIf(TreeNode* t1, TreeNode* t2, TreeNode* t3);
    bool checkAsg(TreeNode* t1, bool i);
    void setType(TreeNode* &idlist, TreeNode* type, bool ifConst);
    string getValueOfId(TreeNode* n);
    void setEntryOfId(string identifier, int level, DeclType type, string value, int nodeId);
    int assignId(TreeNode* &id, TreeNode* expr);
    bool checkFuncCall(TreeNode* id, TreeNode* param);
%}

%token  ASG ADDASG MINASG MULASG DIVASG MODASG ADDASGO MINASGO
%token  DOT REF POI NOT
%token  ADD MIN MUL DIV MOD
%token  EQU GT LT GTQ LTQ NEQ
%token  AND OR
%token  LBRACE RBRACE LPAREN RPAREN
%token  ID INTEGER MAIN
%token  DEC OCT HEX
%token  CHAR BOOL STRING
%token  T_BOOL T_INT T_CHAR T_STRING T_VOID
%token  CONST STRUCT IF ELSE WHILE FOR RETURN CONTINUE BREAK
%token  PRINTF SCANF
%token  SEMICOLON COMMA


%right  ASG ADDASG MINASG MULASG DIVASG MODASG
%left   AND OR
%left   EQU GT LT GTQ LTQ NEQ
%left   ADD MIN
%left   MUL DIV MOD
%left   REF NOT
%left   DOT POI


%%

program 
: statements    { root = new TreeNode(0, NODE_Prog); root->addChild($1); fputs("root \n", yyout); }
;



statements
: statement { $$ = $1; fputs("statements <= statement \n", yyout);}
| statements statement { $$ = $1; $$->addSibling($2); fputs("statements <= statements statement \n", yyout);}
;

statement
: SEMICOLON { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_SKIP); fputs("skip \n", yyout);}
| declaration SEMICOLON { $$ = $1; fputs("statement <= declaration \n", yyout); }
| assignment SEMICOLON  { $$ = $1; fputs("statement <= assignment \n", yyout); }
| jump SEMICOLON { $$ = $1; fputs("statement <= jump \n", yyout); }
| loop      { $$ = $1; fputs("statement <= loop \n", yyout); }
| control   { $$ = $1; fputs("statement <= control \n", yyout); }
| function  { $$ = $1; fputs("statement <= function\n", yyout); }
;

function
: functionDecl SEMICOLON { $$ = $1; }
| functionCall SEMICOLON { $$ = $1; }
| functionDefi { $$ = $1; }
;

functionDefi
: type MAIN LBRACE RBRACE LPAREN statements RPAREN  {   TreeNode* node = new TreeNode(lineno, NODE_Func);
                                                        node->setFunctionType(FUNC_DEFI);
                                                        node->setDeclType($1->getDeclType());
                                                        node->setIdentifier((string)"main");
                                                        $1->setFunctionType(FUNC_TYPE);
                                                        node->addChild($1);
                                                        $6->setFunctionType(FUNC_BODY);
                                                        node->addChild($6);
                                                        $$ = node;
                                                    }
;

functionDecl
: type ID LBRACE RBRACE
;

functionCall
: SCANF LBRACE STRING scanfIdlist RBRACE {   TreeNode* node = new TreeNode(lineno, NODE_Func);
                                    node->setFunctionType(FUNC_CALL);
                                    TreeNode* id = new TreeNode(lineno, NODE_Func);
                                    id->setFunctionType(FUNC_ID);
                                    id->setIdentifier((string)"scanf");
                                    node->setIdentifier((string)"scanf");
                                    node->addChild($3);
                                    node->addChild($4);
                                    $$ = node;
                                    // if(checkFuncCall(id, $3)) {
                                    //     node->addChild(id);
                                    //     if (checkFuncIO($3)) {
                                    //         cout << id->getSibling() << endl;
                                    //         cout << $3->getSibling() << endl;
                                    //         node->addChild($3);
                                    //     } else {
                                    //         yyerror("check function scanf call failed\n");
                                    //     }
                                    //     $$ = node;
                                    // } else {
                                    //     yyerror("check function call failed!\n");
                                    // }
                                    fputs("function call <= scanf \n", yyout);
                                }
| PRINTF LBRACE STRING printfIdlist RBRACE  {   TreeNode* node = new TreeNode(lineno, NODE_Func);
                                                node->setFunctionType(FUNC_CALL);
                                                TreeNode* id = new TreeNode(lineno, NODE_Func);
                                                id->setFunctionType(FUNC_ID);
                                                id->setIdentifier((string)"printf");
                                                node->setIdentifier((string)"printf");
                                                node->addChild(id);
                                                node->addChild($3);
                                                node->addChild($4);
                                                $$ = node;
                                                fputs("function call <= printf \n", yyout);
                                            }
| ID LBRACE paramList RBRACE  { TreeNode* node = new TreeNode(lineno, NODE_Stmt);
                                node->setFunctionType(FUNC_CALL);
                                node->setIdentifier($1->getIdentifier());
                                if(checkFuncCall($1, $3)){
                                    node->addChild($1);
                                    node->addChild($3);
                                    $$ = node;
                                } else {
                                    yyerror("check function call failed!\n");
                                }
                                fputs("function call <= general \n", yyout);
                            }
;

paramList
: paramList COMMA expr  {   $3->setFunctionType(FUNC_PARAM);
                            $$ = $1;
                            $$->addSibling($3);
                            // cout << $$->getNodeId() << " " << $3->getNodeId();
                            fputs("param , expr\n", yyout);
                        }
| expr  {   $1->setFunctionType(FUNC_PARAM);
            $$ = $1; 
            // cout << $$->getNodeId();
            fputs("expr\n", yyout);
        }
|   {  TreeNode* node = new TreeNode(lineno, NODE_Func);
        node->setFunctionType(FUNC_PARAM);
        node->setDeclType(D_VOID);
        fputs("Empty paramList\n", yyout);
        $$ = node;
    }
; 

scanfIdlist
: scanfIdlist COMMA REF ID  {   $$ = $1;
                                $$->addSibling($4);
                                fputs("scanf idlist\n", yyout);
                            }
| COMMA REF ID  {   $$ = $3;
                    fputs("scanf id\n", yyout);
                }
;

printfIdlist
: printfIdlist COMMA ID  {   $$ = $1;
                            $$->addSibling($3);
                            fputs("printf idlist\n", yyout);
                        }
| COMMA ID  {   $$ = $2;
                fputs("printf id\n", yyout);
            }
;

idlist
: idlist COMMA ID ASG expr  {   $$ = $1; 
                                assignId($3, $5);
                                $3->generateNodeID();
                                $$->addSibling($3);
                                setEntryOfId($3->getIdentifier(), level, $3->getDeclType(), getValueOfId($5), $3->getNodeId());
                                fputs("idlist with assignment \n", yyout);
                            }
| idlist COMMA ID   {   $$ = $1; 
                        $3->generateNodeID();
                        $$->addSibling($3);
                        setEntryOfId($3->getIdentifier(), level, $3->getDeclType(), getValueOfId(nullptr), $3->getNodeId());
                        fputs("idlist \n", yyout);
                    }
| ID ASG expr   {   assignId($1, $3);
                    $1->generateNodeID();
                    $$ = $1;
                    setEntryOfId($1->getIdentifier(), level, $1->getDeclType(), getValueOfId($3), $1->getNodeId());
                    fputs("id with assignment \n", yyout);
                }
| ID            {   $$ = $1;
                    $1->generateNodeID();
                    setEntryOfId($1->getIdentifier(), level, $1->getDeclType(), getValueOfId(nullptr), $1->getNodeId());
                    fputs("id \n", yyout);
                }
;

declaration
: type idlist   {   setType($2, $1, 0); $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_DECL); $$->addChild($1); $$->addChild($2); fputs("declaration <= variable \n", yyout); }
| CONST type idlist {   setType($3, $2, 1); $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_DECL); $$->addChild($2); $$->addChild($3); fputs("declaration <= const \n", yyout); }
;

type
: T_BOOL { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_BOOL); fputs("type <= bool \n", yyout); }
| T_INT { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_INT); fputs("type <= int \n", yyout); }
| T_CHAR { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_CHAR); fputs("type <= char \n", yyout); }
| T_STRING { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_STRING); fputs("type <= string \n", yyout); }
| T_VOID { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_VOID); fputs("type <= bool \n", yyout); }
;

loop
: FOR LBRACE forcon RBRACE LPAREN statements RPAREN {   if(checkFor($3, $6)) {
                                                            $$ = new TreeNode(lineno, NODE_Stmt);
                                                            $$->addChild($3);
                                                            $$->addChild($6);
                                                            $$->setStatementType(STMT_FOR);
                                                            // fputs(to_string(level).c_str(), yyout);
                                                        } else {
                                                            yyerror("FOR error, check failed!");
                                                        }
                                                        fputs("loop <= for \n", yyout);                                                        
                                                    }
| WHILE LBRACE expr RBRACE LPAREN statements RPAREN {   if(checkWhile($3, $6)) {
                                                            $$ = new TreeNode(lineno, NODE_Stmt);
                                                            $$->addChild($3);
                                                            $$->addChild($6);
                                                            $$->setStatementType(STMT_WHILE);
                                                        } else {
                                                            yyerror("WHILE error, check failed!");
                                                        }
                                                        fputs("loop <= while \n", yyout); 
                                                    }
;

forcon
: declaration SEMICOLON expr SEMICOLON assignment { if(checkIfCon($1, $3, $5)) {
                                                        // fputs(to_string(level).c_str(), yyout);
                                                        $$ = new TreeNode(lineno, NODE_Stmt);
                                                        $$->setStatementType(STMT_FORCON);
                                                        $$->addChild($1);
                                                        $$->addChild($3);
                                                        $$->addChild($5);
                                                    } else {
                                                        yyerror("FOR CON error, check failed!");
                                                    }
                                                    fputs("for conditions \n", yyout);
                                                }
| assignment SEMICOLON expr SEMICOLON assignment { if(checkIfCon($1, $3, $5)) {
                                                        $$ = new TreeNode(lineno, NODE_Stmt);
                                                        $$->setStatementType(STMT_FORCON);
                                                        $$->addChild($1);
                                                        $$->addChild($3);
                                                        $$->addChild($5);
                                                    } else {
                                                        yyerror("FOR CON error, check failed!");
                                                    }
                                                    fputs("for conditions \n", yyout);
                                                }
;

control
: IF LBRACE expr RBRACE LPAREN statements RPAREN    {   if(checkIf($3, $6, NULL)) {
                                                            $$ = new TreeNode(lineno, NODE_Stmt);
                                                            $$->addChild($3);
                                                            $$->addChild($6);
                                                            $$->setStatementType(STMT_IF);
                                                        } else {
                                                            yyerror("IF error, check failed!");
                                                        }
                                                        fputs("control <= if then \n", yyout); 
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
                                                                                    fputs("control <= if then else \n", yyout);  
                                                                                }
;

jump
: BREAK { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_BREAK); fputs("jump <= break \n", yyout); }
| CONTINUE { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_CONTINUE); fputs("jump <= continue \n", yyout); }
| RETURN  expr { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_RETURN); $$->addChild($2); fputs("jump <= return expr \n", yyout); }
| RETURN { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_RETURN); fputs("jump <= return \n", yyout); }
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
                        fputs("assignment <= = \n", yyout);
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
                        fputs("assignment <= += \n", yyout);
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
                        fputs("assignment <= -= \n", yyout);
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
                        fputs("assignment <= *= \n", yyout);
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
                        fputs("assignment <= \\= \n", yyout);
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
                        fputs("assignment <= %= \n", yyout);
                    }
| ADDASGO ID        {   if(checkAsg($2, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ADDASIGO);
                            $$->addChild($2);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                        fputs("assignment <= ++i \n", yyout);
                    }
| MINASGO ID        {   if(checkAsg($2, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MINASIGO);
                            $$->addChild($2);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                        fputs("assignment <= --i \n", yyout);
                    }
| ID ADDASGO        {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ADDASIGO);
                            $$->addChild($1);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                        fputs("assignment <= i++ \n", yyout);
                    }
| ID MINASGO        {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MINASIGO);
                            $$->addChild($1);
                        } else {
                            yyerror("ASSIGN error!");
                        }
                        fputs("assignment <= i-- \n", yyout);
                    }
;

expr
: expr ADD expr {   TreeNode* node = addOperatorNode($1, $3, OP_ADD, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr MIN expr {   TreeNode* node = addOperatorNode($1, $3, OP_MIN, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr MUL expr {   TreeNode* node = addOperatorNode($1, $3, OP_MUL, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr DIV expr {   TreeNode* node = addOperatorNode($1, $3, OP_DIV, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr MOD expr {   TreeNode* node = addOperatorNode($1, $3, OP_MOD, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr AND expr {   TreeNode* node = addOperatorNode($1, $3, OP_AND, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr OR  expr {   TreeNode* node = addOperatorNode($1, $3, OP_OR, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr GT  expr {   TreeNode* node = addOperatorNode($1, $3, OP_GT, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr GTQ expr {   TreeNode* node = addOperatorNode($1, $3, OP_GTQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr LT  expr {   TreeNode* node = addOperatorNode($1, $3, OP_LT, lineno); 
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr LTQ expr {   TreeNode* node = addOperatorNode($1, $3, OP_LTQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr NEQ expr {   TreeNode* node = addOperatorNode($1, $3, OP_NEQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| expr EQU expr {   TreeNode* node = addOperatorNode($1, $3, OP_EQU, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    $$ = node;
                }
| NOT  expr     { if($2->getNodeType() == NODE_Var || $2->getNodeType() == NODE_ConstVar || $2->getNodeType() == NODE_Const) {
                    if ($1->getDeclType() != D_STRING) {
                        TreeNode* node = new TreeNode(lineno, NODE_Op);
                        node->setStatementType(STMT_EXPR);
                        node->setOperatorType(OP_NOT);
                        node->setDeclType($2->getDeclType());
                        node->addChild($2);
                        $$ = node;
                    }
                  } else {
                      yyerror("NOT Type error, this node is a string.");
                  }
                }
| ADD  expr     { $$ = $2;}
| MIN  expr     { if(($2->getNodeType() == NODE_Var || $2->getNodeType() == NODE_ConstVar  || $2->getNodeType() == NODE_Const) && $2->getDeclType() == D_INT) {
                    int value = $2->getIntValue();
                    TreeNode* node = new TreeNode(lineno, NODE_Op);
                    node->setStatementType(STMT_EXPR);
                    node->setOperatorType(OP_MIN);
                    node->setDeclType($2->getDeclType());
                    node->setIntValue(-value);
                    node->addChild($2);
                    $$ = node;
                  } else {
                      yyerror("UMINUS Type error, this node is not an integer.");
                  }
                }
| REF  expr     { if($2->getNodeType() == NODE_Var || $2->getNodeType() == NODE_ConstVar) {
                    if ($1->getIdentifier() != "") {
                        TreeNode* node = new TreeNode(lineno, NODE_Op);
                        node->setStatementType(STMT_EXPR);
                        node->setOperatorType(OP_REF);
                        node->setDeclType($2->getDeclType());
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
    if ((t1->getNodeType() == NODE_Const || t1->getNodeType() == NODE_Var || t1->getNodeType() == NODE_ConstVar) &&
        (t2->getNodeType() == NODE_Const || t2->getNodeType() == NODE_Var || t2->getNodeType() == NODE_ConstVar)) {
            // arithmetics type check
        if (t1->getDeclType() != t2->getDeclType()) {
            cerr << "expression: Two operands have different types." << endl;
        }
        node = new TreeNode(lineno, NODE_Op);
        node->setDeclType(t1->getDeclType());
        node->setStatementType(STMT_EXPR);
        node->setOperatorType(op);
        node->addChild(t1);
        node->addChild(t2);
    } else if(t1->getStatementType() == STMT_EXPR || t2->getStatementType() == STMT_EXPR) {
        if (t1->getDeclType() != t2->getDeclType()) {
            cerr << "expression: Two operands have different types." << endl;
        }
        node = new TreeNode(lineno, NODE_Op);
        node->setStatementType(STMT_EXPR);
        node->setDeclType(t1->getDeclType());
        node->setOperatorType(op);
        node->addChild(t1);
        node->addChild(t2);
    }
    return node;
}

bool checkFor(TreeNode* t1, TreeNode* t2)
{
    if((t1->getNodeType() != NODE_Stmt && t1->getNodeType() != NODE_Func) || (t2->getNodeType() != NODE_Stmt && t2->getNodeType() != NODE_Func)) {
        return false;
    }
    return true;
}

bool checkIfCon(TreeNode* t1, TreeNode* t2, TreeNode* t3){
    if(t1->getStatementType() != STMT_ASIG && t1->getStatementType() != STMT_DECL) {
        // cout << "check declaration/assignment" << endl;
        return false;
    }
    if(t1->getStatementType() == STMT_ASIG) {
        // id should be declared before.
    }
    if(t2->getOperatorType() != OP_EQU && t2->getOperatorType() != OP_NEQ &&
        t2->getOperatorType() != OP_GT && t2->getOperatorType() != OP_GTQ &&
        t2->getOperatorType() != OP_LT && t2->getOperatorType() != OP_LTQ) {
            // cout << "check comparison" << endl;
            return false;
    }
    return true;
}

bool checkWhile(TreeNode* t1, TreeNode* t2)
{
    if(t1->getNodeType() != NODE_Var && t1->getNodeType() != NODE_Const  && t1->getNodeType() == NODE_ConstVar && t1->getNodeType() != NODE_Op) {
        return false;
    }
    if(t2->getNodeType() != NODE_Stmt) {
        return false;
    }
    if(t1->getNodeType() == NODE_Var || t1->getNodeType() == NODE_Const || t1->getNodeType() == NODE_ConstVar) {
        if (t1->getDeclType() == D_STRING) {
            return false;
        }
    }
    return true;
}

bool checkIf(TreeNode* t1, TreeNode* t2, TreeNode* t3)
{
    if (t1->getNodeType() != NODE_Var && t1->getNodeType() != NODE_Const  && t1->getNodeType() != NODE_ConstVar && t1->getNodeType() != NODE_Op) {
        // cout << "checkIf 1" << endl;
        return false;
    }
    if (t2->getNodeType() != NODE_Stmt && t2->getNodeType() != NODE_Func) {
        // cout << "checkIf 2" << endl;
        // cout << TreeNode::nodeType2String(t2->getNodeType()) << endl;
        return false;
    }
    if (t3 != NULL && t3->getNodeType() != NODE_Stmt) {
        // cout << "checkIf 3" << endl;
        return false;
    }
    if (t1->getNodeType() == NODE_Var || t1->getNodeType() == NODE_Const  || t1->getNodeType() == NODE_ConstVar) {
        if (t1->getDeclType() == D_STRING) {
            // cout << "checkIf 4" << endl;
            return false;
        }
    }
    return true;
}

bool checkAsg(TreeNode* t1, bool i)
{
    assert (t1 != nullptr);
    if (t1->getNodeType() != NODE_Var) {
        string msg = (string)"variable should be a left value instead of" + TreeNode::nodeType2String(t1->getNodeType());
        yyerror(msg.c_str());
        return false;
    }
    if (i) {
        if (t1->getDeclType() != D_INT) {
            return false;
        }
    }
    // id check
    int res = checkRange(t1->getIdentifier(), level);
    if(res == -1){
        return false;
    }
    // if (identifierTable.find(t1->getIdentifier()) == identifierTable.end()) {
    //     return false;
    // } else {
    //     stack<idAttr> s = identifierTable.find(t1->getIdentifier())->second;
    //     // cout << "checkAsg" << endl;
    //     if (s.size() == 0) {
    //         return false;
    //     }
    // }
    return true;
}

void setType(TreeNode* &idlist, TreeNode* type, bool ifConst) {
    if(ifConst){
        // iterate nodes to set type and const
        // cout << "ifConst here" << endl;
        TreeNode* node = idlist;
        assert (node != nullptr);
        node->setNodeType(NODE_ConstVar);
        node->setDeclType(type->getDeclType());
        while ((node = node->getSibling()) != nullptr) {
            node->setNodeType(NODE_ConstVar);
            node->setDeclType(type->getDeclType());
        }
    } else {
        TreeNode* node = idlist;
        assert (node != nullptr);
        node->setNodeType(NODE_Var);
        node->setDeclType(type->getDeclType());
        while ((node = node->getSibling()) != nullptr) {
            node->setNodeType(NODE_Var);
            node->setDeclType(type->getDeclType());
        }
    }
}

string getValueOfId(TreeNode* n) {
    if (n == nullptr){
        string res = to_string(0);
        return res;
    }
    switch(n->getDeclType()){
        case D_BOOL:
            return to_string((int)n->getBoolValue());
        case D_INT:
            return to_string(n->getIntValue());
        case D_CHAR:{
            string res(1, n->getCharValue());
            return res;
        }
        case D_STRING:{
            return n->getStringValue();
        }
        default:
            return (string)"";
    }
}

void setEntryOfId(string identifier, int level, DeclType type, string value, int nodeId){
    // cout << identifier << " declared in level " << level << endl;
    idAttr attr;
    attr.level = level;
    attr.type = type;
    // type check
    attr.value = value;
    attr.id = nodeId;
    stack<idAttr> s;
    if(identifierTable.find(identifier) != identifierTable.end()) {
        s = (identifierTable.find(identifier)->second);
    }
    s.push(attr);
    identifierTable[identifier] = s;
}

int assignId(TreeNode* &id, TreeNode* expr){
    id->setDeclType(expr->getDeclType());
    switch(id->getDeclType()){
        case D_BOOL:
        {
            id->setBoolValue(expr->getBoolValue());
            break;
        }
        case D_CHAR:
        {
            id->setCharValue(expr->getCharValue());
            break;
        }
        case D_INT:
        {
            id->setIntValue(expr->getIntValue());
            break;
        }
        case D_STRING:
        {
            id->setStringValue(expr->getStringValue());
            break;
        }
    }
    return 0;
    
}

bool checkFuncCall(TreeNode* id, TreeNode* param){
    // cout << "checkFuncCall" << endl;
    if (identifierTable.find(id->getIdentifier()) == identifierTable.end()) {
        if (id->getIdentifier() != (string)"scanf" && id->getIdentifier() != (string)"printf") {
            return false;
        }
    }
    if (id->getFunctionType() != FUNC_ID) {
        return false;
    }
    if (param->getFunctionType() != FUNC_PARAM) {
        return false;
    }
    return true;
}
