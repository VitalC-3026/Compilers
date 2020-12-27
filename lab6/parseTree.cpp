#include "parseTree.h"
#include "common.h"
#include <list>
#include <cstring>
#include <cassert>
extern FILE *yyout;
extern string getValueOfId(TreeNode*);
extern map<string, stack<idAttr>> identifierTable;
extern void yyerror(const char*);
void typeIncompatible(int, string);
void noOperands(int);


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
    if (this->getIsAlive() == false){
        return;
    }
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
                if (this->opType == OP_ADD || this->opType == OP_MIN || this->opType == OP_MUL ||
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
                                typeIncompatible(child->sibling->getNodeId(), (string)"Node_Var/ConstVar");
                                this->setDeclType(D_NONE);
                                this->setIsAlive(false);
                                return false;
                            }
                            
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
                            this->setDeclType(dType);
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
                                return true;
                            } else {
                                this->setDeclType(D_NONE);
                                typeIncompatible(child->nodeID, (string)"Node_Var/ConstVar");
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
                    } else if (dType == D_INT){
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
                        this->setIsAlive(false);
                        return true;
                    } else {
                        if (dType != D_BOOL) {
                            this->setDeclType(D_NONE);
                            typeIncompatible(child->nodeID, (string)"Node_Var/ConstVar");
                        }
                        if (child->sibling->getDeclType() != D_BOOL) {
                            this->setDeclType(D_NONE);
                            typeIncompatible(child->nodeID, (string)"Node_Var/ConstVar");
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
                                    typeIncompatible(this->nodeID, (string)"NODE_Assignment");
                                    this->setIsAlive(false);
                                    return false;
                                }
                                break;
                            }
                            case D_CHAR: {
                                if(siblingDType == D_CHAR || siblingDType == D_INT || siblingDType == D_BOOL) {
                                    return true;
                                } else {
                                    typeIncompatible(this->nodeID, (string)"NODE_Assignment");
                                    this->setIsAlive(false);
                                    return false;
                                }
                                break;
                            case D_STRING:
                                if(siblingDType != D_STRING) {
                                    typeIncompatible(this->nodeID, (string)"NODE_Assignment");
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
                                    typeIncompatible(this->nodeID, (string)"NODE_Assignment");
                                    this->setIsAlive(false);
                                    return false;
                                }
                            }
                            default: {
                                typeIncompatible(this->nodeID, (string)"NODE_Assignment");
                                this->setIsAlive(false);
                                return false;
                            }
                        }
                    } 
                    else if (this->child->getSibling() == nullptr && 
                    (this->child->getAssignmentType() == ADDASIGO || this->child->getAssignmentType() == MINASIGO)) {
                        if(dType != D_INT){
                            typeIncompatible(this->nodeID, (string)"NODE_Assignment");
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
                            typeIncompatible(this->nodeID, (string)"NODE_IF");
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
                            typeIncompatible(this->nodeID, (string)"NODE_While");
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

void typeIncompatible(int nodeID, string nodeType){
    string msg = (string)"Node@" + to_string(nodeID) + (string)" " + nodeType + (string)": type incompatible.";
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
            TreeNode* expr = this->getChild();
            TreeNode* trueBody = this->child->sibling;
            TreeNode* falseBody = nullptr;
            if(this->child->sibling->sibling){
                falseBody = this->child->sibling->sibling;
            }
            if (this->label.beginLabel == "") {
                this->label.beginLabel = newLabel();
            }
            trueBody->label.beginLabel = expr->label.trueLabel = newLabel();
            if (falseBody) {
                falseBody->label.beginLabel = expr->label.falseLabel = newLabel();
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
            falseBody->recursiveGenLabel();
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
                    if (operand2->stmtType == STMT_EXPR) {
                        operand2->recursiveGenLabel();
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
                    }
                    break;
                }
            }
            break;
        }
        default: {
            break;
        }

    }

}

string TreeNode::newLabel(){
    char tmp[20] = {0};
    sprintf(tmp, "@%d", TreeNode::labelCount);
    TreeNode::labelCount++;
    return (string)tmp;
}

void TreeNode::recursiveGenLabel() {
    if (this->nodeType == NODE_Stmt || this->stmtType == STMT_EXPR) {
        this->genStmtLabel();
    } 
    else if (this->nodeType == NODE_Func) {
        this->genFuncLabel();
    }
    else {
        if (this->nodeType == NODE_Prog) {
            this->label.beginLabel = "_start";
        }
        TreeNode* child = this->child;
        while(child != nullptr){
            child->recursiveGenLabel();
        }
    }
}

