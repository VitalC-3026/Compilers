#include "parseTree.h"
#include "common.h"
#include <list>
#include <cstring>
#include <cassert>
extern FILE *yyout;
extern string getValueOfId(TreeNode*);
extern map<string, stack<idAttr>> identifierTable;
extern void yyerror(const char*);
void typeIncompatible(int, int, string);
void noOperands(int);
int rostringNum = 0;
int tempVarNum = 0;
int tempLabelNum = 0;
vector<constString> rostring;
vector<tempVar> tempVariables;
vector<string> basicCodeBlock;


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
    // if (this->getIsAlive() == false){
    //     return;
    // }
    string info = this->printInfo();
    string childrenInfo = (string)"\tChildren:[ ";
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
            return (string)"Const Var";
        case 3:
            return (string)"Variable";
        case 4:
            return (string)"Operator";
        case 5:
            return (string)"Statement";
        case 6:
            return (string)"Function";
        case 7:
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
        case 5: {
            string stmt = statementType2String(this->stmtType);
            if(stmt == (string)"Assignment") {
                string asig = assignmentType2String(this->asigType);
                return stmt+(string)" "+asig; 
            }
            return stmt;
        }
        case 6: {
        // function
            string func = functionType2String(this->funcType);
            func += (string)"\tFuncName: ";
            func += this->identifier;
            return func;
        }
        case 7:
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
        case STMT_ASIG:
            return (string)"Assignment";
        case STMT_EXPR:
            return (string)"Expression";
        case STMT_DECL:
            return (string)"Declaration";
        case STMT_IF:
            return (string)"If";
        case STMT_FOR:
            return (string)"For";
        case STMT_WHILE:
            return (string)"While";
        case STMT_BREAK:
            return (string)"Break";
        case STMT_CONTINUE:
            return (string)"Continue";
        case STMT_RETURN:
            return (string)"Return";
        case STMT_SKIP:
            return (string)"Skip";
        case STMT_FORCON:
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

