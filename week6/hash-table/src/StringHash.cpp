#include "../deps/StringHash.h"
#include <stdexcept>
#include <string>

using std::string;

// constants
const unsigned int BASE = 26;   // base for hash value
const int DEFAULT = 11;         // default table size
const string EMPTY = "_EMPTY_"; // empty cell
const string DEL = "_DELETED_"; // deleted but still full cell

// default constructor
StringHash::StringHash() : tSize(DEFAULT) { initArr(); }

// overloaded constructor. both offload most of inits to initArr
StringHash::StringHash(unsigned int size) {
  // ensure the provided value is a prime number
  tSize = NextLowestPrime(size);
  initArr();
}

// create the array of values and fill it with the EMPTY string const
//   also resets numItems as this gets called again when the array is resized
void StringHash::initArr() {
  numItems = 0;
  wordArr = new string[tSize];
  for (unsigned int a = 0; a < tSize; a++)
    wordArr[a] = EMPTY;
}

// a simple hash method to generate the index to store a value at
int StringHash::Hash(string input) {
  // use of unsigned int prevent undefined behavior when modulus called
  //   negative numbers
  unsigned int index = BASE;
  for (unsigned int i = 0; i < input.length(); i++) {
    index *= BASE;
    // multiplying the input times itself seems to give slightly better spread
    index += input[i] * input[i];
    index %= tSize;
  }
  return index;
}

void StringHash::resize() {
  // store the old size as this is needed to index into the old array
  unsigned int oldSize = tSize;
  tSize = NextLowestPrime(tSize * 2);
  // store the old array
  string *oldArr = wordArr;
  // initialize a new array
  initArr();
  for (unsigned int i = 0; i < oldSize; i++) {
    // only copy over valid entries
    if (oldArr[i] != EMPTY && oldArr[i] != DEL)
      addValue(oldArr[i]);
  }
  delete[] oldArr;
}

void StringHash::addValue(string word) {
  // call resize if the table is over half full
  if (numItems > tSize / 2)
    resize();
  // generate the index where the input word will be stored
  unsigned int index = Hash(word);
  // use linear probing to find the next empty or deleted space
  //   and place the word there
  while (wordArr[index] != EMPTY && wordArr[index] != DEL) {
    index++;
    if (index >= tSize)
      index = 0;
  }
  // increment the count of items in the table
  numItems++;
  wordArr[index] = word;
}

// this returns the index where the word was found
//   returns the size of the table if not found which acts as
//   false since no value can be at this location
unsigned int StringHash::find(string word) {
  unsigned int index = Hash(word);
  while (wordArr[index] != EMPTY && wordArr[index] != word) {
    index++;
    if (index == tSize)
      index = 0;
  }
  return (wordArr[index] == word) ? index : tSize;
}

// returns false if the value returned from find is the array size
//   true if a valid index
bool StringHash::findValue(string word) {
  unsigned int index = find(word);
  return (index < tSize);
}

// same as above but use valid index to delete a value
bool StringHash::removeValue(string word) {
  unsigned int index = find(word);
  if (index < tSize)
    wordArr[index] = DEL;
  return (index < tSize);
}

// simply display contents of each element of the table
string StringHash::displayTable() {
  string out = "";
  for (unsigned int i = 0; i < tSize; i++)
    out += wordArr[i] + "\n";
  return out;
}

// finds the next lowest prime number below a given number
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
