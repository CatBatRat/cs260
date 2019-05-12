//
//  Tree.h
//  binary_search_tree
//
//  Created by Jim Bailey on 11/1/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#ifndef Tree_h
#define Tree_h

#include <string>

// definition of class
// using public variables rather than setters/getters
class Node {
public:
  // constructor to build new node
  Node(int v)
      : left(nullptr), right(nullptr), parent(nullptr), value(v),
        present(true) {}

  // public variables for contents
  Node *left;
  Node *right;
  Node *parent;
  int value;
  bool present;
};

// definition of binary search tree
class Tree {
private:
  Node *root;

  // for display function
  static const int SPACE = 8;

  // private functions for recursion
  bool recFind(int value, Node *ptr);
  std::string recPreOrder(Node *ptr);
  std::string recInOrder(Node *ptr);
  std::string recPostOrder(Node *ptr);

  // recursive method for destructor
  void recDestruct(Node *ptr);

  // private methods for delete
  Node *recDelete(Node *ptr, int value);
  Node *minValueNode(Node *ptr);

  // recursive method for display
  std::string recDisplay(Node *ptr, int level);

public:
  // constructor and destructor
  Tree();
  ~Tree();

  // maintenance methods
  void addNode(int value);
  bool find(int value);
  // delete by marking absent
  bool deleteMark(int value);
  // delete by removing
  bool deleteRemove(int value);

  // traversals
  std::string preOrder();
  std::string inOrder();
  std::string postOrder();

  // graphical display
  std::string displayTree();
};

#endif /* Tree_h */