bool TreeNode::typeCheck(){
    switch (this->nodeType)
    {
        case NODE_Op:{
            TreeNode* child = this->child;
            if (child == nullptr) {
                noOperands(this->nodeID);
                this->setDeclType(D_NONE);
                this->setIsAlive(false);
                return false;
            } 
            else {
                // whether children are defined
                if(child->getNodeType() == NODE_Var && identifierTable.find(child->getIdentifier()) == identifierTable.end()){
                    string msg = (string)"Node@" + to_string(nodeID) + (string)" NODE_Op: children not defined.";
                    yyerror(msg.c_str());
                    this->setIsAlive(false);
                    return false;
                }
                if (child->sibling != nullptr && child->sibling->getNodeType() == NODE_Var && identifierTable.find(child->sibling->getIdentifier()) == identifierTable.end()) {
                    string msg = (string)"Node@" + to_string(nodeID) + (string)" NODE_Op: children not defined.";
                    yyerror(msg.c_str());
                    this->setIsAlive(false);
                    return false;
                }
                DeclType dType = child->declType;
                if (this->opType == OP_ADD || this->opType == OP_MUL ||
                this->opType == OP_DIV || this->opType == OP_MOD) {
                    if(child->sibling == nullptr) {
                        noOperands(this->nodeID);
                        this->setDeclType(D_NONE);
                        this->setIsAlive(false);
                        return false;
                    } else {
                        if(child->sibling->getDeclType() == dType && (dType == D_INT || dType == D_CHAR || dType == D_BOOL)){
                            this->setDeclType(dType);
                            return true;
                        } else {
                            bool left = true, right = true;
                            if (!(dType == D_INT || dType == D_CHAR || dType == D_BOOL)) {
                                left = false;
                            }
                            if (!(child->sibling->getDeclType() == D_CHAR || child->sibling->getDeclType() == D_BOOL || child->sibling->getDeclType() == D_INT)) {
                                right = false;
                            }
                            if (left && right){
                                return true;
                            } 
                            else {
                                typeIncompatible(child->sibling->lineno, child->sibling->getNodeId(), (string)"Node_Var/ConstVar");
                                this->setDeclType(D_NONE);
                                this->setIsAlive(false);
                                return false;
                            }
                            
                        }
                    }
                }
                if (this->opType == OP_MIN) {
                    if (child->sibling != nullptr) {
                        if(child->sibling->getDeclType() == dType && (dType == D_INT || dType == D_CHAR || dType == D_BOOL)){
                            this->setDeclType(dType);
                            return true;
                        } else {
                            bool left = true, right = true;
                            if (!(dType == D_INT || dType == D_CHAR || dType == D_BOOL)) {
                                left = false;
                            }
                            if (!(child->sibling->getDeclType() == D_CHAR || child->sibling->getDeclType() == D_BOOL || child->sibling->getDeclType() == D_INT)) {
                                right = false;
                            }
                            if (left && right){
                                return true;
                            } 
                            else {
                                if (!left) {
                                    typeIncompatible(child->lineno, child->getNodeId(), (string)"Node_Var/ConstVar");
                                }
                                if (!right) {
                                    typeIncompatible(child->sibling->lineno, child->sibling->getNodeId(), (string)"Node_Var/ConstVar");
                                }
                                this->setDeclType(D_NONE);
                                this->setIsAlive(false);
                                return false;
                            }            
                        }
                    }
                    else {
                        if (dType != D_INT && dType != D_CHAR) {
                            typeIncompatible(child->lineno, child->nodeID, (string)"Node_Var/ConstVar");
                            this->setDeclType(D_NONE);
                            this->setIsAlive(false);
                            return false;
                        }
                    }
                }
                if (this->opType == OP_EQU ||this->opType == OP_GT ||this->opType == OP_LT ||
                this->opType == OP_GTQ ||this->opType == OP_LTQ ||this->opType == OP_NEQ) {
                    if(child->sibling == nullptr) {
                        noOperands(this->nodeID);
                        this->setDeclType(D_NONE);
                        this->setIsAlive(false);
                        return false;
                    } else {
                        if(child->sibling->getDeclType() == dType && (dType == D_INT || dType == D_CHAR || dType == D_BOOL)){
                            this->setDeclType(D_BOOL);
                            return true;
                        } else {
                            bool left = true, right = true;
                            if (dType != D_INT && dType != D_CHAR && dType != D_BOOL) {
                                left = false;
                            }
                            if (child->sibling->getDeclType() != D_INT && child->sibling->getDeclType() != D_CHAR && child->sibling->getDeclType() != D_STRING) {
                                right = false;
                            }
                            if (left && right) {
                                this->setDeclType(D_BOOL);
                                return true;
                            } else {
                                this->setDeclType(D_NONE);
                                if(!left) {
                                    typeIncompatible(child->lineno, child->nodeID, (string)"Node_Var/ConstVar");
                                }
                                if (!right) {
                                    typeIncompatible(child->sibling->lineno, child->sibling->nodeID, (string)"Node_Var/ConstVar");
                                }
                                this->setIsAlive(false);
                                return false;
                            }
                        }
                    }
                }
                if (this->opType == OP_NOT) {
                    if(dType == D_BOOL){
                        this->setDeclType(D_BOOL);
                        return true;
                    } else if (dType == D_INT || dType == D_CHAR){
                        // type cast?
                        this->setDeclType(D_BOOL);
                        return true;
                    } else {
                        noOperands(this->nodeID);
                        this->setDeclType(D_NONE);
                        this->setIsAlive(false);
                        return false;
                    }
                }
                if (this->opType == OP_AND || OP_OR){
                    if (child->sibling==nullptr) {
                        noOperands(this->nodeID);
                        this->setDeclType(D_NONE);
                        this->setIsAlive(false);
                        return false;
                    }
                    if(child->sibling->getDeclType() == dType && dType == D_BOOL){
                        this->setDeclType(D_BOOL);
                        return true;
                    } else {
                        if (dType != D_BOOL) {
                            this->setDeclType(D_NONE);
                            typeIncompatible(child->lineno, child->nodeID, (string)"Node_Var/ConstVar");
                        }
                        if (child->sibling->getDeclType() != D_BOOL) {
                            this->setDeclType(D_NONE);
                            typeIncompatible(child->sibling->lineno, child->sibling->nodeID, (string)"Node_Var/ConstVar");
                        }
                        this->setIsAlive(false);
                        return false;
                    }
                }
            
            }
            break;
        }
        case NODE_Stmt: {
            switch (this->stmtType)
            {
                case STMT_ASIG: {
                    cout << "assign here" << endl;
                    assert (this->child != nullptr);
                    if (this->child->getNodeType() != NODE_Var) {
                        string msg = (string)"Node@" + to_string(nodeID) + (string)" NODE_Assignment: we expect a left value.";
                        yyerror(msg.c_str());
                        this->setIsAlive(false);
                        return false;
                    }
                    DeclType dType = this->child->getDeclType();
                    if (this->child->getSibling() != nullptr) {
                        DeclType siblingDType = this->child->getSibling()->getDeclType();
                        switch (dType)
                        {
                            case D_INT: {
                                if (siblingDType == D_INT || siblingDType == D_CHAR || siblingDType == D_BOOL) {
                                    return true;
                                } else {
                                    typeIncompatible(this->lineno, this->nodeID, (string)"NODE_Assignment");
                                    this->setIsAlive(false);
                                    return false;
                                }
                                break;
                            }
                            case D_CHAR: {
                                if(siblingDType == D_CHAR || siblingDType == D_INT || siblingDType == D_BOOL) {
                                    return true;
                                } else {
                                    typeIncompatible(this->lineno, this->nodeID, (string)"NODE_Assignment");
                                    this->setIsAlive(false);
                                    return false;
                                }
                                break;
                            case D_STRING:
                                if(siblingDType != D_STRING) {
                                    typeIncompatible(this->lineno, this->nodeID, (string)"NODE_Assignment");
                                    this->setIsAlive(false);
                                    return false;
                                } else {
                                    return true;
                                }
                            }
                            case D_BOOL: {
                                if(siblingDType == D_CHAR || siblingDType == D_INT || siblingDType == D_BOOL) {
                                    return true;
                                } else {
                                    typeIncompatible(this->lineno, this->nodeID, (string)"NODE_Assignment");
                                    this->setIsAlive(false);
                                    return false;
                                }
                            }
                            default: {
                                typeIncompatible(this->lineno, this->nodeID, (string)"NODE_Assignment");
                                this->setIsAlive(false);
                                return false;
                            }
                        }
                    } 
                    else if (this->child->getSibling() == nullptr && 
                    (this->child->getAssignmentType() == ADDASIGO || this->child->getAssignmentType() == MINASIGO)) {
                        if(dType != D_INT){
                            typeIncompatible(this->lineno, this->nodeID, (string)"NODE_Assignment");
                            this->setIsAlive(false);
                            return false;
                        } else {
                            return true;
                        }
                    } 
                    else {
                        string msg = (string)"Node@" + to_string(nodeID) + (string)" NODE_Assignment: missing assignment value.";
                        yyerror(msg.c_str());
                        this->setIsAlive(false);
                        return false;
                    }
                }
            
                case STMT_IF:{
                    if (this->child == nullptr) {
                        string msg = (string)"Node@" + to_string(nodeID) + (string)" NODE_If: missing conditions.";
                        yyerror(msg.c_str());
                        this->setIsAlive(false);
                        return false;
                    }
                    DeclType dType = this->child->getDeclType();
                    if (this->child->getSibling() == nullptr) {
                        string msg = (string)"Node@" + to_string(nodeID) + (string)" NODE_If: missing true statements.";
                        yyerror(msg.c_str());
                        this->setIsAlive(false);
                        return false;
                    }
                    DeclType tType = this->child->getSibling()->getDeclType();
                    if (this->child->getNodeType() == NODE_Const || this->child->getNodeType() == NODE_ConstVar 
                    || this->child->getNodeType() == NODE_Var) {
                        if (dType != D_STRING && dType != D_NONE && dType != D_VOID) {
                            return true;
                        }
                        else {
                            typeIncompatible(this->lineno, this->nodeID, (string)"NODE_IF");
                            this->setIsAlive(false);
                            return false;
                        }
                    }    
                }
                
                case STMT_WHILE:{
                    if (this->child == nullptr) {
                        string msg = (string)"Node@" + to_string(nodeID) + (string)" NODE_While: missing conditions.";
                        yyerror(msg.c_str());
                        this->setIsAlive(false);
                        return false;
                    }
                    DeclType dType = this->child->getDeclType();
                    if (this->child->getNodeType() == NODE_Const || this->child->getNodeType() == NODE_ConstVar 
                    || this->child->getNodeType() == NODE_Var) {
                        if (dType != D_STRING) {
                            return true;
                        }
                        else {
                            typeIncompatible(this->lineno, this->nodeID, (string)"NODE_While");
                            this->setIsAlive(false);
                            return false;
                        }
                    }
                }
                
                default:
                    break;
            }
        break;
        }
        case NODE_Func: {
            if(this->getFunctionType() == FUNC_CALL) {
                // check funciton type
            } 
            else if (this->getFunctionType() == FUNC_DEFI) {

            }
            else if (this->getFunctionType() == FUNC_DECL) {

            }
            break;
        }
        default: {
            this->declType = D_NONE;
            break;
        }
    }
}

