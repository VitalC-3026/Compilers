#include "common.h"
#include <fstream>
#include <map>
#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

TreeNode *root = nullptr;
map<string, stack<idAttr>> identifierTable;
int TreeNode::count = 0;
int TreeNode::labelCount = 0;
extern int yyparse();
extern int lineno;
extern FILE *yyin;
extern FILE *yyout;
int error = 0;

int main(int argc, char *argv[]) 
{
    if (argc == 3) 
    {
        FILE *fin = fopen(argv[1], "r");
        FILE *fout = fopen(argv[2], "w");
        if (fin != nullptr) {
            yyin = fin;
        } else {
            cerr << "failed to open file to read: " << argv[1] << endl;
        }
        if (fout != nullptr) {
            yyout = fout;
        } else {
            cerr << "failed to open file to write: " << argv[2] << endl;
        }
    }

    yyparse();
    fputs("+++++++++++++Tree Structure++++++++++++++\n", yyout);
    if (root != nullptr) {
        root->printAST();
    }
    // if (error > 0){
    //     exit(-1);
    // }
    return 0;
}

void yyerror(const char* msg)
{   
    if(strcmp(msg, "syntax error") == 0){
        cerr << "syntax error " << lineno << endl;
        return;
    }
    cerr << msg << endl;
}

