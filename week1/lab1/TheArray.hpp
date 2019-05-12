#ifndef THE_ARRAY
#define THE_ARRAY

#include <iostream>
#include <stdexcept>
#include <string>

// Global value for default size of the array.
const int DEF_SIZE = 10;

// I don't think this is setup for all types, but it should handle most cases.
template <class T> class TheArray {
private:
  int bounds;
  int index;
  T *arr;
  void increase(int i);
  void decrease(int i);
  void newSize(int s);

  inline void ifError(int i) const;
  inline void swapper(T &left, T &right);

public:
  TheArray();
  TheArray(int size);
  ~TheArray() { delete[] arr; }
  void setSize(int s);

  void append(T n);
  void setAt(int i, T n);
  // Takes a number (int n) and index (int i) and inserts n at i position.
  void insertAt(int i, T n);
  T removeAt(int i);

  const T &getAt(int i) const;
  const T &getFirst() const { return arr[0]; }
  const T &getLast() const { return arr[index - 1]; }
  const T &getSize() const { return bounds; }
  T &operator[](int i) {
    ifError(i);
    return arr[i];
  }
  const T &operator[](int i) const {
    ifError(i);
    return arr[i];
  }
};

// ==Method=Definitions========================================================

// --private-methods-----------------------------------------------------------

// Simple bit of reusable code set as inline because it will be used more
// than ones and performs a simple task.
template <class T> inline void TheArray<T>::ifError(int i) const {
  if (i < 0 or i >= bounds) {
    throw std::out_of_range("Not a valid position in array.");
  }
}

template <class T> void TheArray<T>::newSize(int s) {
  T *temp = new T[s];
  for (int x = 0; x < index; x++) {
    temp[x] = arr[x];
  }
  delete[] arr;
  arr = temp;
}

template <class T> void TheArray<T>::increase(int i) {
  if (i >= bounds) {
    while (i >= bounds - 1) {
      bounds *= 2;
    }
    newSize(bounds);
  }
}

template <class T> void TheArray<T>::decrease(int i) {
  if (i < bounds / 2 && i > 10) {
    bounds /= 2;
    newSize(bounds);
  } else if (i < 10) {
    bounds = i + 10;
    newSize(bounds);
  }
}

// Use bitwise operations for swapping because they don't need an extra
// variable.
template <class T> inline void TheArray<T>::swapper(T &l, T &r) {
  l ^= r;
  r ^= l;
  l ^= r;
}

// --public-methods------------------------------------------------------------

template <class T> TheArray<T>::TheArray() : bounds(DEF_SIZE), index(0) {
  arr = new T[DEF_SIZE];
}

template <class T> TheArray<T>::TheArray(int n) : index(0) {
  if (n < 1) {
    bounds = DEF_SIZE;
    arr = new int[DEF_SIZE];
  } else {
    bounds = n;
    arr = new int[n];
  }
}

// If new size greater than number of items in array then resize.
template <class T> void TheArray<T>::setSize(int s) {
  if (s > index) {
    bounds = s;
    newSize(s);
  }
}

// remember to increment the index for each new item added.
template <class T> void TheArray<T>::append(T n) {
  increase(index);
  arr[index] = n;
  index++;
}

// Set some value in the array as long as it is within the bounds/size
template <class T> void TheArray<T>::setAt(int i, T n) {
  ifError(i);
  if (i > index) {
    index = i + 1;
  }
  arr[i] = n;
}

// Insert a new value and move all other items over in the array.
// Also remember to increment the index and resize the array if
// it approaches the bounds.
template <class T> void TheArray<T>::insertAt(int i, T n) {
  ifError(i);
  increase(++index);
  for (int x = index; x > i; x--) {
    swapper(arr[x], arr[x - 1]);
  }
  arr[i] = n;
}

// Check to see if the array is empty before attempting to remove an item
// from the array. Also check if index requested is out of bounds and throw
// an error message if it is not valid. Array will also decrease in size if
// the index is less than half of the bounds.
template <class T> T TheArray<T>::removeAt(int i) {
  ifError(i);
  if (index == 0)
    throw std::out_of_range("Cannot remove from an empty array.");
  T temp = arr[i];
  for (int x = i; x < index; x++) {
    swapper(arr[x], arr[x + 1]);
  }
  // Make sure to decrement the index when a value is removed.
  index--;
  decrease(index);
  return temp;
}

template <class T> const T &TheArray<T>::getAt(int i) const {
  ifError(i);
  return arr[i];
}

#endif // THE_ARRAY
