%{
    #include "common.h"
    #include <cassert>
    extern TreeNode* root;
    int yylex();
    extern void yyerror(const char*);
    extern int lineno, level, error;
    extern FILE* yyout;
    extern map<string, stack<idAttr>> identifierTable;
    extern map<string, vector<functionAttr>> functionTable;
    extern int checkRange(string id, int level);
    TreeNode* addOperatorNode(TreeNode* t1, TreeNode* t2, OperatorType op, int lineno);
    bool checkFor(TreeNode* t1, TreeNode* t2);
    bool checkForCon(TreeNode* t1, TreeNode* t2, TreeNode* t3);
    bool checkWhile(TreeNode* t1, TreeNode* t2);
    bool checkIf(TreeNode* t1, TreeNode* t2, TreeNode* t3);
    bool checkAsg(TreeNode* t1, bool i);
    void setType(TreeNode* &idlist, TreeNode* type, bool ifConst);
    string getValueOfId(TreeNode* n);
    bool setEntryOfId(string identifier, int level, DeclType type, string value, int nodeId);
    int assignId(TreeNode* &id, TreeNode* expr);
    bool checkFuncCall(TreeNode* id, TreeNode* param);
    void generateFuncTable(string funcName, TreeNode* parameterList, TreeNode* returnType);
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
| jump SEMICOLON { $$ = $1; }
| loop      { $$ = $1; }
| control   { $$ = $1; }
| function  { $$ = $1; }
;

function
: functionDecl SEMICOLON { $$ = new TreeNode(lineno, NODE_Stmt); $$->addChild($1); }
| functionCall SEMICOLON { $$ = new TreeNode(lineno, NODE_Stmt); $$->addChild($1); }
| functionDefi { $$ = new TreeNode(lineno, NODE_Stmt); $$->addChild($1); }
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
                                                        generateFuncTable((string)"main", nullptr, $1);
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
                                    node->addChild(id);
                                    node->addChild($3);
                                    node->addChild($4);
                                    $$ = node;
                                    
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
                            }
;

paramList
: paramList COMMA expr  {   $3->setFunctionType(FUNC_PARAM);
                            $$ = $1;
                            $$->addSibling($3);
                        }
| expr  {   $1->setFunctionType(FUNC_PARAM);
            $$ = $1; 
        }
|   {  TreeNode* node = new TreeNode(lineno, NODE_Func);
        node->setFunctionType(FUNC_PARAM);
        node->setDeclType(D_VOID);
        $$ = node;
    }
; 

scanfIdlist
: scanfIdlist COMMA REF ID  {   $$ = $1;
                                $$->addSibling($4);
                            }
| COMMA REF ID  {   $$ = $3; }
;

printfIdlist
: printfIdlist COMMA ID  {   $$ = $1;
                            $$->addSibling($3);
                        }
| COMMA ID  {   $$ = $2;
            }
;

idlist
: idlist COMMA ID ASG expr  {   $$ = $1; 
                                assignId($3, $5);
                                $3->addChild($5);
                                $$->addSibling($3);
                                if (setEntryOfId($3->getIdentifier(), level, $3->getDeclType(), getValueOfId($5), $3->getNodeId())){
                                    string msg = (string)"Node@" + to_string($3->getNodeId()) + (string)" ID : redefined.";
                                    yyerror(msg.c_str());
                                    $3->setIsAlive(false);
                                }
                            }
| idlist COMMA ID   {   $$ = $1; 
                        $$->addSibling($3);
                        if (setEntryOfId($3->getIdentifier(), level, $3->getDeclType(), getValueOfId(nullptr), $3->getNodeId())){
                            string msg = (string)"Node@" + to_string($3->getNodeId()) + (string)" ID : redefined.";
                            yyerror(msg.c_str());
                            $3->setIsAlive(false);
                        }
                    }
| ID ASG expr   {   assignId($1, $3);
                    $1->addChild($3);
                    $$ = $1;
                    if (setEntryOfId($1->getIdentifier(), level, $1->getDeclType(), getValueOfId($3), $1->getNodeId())){
                        string msg = (string)"Node@" + to_string($1->getNodeId()) + (string)" ID : redefined.";
                        yyerror(msg.c_str());
                        $1->setIsAlive(false);
                    }
                }
| ID            {   $$ = $1;
                    if (setEntryOfId($1->getIdentifier(), level, $1->getDeclType(), getValueOfId(nullptr), $1->getNodeId())){
                        string msg = (string)"Node@" + to_string($1->getNodeId()) + (string)" ID : redefined.";
                        yyerror(msg.c_str());
                        $1->setIsAlive(false);
                    }
                }
;

declaration
: type idlist   {   setType($2, $1, 0); $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_DECL); $$->addChild($1); $$->addChild($2); }
| CONST type idlist {   setType($3, $2, 1); $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_DECL); $$->addChild($2); $$->addChild($3); }
;

