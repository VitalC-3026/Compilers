#include "common.h"
#include <fstream>
#include <map>
#include <ostream>
#include <iostream>
#include <stack>
#include <cstring>
#include <vector>

using namespace std;

TreeNode *root = nullptr;
map<string, stack<idAttr>> identifierTable;
map<string, vector<functionAttr>> functionTable;
int TreeNode::count = 0;
int TreeNode::labelCount = 0;
extern int yyparse();
extern int lineno;
extern FILE *yyin;
extern FILE *yyout;
int error = 0;

int main(int argc, char *argv[]) 
{
    if (argc == 4) 
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
    // fputs("+++++++++++++Tree Structure++++++++++++++\n", yyout);
    // cout << "genTree start" << endl;
    // if (root != nullptr) {
    //     root->printAST();
    // }
    // cout << "genLabel start" << endl;
    root->recursiveGenLabel();
    ostream* asm_out = new ofstream(argv[3]);
    // cout << "genCode start" << endl;
    root->genCode(*asm_out);
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

