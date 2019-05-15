#ifndef _CHAINED_HASH_
#define _CHAINED_HASH_

#include <stdexcept>
#include <string>

using std::string;

struct Node {
  string word;
  Node *next;
  Node(string word, Node *next = nullptr)
      : word(word), next(next) {}
};

class ChainedHash {
private:
  int tSize = 17;
  Node **wordArr;

  int NextLowestPrime(unsigned int number);
  void deleteChain(Node *ptr);
  void initArr();
  int Hash(string input);

public:
  ChainedHash();
  ChainedHash(unsigned int size);
  ~ChainedHash();
  void addValue(string word);
  bool findValue(string word);
  bool removeValue(string word);
  string displayTable();
};

#endif //_CHAINED_HASH_