type
: T_BOOL { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_BOOL); }
| T_INT { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_INT); }
| T_CHAR { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_CHAR); }
| T_STRING { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_STRING); }
| T_VOID { $$ = new TreeNode(lineno, NODE_Type); $$->setDeclType(D_VOID); }
;

loop
: FOR LBRACE forcon RBRACE LPAREN statements RPAREN {   if(checkFor($3, $6)) {
                                                            $$ = new TreeNode(lineno, NODE_Stmt);
                                                            $$->addChild($3);
                                                            $$->addChild($6);
                                                            $$->setStatementType(STMT_FOR);
                                                            $$->typeCheck();
                                                        } else {
                                                            string msg = (string)"Line@" + to_string(lineno) + (string)" For : Not syntactically defined.";
                                                            yyerror(msg.c_str());
                                                        }                                                      
                                                    }
| WHILE LBRACE expr RBRACE LPAREN statements RPAREN {   if(checkWhile($3, $6)) {
                                                            $$ = new TreeNode(lineno, NODE_Stmt);
                                                            $$->addChild($3);
                                                            $$->addChild($6);
                                                            $$->setStatementType(STMT_WHILE);
                                                            $$->typeCheck();
                                                        } else {
                                                            string msg = (string)"Line@" + to_string(lineno) + (string)" While : Not syntactically defined.";
                                                            yyerror(msg.c_str());
                                                        }
                                                    }
;

forcon
: declaration SEMICOLON expr SEMICOLON assignment { if(checkForCon($1, $3, $5)) {
                                                        $$ = new TreeNode(lineno, NODE_Stmt);
                                                        $$->setStatementType(STMT_FORCON);
                                                        $$->addChild($1);
                                                        $$->addChild($3);
                                                        $$->addChild($5);
                                                    } else {
                                                        string msg = (string)"Line@" + to_string(lineno) + (string)" ForCon : Not syntactically defined.";
                                                        yyerror(msg.c_str());
                                                    }
                                                }
| assignment SEMICOLON expr SEMICOLON assignment { if(checkForCon($1, $3, $5)) {
                                                        $$ = new TreeNode(lineno, NODE_Stmt);
                                                        $$->setStatementType(STMT_FORCON);
                                                        $$->addChild($1);
                                                        $$->addChild($3);
                                                        $$->addChild($5);
                                                    } else {
                                                        string msg = (string)"Line@" + to_string(lineno) + (string)" ForCon : Not syntactically defined.";
                                                        yyerror(msg.c_str());
                                                    }
                                                }
;

control
: IF LBRACE expr RBRACE LPAREN statements RPAREN    {   if(checkIf($3, $6, NULL)) {
                                                            $$ = new TreeNode(lineno, NODE_Stmt);
                                                            $$->addChild($3);
                                                            $$->addChild($6);
                                                            $$->setStatementType(STMT_IF);
                                                            $$->typeCheck();
                                                        } else {
                                                            string msg = (string)"Line@" + to_string(lineno) + (string)" ForCon : Not syntactically defined.";
                                                            yyerror(msg.c_str());
                                                        }
                                                    }
| IF LBRACE expr RBRACE LPAREN statements RPAREN ELSE LPAREN statements RPAREN  {   if(checkIf($3, $6, $10)) {
                                                                                        $$ = new TreeNode(lineno, NODE_Stmt);
                                                                                        $$->addChild($3);
                                                                                        $$->addChild($6);
                                                                                        $$->addChild($10);
                                                                                        $$->setStatementType(STMT_IF);
                                                                                        $$->typeCheck();
                                                                                    } else {
                                                                                        string msg = (string)"Line@" + to_string(lineno) + (string)" ForCon : Not syntactically defined.";
                                                                                        yyerror(msg.c_str());
                                                                                    }
                                                                                }
;

