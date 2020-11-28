#include "pch.h"
#include "common.h"


using namespace std;

TreeNode *root = nullptr;
map<string, stack<int>> identifierTable;

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

