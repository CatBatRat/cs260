#include <stdexcept>
#include <string>

#ifndef __OPEN_HASH__
#define __OPEN_HASH__

using std::string;

class StringHash {
private:
  const unsigned int BASE = 26;
  unsigned int numItems = 0;
  unsigned int tSize;
  string *wordArr;

  unsigned int NextLowestPrime(unsigned int number);
  unsigned int find(string word);
  void resize();
  void initArr();
  int Hash(string input);

public:
  StringHash();
  ~StringHash() { delete[] wordArr; }
  void addValue(string word);
  bool findValue(string word);
  bool removeValue(string word);
  string displayTable();
};

#endif //__OPEN_HASH__
