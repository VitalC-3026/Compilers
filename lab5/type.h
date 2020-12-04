#ifndef TYPE_H
#define TYPE_H


enum NodeType
{   
    NODE_Prog,
    NODE_Const,
    NODE_ConstVar,
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
    
    OP_EQU,
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
    D_BOOL,
    D_VOID
};

enum StatementType
{
    STMT_ASIG,
    STMT_EXPR,
    STMT_DECL,
    STMT_IF,
    STMT_FOR,
    STMT_WHILE,
    STMT_BREAK,
    STMT_CONTINUE,
    STMT_RETURN,
    STMT_SKIP,
    STMT_FORCON
};

enum RadixType
{
    DECIMAL,
    OCTAL,
    HEXA
};

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
};

enum FunctionType
{
    FUNC_DECL,
    FUNC_DEFI,
    FUNC_CALL,
    FUNC_TYPE,
    FUNC_ID,
    FUNC_PARAM,
    FUNC_BODY
};

#endif