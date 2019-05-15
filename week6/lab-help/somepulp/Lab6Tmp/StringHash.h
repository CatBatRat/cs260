#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string EMPTY = "_empty_";
const string DEL = "_dele_";
const int DEFAULT = 37;

class StringHash {
private:
  string *arr;
  int prime[5] = {23, 47, 97, 197, 397};
  int n; // Index for prime[]
  int count;
  int size;

public:
  StringHash();
  StringHash(int nSize);
  ~StringHash();
  void resize();
  void addItem(string value);
  // bool findItem(string value);
  // bool removeItem(string value);
  string displayTable();
  int hash(string value);
};

StringHash::StringHash() {
  arr = new string[DEFAULT];
  size = DEFAULT;
  // initialize all indices to EMPTY
  for (int i = 0; i < DEFAULT; i++)
    arr[i] = EMPTY;
}

StringHash::StringHash(int nSize) {
  arr = new string[nSize];
  for (int i = 0; i < nSize; i++)
    arr[i] = EMPTY;
  size = nSize;
}

StringHash::~StringHash() {}

void StringHash::resize() {
  int primes[5] = {23, 47, 97, 197, 397};
  int j = 0;
  int oldSize = size;

  // Cycle through primes until greater than 2*size
  while (primes[j] < size * 2)
    j++;

  // create tmp array of strings whose size is determined by next prime number
  // in prime[]
  arr = new string[primes[j]];
  size = primes[j];

  for (int i = 0; i < size; i++)
    if (arr[i] != EMPTY)
      addItem(arr[i]);
}

void StringHash::addItem(string value) {

  if (count >= (size / 2))
    resize();

  // Assign the index by converting string to int with hash function
  int index = hash(value);

  // Implements linear probing
  while (arr[index] != EMPTY) {
    index++;
    // Wrap back to 0
    if (index >= size)
      index = 0;
  }

  count++;
  arr[index] = value;
}

// bool StringHash::findItem(string value) {}

// bool StringHash::removeItem(string value) {}

string StringHash::displayTable() {
  ostringstream output;
  for (int i = 0; i < size; i++)
    output << arr[i] << endl;

  return output.str();
}

int StringHash::hash(string value) {
  int index = 0;

  for (int i = 0; i < static_cast<int>( value.length() ); i++) {
    index *= 26;
    index += value[i];
    index %= size;
  }

  return index;
}