void noOperands(int nodeID){
    string msg = (string)"Node@" + to_string(nodeID) + (string)" NODE_Op: missing operand(s).";
    yyerror(msg.c_str());
}

void typeIncompatible(int lineno, int nodeID, string nodeType){
    string msg = (string)"Line@" + to_string(lineno) + (string)" Node@" + to_string(nodeID) + (string)" " + nodeType + (string)": type incompatible.";
    yyerror(msg.c_str());
}


void TreeNode::genStmtLabel(){
    switch(this->stmtType){
        case STMT_WHILE: {
            TreeNode* expr = this->getChild();
            TreeNode* body = this->getChild()->getSibling();
            if (this->label.beginLabel == "") {
                this->label.beginLabel = newLabel();
            }
            body->label.nextLabel = this->label.beginLabel;
            body->label.beginLabel = expr->label.trueLabel = newLabel();
            if(this->label.nextLabel == "") {
                this->label.nextLabel = newLabel();
            }
            expr->label.falseLabel = this->label.nextLabel;
            if (this->sibling != nullptr) {
                this->sibling->label.beginLabel = this->label.nextLabel;
                
            }
            expr->recursiveGenLabel();
            body->recursiveGenLabel();
            break;
        }
        case STMT_IF: {
            cout << "if" << endl;
            TreeNode* expr = this->child;
            TreeNode* trueBody = this->child->sibling;
            TreeNode* falseBody = this->child->sibling->sibling;
            if(this->child->sibling->sibling){
                falseBody = this->child->sibling->sibling;
            }
            if (this->label.beginLabel == "") {
                this->label.beginLabel = newLabel();
                cout << "if beginL" << this->label.beginLabel << endl;
            }
            trueBody->label.beginLabel = expr->label.trueLabel = newLabel();
            cout << "if beginT" << trueBody->label.beginLabel << endl;
            expr->label.falseLabel = newLabel();
            if (falseBody) {
                falseBody->label.beginLabel = expr->label.falseLabel;
                cout << "if beginF" << falseBody->label.beginLabel << endl;
            }
            if(this->label.nextLabel == ""){
                this->label.nextLabel = newLabel();
            }
            trueBody->label.nextLabel = this->label.nextLabel;
            if (falseBody) {
                falseBody->label.nextLabel = this->label.nextLabel;
            }
            if (this->sibling != nullptr) {
                this->sibling->label.beginLabel = this->label.nextLabel;
            }
            expr->recursiveGenLabel();
            trueBody->recursiveGenLabel();
            if (falseBody != nullptr) {
                falseBody->recursiveGenLabel();
            }
            break;
        }
        case STMT_FOR: {
            TreeNode* body = this->child->sibling;
            TreeNode* forcon1 = this->child->child; // assignment/declaration
            TreeNode* forconE = this->child->child->sibling; // loop conditions
            TreeNode* forconI = this->child->child->sibling->sibling; // iteration
            if (this->label.beginLabel == "") {
                this->label.beginLabel = newLabel();
            }
            body->label.beginLabel = forconE->label.trueLabel = newLabel();
            body->label.nextLabel = forconI->label.beginLabel = newLabel();
            forconI->label.nextLabel = this->label.beginLabel;
            if (this->label.nextLabel == "") {
                this->label.nextLabel = newLabel();
            }
            forconE->label.falseLabel = this->label.nextLabel;
            if (this->sibling != nullptr) {
                this->sibling->label.beginLabel = this->label.nextLabel;
            }
            forconE->recursiveGenLabel();
            body->recursiveGenLabel();
            break;
        }
        case STMT_EXPR: {
            this->genExprLabel();
            break;
        }
        case STMT_ASIG: {
            TreeNode* expr = this->child->sibling;
            if (expr != nullptr) {
                expr->recursiveGenLabel();
            } 
        }
        default: {
            break;
        }

    }

}

void TreeNode::genExprLabel() {
    TreeNode* operand1 = this->child;
    TreeNode* operand2 = this->child->sibling;
    switch (this->opType)
    {
        case OP_AND: {
            operand2->label.trueLabel = this->label.trueLabel;
            operand1->label.trueLabel = newLabel();
            operand1->label.falseLabel = operand2->label.falseLabel = this->label.falseLabel;
            if (operand1->stmtType == STMT_EXPR) {
                operand1->recursiveGenLabel();
            }
            if (operand2->stmtType == STMT_EXPR) {
                operand2->recursiveGenLabel();
            }
            break;
        }
        case OP_OR: {
            operand1->label.trueLabel = operand2->label.trueLabel = this->label.trueLabel;
            operand1->label.falseLabel = newLabel();
            operand2->label.falseLabel = this->label.falseLabel;
            if (operand1->stmtType == STMT_EXPR) {
                operand1->recursiveGenLabel();
            }
            if (operand2->stmtType == STMT_EXPR) {
                operand2->recursiveGenLabel();
            }
            break;
        }
        case OP_NOT: {
            operand1->label.trueLabel = this->label.falseLabel;
            operand1->label.falseLabel = this->label.trueLabel;
            if (operand1->stmtType == STMT_EXPR) {
                operand1->recursiveGenLabel();
            }
            break;
        }
        default: {
            // < > <= >= == != ??
            if (this->opType == OP_GT || this->opType == OP_GTQ ||
            this->opType == OP_LT || this->opType == OP_LTQ ||
            this->opType == OP_EQU || this->opType == OP_NEQ) {
                this->label.trueLabel = newLabel();
                this->label.falseLabel = newLabel();
                if (operand1->stmtType == STMT_EXPR) {
                    operand1->recursiveGenLabel();
                }
                if (operand2->stmtType == STMT_EXPR) {
                    operand2->recursiveGenLabel();
                }
            } 
            else if (this->opType == OP_ADD || this->opType == OP_MUL || 
            this->opType == OP_DIV || this->opType == OP_MOD) {
                if (operand1->stmtType == STMT_EXPR) {
                    operand1->recursiveGenLabel();
                }
                if (operand2->stmtType == STMT_EXPR) {
                    operand2->recursiveGenLabel();
                }
            } else if (this->opType == OP_MIN) {
                cout << "min" << endl;
                if (operand1->stmtType == STMT_EXPR) {
                    operand1->recursiveGenLabel();
                }
                if (operand2 != nullptr && operand2->stmtType == STMT_EXPR) {
                    operand2->recursiveGenLabel();
                }
            }
            break;
        }
    }
    this->tempId = to_string(tempVarNum);
    tempVar var;
    var.num = tempVarNum;
    var.value = this->nodeID;
    tempVarNum++;
    tempVariables.push_back(var);
    cout << "tmpSize" << tempVariables.size() << endl;
}

