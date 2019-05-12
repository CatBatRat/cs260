#include "../deps/StringHash.h"
#include <iostream>
#include <stdexcept>
#include <string>

using std::string;

StringHash::StringHash() : tSize(5) {
  wordArr = new string[tSize];
  initArr();
}

void StringHash::initArr() {
  for (unsigned int a = 0; a < tSize; a++)
    wordArr[a] = "_empty_";
}

int StringHash::Hash(string input) {
  unsigned int index = BASE;
  for (int i = 0; i < static_cast<int>(input.length()); i++) {
    index *= BASE;
    index += input[i] * input[i];
    index %= tSize;
  }
  return index;
}

void StringHash::resize() {
  unsigned int oldSize = tSize;
  tSize = NextLowestPrime(tSize * 2);
  string *oldArr = wordArr;
  wordArr = new string[tSize];
  initArr();
  for (unsigned int i = 0; i < oldSize; i++) {
    if(oldArr[i] != "_empty_" && oldArr[i] != "_dele_")
      addValue(oldArr[i]);
  }
  delete[] oldArr;
}

void StringHash::addValue(string word) {
  if (numItems > tSize / 2)
    resize();
  unsigned int index = Hash(word);
  while (wordArr[index] != "_empty_") {
    index++;
    if (index >= tSize)
      index = 0;
  }
  numItems++;
  wordArr[index] = word;
}

unsigned int StringHash::find(string word) {
  unsigned int index = Hash(word);
  while (wordArr[index] != "_empty_" && wordArr[index] != word) {
    index++;
    if (index == tSize)
      index = 0;
  }
  return (wordArr[index] == word) ? index : tSize;
}

bool StringHash::findValue(string word) {
  unsigned int index = find(word);
  return (index < tSize);
}

bool StringHash::removeValue(string word) {
  unsigned int index = find(word);
  if (index < tSize) {
    wordArr[index] = "_dele_";
    return true;
  } else
    return false;
}

string StringHash::displayTable() {
  string out = "";
  for (unsigned int i = 0; i < tSize; i++)
    out += ((wordArr[i] != "_empty_") ? wordArr[i] + " " : "");
  return out;
}

unsigned int StringHash::NextLowestPrime(unsigned int number) {
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
