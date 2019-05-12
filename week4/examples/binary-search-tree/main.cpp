//
//  main.cpp
//  binary_search_tree
//
//  Created by Jim Bailey on 11/1/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include "Tree.h"
#include <iostream>

using namespace std;

int main() {
  Tree fir;

  // build a nice noble fir that is balanced
  fir.addNode(20);
  fir.addNode(30);
  fir.addNode(25);
  fir.addNode(35);
  fir.addNode(10);
  fir.addNode(15);
  fir.addNode(5);
  fir.addNode(2);
  fir.addNode(7);
  fir.addNode(12);
  fir.addNode(17);
  fir.addNode(22);
  fir.addNode(27);
  fir.addNode(32);
  fir.addNode(37);

  // do normal traversals
  cout << fir.inOrder() << endl;
  cout << fir.postOrder() << endl;
  cout << fir.preOrder() << endl;

  // check find
  cout << "Looking for 10 " << (fir.find(10) ? "found" : "not found") << endl;
  cout << "Looking for 11 " << (fir.find(11) ? "found" : "not found") << endl;

  // check display
  cout << "Starting tree" << endl;
  cout << fir.displayTree() << endl << endl;

  // delete 10 and see if still there
  fir.deleteMark(10);
  cout << "Looking for 10 " << (fir.find(10) ? "found" : "not found") << endl;
  cout << "Tree with 10 marked as removed " << endl;
  cout << fir.displayTree() << endl << endl;

  // add 10 back
  fir.addNode(10);
  cout << "Tree with 10 added back" << endl;
  cout << fir.displayTree() << endl << endl;

  // check delete move
  fir.deleteRemove(10);
  cout << "Tree with 10 removed " << endl;
  cout << fir.displayTree() << endl;

  fir.deleteRemove(20);
  cout << "Tree with 20 removed " << endl;
  cout << fir.displayTree() << endl;
  return 0;
}
