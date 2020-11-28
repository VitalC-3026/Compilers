#ifndef TYPE_H
#define TYPE_H


enum NodeType
{   
    NODE_Prog,
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
    STMT_ASIG,
    STMT_EXPR,
    STMT_DECL,
    STMT_IF,
    STMT_WHILE,
    STMT_BREAK,
    STMT_CONTINUE,
    STMT_RETURN,
    STMT_SKIP
};

enum RadixType
{
    DECIMAL,
    OCTAL,
    HEX
}

enum AssignmentType
{
    ASIG,
    ADDASIG,
    MINASIG,
    MULASIG,
    DIVASIG,
    MODASIG,
    ADDASIGO,
    MINASIGO
}

#endif