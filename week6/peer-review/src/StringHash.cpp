#include <memory.h>
#include "StringHash.h"

const std::string EMPTY = "_empty_";
const std::string DELETED = "_deleted_";

// Creates a hash table of a default size.
StringHash::StringHash() {

    table = new std::string[11];
    tableSize = 11;

    initialize();
}

// Creates a hash table with a custom size.
StringHash::StringHash(int newSize) {

    table = (newSize <= 0) ? new std::string[11] : new std::string [newSize];
    tableSize = (newSize <= 0) ? 11 : newSize;

    initialize();
}

// Initializes common values that both constructors need.
void StringHash::initialize() {

    for(int i = 0; i < tableSize; i++)
        table[i] = EMPTY;

    itemCount = 0;
}

// Resizes the array.
void StringHash::resize() {

    int newSize = (2 * tableSize);

    std::string *temp = new std::string[newSize];

    for(int i = 0; i < tableSize; i++)
        temp[i] = table[i];

    delete[] table;
    table = temp;
}

// Adds an item to the hash table.
void StringHash::addItem(std::string value) {

    // Resizes when over 50% full.
    if(itemCount > (tableSize / 2))
        resize();

    // Gets an index to add at.
    int index = hash(value);

    // Uses linear probing to find the next available
    // value in the hash table.
    while(table[index] != EMPTY && table[index] != DELETED) {

        index++;

        if(index >= tableSize)
            index = 0;
    }

    // Updates the count and adds the item.
    if(table[index] != DELETED) {
        table[index] = value;
        itemCount++;
    }

}

// Finds an item in the hash table.
bool StringHash::findItem(std::string value) {

    // Acquires the starting index.
    int index = hash(value);

    // Checks if the current value is the value
    // we're searching for. Uses linear probing
    // to iterate.
    while(table[index] != EMPTY) {

        if(table[index] == value)
            return true;

        index++;

        if(index >= tableSize)
            index = 0;
    }

    // The value must not have been found.
    return false;
}

// Removes an item from the hash table
bool StringHash::removeItem(std::string value) {

    int index = hash(value);

    while(table[index] != EMPTY) {

        if(table[index] == value) {
            table[index] = DELETED;
            return true;
        }

        index++;

        if(index >= tableSize)
            index = 0;
    }

    return false;
}

// Displays the table as a list with
// each item on a new line.
std::string StringHash::displayTable() {

    std::string list = "";

    for(int i = 0; i < tableSize; i++)
        list += table[i] + "\n";

    return list;
}

int StringHash::hash(std::string value) {

    int index = 0;

    for(int i = 0; i < static_cast<int>(value.length()); i++) {

        index *= 26;

        index += value[i];

        index %= tableSize;
    }

    return index;
}

// Deletes the hash table from memory.
StringHash::~StringHash() {
    delete[] table;
}
