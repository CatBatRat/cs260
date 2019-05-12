//
//  Tree.cpp
//  binary_search_tree
//
//  Created by Jim Bailey on 11/1/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include "Tree.h"
#include <iomanip>
#include <iostream>
#include <sstream>

// constructor
Tree::Tree() { root = nullptr; }

// destructor, remove all nodes
Tree::~Tree() { recDestruct(root); }

// recursive destructor, does the work
void Tree::recDestruct(Node *ptr) {
  // if at leaf, nothing to do
  if (ptr == nullptr)
    return;

  // delete children
  recDestruct(ptr->left);
  recDestruct(ptr->right);

  // delete self
  delete ptr;
}

// Add a node containing value
void Tree::addNode(int value) {
  // special case empty tree
  if (root == nullptr) {
    root = new Node(value);
    return;
  }

  // now we start at root
  // find proper leaf location
  // and add it there
  Node *ptr = root;
  while (true) {
    // see if happens to have right value and deleted
    if (ptr->value == value and !ptr->present) {
      ptr->present = true;
      return;
    }

    // see if add to the left
    if (ptr->value > value) {
      // nothing there, leaf
      if (ptr->left == nullptr) {
        ptr->left = new Node(value);
        ptr->left->parent = ptr;
        return;
      }
      // need to go down branch further
      else {
        ptr = ptr->left;
      }
    }
    // otherwise we are going right
    else {
      // nothing there, leaf
      if (ptr->right == nullptr) {
        ptr->right = new Node(value);
        ptr->right->parent = ptr;
        return;
      }
      // need to go down branch further
      else {
        ptr = ptr->right;
      }
    }
  }
}

// return true if value is in the tree
bool Tree::find(int value) { return recFind(value, root); }

bool Tree::recFind(int value, Node *ptr) {
  // base case
  if (ptr == nullptr)
    return false;

  // base, found
  if (ptr->value == value and ptr->present)
    return true;

  // need to go further
  if (ptr->value > value)
    return recFind(value, ptr->left);
  else
    return recFind(value, ptr->right);
}

// delete by marking absent
// based on non-recursive find
bool Tree::deleteMark(int value) {
  // start at root
  Node *ptr = root;

  // until done with path
  while (ptr != nullptr) {
    if (ptr->value == value and ptr->present) {
      ptr->present = false;
      return true;
    }
    if (ptr->value > value)
      ptr = ptr->left;
    else
      ptr = ptr->right;
  }
  return false;
}

// delete by removing
bool Tree::deleteRemove(int value) {
  // see if it is there
  bool found = recFind(value, root);

  // call recursive delete, returns root of modified tree
  root = recDelete(root, value);

  return found;
}

// recursive delete function
Node *Tree::recDelete(Node *ptr, int value) {
  // base case
  if (ptr == nullptr)
    return nullptr;

  // if left, go there
  if (ptr->value > value)
    ptr->left = recDelete(ptr->left, value);
  else {
    // if right, go there
    if (ptr->value < value)
      ptr->right = recDelete(ptr->right, value);

    // finally, we have the node, so delete it
    else {
      // first, no left child
      if (ptr->left == nullptr) {
        Node *temp = ptr->right;
        delete ptr;
        return temp;
      }

      // second, no right child
      if (ptr->right == nullptr) {
        Node *temp = ptr->right;
        delete ptr;
        return temp;
      }

      // two children, need to replace with inorder successor

      // find smallest value in right subtree
      Node *temp = minValueNode(ptr->right);

      // copy that value to this node
      ptr->value = temp->value;

      // now delete that node
      ptr->right = recDelete(ptr->right, temp->value);
    }
  }
  return ptr;
}

Node *Tree::minValueNode(Node *ptr) {
  Node *current = ptr;

  while (current->left != nullptr)
    current = current->left;
  return current;
}

// traversals
std::string Tree::preOrder() { return recPreOrder(root); }
std::string Tree::inOrder() { return recInOrder(root); }
std::string Tree::postOrder() { return recPostOrder(root); }

// recursive traversals, build string from value
std::string Tree::recPreOrder(Node *ptr) {
  std::string buffer = "";

  // if done with branch, return empty
  if (ptr == nullptr)
    return buffer;

  // get this nodes value
  std::stringstream temp;
  temp << std::setw(5) << ptr->value;

  // build buffer in proper order
  buffer += temp.str();
  buffer += recPreOrder(ptr->left);
  buffer += recPreOrder(ptr->right);

  return buffer;
}
std::string Tree::recInOrder(Node *ptr) {
  std::string buffer = "";

  // if done with branch, return empty
  if (ptr == nullptr)
    return buffer;

  // get this nodes value
  std::stringstream temp;
  temp << std::setw(5) << ptr->value;

  // build buffer in proper order
  buffer += recInOrder(ptr->left);
  buffer += temp.str();
  buffer += recInOrder(ptr->right);

  return buffer;
}
std::string Tree::recPostOrder(Node *ptr) {
  std::string buffer = "";

  // if done with branch, return empty
  if (ptr == nullptr)
    return buffer;

  // get this nodes value
  std::stringstream temp;
  temp << std::setw(5) << ptr->value;

  // build buffer in proper order
  buffer += recPostOrder(ptr->left);
  buffer += recPostOrder(ptr->right);
  buffer += temp.str();

  return buffer;
}

// graphical display
std::string Tree::displayTree() { return recDisplay(root, 0); }
// recursive methods called by public methods
std::string Tree::recDisplay(Node *ptr, int space) {
  // base case, quit on leaf
  if (ptr == nullptr)
    return "";

  std::stringstream buffer;
  space += SPACE;

  buffer << recDisplay(ptr->right, space);
  buffer << std::endl
         << std::setw(space - SPACE) << " " << std::setw(4) << ptr->value;
  if (ptr->present)
    buffer << std::endl;
  else
    buffer << " dele" << std::endl;
  buffer << recDisplay(ptr->left, space);

  return buffer.str();
}
