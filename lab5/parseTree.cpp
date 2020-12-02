#include "parseTree.h"
extern FILE *yyout;
extern string getValueOfId(TreeNode*);

void TreeNode::addChild(TreeNode* &child) {
    if (this->child == nullptr) {
        this->child = child;
    } else {
        this->child->addSibling(child);
    }
}

void TreeNode::addSibling(TreeNode* &sibling) {
    TreeNode* node = this;
    string info = to_string(sibling->getNodeId()) + (string)" add sibling\n";
    fputs(info.c_str(), yyout);
    
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
}

// TreeNode::TreeNode(){}

void TreeNode::generateNodeID() {
    this->nodeID = ++count;
}

int TreeNode::getNodeId() {
    return this->nodeID;
}

void TreeNode::setNodeId(int i) {
    this->nodeID = i;
    count--;
}

void TreeNode::printInfo() {
    string info = (string)"NodeID: " + to_string(this->nodeID);
    info += (string)" NodeType: " + TreeNode::nodeType2String(this->nodeType);
    info += (string)" Attributes: " + this->attributes() + "\n";
    fputs(info.c_str(), yyout);
}

void TreeNode::printAST() {
    this->printInfo();
    string info = to_string(this->lineno) + " " + to_string(this->nodeID) + (string)"'s children\n";
    fputs(info.c_str(), yyout);
    TreeNode* node = this->child;
    if(node != nullptr){
        node->printAST();
        node = node->sibling;
        while(node != nullptr) {
            node->printAST();
            node = node->sibling;
        }
    }
    // info = "end " + to_string(this->nodeID) + (string)"'s child\n";
    // fputs(info.c_str(), yyout);
    // info = to_string(this->lineno) + " " + to_string(this->nodeID) + (string)"'s sibling\n";
    // fputs(info.c_str(), yyout);
    // if (this->getNodeId() == 1) {
    //     cout << this->getNodeId() << ": " << (this->sibling == nullptr) << endl;
    // }
    // if (this->getNodeId() == 2) {
    //     cout << this->getNodeId() << ": " << this->sibling->getNodeId() << endl;
    // }
    // if (this->getNodeId() == 3) {
    //     cout << this->getNodeId() << ": " << this->sibling->getNodeId() << endl;
    // }
    // if (this->getNodeId() == 4) {
    //     cout << this->getNodeId() << ": " << this->sibling->getNodeId() << endl;
    // }
    info = "end " + to_string(this->nodeID) + (string)"'s children\n";
    fputs(info.c_str(), yyout);
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

string TreeNode::nodeType2String(NodeType t){
    switch(t){
        case 0:
            return (string)"Program Root";
        case 1:
            return (string)"Const Variable";
        case 2:
            return (string)"Variable";
        case 3:
            return (string)"Operator";
        case 4:
            return (string)"Expression";
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
            value += getValueOfId(this);
            return decl + value;
        }
        case 3:
            return operatorType2String(this->opType);
        case 4:
        // expression
            return "";
        case 5: {
            string stmt = statementType2String(this->stmtType);
            if(stmt == (string)"Assignment") {
                string asig = assignmentType2String(this->asigType);
                return stmt+(string)" "+asig; 
            }
            return stmt;
        }
        case 6:
        // function
            return "";
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
        default:
            return (string)"";
    }
}