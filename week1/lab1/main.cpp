//
//  main.cpp
//  TheArray
//
//  Created by Jim Bailey on 4/1/18.
//  Licensed under Creative Commons Attribution 4.0 International License.
//

#include "TheArray.hpp"
#include <iomanip>
#include <iostream>
#include <stdexcept>

#define TEST_CONSTRUCTOR
#define TEST_SET_GET
#define TEST_APPEND
#define TEST_MAKE_ROOM
#define TEST_INSERT_REMOVE

// Compiler complained about unused variables.
// int main(int argc, const char * argv[]) {
int main() {
#ifdef TEST_CONSTRUCTOR
  const int DEFAULT = 10;
  const int OVERLOAD = 15;
  std::cout << "Testing default and overloaded constructors." << std::endl;

  TheArray<int> defaultSize;
  TheArray<int> defineSize(OVERLOAD);

  std::cout << "Default size should be " << DEFAULT << " and is "
            << defaultSize.getSize() << std::endl;
  std::cout << "Overload size should be " << OVERLOAD << " and is "
            << defineSize.getSize() << std::endl;
  std::cout << std::endl << std::endl;
#endif // TEST_CONSTRUCTOR

#ifdef TEST_SET_GET
  std::cout << "Testing setting values and reading them back" << std::endl
            << std::endl;

  TheArray<int> setGet(7);
  std::cout << "Testing invalid setAt index of -1" << std::endl;
  try {
    setGet.setAt(-1, 12);
    std::cout << "Should have thrown an exception" << std::endl;
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << std::endl;
  } catch (...) {
    std::cout << "Caught something weird " << std::endl;
  }

  std::cout << std::endl
            << "Now loading some values and displaying them" << std::endl;
  setGet.setAt(0, 3);
  setGet.setAt(2, 7);
  setGet.setAt(1, 5);
  setGet.setAt(4, 13);
  setGet.setAt(3, 11);
  setGet.setAt(5, 17);

  std::cout << "The values should be:  3, 5, 7, 11, 13, 17, unknown value"
            << std::endl;
  std::cout << "The values really are: ";
  for (int i = 0; i < 6; i++)
    std::cout << setGet.getAt(i) << ", ";
  std::cout << setGet.getAt(6) << std::endl;

  std::cout << std::endl
            << "Testing invalid getAt index that is larger than array size"
            << std::endl;
  try {
    setGet.getAt(7);
    std::cout << "Should have thrown an exception" << std::endl;
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << std::endl;
  } catch (...) {
    std::cout << "Caught something weird " << std::endl;
  }
  std::cout << std::endl << std::endl;
#endif // TEST_SET_GET

#ifdef TEST_APPEND
  std::cout << "Testing append with mix of appends and sets" << std::endl
            << std::endl;

  TheArray<int> appends;

  appends.append(2);
  appends.append(4);
  appends.setAt(3, 16);
  appends.append(32);

  std::cout << "The array should be: 2, 4, unknown, 16, 32" << std::endl;
  std::cout << "The array really is: ";
  for (int i = 0; i < 4; i++)
    std::cout << appends.getAt(i) << ", ";
  std::cout << appends.getAt(4) << std::endl;

  std::cout << std::endl << std::endl;
#endif // TEST_APPEND

#ifdef TEST_MAKE_ROOM
  const int START = 7;
  const int UPDATE = 12;
  std::cout << "Testing setSize and auto expansion on appends" << std::endl
            << std::endl;

  TheArray<int> room(START);
  std::cout << "Starting size should be " << START << " and is "
            << room.getSize() << std::endl;
  room.setSize(UPDATE);
  std::cout << "After setSize, size should be " << UPDATE << " and is "
            << room.getSize() << std::endl;
  std::cout << std::endl
            << "Get at 8 should succeed, get at 12 should fail " << std::endl;
  try {
    room.getAt(8);
    std::cout << "Get at 8 succeeded" << std::endl;
  } catch (...) {
    std::cout << "Get at 8 failed" << std::endl;
  }
  try {
    room.getAt(12);
    std::cout << "Get at 12 succeeded" << std::endl;
  } catch (...) {
    std::cout << "Get at 12 failed" << std::endl;
  }

  std::cout << std::endl
            << "Now going to fill array and see if expands" << std::endl;
  for (int i = 0; i < UPDATE; i++)
    room.append(2 * i + 1);
  std::cout << "Filled with 12 values, no problem" << std::endl;
  std::cout << "Size should still be " << UPDATE << " and is " << room.getSize()
            << std::endl;
  std::cout << std::endl << "Adding one more" << std::endl;
  room.append(25);
  std::cout << "Size should now be " << 2 * UPDATE << " and is "
            << room.getSize() << std::endl;

  std::cout << std::endl
            << "Displaying values, should be odd numbers 1 - 25" << std::endl;
  for (int i = 0; i <= UPDATE; i++)
    std::cout << room.getAt(i) << " ";

  std::cout << std::endl << std::endl;
#endif // TEST_MAKE_ROOM

#ifdef TEST_INSERT_REMOVE
  const int BEGIN = 10;
  std::cout << "Testing insert and remove " << std::endl << std::endl;

  TheArray<int> insertRemove;
  for (int i = 0; i < BEGIN; i++)
    insertRemove.append(2 * i);
  std::cout << "Array starting with: ";
  for (int i = 0; i < BEGIN; i++)
    std::cout << insertRemove.getAt(i) << " ";
  std::cout << std::endl
            << "Size should be " << BEGIN << " and is "
            << insertRemove.getSize() << std::endl;

  std::cout << std::endl
            << "Now inserting the numbers 5, 9, and 13" << std::endl;
  insertRemove.insertAt(7, 13);
  insertRemove.insertAt(5, 9);
  insertRemove.insertAt(3, 5);
  std::cout << "Size should be " << 2 * BEGIN << " and is "
            << insertRemove.getSize() << std::endl;
  std::cout << "The values should be:  0 2 4 5 6 8 9 10 12 13 14 16 18"
            << std::endl;
  std::cout << "The values really are: ";
  for (int i = 0; i < BEGIN + 3; i++)
    std::cout << insertRemove.getAt(i) << " ";

  std::cout << std::endl
            << std::endl
            << "Now trying to remove the values 12, 8, 0 -- removed:  ";
  std::cout << insertRemove.removeAt(8) << ", ";
  std::cout << insertRemove.removeAt(5) << ", ";
  std::cout << insertRemove.removeAt(0) << std::endl;

  std::cout << "The array should be: 2 4 5 6 9 10 13 14 16 18 " << std::endl;
  std::cout << "The array really is: ";
  for (int i = 0; i < BEGIN; i++)
    std::cout << insertRemove.getAt(i) << " ";

  std::cout << std::endl
            << std::endl
            << "Now testing illegal inserts and removes " << std::endl;
  std::cout << std::endl
            << "Testing invalid insertAt at index larger than array size"
            << std::endl;
  try {
    insertRemove.insertAt(BEGIN * 3, -1);
    std::cout << "Should have thrown an exception inserting at -1" << std::endl;
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << std::endl;
  } catch (...) {
    std::cout << "Caught something weird " << std::endl;
  }

  std::cout << std::endl
            << "Emptying the array, expecting: 2 4 5 6 9 10 13 14 16 18 ";
  std::cout << std::endl << "Actually removed the values  : ";
  for (int i = 0; i < BEGIN; i++)
    std::cout << insertRemove.removeAt(0) << " ";
  std::cout << std::endl;

  std::cout << std::endl << "Now testing removeAt on empty array" << std::endl;
  try {
    insertRemove.removeAt(0);
    std::cout << "Should have thrown an exception" << std::endl;
  } catch (std::out_of_range &ex) {
    std::cout << "Caught out of range with message: " << ex.what() << std::endl;
  } catch (...) {
    std::cout << "Caught something weird " << std::endl;
  }
  std::cout << std::endl << std::endl;

#endif // TEST_INSERT_REMOVE

  return 0;
}
