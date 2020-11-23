#include <iostream>
#include "common.h"


using std::cout;
using std::endl;

TreeNode *root = nullptr;

int main() 
{
    yyparse();
    if (root) {
        root->getNodeId();
        root->printAST();
    }
}

void yyerror(const char* msg)
{   
    cout << msg << endl;
}

//