#include "HeapSort.hpp"
#include <iostream>

// Inline swap function that use bitwise XOR to swap the bit of the variables
// without having to create an new variable as the transfer point.
inline void HeapSort::intSwap(int &l, int &r) {
  l ^= r;
  r ^= l;
  l ^= r;
}

// tried a few different methods here that all work.
void HeapSort::heapify() {
  for (int i = 0; i < size; i++)
    bubbleUp(i);
}

void HeapSort::heapSort(int arr[], int size) {
  this->heap = arr;
  this->size = size;
  int fullSize = size;
  heapify();
  for (int h = 0; h < fullSize; h++) {
    minSort();
  }
}

// Swap element at front with end that call trickle down to re-heap
//   decrement `--size`
inline void HeapSort::minSort() {
  // only perform the sort while `size` is greater than 0
  if(--size > 0) { // decrement the size before comparison
    intSwap(heap[0], heap[size]);
    trickleDown(0);
  }
}

// Swap with parent until child is not greater than parent.
void HeapSort::bubbleUp(int i) {
  int p = parent(i);
  while (i > 0 && (heap[i] > heap[p])) {
    intSwap(heap[p], heap[i]);
    i = p;
    p = parent(i);
  }
}

// Compare the current node to both children and swap with the lowest of the two
// then set current to the one swapped with and run the check again until they
// are in decending order per level of the tree.
void HeapSort::trickleDown(int i) {
  do {
    int child = -1;
    int r = right(i);
    if (r < size && heap[r] > heap[i]) {
      int l = left(i);
      if (heap[l] > heap[r]) {
        child = l;
      } else {
        child = r;
      }
    } else {
      int l = left(i);
      if (l < size && heap[l] > heap[i]) {
        child = l;
      }
    }
    if (child >= 0)
      intSwap(heap[i], heap[child]);
    i = child;
  } while (i >= 0);
}
