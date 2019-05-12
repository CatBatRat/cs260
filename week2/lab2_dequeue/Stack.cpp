#include "Stack.h"
#include <stdexcept>

void Stack::push(int n) {
  addRight(n);
}

int Stack::pop() {
  if(isEmpty())
    arrError("stack");
  return getRight();
}

int Stack::peek() {
  if(isEmpty())
    arrError("stack");
  int temp = getRight();
  addRight(temp);
  return temp;
}