void TreeNode::genFuncLabel() {
    if (this->funcType == FUNC_DEFI) {
        this->label.beginLabel = newLabel();
        TreeNode* body = this->child->sibling;
        while(body != nullptr) {
            body->recursiveGenLabel();
            body = body->sibling;
        }
    } else if (this->funcType == FUNC_CALL) {
        if (strcmp(this->child->identifier.c_str(), "scanf") == 0 || 
            strcmp(this->child->identifier.c_str(), "printf") == 0) {
            string str = this->child->sibling->getStringValue();
            str = str.replace(str.find("\""), 1, "").replace(str.find("\""), 1, "");
            if (str.find("\\n") != -1) {
                str = str.substr(0, str.find("\\n"));
                str = str + (string)"\\12";
                cout << "\\n" << str << endl;
            }
            else if (str.find("\\r") != -1) {
                str = str.substr(0, str.find("\\r"));
                str = str + (string)"\\15";
                cout << "\\r" << str << endl;
            }
            else if (str.find("\\t") != -1) {
                str = str.substr(0, str.find("\\t"));
                str = str + (string)"\\11";
                cout << "\\t" << str << endl;
            }
            else if (str.find("\\a") != -1) {
                str = str.substr(0, str.find("\\a"));
                str = str + (string)"\\7";
                cout << "\\q" << str << endl;
            }
            else if (str.find("\\b") != -1) {
                str = str.substr(0, str.find("\\b"));
                str = str + (string)"\\10";
                cout << "\\b" << str << endl;
            }
            else if (str.find("\\v") != -1) {
                str = str.substr(0, str.find("\\v"));
                str = str + (string)"\\13";
                cout << "\\v" << str << endl;
            }
            else if (str.find("\\f") != -1) {
                str = str.substr(0, str.find("\\f"));
                str = str + (string)"\\14";
                cout << "\\f" << str << endl;
            }
            str = "\"" + str + (string)"\\0\"";
            constString info;
            info.str = str;
            info.num = rostringNum;
            cout << str << endl;
            rostring.push_back(info);
            this->child->sibling->tempId = to_string(rostringNum);
            rostringNum++;
        }
    }
    
}

string TreeNode::newLabel(){
    char tmp[20] = {0};
    sprintf(tmp, "L%d", TreeNode::labelCount);
    TreeNode::labelCount++;
    return (string)tmp;
}

void TreeNode::recursiveGenLabel() {
    if (this->nodeType == NODE_Stmt) {
        cout << "recursiveGenStmt " << this->nodeID << endl;
        this->genStmtLabel();
    } 
    else if (this->stmtType == STMT_EXPR) {
        cout << "recursiveGenExpr " << this->nodeID << endl;
        this->genExprLabel();
    }
    else if (this->nodeType == NODE_Func) {
        cout << "recursiveGenFunc " << this->nodeID << endl;
        this->genFuncLabel();
    }
    else if (this->nodeType == NODE_Prog) {
            this->label.beginLabel = "_start";
            TreeNode* child = this->child;
            while(child != nullptr){
                child->recursiveGenLabel();
                child = child->sibling;
            }
    }
}

void TreeNode::genCode(ostream &out) {
    for(int i = 0 ; i < tempVariables.size(); i++) {
        cout << tempVariables[i].num << " " << tempVariables[i].value << endl;
    }
    out << "# your asm code header here!" << endl;
    if(this->nodeType == NODE_Prog) {
        bool textHeader = true;
        out << "# define your variables and temporal variables here" << endl;
        this->genDeclCode(out);
        TreeNode* child = this->child;
        while(child != nullptr) {
            child->recursiveGenCode(out);
            child = child->sibling;
        }
    }
    out << "\t.section\t.note.GNU-stack,\"\",@progbits" << endl;
}

void TreeNode::recursiveGenCode(ostream &out) {
    if (this->nodeType == NODE_Stmt) {
        this->genStmtCode(out);
    } 
    else if (this->nodeType == NODE_Func) {
        this->genFuncCode(out);
    }
    else if (this->nodeType == NODE_Op) {
        this->genExprCode(out);
    }
}