jump
: BREAK { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_BREAK); }
| CONTINUE { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_CONTINUE); }
| RETURN  expr { $$ = new TreeNode(lineno, NODE_Stmt); $$->setStatementType(STMT_RETURN); $$->addChild($2); }
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
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| ID ADDASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ADDASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| ID MINASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MINASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| ID MULASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MULASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| ID DIVASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(DIVASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| ID MODASG expr    {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MODASIG);
                            $$->addChild($1);
                            $$->addChild($3);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| ADDASGO ID        {   if(checkAsg($2, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ADDASIGO);
                            $$->addChild($2);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| MINASGO ID        {   if(checkAsg($2, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MINASIGO);
                            $$->addChild($2);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| ID ADDASGO        {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(ADDASIGO);
                            $$->addChild($1);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
| ID MINASGO        {   if(checkAsg($1, 1)) {
                            $$ = new TreeNode(lineno, NODE_Stmt);
                            $$->setStatementType(STMT_ASIG);
                            $$->setAssignmentType(MINASIGO);
                            $$->addChild($1);
                            $$->typeCheck();
                        } else {
                            string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            yyerror(msg.c_str());
                        }
                    }
;

expr
: expr ADD expr {   TreeNode* node = addOperatorNode($1, $3, OP_ADD, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    } else {
                        $$ = node;
                    }
                    
                }
| expr MIN expr {   TreeNode* node = addOperatorNode($1, $3, OP_MIN, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    } else {
                        $$ = node;
                    }
                    
                }
| expr MUL expr {   TreeNode* node = addOperatorNode($1, $3, OP_MUL, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr DIV expr {   TreeNode* node = addOperatorNode($1, $3, OP_DIV, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr MOD expr {   TreeNode* node = addOperatorNode($1, $3, OP_MOD, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr AND expr {   TreeNode* node = addOperatorNode($1, $3, OP_AND, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr OR  expr {   TreeNode* node = addOperatorNode($1, $3, OP_OR, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr GT  expr {   TreeNode* node = addOperatorNode($1, $3, OP_GT, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr GTQ expr {   TreeNode* node = addOperatorNode($1, $3, OP_GTQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr LT  expr {   TreeNode* node = addOperatorNode($1, $3, OP_LT, lineno); 
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr LTQ expr {   TreeNode* node = addOperatorNode($1, $3, OP_LTQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr NEQ expr {   TreeNode* node = addOperatorNode($1, $3, OP_NEQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
                }
| expr EQU expr {   TreeNode* node = addOperatorNode($1, $3, OP_EQU, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        $$ = node;
                    }
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
| ID   {    if(identifierTable.find($1->getIdentifier()) == identifierTable.end()) {
                string msg = (string)"Node@" + to_string($1->getNodeId()) + (string)" NODE_Var/ConstVar : ID not defined.";
                yyerror(msg.c_str());
            }
            $$ = $1;
            
        }
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
        node = new TreeNode(lineno, NODE_Op);
        node->setDeclType(t1->getDeclType());
        node->setStatementType(STMT_EXPR);
        node->setOperatorType(op);
        node->addChild(t1);
        node->addChild(t2);
        if (node->typeCheck() == false) { error++; }
        
    } else if(t1->getStatementType() == STMT_EXPR || t2->getStatementType() == STMT_EXPR) {
        node = new TreeNode(lineno, NODE_Op);
        node->setStatementType(STMT_EXPR);
        node->setDeclType(t1->getDeclType());
        node->setOperatorType(op);
        node->addChild(t1);
        node->addChild(t2);
        if (node->typeCheck() == false) { error++; }
    }
    return node;
}

bool checkFor(TreeNode* t1, TreeNode* t2)
{
    // if((t1->getNodeType() != NODE_Stmt && t1->getNodeType() != NODE_Func) || (t2->getNodeType() != NODE_Stmt && t2->getNodeType() != NODE_Func)) {
    //     return false;
    // }
    if(t1->getNodeType() != NODE_Stmt || t2->getNodeType() != NODE_Stmt) {
        return false;
    }
    return true;
}

bool checkForCon(TreeNode* t1, TreeNode* t2, TreeNode* t3){
    if(t1->getStatementType() != STMT_ASIG && t1->getStatementType() != STMT_DECL) {
        return false;
    }
    if(t3->getStatementType() != STMT_ASIG || t3->getNodeType() != NODE_Stmt) {
        return false;
    }
    // if(t1->getStatementType() == STMT_ASIG) {
    //     // id should be declared before. checked in ASIG    
    // }
    if (t2->getNodeType() == NODE_Stmt){

    }
    if(t2->getOperatorType() != OP_EQU && t2->getOperatorType() != OP_NEQ &&
        t2->getOperatorType() != OP_GT && t2->getOperatorType() != OP_GTQ &&
        t2->getOperatorType() != OP_LT && t2->getOperatorType() != OP_LTQ) {
            // cout << "check comparison" << endl;
            return false;
    }
    if(t1->getStatementType() == STMT_DECL) {
        TreeNode* node = t1->getChild();
        while(node != nullptr) {
            if (node->getNodeType() == NODE_Var){
                if(identifierTable.find(node->getIdentifier()) != identifierTable.end()) {
                    stack<idAttr> s = identifierTable.find(node->getIdentifier())->second;
                    idAttr attr = s.top();
                    attr.level += 1;
                    s.pop();
                    s.push(attr);
                    identifierTable[node->getIdentifier()] = s;
                }
            }
            node = node->getSibling();
        }
    }
    

    return true;
}

bool checkWhile(TreeNode* t1, TreeNode* t2)
{
    if(t2->getNodeType() != NODE_Stmt) {
        string msg = (string)"Node@" + to_string(t2->getNodeId()) + (string)" NODE_While: unexpected type for while body.";
        yyerror(msg.c_str());
        return false;
    }
    return true;
}

bool checkIf(TreeNode* t1, TreeNode* t2, TreeNode* t3)
{
    if (t2->getNodeType() != NODE_Stmt) {
        string msg = (string)"Node@" + to_string(t2->getNodeId()) + (string)" NODE_If: unexpected type for true statements";
        yyerror(msg.c_str());
        return false;
    }
    if (t3 != NULL && t3->getNodeType() != NODE_Stmt) {
        string msg = (string)"Node@" + to_string(t2->getNodeId()) + (string)" NODE_If: unexpected type for false statements";
        yyerror(msg.c_str());
        return false;
    }
    return true;
}

bool checkAsg(TreeNode* t1, bool i)
{
    assert (t1 != nullptr);
    // if (t1->getNodeType() != NODE_Var) {
    //     string msg = (string)"variable should be a left value instead of" + TreeNode::nodeType2String(t1->getNodeType());
    //     yyerror(msg.c_str());
    //     return false;
    // }
    // if (i) {
    //     if (t1->getDeclType() != D_INT) {
    //         return false;
    //     }
    // }
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
        node->setStatementType(STMT_DECL);
        node->setDeclType(type->getDeclType());
        stack<idAttr> s = identifierTable.find(node->getIdentifier())->second;
        while(!s.empty()) {
            idAttr attr = s.pop();
            attr.isConst = true;
            s.push(attr);
        }
        identifierTable[node->getIdentifier()] = s;
        while ((node = node->getSibling()) != nullptr) {
            node->setNodeType(NODE_ConstVar);
            node->setDeclType(type->getDeclType());
            node->setStatementType(STMT_DECL);
            stack<idAttr> s = identifierTable.find(node->getIdentifier())->second;
        while(!s.empty()) {
            idAttr attr = s.pop();
            attr.isConst = true;
            s.push(attr);
        }
        identifierTable[node->getIdentifier()] = s;
        }
    } else {
        TreeNode* node = idlist;
        assert (node != nullptr);
        node->setNodeType(NODE_Var);
        node->setStatementType(STMT_DECL);
        node->setDeclType(type->getDeclType());
        while ((node = node->getSibling()) != nullptr) {
            node->setNodeType(NODE_Var);
            node->setStatementType(STMT_DECL);
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

bool setEntryOfId(string identifier, int level, DeclType type, string value, int nodeId){
    // cout << identifier << " declared in level " << level << endl;
    idAttr attr;
    attr.level = level;
    attr.type = type;
    // type check
    attr.value = value;
    attr.id = nodeId;
    bool redefined = false;
    stack<idAttr> s, tmp;
    if(identifierTable.find(identifier) != identifierTable.end()) {
        s = (identifierTable.find(identifier)->second);
        tmp = (identifierTable.find(identifier)->second);
    }
    while (!tmp.empty()) {
        if(tmp.top().level == level){
            redefined = true;
            break;
        }
        tmp.pop();
    }
    if(redefined){
        return true;
    } else{
        s.push(attr);
        identifierTable[identifier] = s;
        return false;
    }
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
        default:
            break;
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

bool compareFuncAttr(functionAttr a1, functionAttr a2) {
    if (a1.returnValue != a2.returnValue) {
        return false;
    }
    if (a1.parameterList.size() != a2.parameterList.size()) {
        return false;
    }
    for(int i = 0; i < a1.parameterList.size(); i++) {
        if (a1.parameterList[i] != a2.parameterList[i]) {
            return false;
        }
    }
    return true;
}

void generateFuncTable(string funcName, TreeNode* parameterList, TreeNode* returnType){
    functionAttr attr;
    attr.returnValue = returnType->getDeclType();
    if (parameterList != nullptr) {
        attr.parameterList.push_back(parameterList->getDeclType());
        TreeNode* node = parameterList->getSibling();
        bool flagEqual = false;
        while(node != nullptr) {
            attr.parameterList.push_back(node->getDeclType());
            node = node->getSibling();
        }
    }
    
    if (functionTable.find(funcName) != functionTable.end()) {
        vector<functionAttr> v = functionTable.find(funcName)->second;
        for(vector<functionAttr>::iterator it=v.begin(); it!=v.end();it++){
            if(compareFuncAttr(*it, attr)) {
                flagEqual = true;
                break;
            }
        }
        if (!flagEqual) {
            v.push_back(attr);
            functionTable[funcName] = v;
        }
    } 
    else { 
        vector<functionAttr> v;
        v.push_back(attr);
        functionTable[funcName] = v;
    }
}


