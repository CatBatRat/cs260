#include <iostream>
using namespace std;

struct node *tree = nullptr;

struct node {
  int data;
  struct node *left;
  struct node *right;
};

struct node *newNode(int data) {
  struct node *tree = new (struct node);
  tree->data = data;
  tree->left = nullptr;
  tree->right = nullptr;

  return (tree);
}

struct node *insert(struct node *tree, int data) {

  if (tree == nullptr) {
    return (newNode(data));
  } else {
    if (data <= tree->data)
      tree->left = insert(tree->left, data);
    else
      tree->right = insert(tree->right, data);
    return (tree);
  }
}

void printTree(struct node *tree) {

  if (tree == nullptr)
    return;

  printTree(tree->left);
  cout << tree->data;
  printTree(tree->right);
}

int main() {

  int i;

  do {
    cout << "enter a number into the tree plz.. ";
    cin >> i;
    tree = insert(tree, i);
  } while (i != -0);

  printTree(tree);

  return 0;
}