void TreeNode::genStmtCode(ostream &out) {
    switch(this->stmtType) {
        case STMT_ASIG: {
            TreeNode* id = this->child;
            if(this->child->sibling != nullptr){
                TreeNode* expr = this->child->sibling;
                expr->recursiveGenCode(out);
                switch (this->asigType)
                {
                    case ASIG: {
                        if (expr->nodeType == NODE_Const) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl $" << expr->getIntValue() << ", _" << id->identifier << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb $" << expr->getBoolValue() << ", _" << id->identifier << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb $" << expr->getCharValue() << ", _" << id->identifier << endl;
                            }
                        } else {
                            expr->recursiveGenCode(out);
                            out << "\tpopl %eax" << endl;
                            if (id->declType == D_CHAR || id->declType == D_BOOL) {
                                out << "\tmovb %al, _" << id->identifier << endl;
                            } else {
                                out << "\tmovl %eax, _" << id->identifier << endl;
                            }
                        }
                        break;
                    }
                    case ADDASIG: {
                        out << "\tmovl _" << id->identifier << ", %edx" << endl;
                        if (expr->nodeType == NODE_Const) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl $" << expr->getIntValue() << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb $" << expr->getBoolValue() << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb $" << expr->getCharValue() << ", %ecx" << endl;
                            }
                        }
                        else if (expr->nodeType == NODE_Var || expr->nodeType == NODE_ConstVar) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl _" << expr->identifier << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                        }
                        else {
                            expr->recursiveGenCode(out);
                            out << "\tpopl %ecx" << endl;
                        }
                        
                        out << "\taddl %ecx, %edx" << endl;
                        if (id->declType == D_CHAR || id->declType == D_BOOL) {
                            out << "\tmovb %dl, _" << id->identifier << endl;
                        } else {
                            out << "\tmovl %edx, _" << id->identifier << endl;
                        }
                        break;
                    }
                    case MINASIG: {
                        out << "\tmovl _" << id->identifier << ", %edx" << endl;
                        if (expr->nodeType == NODE_Const) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl $" << expr->getIntValue() << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb $" << expr->getBoolValue() << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb $" << expr->getCharValue() << ", %ecx" << endl;
                            }
                        }
                        else if (expr->nodeType == NODE_Var || expr->nodeType == NODE_ConstVar) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl _" << expr->identifier << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                        }
                        else {
                            expr->recursiveGenCode(out);
                            out << "\tpopl %ecx" << endl;
                        }
                        
                        out << "\tsubl %ecx, %edx" << endl;
                        if (id->declType == D_CHAR || id->declType == D_BOOL) {
                            out << "\tmovb %dl, _" << id->identifier << endl;
                        } else {
                            out << "\tmovl %edx, _" << id->identifier << endl;
                        } 
                        break;
                    }
                    case MULASIG: {
                        out << "\tmovl _" << id->identifier << ", %edx" << endl;
                        if (expr->nodeType == NODE_Const) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl $" << expr->getIntValue() << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb $" << expr->getBoolValue() << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb $" << expr->getCharValue() << ", %ecx" << endl;
                            }
                        }
                        else if (expr->nodeType == NODE_Var || expr->nodeType == NODE_ConstVar) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl _" << expr->identifier << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                        }
                        else {
                            expr->recursiveGenCode(out);
                            out << "\tpopl %ecx" << endl;
                        }
                        out << "\timull %ecx, %edx" << endl;
                        if (id->declType == D_CHAR || id->declType == D_BOOL) {
                            out << "\tmovb %dl, _" << id->identifier << endl;
                        } else {
                            out << "\tmovl %edx, _" << id->identifier << endl;
                        }
                        break;
                    }
                    case DIVASIG: {
                        out << "\tmovl _" << id->identifier << ", %eax" << endl;
                        if (expr->nodeType == NODE_Const) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl $" << expr->getIntValue() << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb $" << expr->getBoolValue() << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb $" << expr->getCharValue() << ", %ecx" << endl;
                            }
                        }
                        else if (expr->nodeType == NODE_Var || expr->nodeType == NODE_ConstVar) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl _" << expr->identifier << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                        }
                        else {
                            expr->recursiveGenCode(out);
                            out << "\tpopl %ecx" << endl;
                        }
                        out << "\tcltd" << endl;
                        out << "\tidivl %ecx" << endl;
                        if (id->declType == D_CHAR || id->declType == D_BOOL) {
                            out << "\tmovb %al, _" << id->identifier << endl;
                        } else {
                            out << "\tmovl %eax, _" << id->identifier << endl;
                        }
                        break;
                    }
                    case MODASIG: {
                        out << "\tmovl _" << id->identifier << ", %eax" << endl;
                        if (expr->nodeType == NODE_Const) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl $" << expr->getIntValue() << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb $" << expr->getBoolValue() << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb $" << expr->getCharValue() << ", %ecx" << endl;
                            }
                        }
                        else if (expr->nodeType == NODE_Var || expr->nodeType == NODE_ConstVar) {
                            if (expr->declType == D_INT) {
                                out << "\tmovl _" << expr->identifier << ", %ecx" << endl;
                            } 
                            else if (expr->declType == D_BOOL) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                            else if (expr->declType == D_CHAR) {
                                out << "\tmovb _" << expr->identifier << ", %ecx" << endl;
                            }
                        }
                        else {
                            expr->recursiveGenCode(out);
                            out << "\tpopl %ecx" << endl;
                        }
                        out << "\tcltd" << endl;
                        out << "\tidivl %ecx" << endl;
                        if (id->declType == D_CHAR || id->declType == D_BOOL) {
                            out << "\tmovb %dl, _" << id->identifier << endl;
                        } else {
                            out << "\tmovl %edx, _" << id->identifier << endl;
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
            else {
                out << "\tmovl _" << this->identifier << ", %eax" << endl;
                if (this->asigType == ADDASIGO) {
                    out << "\taddl $1, %eax" << endl;
                } else if (this->asigType == MINASIGO) {
                    out << "\tsubl $1, %eax" << endl;
                }
                out << "\tmovl %eax, _" << this->identifier << endl;
            }
            break;
        }
        case STMT_FOR: {
            TreeNode* forcon = this->child;
            assert (forcon->stmtType == STMT_FORCON);
            TreeNode* con1 = forcon->child;
            out << this->label.beginLabel << ":" << endl; // for start label
            if (con1 != nullptr) {
                con1->recursiveGenCode(out);
            }
            out << this->label.beginLabel << ":" << endl;
            TreeNode* con2 = forcon->child->sibling;
            if (con2 != nullptr) {
                con2->recursiveGenCode(out);
                out << "\tmovl t" << con2->tempId << ", %eax" << endl;
                out << "\tcmpl $1, %eax" << endl;
                out << "\tjne " << con2->label.falseLabel << endl;
            }
            TreeNode* con3 = forcon->child->sibling->sibling;
            TreeNode* stmt = this->child->sibling;
            if (stmt) {
                stmt->recursiveGenCode(out);
            }
            if (con3) {
                con3->recursiveGenCode(out);
            }
            out << "\tjmp " << this->label.beginLabel << endl;
            out << con2->label.falseLabel << ":" << endl;
            break;
        }
        case STMT_WHILE: {
            TreeNode* expr = this->child;
            TreeNode* body = this->child->sibling;
            out << this->label.beginLabel << ":" << endl;
            assert (expr != nullptr);
            assert (body != nullptr);
            expr->recursiveGenCode(out);
            out << "\tpopl %eax" << endl;
            out << "\tcmpl $1, %eax" << endl;
            out << "\tjne " << expr->label.falseLabel << endl;
            while (body != nullptr) {
                body->recursiveGenCode(out);
                body = body->sibling;
            }
            out << "\tjmp " << this->label.beginLabel << endl;
            out << expr->label.falseLabel << ":" << endl;
            break;
        }
        case STMT_IF: {
            TreeNode* expr = this->child;
            TreeNode* trueStmt = this->child->sibling;
            expr->recursiveGenCode(out);
            out << "\tpopl %eax" << endl;
            out << "\tcmpl $0, %eax" << endl;
            out << "\tje ";
            if (trueStmt->sibling != nullptr) {
                out << expr->label.falseLabel << endl;
            } else {
                out << this->label.nextLabel << endl;
            }
            trueStmt->recursiveGenCode(out);
            if (trueStmt->sibling != nullptr) {
                out << "\tjmp " << this->label.nextLabel << endl;
                out << expr->label.falseLabel << ":" << endl;
                TreeNode* falseStmt = this->child->sibling->sibling;
                falseStmt->recursiveGenCode(out);
            }
            out << this->label.nextLabel << ":" << endl;
            
            break;
        }
        case STMT_EXPR: {
            this->genExprCode(out);
            break;
        }
        case STMT_DECL: {
            // this->genDeclCode(out);
            break;
        }
        case STMT_RETURN: {
            if (this->child != nullptr) {
                out << "\tmovl $";
                if (this->child->declType == D_INT) {
                    out << this->child->getIntValue(); 
                }
                else if (this->child->declType == D_CHAR) {
                    out << this->child->getCharValue();
                }
                else if (this->child->declType == D_BOOL) {
                    if (this->child->getBoolValue()) {
                        out << "1";
                    } else {
                        out << "0";
                    }
                }
                out << ", %eax" << endl;
            }
        }
        default:
            break;
    }
}

