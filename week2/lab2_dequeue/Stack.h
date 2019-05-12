#ifndef STACK
#define STACK

#include "Dequeue.h"

class Stack : public Dequeue {
  public:
    Stack() { arr = new int[bounds]; }
    Stack(int size) { arr = new int[size]; }
    ~Stack() { delete[] arr; }
    void push(int n);
    int pop();
    int peek();
};


#endif // STACK
