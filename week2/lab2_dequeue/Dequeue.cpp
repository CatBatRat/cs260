#include "Dequeue.h"
#include <iostream>
#include <sstream>
#include <string>

// I was starting left and right from the 0 index, but that required special
// logic for whether an item was the first being added to an empty array.
// Now they don't start overlapped, so indexing them is much easier.
Dequeue::Dequeue() : left(0), right(1), len(0), bounds(10) {
  arr = new int[bounds];
}

// Starting at the center, but there is not need to and, in fact, will not stay
// centered if the array is resized.
Dequeue::Dequeue(int size) : left(0), right(1), len(0) {
  bounds = size;
  arr = new int[bounds];
}

inline void Dequeue::arrError(std::string type) {
  throw std::range_error("There is nothing left in the " + type + ".");
}

// I realized this would be used in more than one place, so I broke it into a
// function that works with a reference so the value passed in could changed
// producing cleaner code. This also meant I didn't need any other condition to
// determine which value I would be working with as it would simply work with
// whatever was fed into it.
inline int &Dequeue::wrap(int &w) {
  w = (w < 0) ? bounds - 1 : w;
  w = (w >= bounds) ? w = 0 : w;
  return w;
}

// Simply determines whether the dequeue is full before calling resize with
// double the bounds size.
void Dequeue::grow() {
  if (isFull()) {
    resize(bounds * 2);
  }
}

// This gets called by grow. I broke it into a separate function because I
// thought I should have some means of shrinking the array as elements are
// taken out, but I could not come up with a good solution that would hold up
// in many situations.
void Dequeue::resize(int newSize) {
  int *temp = new int[newSize];
  for (int i = 0; i < bounds; i++) {
    temp[i] = arr[(i + left) % bounds];
  }
  left = 0;
  right = bounds - 1;
  bounds = newSize;
  delete[] arr;
  arr = temp;
}

// The only difference between the ways adding and getting are handled is the
// order that the left/right values are incremented. This way I was able to
// keep the functions simple and clean and it made it a lot easier to for me to
// follow the logic of my own code. `wrap()` is called at the same time the
// left/right index is incremented so it can work with the future value and I
// am free to use said value right away.
void Dequeue::addLeft(int n) {
  len++;
  grow();
  arr[left] = n;
  wrap(--left);
}

int Dequeue::getLeft() {
  if (isEmpty())
    arrError("dequeue");
  len--;
  wrap(++left);
  return arr[left];
}

void Dequeue::addRight(int n) {
  len++;
  grow();
  arr[right] = n;
  wrap(++right);
}

int Dequeue::getRight() {
  if (isEmpty())
    arrError("dequeue");
  len--;
  wrap(--right);
  return arr[right];
}

// Simply use getLeft as it already has all the features I need to handle
// pulling values out of the array.
std::string Dequeue::listLeftRight() {
  int tempLen = len;
  std::ostringstream out;
  for (int i = 0; i < tempLen; i++) {
    out << getLeft() << " ";
  }
  len = tempLen;
  return out.str();
}

// Measure `len` and if it is 0 the list is empty. This relies on me properly
// incrementing and decrementing the value as the program is running.
bool Dequeue::isEmpty() {
  if (len <= 0)
    return true;
  return false;
}

// Same, but in the other direction.
bool Dequeue::isFull() {
  if (len + 1 >= bounds)
    return true;
  return false;
}
