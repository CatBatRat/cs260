#ifndef  __PRIORITY_QUEUE__
#define  __PRIORITY_QUEUE__

#include "Heap.h"

class PriorityQueue {
  private:
    Heap prQueue;
  public:
    PriorityQueue(int qSize = 10): prQueue(qSize) {}

    // This simply uses some of the functions of Heap class to create a Priority Queue
    void insert(int value) {prQueue.insert(value);}
    int peek() {return prQueue.largest();}
    int remove() {return prQueue.remove();}
};

#endif //__PRIORITY_QUEUE__