// temp variables => how to identify and generate
void TreeNode::genDeclCode(ostream &out) {
    out << endl << "# define your variables here" << endl;
    map<string, stack<idAttr>>::iterator it = identifierTable.begin();
    bool bssOne = true;
    for(; it != identifierTable.end(); it++) {
        if(!it->second.empty()){
            idAttr attr = it->second.top();
            if (!attr.isConst) {
                out << "\t.globl\t" << "_" << it->first << endl;
                if (bssOne) {
                    out << "\t.bss" << endl;
                    bssOne = false;
                }
                
            }
            else {
                out << "\t.section\t.rodata" << endl;
            }
            out << "_" << it->first << ":" << endl;
            if (attr.type == D_INT) {
                if (attr.value == to_string(0) && !attr.isConst) {
                    out << "\t.align\t4" << endl;
                    out << "\t.zero\t4" << endl;
                }
                else {
                    out << "\t.long\t" << atoi(attr.value.c_str()) << endl;
                }
            }
            else if (attr.type == D_CHAR) {
                if (attr.value == to_string(0) && !attr.isConst) {
                    out << "\t.zero\t1" << endl;
                }
                else {
                    out << "\t.byte\t" << (int)(attr.value.c_str()[0]) << endl;
                }
            }
            else if (attr.type == D_STRING) {
                if (attr.value == to_string(0) && !attr.isConst) {
                    out << "\t.zero\t1" << endl;
                    out << "\t.align\t1" << endl;
                }
                else {
                    out << "\t.string\t\"" << attr.value << "\"" << endl;  
                }
                
            }
            else if (attr.type == D_BOOL && !attr.isConst) {
                out << "\t.zero\t1" << endl;
            }
        } 
        else {
            continue;
        }
        
    }
    for (int i = 0; i < tempVarNum; i++) {
        out << "\t.globl\tt" << i << endl;
        out << "t" << i << ":" << endl;
        out << ".align\t4" << endl;
        out << ".zero\t4" << endl;
    }
    out << endl << "\t.section .rodata" << endl;
    cout << "rostring" << rostring.size() << endl;
    for (int i = 0; i < rostring.size(); i++) {
        out << "LC" << rostring[i].num << ":" << endl;
        out << "\t.ascii " << rostring[i].str << endl;
    }
}

