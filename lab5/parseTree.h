#ifndef PARSETREE_H
#define PARSETREE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <map>
#include <stack>

using namespace std;

#include "type.h"

class TreeNode{
private:
    static int count;

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
    void generateNodeID();
    int getNodeId();
    void setNodeId(int i);
    void printAST();
    void printInfo();
    void addChild(TreeNode*&);
    void addSibling(TreeNode*&);
    TreeNode* getChild();
    TreeNode* getSibling();

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

    TreeNode(int, NodeType);
    // TreeNode();
    string attributes();
    static string nodeType2String(NodeType);
    static string declType2String(DeclType);
    static string operatorType2String(OperatorType);
    static string radixType2String(RadixType);
    static string assignmentType2String(AssignmentType);
    static string statementType2String(StatementType);
};

#endif