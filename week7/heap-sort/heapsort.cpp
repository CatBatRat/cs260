#include "Heap.h"
#include <iostream>

using namespace std;

// Inline swap function that use bitwise XOR to swap the bit of the variables
// without having to create an new variable as the transfer point.
inline void Heap::intSwap(int &l, int &r) {
  l ^= r;
  r ^= l;
  l ^= r;
}

// Insert new element at end of heap then use bubbleUp to place element at the
// right level.
void Heap::insert(int n) {
  grow();
  heap[size] = n;
  bubbleUp(size);
  size++;
}

// Swap with parent until child is not greater than parent.
void Heap::bubbleUp(int i) {
  int p = parent(i);
  while (i > 0 && (heap[i] > heap[p])) {
    intSwap(heap[p], heap[i]);
    i = p;
    p = parent(i);
  }
}

// Store element at index 0, fill posision with element at end the trickle down
// until in the proper place
int Heap::remove() {
  if (size <= 0)
    throw std::length_error("No more items to remove from heap.");
  int temp = heap[0];
  heap[0] = heap[--size];
  trickleDown(0);
  return temp;
}

// Compare the current node to both children and swap with the lowest of the two
// then set current to the one swapped with and run the check again until they
// are in decending order per level of the tree.
void Heap::trickleDown(int i) {
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

// Simple function to check if the heap should be resized.
inline void Heap::grow() {
  if (size >= bounds)
    resize(bounds * 2);
}

// Create a new heap array and copy the contents from old to new then delete the
// old one.
void Heap::resize(int s) {
  int *newHeap = new int[s];
  for (int s = 0; s < bounds; s++) {
    newHeap[s] = heap[s];
  }
  delete[] heap;
  heap = newHeap;
  bounds *= 2;
}
