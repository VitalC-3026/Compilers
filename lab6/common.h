#ifndef COMMON_H
#define COMMON_H

#include "parseTree.h"
#define YYSTYPE TreeNode *

struct idAttr{
    int level;
    DeclType type;
    string value;
    bool isConst = false;
    int id;
};

struct functionAttr{
    vector<DeclType> parameterList;
    DeclType returnValue;
};

struct constString{
    int num;
    string str;
};

struct localVar{
    string identifier;
    int id;
    int level;
    int offset = 0;
    int size;
    idAttr attr;
};

#endif