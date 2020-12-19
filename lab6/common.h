#ifndef COMMON_H
#define COMMON_H

#include "parseTree.h"
#define YYSTYPE TreeNode *

struct idAttr{
    int level;
    DeclType type;
    string value;
    int id;
};

#endif