// queue_fifo.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file

//
//  main.cpp
//  Array_project
//
//  Created by Jim Bailey on 9/30/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include "Dequeue.h"
#include "Stack.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace std;

// uncomment the lines for the tests
// you want to run.  Each is separate

#define TEST_DEQUEUE_LIFO
#define TEST_DEQUEUE_FIFO
#define TEST_DEQUEUE_WRAP
#define TEST_DEQUEUE_EXCEPTS
#define TEST_DEQUEUE_GROW

#define TEST_LIST_DEQUEUE

#define TEST_STACK

int main() {

  const int DEF_SIZE = 10;

// testing adding and removing from each side
#ifdef TEST_DEQUEUE_LIFO
  cout << endl << "Testing double ended queue as two LIFOs:" << endl << endl;
  Dequeue aQ(DEF_SIZE);

  cout << "Before testing array should be empty and it "
       << (aQ.isEmpty() ? "is" : "is not") << endl;

  cout << "first add left, get left\n";
  aQ.addLeft(1);
  aQ.addLeft(2);
  aQ.addLeft(3);
  cout << "  last, sb 3 = " << aQ.getLeft() << " ";
  cout << " next, sb 2 = " << aQ.getLeft() << " ";
  cout << " first, sb 1 = " << aQ.getLeft() << endl;

  cout << "\nnext add right, get right\n";
  aQ.addRight(6);
  aQ.addRight(7);
  aQ.addRight(8);
  cout << "  last, sb 8 = " << aQ.getRight() << " ";
  cout << " next, sb 7 = " << aQ.getRight() << " ";
  cout << " first, sb 6 = " << aQ.getRight() << endl;

  cout << endl
       << "After testing array should be empty and it "
       << (aQ.isEmpty() ? "is" : "is not") << endl
       << endl;

#endif // TEST_DEQUEUE_LIFO

// testing adding from one side and removing from the other
#ifdef TEST_DEQUEUE_FIFO
  cout << "Testing double ended queue as two FIFOs:" << endl << endl;
  Dequeue bQ(DEF_SIZE);

  cout << "Before testing array should be empty and it "
       << (bQ.isEmpty() ? "is" : "is not") << endl
       << endl;

  cout << "first add left, get right\n";
  bQ.addLeft(1);
  bQ.addLeft(2);
  bQ.addLeft(3);
  cout << "  first, sb 1 = " << bQ.getRight() << " ";
  cout << " next, sb 2 = " << bQ.getRight() << " ";
  cout << " last, sb 3 = " << bQ.getRight() << endl;

  cout << endl << "now add right, get left" << endl;
  bQ.addRight(6);
  bQ.addRight(7);
  bQ.addRight(8);
  cout << "  first, sb 6 = " << bQ.getLeft() << " ";
  cout << " next, sb 7 = " << bQ.getLeft() << " ";
  cout << " last, sb 8 = " << bQ.getLeft() << endl;

  cout << endl
       << "After testing array should be empty and it "
       << (bQ.isEmpty() ? "is" : "is not") << endl
       << endl;

#endif // TEST_DEQUEUE_FIFO

// test if the queue wraps from left to right and right to left
#ifdef TEST_DEQUEUE_WRAP
  Dequeue dq(DEF_SIZE);

  cout << "Testing wrap from left to right: " << endl << endl;
  cout << "Adding 10 even ints to left, removing four from right" << endl;
  for (int i = 0; i < 10; i++)
    dq.addLeft(2 * i);

  cout << " should be: 0  2  4  6  " << endl;
  cout << " they are:";
  for (int i = 0; i < 4; i++)
    cout << setw(3) << dq.getRight();
  cout << endl << endl;

  cout << "Adding 3 more to left " << endl;
  for (int i = 10; i < 13; i++)
    dq.addLeft(2 * i);

  cout << "Now removing all from the right \n should be: 8 10 12 14 16 18 20 "
          "22 24"
       << endl;
  cout << " they are:";
  while (!dq.isEmpty())
    cout << setw(3) << dq.getRight();
  cout << endl << endl;

  cout << "Now repeating test from right to left with odd numbers" << endl;
  for (int i = 0; i < 10; i++)
    dq.addRight(2 * i + 1);
  cout << " should be: 1  3  5  7 " << endl;
  cout << " they are:";
  for (int i = 0; i < 4; i++)
    cout << setw(3) << dq.getLeft();
  cout << endl << endl;

  cout << "Adding 3 more to right " << endl;
  for (int i = 10; i < 13; i++)
    dq.addRight(2 * i + 1);

  cout << "Now removing all from the left \n should be: 9 11 13 15 17 19 21 23 "
          "25 "
       << endl;
  cout << " they are:";
  while (!dq.isEmpty())
    cout << setw(3) << dq.getLeft();
  cout << endl;

  cout << endl << "Done with testing wrap on dequeue." << endl << endl;

#endif // TEST_DEQUEUE_WRAP

// testing removing from empty
#ifdef TEST_DEQUEUE_EXCEPTS
  cout << endl << "Now testing exceptions " << endl << endl;
  Dequeue eq(DEF_SIZE);

  cout << "\nTesting get left on empty queue, should throw exception" << endl;
  try {
    eq.getLeft();
    cout << "Should thrown exception, did not" << endl;
  } catch (range_error &err) {
    cout << "Caught error with message " << err.what() << endl;
  } catch (...) {
    cout << "Caught some other exception" << endl;
  }

  cout << "\nTesting get right on empty queue, should throw exception" << endl;
  try {
    eq.getRight();
    cout << "Should thrown exception, did not" << endl;
  } catch (range_error &err) {
    cout << "Caught error with message " << err.what() << endl;
  } catch (...) {
    cout << "Caught some other exception" << endl;
  }

  cout << endl << endl << "Done testing exceptions" << endl << endl;
#endif // TEST_DEQUEUE_EXCEPTS

// testing adding to full queue
#ifdef TEST_DEQUEUE_GROW
  cout << "Now testing adding to a full array" << endl << endl;

  Dequeue fq(DEF_SIZE);
  cout << "Testing overflow when adding to the left" << endl;
  cout << "Adding first ten odd integers to left side of Dequeue " << endl;
  for (int i = 0; i < 10; i++)
    fq.addLeft(2 * i + 1);

  cout << " and removing three of them" << endl
       << " should be: 1  3  5 " << endl;
  cout << " they are:";
  for (int i = 0; i < 3; i++)
    cout << setw(3) << fq.getRight();
  cout << endl;

  cout << endl << "Now adding five more, should cause wrap with growth" << endl;
  for (int i = 10; i < 15; i++)
    fq.addLeft(2 * i + 1);

  cout << "when we remove the remaining values," << endl
       << " should be: 7  9 11 13 15 17 19 21 23 25 27 29 " << endl;
  cout << " they are:";
  while (!fq.isEmpty())
    cout << setw(3) << fq.getRight();
  cout << endl << endl;

  Dequeue gq(DEF_SIZE);
  cout << "Now testing overflow when adding to the right" << endl << endl;
  cout << "Adding first ten even integers to right side of Dequeue " << endl;
  for (int i = 0; i < 10; i++)
    gq.addRight(2 * i);

  cout << "First removing three of them" << endl
       << " should be: 0  2  4 " << endl;
  cout << " they are:";
  for (int i = 0; i < 3; i++)
    cout << setw(3) << gq.getLeft();
  cout << endl;

  cout << endl << "Now adding five more, should cause wrap with growth" << endl;
  for (int i = 10; i < 15; i++)
    gq.addRight(2 * i);

  cout << "when we remove the remaining values" << endl
       << " should be:  6  8 10 12 14 16 18 20 22 24 26 28 " << endl;
  cout << " they are: ";
  while (!gq.isEmpty())
    cout << setw(3) << gq.getLeft();
  cout << endl << endl;

  cout << endl << "Done testing adding to full dequeue" << endl << endl;
#endif // TEST_DEQUEUE_EXCEPTS

// testing list function
#ifdef TEST_LIST_DEQUEUE
  Dequeue cQ;
  cout << endl << "Now testing list function:" << endl << endl;
  cQ.addLeft(33);
  cQ.addRight(43);
  cQ.addLeft(34);
  cQ.addRight(47);
  ;
  cout << "listing left to right:" << endl
       << "  should be 34 33 43 47 " << endl;
  cout << "  really is " << cQ.listLeftRight();

  cout << endl << "End of testing list functions " << endl << endl;
#endif // TEST_LIST_DEQUEUE

// testing stack using dequeue
#ifdef TEST_STACK
  cout << endl << "Now testing Stack based on Dequeue" << endl << endl;
  Stack aStack(DEF_SIZE);

  cout << "Pushing 6 followed by 7" << endl;
  aStack.push(6);
  aStack.push(7);

  cout << " first peek, sb 7 = " << aStack.peek() << endl;
  cout << " next  pop,  sb 7 = " << aStack.pop() << endl;
  cout << " final pop,  sb 6 = " << aStack.pop() << endl;

  cout << endl << "Now testing exception on empty stack" << endl;
  try {
    aStack.pop();
    cout << "Should thrown exception, did not" << endl;
  } catch (range_error &err) {
    cout << "Caught error with message " << err.what() << endl;
  } catch (...) {
    cout << "Caught some other exception" << endl;
  }

  cout << endl << "End of testing Stack" << endl;
#endif // TEST_STACK

  return 0;
}
