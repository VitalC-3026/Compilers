#include "parseTree.h"
#include "common.h"
#include <list>
#include <cstring>
#include <cassert>
extern FILE *yyout;
extern string getValueOfId(TreeNode*);
extern map<string, stack<idAttr>> identifierTable;

void TreeNode::addChild(TreeNode* &child) {
    string info = to_string(this->getNodeId()) + (string)" add child " + to_string(child->getNodeId()) + "\n";
    //fputs(info.c_str(), yyout);
    if (this->child == nullptr) {
        this->child = child;
    } else {
        this->child->addSibling(child);
    }
}

void TreeNode::addSibling(TreeNode* &sibling) {
    TreeNode* node = this;
    string info = to_string(this->getNodeId()) + (string)" add sibiling " + to_string(sibling->getNodeId()) + "\n";
    //fputs(info.c_str(), yyout);
    
    while(node->sibling != nullptr){
        node = node->sibling;
    } 
    
    node->sibling = sibling;
}


TreeNode* TreeNode::getChild(){
        return this->child;
}

TreeNode* TreeNode::getSibling(){
        return this->sibling;
}

TreeNode::TreeNode(int lineno, NodeType type) {
    this->lineno = lineno;
    this->nodeType = type;
    generateNodeID();
    this->formerDeclID = this->nodeID;
}

// TreeNode::TreeNode(){}

void TreeNode::generateNodeID() {
    this->nodeID = ++count;
}

int TreeNode::getNodeId() {
    return this->nodeID;
}

void TreeNode::setFormerNodeId(int i) {
    this->formerDeclID = i;
}

string TreeNode::printInfo() {
    string info = (string)"lno@" + to_string(this->lineno) + (string)"\tID@" + to_string(this->nodeID);
    info += (string)"\tNodeType: " + TreeNode::nodeType2String(this->nodeType);
    if (strcmp(TreeNode::nodeType2String(this->nodeType).c_str(), "Program Root") == 0) {
        info += (string)"\tAttributes: " + this->attributes();
    } else if (strcmp(TreeNode::nodeType2String(this->nodeType).c_str(), "Const") == 0) {
        info += (string)"\t\t\tAttributes: " + this->attributes();
    } else {
        info += (string)"\t\tAttributes: " + this->attributes();
    }

    
    return info;
}

void TreeNode::printAST() {
    if (this->nodeID == 87) {
        cout << "@87 former: " << this->formerDeclID << endl;
    }
    string info = this->printInfo();
    string childrenInfo = (string)"\tChildern:[ ";
    list<int> children;
    TreeNode* node = this->child;
    if(node != nullptr){
        children.push_back(node->getNodeId());
        node = node->sibling;
        while(node != nullptr) {
            children.push_back(node->getNodeId());
            node = node->sibling;
        }
        list<int>::iterator iter;
        for (iter = children.begin(); iter != children.end(); iter++) {
            childrenInfo += "@" + to_string(*iter) + " ";
        }
        childrenInfo += "]\n";
        info += childrenInfo;
        fputs(info.c_str(), yyout);
        node = this->child;
        node->printAST();
        node = node->sibling;
        while(node != nullptr) {
            node->printAST();
            node = node->sibling;
        }
    } else {
        info += "\n";
        fputs(info.c_str(), yyout);
    }
}

void TreeNode::setNodeType(NodeType type) {
    this->nodeType = type;
}


void TreeNode::setStatementType(StatementType type) {
    this->stmtType = type;
}

void TreeNode::setAssignmentType(AssignmentType type) {
    this->asigType = type;
}

void TreeNode::setOperatorType(OperatorType type) {
    this->opType = type;
}

void TreeNode::setDeclType(DeclType type) {
    this->declType = type;
}

void TreeNode::setRadixType(RadixType type) {
    this->radixType = type;
}

void TreeNode::setFunctionType(FunctionType type) {
    this->funcType = type;
}

void TreeNode::setIntValue(int i) {
    this->intVal = i;
}  

void TreeNode::setCharValue(char c) {
    this->charVal = c;
}

