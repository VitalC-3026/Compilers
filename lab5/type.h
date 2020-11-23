#ifndef TYPE_H
#define TYPE_H


enum NodeType
{
    NODE_Const,
    NODE_Var, 
    NODE_Op, 
    NODE_Expr,
    NODE_Stmt,
    NODE_Func,
    NODE_Type
};

enum OperatorType
{
    OP_DOT,
    OP_REF,
    OP_POI,
    OP_NOT,

    OP_ADD,
    OP_MIN,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    
    OP_EQ,
    OP_GT,
    OP_LT,
    OP_GTQ,
    OP_LTQ,
    OP_NEQ,

    OP_AND,
    OP_OR
};

enum DeclType
{
    D_INT,
    D_CHAR,
    D_STRING,
    D_BOOL
};

enum StatementType
{
    TYPE_ASIG,
    TYPE_EXPR,
    TYPE_DECL,
    TYPE_IF,
    TYPE_WHILE,
    TYPE_CONTROL
};

#endif