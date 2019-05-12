#ifndef _CHAINED_HASH_
#define _CHAINED_HASH_

#include <stdexcept>
#include <string>

using std::string;

struct Chain {
  string word;
  Chain *next;
  Chain(string word, Chain *next = nullptr)
      : word(word), next(next) {}
};

class ChainedHash {
private:
  const int BASE = 26;
  int tSize = 17;
  Chain **wordArr;

  int NextLowestPrime(int number);
  void deleteChain(Chain *ptr);
  void initArr();
  int Hash(string input);

public:
  ChainedHash();
  ~ChainedHash();
  void addValue(string word);
  bool findValue(string word);
  bool removeValue(string word);
  string displayTable();
};

#endif //_CHAINED_HASH_
