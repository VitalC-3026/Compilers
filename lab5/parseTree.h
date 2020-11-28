#include "type.h"
#include <string>

using namespace std;

class TreeNode{
private:
    NodeType nodeType;
    TreeNode* child = nullptr;
    TreeNode* sibling = nullptr;
    int nodeID;
    int lineno;

    OperatorType opType;
    StatementType stmtType;
    AssignmentType asigType;
    DeclType declType;
    RadixType radixType;
    int intVal;
    char charVal;
    string stringVal;
    bool boolVal;
    string identifier = "";

public:
    int getNodeId();
    void printAST();
    void addChild(TreeNode*);
    void addSibling(TreeNode*);
    void setNodeType(NodeType); // type of nodes
    void setStatementType(StatementType); // type of statement nodes
    void setAssignmentType(AssignmentType); // type of assignment
    void setOperatorType(OperatorType); // type of operator nodes
    void setDeclType(DeclType); // type of type nodes
    void setRadixType(RadixType); // type of integer nodes

    void setIntValue(int);
    void setCharValue(char);
    void setStringValue(string);
    void setBoolValue(bool);
    void setIdentifier(string);

    int getIntValue();
    char getCharValue();
    string getStringValue();
    bool getBoolValue();
    string getIdentifier();

    NodeType getNodeType();
    DeclType getDeclType();
    StatementType getStatementType();
    OperatorType getOperatorType();
    AssignmentType getAssignmentType();
    RadixType getRadixType();

public:
    TreeNode(int, NodeType);

public:
    int generateNodeID();
};