void TreeNode::genExprCode(ostream& out) {
    TreeNode* child1 = this->child;
    TreeNode* child2 = this->child->sibling;
    bool charFlag = false;
    switch (this->opType)
    {
        case OP_ADD: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child1->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child1->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child1->declType)
                {
                    case D_INT:{
                        out << "$" << child1->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child1->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %edx" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %dl, %edx" << endl;
                charFlag = false;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child2->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child2->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child2->declType)
                {
                    case D_INT:{
                        out << "$" << child2->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child2->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %eax" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %al, %eax" << endl;
                charFlag = false;
            }
            out << "\taddl %edx, %eax" << endl;
            out << "\tpushl %eax" << endl;
            break;
        }
        case OP_MIN: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child1->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child1->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child1->declType)
                {
                    case D_INT:{
                        out << "$" << child1->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child1->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %eax" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %al, %eax" << endl;
                charFlag = false;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child2->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child2->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child2->declType)
                {
                    case D_INT:{
                        out << "$" << child2->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child2->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %edx" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %dl, %edx" << endl;
                charFlag = false;
            }
            out << "\tsubl %edx, %eax" << endl;
            out << "\tpushl %eax" << endl;
        }
        case OP_MUL: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child1->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child1->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child1->declType)
                {
                    case D_INT:{
                        out << "$" << child1->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child1->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %edx" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %dl, %edx" << endl;
                charFlag = false;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child2->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child2->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child2->declType)
                {
                    case D_INT:{
                        out << "$" << child2->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child2->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %eax" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %al, %eax" << endl;
                charFlag = false;
            }
            out << "\timull %edx, %eax" << endl;
            out << "\tpushl %eax" << endl;
            break;
        }
        case OP_DIV: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child1->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child1->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child1->declType)
                {
                    case D_INT:{
                        out << "$" << child1->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child1->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %eax" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %al, %eax" << endl;
                charFlag = false;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child2->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child2->identifier;
                }
                out << ", %ebx" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child2->declType)
                {
                    case D_INT:{
                        out << "$" << child2->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child2->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %ebx" << endl;
            }
            else {
                child2->recursiveGenCode(out); 
                out << "\tpopl %ebx" << endl;
            }
            
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %al, %ebx" << endl;
                charFlag = false;
            }
            out << "\tcltd" << endl;
            out << "\tidivl %ebx" << endl;
            out << "\tpushl %eax" << this->tempId << endl;
            break;
        }
        case OP_MOD: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child1->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child1->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child1->declType)
                {
                    case D_INT:{
                        out << "$" << child1->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child1->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %eax" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %al, %eax" << endl;
                charFlag = false;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_CHAR) {
                    out << "\tmovzbl " << "_" << child2->identifier;
                    charFlag = true;
                }
                else {
                    out << "\tmovl " << "_" << child2->identifier;
                }
                out << ", %ebx" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl ";
                switch (child2->declType)
                {
                    case D_INT:{
                        out << "$" << child2->getIntValue();
                        break;
                    }
                    case D_CHAR: {
                        out << "$" << (int)child2->getCharValue();
                    }
                    default:
                        break;
                }
                out << ", %ebx" << endl;
            }
            else {
                child2->recursiveGenCode(out); 
                out << "\tpopl %ebx" << endl;
            }
            
            if (this->declType == D_INT && charFlag) {
                out << "\tmovsbl %al, %ebx" << endl;
                charFlag = false;
            }
            out << "\tcltd" << endl;
            out << "\tidivl %ebx" << endl;
            out << "\tpushl %edx" << this->tempId << endl;
            break;
        }
        case OP_AND: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->identifier << ", %edx" << endl;
                } else if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->identifier << ", %edx" << endl;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->identifier << ", %edx" << endl;
                }
            }
            else if (child1->nodeType == NODE_Const) {
                if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->getBoolValue() << ", %edx" << endl;
                } else if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->getIntValue() << ", %edx" << endl;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->getCharValue() << ", %edx" << endl;
                }      
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                } else if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->identifier << ", %eax" << endl;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                }
            }
            else if (child2->nodeType == NODE_Const) {
                if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->getBoolValue() << ", %eax" << endl;
                } else if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->getIntValue() << ", %eax" << endl;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->getCharValue() << ", %eax" << endl;
                }       
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            out << "\tandl %edx, %eax" << endl;
            out << "\tpushl %eax" << endl;
            break;
        }
        case OP_OR: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->identifier << ", %edx" << endl;
                } else if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->identifier << ", %edx" << endl;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->identifier << ", %edx" << endl;
                }
            }
            else if (child1->nodeType == NODE_Const) {
                if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->getBoolValue() << ", %edx" << endl;
                } else if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->getIntValue() << ", %edx" << endl;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->getCharValue() << ", %edx" << endl;
                }      
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                } else if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->identifier << ", %eax" << endl;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                }
            }
            else if (child2->nodeType == NODE_Const) {
                if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->getBoolValue() << ", %eax" << endl;
                } else if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->getIntValue() << ", %eax" << endl;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->getCharValue() << ", %eax" << endl;
                }       
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            out << "\torl %edx, %eax" << endl;
            out << "\tpushl %eax" << endl;
            break;
        }
        case OP_NOT: {
            bool value;
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar || 
                child1->nodeType == NODE_Const) {
                if (child1->declType == D_BOOL) {
                    value = child1->getBoolValue();
                    if (value) {
                        out << "\tpushl $0" << endl;
                    } else {
                        out << "\tpushl $1" << endl;
                    }  
                } else if (child1->declType == D_INT) {
                    if (child1->getIntValue() != 0) {
                        out << "\tpushl $0" << endl;
                    } else {
                         out << "\tpushl $1" << endl;
                    }
                } else if (child->declType == D_CHAR) {
                    if (child1->getCharValue() != 0) {
                        out << "\tpushl $0" << endl;
                    } else {
                         out << "\tpushl $1" << endl;
                    }
                }
            }
            else {
                child1->recursiveGenCode(out); 
                out << "\tpopl %eax" << endl;
                out << "\txorl $1, %eax" << endl;
                out << "\tpush %eax" << endl;
            }
            break;
        }
        case OP_EQU: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->identifier;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child1->declType == D_INT) {
                    out << child1->getIntValue();
                } else if (child1->declType == D_CHAR) {
                    out << (int)child1->getCharValue();
                } else if (child1->declType == D_BOOL) {
                    if (child1->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %edx" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->identifier;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child2->declType == D_INT) {
                    out << child2->getIntValue();
                } else if (child2->declType == D_CHAR) {
                    out << (int)child2->getCharValue();
                } else if (child2->declType == D_BOOL) {
                    if (child2->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %eax" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            if ((child1->declType == D_CHAR || child1->declType == D_BOOL) && ((child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar))) {
                out << "\tcmpb %al, %dl" << endl;
            } else {
                out << "\tcmpl %eax, %edx" << endl;
            }
            out << "\tjne TmpFalse" << tempLabelNum << endl;
            out << "\tpushl $1" << endl;
            out << "\tjmp TmpNext" << tempLabelNum << endl;
            out << "TmpFalse" << tempLabelNum << ":" << endl;
            out << "\tpushl $0" << endl;
            out << "TmpNext" << tempLabelNum << ":" << endl;
            tempLabelNum++;
            break;
        }
        case OP_GT: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->identifier;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child1->declType == D_INT) {
                    out << child1->getIntValue();
                } else if (child1->declType == D_CHAR) {
                    out << (int)child1->getCharValue();
                } else if (child1->declType == D_BOOL) {
                    if (child1->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %edx" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->identifier;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child2->declType == D_INT) {
                    out << child2->getIntValue();
                } else if (child2->declType == D_CHAR) {
                    out << (int)child2->getCharValue();
                } else if (child2->declType == D_BOOL) {
                    if (child2->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %eax" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            if ((child1->declType == D_CHAR || child1->declType == D_BOOL) && ((child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar))) {
                out << "\tcmpb %al, %dl" << endl;
            } else {
                out << "\tcmpl %eax, %edx" << endl;
            }
            out << "\tjle TmpFalse" << tempLabelNum << endl;
            out << "\tpushl $1" << endl;
            out << "\tjmp TmpNext" << tempLabelNum << endl;
            out << "TmpFalse" << tempLabelNum << ":" << endl;
            out << "\tpushl $0" << endl;
            out << "TmpNext" << tempLabelNum << ":" << endl;
            tempLabelNum++;
            break;
        }
        case OP_LT: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->identifier;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child1->declType == D_INT) {
                    out << child1->getIntValue();
                } else if (child1->declType == D_CHAR) {
                    out << (int)child1->getCharValue();
                } else if (child1->declType == D_BOOL) {
                    if (child1->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %edx" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->identifier;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child2->declType == D_INT) {
                    out << child2->getIntValue();
                } else if (child2->declType == D_CHAR) {
                    out << (int)child2->getCharValue();
                } else if (child2->declType == D_BOOL) {
                    if (child2->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %eax" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            if ((child1->declType == D_CHAR || child1->declType == D_BOOL) && ((child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar))) {
                out << "\tcmpb %al, %dl" << endl;
            } else {
                out << "\tcmpl %eax, %edx" << endl;
            }
            out << "\tjge TmpFalse" << tempLabelNum << endl;
            out << "\tpushl $1" << endl;
            out << "\tjmp TmpNext" << tempLabelNum << endl;
            out << "TmpFalse" << tempLabelNum << ":" << endl;
            out << "\tpushl $0" << endl;
            out << "TmpNext" << tempLabelNum << ":" << endl;
            tempLabelNum++;
            break;
        }
        case OP_GTQ: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->identifier;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child1->declType == D_INT) {
                    out << child1->getIntValue();
                } else if (child1->declType == D_CHAR) {
                    out << (int)child1->getCharValue();
                } else if (child1->declType == D_BOOL) {
                    if (child1->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %edx" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << endl;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->identifier;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child2->declType == D_INT) {
                    out << child2->getIntValue();
                } else if (child2->declType == D_CHAR) {
                    out << (int)child2->getCharValue();
                } else if (child2->declType == D_BOOL) {
                    if (child2->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %eax" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << endl;
            }
            if ((child1->declType == D_CHAR || child1->declType == D_BOOL) && ((child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar))) {
                out << "\tcmpb %al, %dl" << endl;
            } else {
                out << "\tcmpl %eax, %edx" << endl;
            }
            out << "\tjl TmpFalse" << tempLabelNum << endl;
            out << "\tpushl $1" << endl;
            out << "\tjmp TmpNext" << tempLabelNum << endl;
            out << "TmpFalse" << tempLabelNum << ":" << endl;
            out << "\tpushl $0" << endl;
            out << "TmpNext" << tempLabelNum << ":" << endl;
            tempLabelNum++;
            break;
        }
        case OP_LTQ: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->identifier;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child1->declType == D_INT) {
                    out << child1->getIntValue();
                } else if (child1->declType == D_CHAR) {
                    out << (int)child1->getCharValue();
                } else if (child1->declType == D_BOOL) {
                    if (child1->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %edx" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << child1->tempId;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->identifier;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child2->declType == D_INT) {
                    out << child2->getIntValue();
                } else if (child2->declType == D_CHAR) {
                    out << (int)child2->getCharValue();
                } else if (child2->declType == D_BOOL) {
                    if (child2->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %eax" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << child2->tempId;
            }
            if ((child1->declType == D_CHAR || child1->declType == D_BOOL) && ((child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar))) {
                out << "\tcmpb %al, %dl" << endl;
            } else {
                out << "\tcmpl %eax, %edx" << endl;
            }
            out << "\tjg TmpFalse" << tempLabelNum << endl;
            out << "\tpushl $1" << endl;
            out << "\tjmp TmpNext" << tempLabelNum << endl;
            out << "TmpFalse" << tempLabelNum << ":" << endl;
            out << "\tpushl $0" << endl;
            out << "TmpNext" << tempLabelNum << ":" << endl;
            tempLabelNum++;
            break;
        }
        case OP_NEQ: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                if (child1->declType == D_INT) {
                    out << "\tmovl _" << child1->identifier;
                } else if (child1->declType == D_CHAR) {
                    out << "\tmovzbl _" << child1->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child1->declType == D_BOOL) {
                    out << "\tmovzbl _" << child1->identifier;
                }
                out << ", %edx" << endl;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child1->declType == D_INT) {
                    out << child1->getIntValue();
                } else if (child1->declType == D_CHAR) {
                    out << (int)child1->getCharValue();
                } else if (child1->declType == D_BOOL) {
                    if (child1->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %edx" << endl;
            }
            else {
                child1->recursiveGenCode(out);
                out << "\tpopl %edx" << child1->tempId;
            }
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                if (child2->declType == D_INT) {
                    out << "\tmovl _" << child2->identifier;
                } else if (child2->declType == D_CHAR) {
                    out << "\tmovzbl _" << child2->identifier << ", %eax" << endl;
                    out << "\tmovsbl $al";
                } else if (child2->declType == D_BOOL) {
                    out << "\tmovzbl _" << child2->identifier;
                }
                out << ", %eax" << endl;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl $";
                if (child2->declType == D_INT) {
                    out << child2->getIntValue();
                } else if (child2->declType == D_CHAR) {
                    out << (int)child2->getCharValue();
                } else if (child2->declType == D_BOOL) {
                    if (child2->getBoolValue()) {
                        out << 1;
                    } else {
                        out << 0;
                    }
                }
                out << ", %eax" << endl;
            }
            else {
                child2->recursiveGenCode(out);
                out << "\tpopl %eax" << child2->tempId;
            }
            if ((child1->declType == D_CHAR || child1->declType == D_BOOL) && ((child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar))) {
                out << "\tcmpb %al, %dl" << endl;
            } else {
                out << "\tcmpl %eax, %edx" << endl;
            }
            out << "\tje TmpFalse" << tempLabelNum << endl;
            out << "\tpushl $1" << endl;
            out << "\tjmp TmpNext" << tempLabelNum << endl;
            out << "TmpFalse" << tempLabelNum << ":" << endl;
            out << "\tpushl $0" << endl;
            out << "TmpNext" << tempLabelNum << ":" << endl;
            tempLabelNum++;
            break;
        }
        default:
            break;
    }
}

