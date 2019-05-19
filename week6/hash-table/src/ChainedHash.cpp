#include "../deps/ChainedHash.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

const int BASE = 26;

// generate new table and initialize the array
ChainedHash::ChainedHash() {
  initArr();
}

// generate new table and initialize the array
//   ensure the value entered is a prime number
//   and find the next lowest prime if not
ChainedHash::ChainedHash(unsigned int size) {
  tSize = NextLowestPrime(size);
  initArr();
}


// fill new array with `nullptr`
void ChainedHash::initArr() {
  wordArr = new Node *[tSize];
  for (int i = 0; i < tSize; i++) {
    wordArr[i] = nullptr;
  }
}

// Clear of the nodes from each element of the table
ChainedHash::~ChainedHash() {
  for (int i = 0; i < tSize; i++) {
    if (wordArr[i])
      deleteChain(wordArr[i]);
  }
  std::cout << "deleting array" << std::endl;
  delete[] wordArr;
}

void ChainedHash::deleteChain(Node *ptr) {
  if (ptr) {
    deleteChain(ptr->next);
    std::cout << "deleting " << ptr->word << std::endl;
    delete ptr;
  }
}

// display the table with each set of nodes on its on line
//   and each value separated by commas
string ChainedHash::displayTable() {
  std::ostringstream out;
  for (int o = 0; o < tSize; o++) {
    // if node present
    if (wordArr[o]) {
      Node *display = wordArr[o];
      while (display) {
        out << display->word;
        // insert new line if next value nullptr
        //   else `,`
        out << ((display->next) ? ", " : "\n");
        display = display->next;
      }
    } else
      out << "_empty_\n";
  }
  return out.str();
}

// start at first item in table element and move down
//   the chain checking for value
bool ChainedHash::findValue(string word) {
  Node *ptr = wordArr[Hash(word)];
  while (ptr) {
    if (ptr->word == word)
      return true;
    ptr = ptr->next;
  }
  return false;
}

// delete value if single link in list and set next as value in
//   table, else delete link and close gap
bool ChainedHash::removeValue(string word) {
  int index = Hash(word);
  Node *ptr = wordArr[index], *last;
  // special case single node
  if (ptr && ptr->word == word) {
    wordArr[index] = ptr->next;
    delete ptr;
    return true;
  }
  while (ptr) {
    last = ptr;
    ptr = ptr->next;
    if (ptr->word == word) {
      last->next = ptr->next;
      delete ptr;
      return true;
    }
  }
  return false;
}

void ChainedHash::addValue(string word) {
  int index = Hash(word);
  // special case emtpy space in table
  if (wordArr[index] == nullptr)
    wordArr[index] = new Node(word);
  // at head if node present
  else {
    Node *ptr = new Node(word, wordArr[index]);
    wordArr[index] = ptr;
  }
}

// generate hash value from word input and use as index for
//   placement in table
int ChainedHash::Hash(string input) {
  unsigned int index = BASE;
  for (unsigned int i = 0; i < input.length(); i++) {
    index *= BASE;
    index += input[i] * (input[i]);
    index %= tSize;
  }
  return index;
}

// finds the next lowest prime number below a given number
int ChainedHash::NextLowestPrime(unsigned int number) {
  bool prime = true;
  for (unsigned int n = number; n > number / 2; n--) {
    for (unsigned int d = 2; d <= n / 2; d++) {
      if (n % d == 0) {
        prime = false;
        break;
      }
    }
    if (prime) {
      return n;
    }
    prime = true;
  }
  return number;
}
