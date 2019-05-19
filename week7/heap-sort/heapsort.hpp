#ifndef __HEAP__
#define __HEAP__

class HeapSort {
private:
  //int head = 0;
  int size;
  int *heap;

protected:
  inline int left(int i) { return 2 * i + 1; }
  inline int right(int i) { return 2 * i + 2; }
  inline int parent(int i) { return (i - 1) / 2; }
  inline void intSwap(int &left, int &right);
  inline void minSort();
  void heapify();
  void bubbleUp(int index);
  void trickleDown( int index);

public:
  HeapSort() : size(0), heap(nullptr) {}
  void heapSort(int arr[], int size);
};

#endif // __HEAP__
