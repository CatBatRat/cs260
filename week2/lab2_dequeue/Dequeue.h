#ifndef DEQUEUE
#define DEQUEUE

#include <stdexcept>
#include <string>

class Dequeue {
private:
  inline int & wrap(int &w);
  void grow();
  void resize(int newSize);
  int left;
  int right;
  int len;

protected:
  int bounds;
  int *arr;
  inline void arrError(std::string type);

public:
  Dequeue();
  Dequeue(int size);
  ~Dequeue() { delete[] arr; }
  void addLeft(int n);
  int getLeft();
  void addRight(int n);
  int getRight();
  std::string listLeftRight();
  bool isEmpty();
  bool isFull();
};

#endif // DEQUEUE
