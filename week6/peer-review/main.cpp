//
//  main.cpp
//  heap_example
//
//  Created by Jim Bailey on 5/15/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include <iostream>
#include <cstdlib>
#include <stdexcept>

// uncomment the test you want to run
#define STRING_HASH
#define CHAINED_HASH


#ifdef STRING_HASH
#include "StringHash.h"
#endif
#ifdef CHAINED_HASH
#include "ChainedHash.h"
#endif

using namespace std;


int main() {

    const int NUM_VALUES = 10;

    string string_values[NUM_VALUES] = {"dog", "god", "cat", "act", "horse", "cow", "elephant", "otter", "seal", "ales"};

#ifdef STRING_HASH

    // this tests the string hashing code
    // define standard sized table with 11 slots
    StringHash stringHash;

    // place 10 items in a hash table
    // should cause doubling to 22 slots
    for(int i = 0; i < NUM_VALUES; i++)
        stringHash.addItem(string_values[i]);

    // dump the array
    cout << "Displaying the array before find and delete" << endl;
    cout << stringHash.displayTable() << endl;

    // now see if find works
    cout << "Looking for pig, should not find -- " << (stringHash.findItem("pig")?"found":"not found") << endl;
    cout << "Looking for otter, should find -- " << (stringHash.findItem("otter")?"found":"not found") << endl;

    // now delete otter and see if still found
    cout << "Deleting otter, should work -- " << (stringHash.removeItem("otter")?"found":"not found") << endl;
    // now looking again
    cout << "Looking for otter again, should not find -- " << (stringHash.findItem("otter")?"found":"not found") << endl;

    // dump the array
    cout << endl << "Displaying the array after deleting otter, s/b replaced with _deleted_" << endl;
    cout << stringHash.displayTable() << endl;

#endif //STRING_HASH

#ifdef CHAINED_HASH
    // this tests the chained string hashing code

    ChainedHash chainHash;

    // place 10 items in a hash table
        for(int i = 0; i < NUM_VALUES; i++)
            chainHash.addItem(string_values[i]);

    // dump the array
    cout << "Displaying the array before find and delete" << endl;
    cout << chainHash.displayTable() << endl;

    // now see if find works
    cout << "Looking for pig, should not find -- " << (chainHash.findItem("pig")?"found":"not found") << endl;
    cout << "Looking for otter, should find -- " << (chainHash.findItem("otter")?"found":"not found") << endl;

    // now delete otter and see if still found
    cout << "Deleting otter, should work -- " << (chainHash.removeItem("otter")?"found":"not found") << endl;
    cout << "Looking for otter again, should not find -- " << (chainHash.findItem("otter")?"found":"not found") << endl;

    // dump the array
    cout << endl << "Displaying the array after deleting otter, should no longer be there" << endl;
    cout << chainHash.displayTable() << endl;

#endif // CHAINED_TEST

    return 0;
}