void TreeNode::setStringValue(string s) {
    this->stringVal = s;
}

void TreeNode::setBoolValue(bool b) {
    this->boolVal = b;
}

void TreeNode::setIdentifier(string id) {
    this->identifier = id;
}

int TreeNode::getIntValue() {
    return this->intVal;
}

char TreeNode::getCharValue() {
    return this->charVal;
}

string TreeNode::getStringValue() {
    return this->stringVal;
}

bool TreeNode::getBoolValue() {
    return this->boolVal;
}

string TreeNode::getIdentifier() {
    return this->identifier;
}

NodeType TreeNode::getNodeType() {
    return this->nodeType;
}

DeclType TreeNode::getDeclType() {
    return this->declType;
}

StatementType TreeNode::getStatementType() {
    return this->stmtType;
}

OperatorType TreeNode::getOperatorType() {
    return this->opType;
}

AssignmentType TreeNode::getAssignmentType() {
    return this->asigType;
}

RadixType TreeNode::getRadixType(){
    return this->radixType;
}

FunctionType TreeNode::getFunctionType(){
    return this->funcType;
}

string TreeNode::nodeType2String(NodeType t){
    switch(t){
        case 0:
            return (string)"Program Root";
        case 1:
            return (string)"Const";
        case 2:
            return (string)"Const Variable";
        case 3:
            return (string)"Variable";
        case 4:
            return (string)"Operator";
        case 5:
            return (string)"Expression";
        case 6:
            return (string)"Statement";
        case 7:
            return (string)"Function";
        case 8:
            return (string)"Data Type";
        default:
            return (string)"Unknown Type";
    }
}

string getAttributesOfId(TreeNode* node){
    assert (node->getNodeType() == NODE_ConstVar || node->getNodeType() == NODE_Var);
    string id = node->getIdentifier();
    string value = "";
    if(identifierTable.find(id) != identifierTable.end()){
        stack<idAttr> s = identifierTable.find(id)->second;
        while(!s.empty()) {
            if(s.top().id == node->getNodeId()) {
                value = s.top().value;
                break;
            }
            s.pop();
        }
    }
    return value;
}

string TreeNode::attributes(){
    switch(this->nodeType) {
        case 0:
            return (string)"Root";
        case 1: {
            string decl = declType2String(this->declType);
            string value = (string)" ";
            value += getValueOfId(this);
            // switch(this->declType){
            //     case 0: {
            //         value += to_string(this->getIntValue());
            //         cout << this->getNodeId() << " variable attribute: " << value << endl;
            //         cout << this->getIntValue() << endl;
            //     }
            //     case 1: {
            //         value += to_string(this->getCharValue());
            //         cout << this->getNodeId() << " variable attribute: " << value << endl;
            //         cout << this->getCharValue() << endl;
            //     }
            //     case 2: {
            //         value += this->getStringValue();
            //         cout<< this->getNodeId() << " variable attribute: " << value << endl;
            //         cout << this->getStringValue() << endl;
            //     }
            //     case 3: {
            //         value += to_string(this->getBoolValue());
            //         cout << this->getNodeId() << " variable attribute: " << value << endl;
            //         cout << this->getBoolValue() << endl;
            //     }
            //     default:
            //         break;
            // }
            return decl + value;
        }
        case 2: {
            string decl = declType2String(this->declType);
            string value = " ";
            value += this->identifier;
            // if(getAttributesOfId(this) != ""){
            //     value += getAttributesOfId(this);
            // }
            if (this->stmtType != STMT_DECL) {
                if (identifierTable.find(this->identifier)!=identifierTable.end()){
                    stack<idAttr> s = identifierTable.find(this->identifier)->second;
                    while(!s.empty()) {
                        int l = s.top().level;
                        int idx = s.top().id;
                        if(idx == this->formerDeclID){
                            value += "\tDeclared level@" + to_string(l) + " same as ID@" + to_string(idx);
                            break;
                        }
                        s.pop();
                    }
                }
            }
            return decl + value;
        }
        case 3: {
            string decl = declType2String(this->declType);
            string value = " ";
            value += this->identifier;
            // if(getAttributesOfId(this) != ""){
            //     value += getAttributesOfId(this);
            // }
            if (this->stmtType != STMT_DECL) {
                if (identifierTable.find(this->identifier)!=identifierTable.end()){
                    stack<idAttr> s = identifierTable.find(this->identifier)->second;
                    while(!s.empty()) {
                        int l = s.top().level;
                        int idx = s.top().id;
                        if(idx == this->formerDeclID){
                            value += "\tDeclared level@" + to_string(l) + " same as ID@" + to_string(idx);
                            break;
                        }
                        s.pop();
                    }
                }
            }
            return decl + value;
        }
        case 4:
            return operatorType2String(this->opType);
        case 5:
        // expression
            return "";
        case 6: {
            string stmt = statementType2String(this->stmtType);
            if(stmt == (string)"Assignment") {
                string asig = assignmentType2String(this->asigType);
                return stmt+(string)" "+asig; 
            }
            return stmt;
        }
        case 7: {
        // function
            string func = functionType2String(this->funcType);
            func += (string)"\tFuncName: ";
            func += this->identifier;
            return func;
        }
        case 8:
            return declType2String(this->declType);
        default:
            return (string)"";
    }
}

