//
//  main.cpp
//  heap_example
//
//  Created by Jim Bailey on 5/15/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include <cstdlib>
#include <iostream>
#include <stdexcept>

// uncomment the test you want to run
#define STRING_HASH
#define CHAIN_HASH

#ifdef STRING_HASH
#include "deps/StringHash.h"
#endif
#ifdef CHAIN_HASH
#include "deps/ChainedHash.h"
#endif

using namespace std;

int main() {

  const int NUM_VALUES = 10;

  string string_values[NUM_VALUES] = {"dog",   "god", "cat",      "act",
                                      "horse", "cow", "elephant", "otter",
                                      "seal",  "ales"};

#ifdef STRING_HASH

  // this tests the string hashing code

  // change this to your class name
  StringHash stringHash;

  // place 10 items in a hash table
  try {

    for (int i = 0; i < NUM_VALUES; i++)
      stringHash.addValue(string_values[i]);
  } catch (std::length_error &ex) {
    cout << "Inserting failed with exception: " << ex.what() << endl;
    exit(1);
  }

  // dump the array
  cout << "Displaying the array before find and delete" << endl;
  cout << stringHash.displayTable() << endl;

  // now see if find works
  cout << "Looking for pig, should not find -- "
       << (stringHash.findValue("pig") ? "found" : "not found") << endl;
  cout << "Looking for otter, should find -- "
       << (stringHash.findValue("otter") ? "found" : "not found") << endl;

  // now delete 5 and see if still found
  cout << "Deleting otter, should work -- "
       << (stringHash.removeValue("otter") ? "found" : "not found") << endl;
  // now looking again
  cout << "Looking for otter again, should not find -- "
       << (stringHash.findValue("otter") ? "found" : "not found") << endl;

  // dump the array
  cout
      << endl
      << "Displaying the array after deleting otter, s/b replaced with \"dele\""
      << endl;
  cout << stringHash.displayTable() << endl;

#endif // STRING_HASH

#ifdef CHAIN_HASH
  // this tests the chained string hashing code

  // change this to your class name
  ChainedHash chainHash;

  // place 10 items in a hash table
  try {

    for (int i = 0; i < NUM_VALUES; i++)
      chainHash.addValue(string_values[i]);
  } catch (std::length_error &ex) {
    cout << "Inserting failed with exception: " << ex.what() << endl;
    exit(1);
  }

  // dump the array
  cout << "Displaying the array before find and delete" << endl;
  cout << chainHash.displayTable() << endl;

  // now see if find works
  cout << "Looking for pig, should not find -- "
       << (chainHash.findValue("pig") ? "found" : "not found") << endl;
  cout << "Looking for otter, should find -- "
       << (chainHash.findValue("otter") ? "found" : "not found") << endl;

  // now delete 5 and see if still found
  cout << "Deleting otter, should work -- "
       << (chainHash.removeValue("otter") ? "found" : "not found") << endl;
  // now looking again
  cout << "Looking for otter again, should not find -- "
       << (chainHash.findValue("otter") ? "found" : "not found") << endl;

  // dump the array
  cout << endl
       << "Displaying the array after deleting otter, should no longer be there"
       << endl;
  cout << chainHash.displayTable() << endl;

#endif // CHAINED_TEST

  return 0;
}
