#ifndef __HEAP__
#define __HEAP__

class Heap {
private:
  int size;
  int bounds;
  int *heap;

public:
  Heap(int bounds = 10) : size(0), bounds(bounds) { heap = new int[bounds]; }
  ~Heap() {delete[] heap;}
  inline int left(int i) { return 2 * i + 1; }
  inline int right(int i) { return 2 * i + 2; }
  inline int parent(int i) { return (i - 1) / 2; }
  inline void intSwap(int &left, int &right);
  void bubbleUp(int index);
  void trickleDown( int index);
  void insert(int index);
  inline void grow();
  void resize(int s);
  int largest() {return heap[0];}
  int remove();
};

#endif // __HEAP__
