#include "type.h"
#include <string>

using namespace std;

class TreeNode{
private:
    NodeType nodeType;
    TreeNode* children = nullptr;
    TreeNode* sibilings = nullptr;
    int nodeID;
    int lineno;

    OperatorType opType;
    StatementType stmtType;
    int intVal;
    char charVal;
    string stringVal;
    bool boolVal;
    string identifier;

public:
    void getNodeId();
    void printAST();
    void addChildren(TreeNode*);
    void addSiblings(TreeNode*);
    void setIntValue(int);
    void setCharValue(char);
    void setStringValue(string);
    void setBoolValue(bool);

public:
    TreeNode(NodeType);

public:
    int generateNodeID();
};