#ifndef PARSETREE_H
#define PARSETREE_H

#include <stack>
#include <string>

class ParseNode {
private:
  char value;
  ParseNode *left;
  ParseNode *right;

public:
  ParseNode(char v, ParseNode *l = nullptr, ParseNode *r = nullptr)
      : value(v), left(l), right(r) {}
  char getValue() { return value; }
  ParseNode *Left() { return left; }
  void Left(ParseNode *l) { left = l; }
  ParseNode *Right() { return right; }
  void Right(ParseNode *r) { right = r; }
};

class ParseTree {
public:
  ParseTree(std::string exp = "");
  virtual ~ParseTree();
  // Output binary tree in different orders
  std::string inOrder();
  std::string postOrder();
  std::string preOrder();

private:
  ParseNode *root;
  std::string buffer;

  ParseNode *doParse(std::string exp);
  void recDestruct(ParseNode *ptr);
  std::string recInOrder(ParseNode *ptr);
  std::string recPostOrder(ParseNode *ptr);
  std::string recPreOrder(ParseNode *ptr);
  bool isOperator(char value);
  bool isOperand(char value);
};

#endif // PARSETREE_H