void TreeNode::genCode(ostream &out) {
    out << "# your asm code header here!" << endl;
    if(this->nodeType == NODE_Prog) {
        bool textHeader = true;
        out << "# define your variables and temporal variables here" << endl;
        TreeNode* child = this->child;
        while(child != nullptr) {
            child->recursiveGenCode(out);
        }
    }
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
            break;
        }
        case STMT_EXPR: {
            this->genExprCode(out);
            break;
        }
        case STMT_DECL: {
            this->genDeclCode(out);
            break;
        }
    }
}

// temp variables => how to identify and generate
void TreeNode::genDeclCode(ostream &out) {
    out << endl << "# define your variables here" << endl;
    map<string, stack<idAttr>>::iterator it = identifierTable.begin();
    for(; it != identifierTable.end(); it++) {
        if(!it->second.empty()){
            idAttr attr = it->second.top();
            if (!attr.isConst) {
                out << "\t.globl\t" << "_" << it->first << endl;
                out << "\t.bss" << endl;
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child1->tempId;
            }
            out << ", %edx" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %edx" << endl;
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child2->tempId;
            }
            out << ", %eax" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %eax" << endl;
                charFlag = false;
            }
            out << "\taddl %edx, %eax" << endl;
            if (this->declType == D_CHAR) {
                out << "\tmovb %al, t" << this->tempId << endl;
            } else {
                out << "\tmovl %eax, t" << this->tempId << endl;
            }
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child1->tempId;
            }
            out << ", %edx" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %edx" << endl;
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child2->tempId;
            }
            out << ", %eax" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %eax" << endl;
                charFlag = false;
            }
            out << "\tsubl %edx, %eax" << endl;
            if (this->declType == D_CHAR) {
                out << "\tmovb %al, t" << this->tempId << endl;
            } else {
                out << "\tmovl %eax, t" << this->tempId << endl;
            }
            break;
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child1->tempId;
            }
            out << ", %edx" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %edx" << endl;
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child2->tempId;
            }
            out << ", %eax" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %eax" << endl;
                charFlag = false;
            }
            out << "\timull %edx, %eax" << endl;
            if (this->declType == D_CHAR) {
                out << "\tmovb %al, t" << this->tempId << endl;
            } else {
                out << "\tmovl %eax, t" << this->tempId << endl;
            }
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child1->tempId;
            }
            out << ", %eax" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %eax" << endl;
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child2->tempId;
            }
            out << ", %ebx" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %ebx" << endl;
                charFlag = false;
            }
            out << "\tcltd" << endl;
            out << "\tidivl %ebx" << endl;
            if (this->declType == D_CHAR) {
                out << "\tmovb %al, t" << this->tempId << endl;
            } else {
                out << "\tmovl %eax, t" << this->tempId << endl;
            }
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child1->tempId;
            }
            out << ", %eax" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %eax" << endl;
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
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "t" << child2->tempId;
            }
            out << ", %ebx" << endl;
            if (this->declType == D_INT && charFlag) {
                cout << "\tmovsbl %al, %ebx" << endl;
                charFlag = false;
            }
            out << "\tcltd" << endl;
            out << "\tidivl %ebx" << endl;
            out << "\tmovl %edx, %eax" << endl; // remainder in %edx
            if (this->declType == D_CHAR) {
                out << "\tmovb %al, t" << this->tempId << endl;
            } else {
                out << "\tmovl %eax, t" << this->tempId << endl;
            }
            break;
        }
        case OP_AND: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                out << "\tmovzbl _" << child1->identifier;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl $" << child1->getBoolValue();       
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "\tmovzbl t" << child1->tempId;
            }
            out << ", %edx" << endl;
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                out << "\tmovzbl _" << child2->identifier;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl $" << child1->getBoolValue();       
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "\tmovzbl t" << child2->tempId;
            }
            out << ", %eax" << endl;
            out << "\tandl %edx, %eax" << endl;
            out << "\tmovb %eax, t" << this->tempId << endl;
            break;
        }
        case OP_OR: {
            if (child1->nodeType == NODE_Var || child1->nodeType == NODE_ConstVar) {
                out << "\tmovzbl _" << child1->identifier;
            }
            else if (child1->nodeType == NODE_Const) {
                out << "\tmovl $" << child1->getBoolValue();       
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "\tmovzbl t" << child1->tempId;
            }
            out << ", %edx" << endl;
            if (child2->nodeType == NODE_Var || child2->nodeType == NODE_ConstVar) {
                out << "\tmovzbl _" << child2->identifier;
            }
            else if (child2->nodeType == NODE_Const) {
                out << "\tmovl $" << child1->getBoolValue();       
            }
            else {
                // (child1->nodeType == NODE_Op) 
                out << "\tmovzbl t" << child2->tempId;
            }
            out << ", %eax" << endl;
            out << "\torl %edx, %eax" << endl;
            out << "\tmovb %eax, t" << this->tempId << endl;
            break;
        }
        default:
            break;
    }
}