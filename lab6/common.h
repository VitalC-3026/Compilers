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

struct tempVar{
    int num;
    int value;
};

#endif