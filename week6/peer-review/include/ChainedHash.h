#include <iostream>
#include <list>

#ifndef CHAINEDHASH_H
#define CHAINEDHASH_H

class ChainedHash
{
    public:
        ChainedHash();
        ChainedHash(int newSize);
        void addItem(std::string value);
        bool findItem(std::string value);
        bool removeItem(std::string value);
        std::string displayTable();
        int hash(std::string value);
        ~ChainedHash();

    private:
        std::list<std::string> *table;
        int tableSize;
};

#endif
