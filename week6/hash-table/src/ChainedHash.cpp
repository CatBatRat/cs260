#include "../deps/ChainedHash.h"
#include <sstream>
#include <stdexcept>
#include <string>

ChainedHash::ChainedHash() {
  wordArr = new Chain *[tSize];
  initArr();
}

void ChainedHash::initArr() {
  for (int i = 0; i < tSize; i++) {
    wordArr[i] = nullptr;
  }
}

ChainedHash::~ChainedHash() {
  for (int i = 0; i < tSize; i++) {
    if (wordArr[i])
      deleteChain(wordArr[i]);
  }
  delete[] wordArr;
}

void ChainedHash::deleteChain(Chain *ptr) {
  if (ptr) {
    deleteChain(ptr->next);
    delete ptr;
  }
}

string ChainedHash::displayTable() {
  std::ostringstream out;
  for (int o = 0; o < tSize; o++) {
    if (wordArr[o] != nullptr) {
      Chain *display = wordArr[o];
      while (display) {
        out << display->word;
        out << ((display->next) ? ", " : "\n");
        display = display->next;
      }
    } else
      out << "_empty_\n";
  }
  return out.str();
}

bool ChainedHash::findValue(string word) {
  Chain *ptr = wordArr[Hash(word)];
  while (ptr) {
    if (ptr->word == word)
      return true;
    ptr = ptr->next;
  }
  return false;
}

bool ChainedHash::removeValue(string word) {
  int index = Hash(word);
  Chain *ptr = wordArr[index], *last;
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
  if (wordArr[index] == nullptr)
    wordArr[index] = new Chain(word);
  else {
    Chain *ptr = new Chain(word, wordArr[index]);
    wordArr[index] = ptr;
  }
}

int ChainedHash::Hash(string input) {
  unsigned int index = BASE;
  for (unsigned int i = 0; i < input.length(); i++) {
    index *= BASE;
    index += input[i] * (input[i]);
    index %= tSize;
  }
  return index;
}
