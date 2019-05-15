#ifndef STRINGHASH_H
#define STRINGHASH_H

#include <iostream>

class StringHash
{
    public:
        StringHash();
        StringHash(int newSize);
        void initialize();
        void resize();
        void addItem(std::string value);
        bool findItem(std::string value);
        bool removeItem(std::string value);
        std::string displayTable();
        int hash(std::string value);
        ~StringHash();

    private:
        std::string *table;
        int tableSize;
        int itemCount;
};

#endif
