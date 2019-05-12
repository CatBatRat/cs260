#include "ParseTree.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>

// constructor, build tree from expression
ParseTree::ParseTree(std::string expression) {
  if (expression != "")
    root = doParse(expression);
}

// desctructor, delete nodes in tree
ParseTree::~ParseTree() { recDestruct(root); }

// inorder traversal
std::string ParseTree::inOrder() {
  return recInOrder(root);
}

// postorder traversal
std::string ParseTree::postOrder() { return recPostOrder(root); }

// preorder traversal
std::string ParseTree::preOrder() { return recPreOrder(root); }

// helper function for doParse, true if valueis operator(+ - * /)
bool ParseTree::isOperator(char value) {
  std::string operators = "*/+-";
  for (int i = 0; i < 4; i++)
    if (operators[i] == value)
      return true;
  return false;
}

// helper function for doParse, true if value is letter or digit
bool ParseTree::isOperand(char value) {
  if (std::isdigit(value) || std::isalpha(value))
    return true;
  return false;
}

// helper method to do the parsing and save tree
ParseNode *ParseTree::doParse(std::string exp) {
  // Stack to hold the parts as the string is parsed
  std::stack<ParseNode *> nodes;
  for (unsigned int i = 0; i < exp.length(); i++) {
    char aChar = exp[i];
    // Do nothing is the there is a space
    if (exp[i] == ' ')
      continue;
    else if (isOperand(aChar)) {
      // Temp node to be added to stack and remove later
      // wnen it is time to attach it to the new root
      ParseNode *temp = new ParseNode(aChar);
      nodes.push(temp);
    } else if (isOperator(aChar)) {
      // Use top then pop because pop does not return
      // the value when removing from the stack
      ParseNode *right = nodes.top();
      nodes.pop();
      ParseNode *left = nodes.top();
      nodes.pop();
      ParseNode *oper = new ParseNode(aChar, left, right);
      nodes.push(oper);
    }
  }
  // Return the top of the stack which is now a single item after
  // all elements of the stack have been attached to the root
  return nodes.top();
}

// recursive helper methods
void ParseTree::recDestruct(ParseNode *ptr) {
  if (ptr) {
    recDestruct(ptr->Right());
    recDestruct(ptr->Left());
    delete ptr;
  }
}

// Recursively walk through the binary tree in order
// and wrap operators with operands in perenthisis
std::string ParseTree::recInOrder(ParseNode *ptr) {
  std::string buffer = "";
  if (!ptr)
    return "";
  // Only add perenthisis when is an operator or and not root
  if (isOperator(ptr->getValue()) && ptr != root)
    buffer += "(";
  buffer += recInOrder(ptr->Left());
  buffer += ptr->getValue();
  buffer += recInOrder(ptr->Right());
  if (isOperator(ptr->getValue()) && ptr != root)
    buffer += ")";
  return buffer;
}

// Post order traversle of the binary tree
std::string ParseTree::recPostOrder(ParseNode *ptr) {
  std::string buffer = "";
  if (!ptr)
    return "";
  buffer += recPostOrder(ptr->Left());
  buffer += recPostOrder(ptr->Right());
  buffer += ptr->getValue();
  return buffer;
}

// Pre order traversle of the binary tree
std::string ParseTree::recPreOrder(ParseNode *ptr) {
  std::string buffer = "";
  if (!ptr)
    return "";
  buffer += ptr->getValue();
  buffer += recPreOrder(ptr->Left());
  buffer += recPreOrder(ptr->Right());
  return buffer;
}
