#include <iostream>
using namespace std;

struct node *tree = nullptr;

struct node {
  int value;
  node *left;
  node *right;
  node(int value) : value(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
  node *root;

public:
  BinaryTree() : root(nullptr) {}

  void insert(int n) {
    node *ptr = root;
    while (true) {
      if (root == nullptr) {
        root = new node(n);
        return;
      }
      if (n < ptr->value) {
        if (ptr->left == nullptr) {
          ptr->left = new node(n);
          return;
        } else {
          ptr = ptr->left;
        }
      }
      else {
        if (ptr->right == nullptr) {
          ptr->right = new node(n);
          return;
        } else {
          ptr = ptr->right;
        }
      }
    }
  }

  void print() {
    recprint(root);
  }
  void recprint(node *ptr) {
    static int counter = 0;
    if(ptr == nullptr)
      return;
    counter++;
    recprint(ptr->left);
    cout << ptr->value << endl;
    recprint(ptr->right);
    counter--;
  }

};

int main() {

  int i;
  BinaryTree bt;

  do {
    cout << "enter a number into the tree plz.. ";
    cin >> i;
    bt.insert(i);
  } while (i != -0);

  bt.print();

  return 0;
}