string TreeNode::declType2String(DeclType t){
    switch(t){
        case 0:
            return (string)"int";
        case 1:
            return (string)"char";
        case 2:
            return (string)"string";
        case 3:
            return (string)"bool";
        case 4:
            return (string)"void";
        default:
            return (string)"";
    }
}

string TreeNode::operatorType2String(OperatorType t){
    switch(t){
        case 0:
            return (string)".";
        case 1:
            return (string)"&";
        case 2:
            return (string)"->";
        case 3:
            return (string)"!";
        case 4:
            return (string)"+";
        case 5:
            return (string)"-";
        case 6:
            return (string)"*";
        case 7:
            return (string)"/";
        case 8:
            return (string)"%";
        case 9:
            return (string)"==";
        case 10:
            return (string)">";
        case 11:
            return (string)"<";
        case 12:
            return (string)">=";
        case 13:
            return (string)"<=";
        case 14:
            return (string)"!=";
        case 15:
            return (string)"&&";
        case 16:
            return (string)"||";
        default:
            break;
    }
}

string TreeNode::radixType2String(RadixType t){
    switch(t){
        case 0:
            return (string)"decimal";
        case 1:
            return (string)"octal";
        case 2:
            return (string)"hex";
        default:
            return (string)"";
    }
}

string TreeNode::assignmentType2String(AssignmentType t){
    switch(t) {
        case 0:
            return (string)"=";
        case 1:
            return (string)"+=";
        case 2:
            return (string)"-=";
        case 3:
            return (string)"*=";
        case 4:
            return (string)"/=";
        case 5:
            return (string)"%=";
        case 6:
            return (string)"++";
        case 7:
            return (string)"--";
        default:
            return (string)"";
    }
}

string TreeNode::statementType2String(StatementType t){
    switch(t) {
        case 0:
            return (string)"Assignment";
        case 1:
            return (string)"Expression";
        case 2:
            return (string)"Declaration";
        case 3:
            return (string)"If";
        case 4:
            return (string)"For";
        case 5:
            return (string)"While";
        case 6:
            return (string)"Break";
        case 7:
            return (string)"Continue";
        case 8:
            return (string)"Return";
        case 9:
            return (string)"Skip";
        case 10:
            return (string)"For conditions";
        default:
            return (string)"";
    }
}

string TreeNode::functionType2String(FunctionType t){
    switch(t) {
        case 0:
            return (string)"Declaration";
        case 1:
            return (string)"Definition";
        case 2:
            return (string)"Call";
        case 3:
            return (string)"Type";
        case 4:
            return (string)"Identifier";
        case 5:
            return (string)"Parameters";
        case 6:
            return (string)"Body";
        default:
            return (string)"";
    }
}