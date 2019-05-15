#include <iostream>
#include <algorithm>
#include "ChainedHash.h"

const std::string EMPTY = "_empty_";

// Creates an array of linked lists with a default size
// of 17.
ChainedHash::ChainedHash() {
    table = new std::list<std::string>[17];
    tableSize = 17;
}

// Creates a new hash table using linked lists. Defaults
// to 17 lists in size if the new size is invalid.
ChainedHash::ChainedHash(int newSize) {
    table = (newSize <= 0) ? new std::list<std::string>[17] : new std::list<std::string>[newSize];
    tableSize = (newSize <= 0) ? 17 : newSize;
}

// Adds a new item to the hash table.
void ChainedHash::addItem(std::string value) {

    int index = hash(value);

    table[index].push_front(value);
}

// Finds an item in the hash table.
bool ChainedHash::findItem(std::string value) {

    int index = hash(value);

    return std::find(table[index].begin(), table[index].end(), value) != table[index].end();
}

// Removes an item from the hash table.
bool ChainedHash::removeItem(std::string value) {

    int index = hash(value);

    if(findItem(value)) {
        table[index].remove(value);
        return true;
    }

    else
        return false;
}

// Returns a list of all items in the hash table.
std::string ChainedHash::displayTable() {

    std::string list = "";

    for(int i = 0; i < tableSize; i++) {

        std::string subList = "";

        if(!table[i].empty())
            for(auto o : table[i]) subList += o + "     ";

        else
            subList = EMPTY;


        subList += "\n";
        list += subList;
    }

    return list;
}

int ChainedHash::hash(std::string value) {

    int index = 0;

    for(int i = 0; i < static_cast<int>(value.length()); i++) {

        index *= 26;

        index += value[i];

        index %= tableSize;
    }

    return index;
}

// Deletes the hash table from memory.
ChainedHash::~ChainedHash() {
    delete[] table;
}