void TreeNode::genFuncCode(ostream &out) {
    if (this->funcType == FUNC_DEFI) {
        if (strcmp("main", this->identifier.c_str()) == 0) {
            out << endl << "\t.text" << endl;
            out << "\t.global main" << endl;
            out << "\t.type main, @function" << endl;
            out << this->identifier << ":" << endl;
            out << "\tpushl %ebp" << endl;
            out << "\tmovl %esp, %ebp" << endl;
            TreeNode* bodyChild = this->child->sibling;
            while(bodyChild != nullptr) {
                bodyChild->recursiveGenCode(out);
                bodyChild = bodyChild->sibling;
            }
            out << "\tmovl %ebp, %esp" << endl;
            out << "\tpopl %ebp" << endl;
            out << "\tret" << endl;
        }
    }
    else if (this->funcType == FUNC_CALL) {
        if (strcmp("printf", this->child->identifier.c_str()) == 0) {
            cout << "printf" << endl;
            stack<TreeNode*> nodes;
            TreeNode* str = this->child->sibling;
            TreeNode* var = this->child->sibling->sibling;
            while(var != nullptr) {
                nodes.push(var);
                var = var->sibling;
            }
            int count = nodes.size();
            for (int i = nodes.size(); i > 0; i--) {
                TreeNode* node = nodes.top();
                out << "\tmovl _" << node->identifier << ", %eax" << endl;
                out << "\tpushl %eax" << endl;
                nodes.pop();
            }
            out << "\tpushl $LC" << str->tempId << endl;
            out << "\tcall printf" << endl;
            out << "\taddl $" << (count+1)*4 << ", %esp" << endl;
        }
        else if (strcmp("scanf", this->child->identifier.c_str()) == 0) {
            cout << "scanf" << endl;
            stack<TreeNode*> nodes;
            TreeNode* str = this->child->sibling;
            TreeNode* var = this->child->sibling->sibling;
            while(var != nullptr) {
                nodes.push(var);
                var = var->sibling;
            }
            int count = nodes.size();
            cout << "scanf" << count << endl;
            for (int i = nodes.size(); i > 0; i--) {
                TreeNode* node = nodes.top();
                out << "\tpushl $_" << node->identifier << endl;
                nodes.pop();
            }
            out << "\tpushl $LC" << str->tempId << endl;
            out << "\tcall scanf" << endl;
            out << "\taddl $" << (count+1)*4 << ", %esp" << endl;
        }
    }
    
    
}

