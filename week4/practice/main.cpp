#include <cctype>
#include <iostream>
#include <string>
using namespace std;

struct node *tree = nullptr;

struct node {
  char value;
  node *parent;
  node *left;
  node *right;
  node(char value, node *parent = nullptr)
      : value(value), parent(parent), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
  node *root;

public:
  BinaryTree() : root(nullptr) {}

  void insert(char alg)
  {
    node *ptr = root;
    while (true)
    {
      if (( isOperator(alg) || isOperand(alg) )&& root == nullptr)
      {
        root = new node(alg);
        return;
      }
      if (isOperator(alg))
      {
        if (!ptr->right)
        {
          ptr->right = new node(alg, ptr);
          return;
        }
        else
        {
          ptr = ptr->right;
        }
      }
      if (isOperand(alg))
      {
        if(!ptr->left)
        {
          ptr->left = new node(alg, ptr);
          return;
        }
        else if (!ptr->right)
        {
          ptr->right = new node(alg, ptr);
          return;
        }
        else
        {
          ptr = ptr->left;
        }
      }
    }
  }

  // helper function for doParse, true if valueis operator(+ - * /)
  bool isOperator(char value) {
    std::string operators = "*/+-";
    for (int i = 0; i < 4; i++)
      if (operators[i] == value)
        return true;
    return false;
  }

  // helper function for doParse, true if value is letter or digit
  bool isOperand(char value) {
    if (std::isdigit(value) || std::isalpha(value))
      return true;
    return false;
  }

  void print() { recprint(root); }

  std::string recprint(node *ptr)
  {
    if (ptr == nullptr)
      return "";

    std::string out = "";

    if(isOperator(ptr->parent->value))
    {
      recprint(ptr->left);
      cout << ptr->value << " ";
      recprint(ptr->right);
    }
    return out;
  }
};

int main() {

  BinaryTree bt;

  /*char c = '0';

  do {
    std::cin >> c;
    bt.insert(c);
    bt.print();
  } while (c != '$');*/

  bt.insert('3');
  bt.insert('7');
  bt.insert('-');
  bt.insert('4');
  bt.insert('5');
  bt.insert('+');
  bt.insert('*');

  bt.print();

  return 0;
}
