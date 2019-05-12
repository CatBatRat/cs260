//
//  main.cpp
//  CS260Lab5
//
//  Created by Jim Bailey on 5/3/18.
//  Copyright © 2018 Jim Bailey. All rights reserved.
//

#include "ParseTree.h"
#include <iostream>

//

// optional extension to lab
//#define PARSE_IN_ORDER

//int main(int argc, const char *argv[]) {
int main() {

  std::cout << "Testing Parse Tree" << std::endl << std::endl;

  std::string expression1 = "AB+CD-*";
  std::string expression2 = "AB-C+DE/*";

  ParseTree ptree1(expression1);
  std::cout << "Input is AB+CD-* " << std::endl;
  std::cout
      << "In Order should be ((A+B)*(C-D)) or (((A)+(B))*((C)-(D))) and is "
      << ptree1.inOrder() << std::endl;
  std::cout << "Post Order should be AB+CD-* and is " << ptree1.postOrder()
            << std::endl;
  std::cout << "Pre Order should be *+AB-CD and is " << ptree1.preOrder()
            << std::endl
            << std::endl;

  ParseTree ptree2(expression2);
  std::cout << "Input is AB-C+DE/* " << std::endl;
  std::cout << "In Order output should be (((A-B)+C)*(D/E)) or "
               "((((A)-(B))+(C))*((D)/(E))) and is"
            << ptree2.inOrder() << std::endl;
  std::cout << "Post Order should be AB-C+DE/* and is " << ptree2.postOrder()
            << std::endl;
  std::cout << "Pre Order should be *+-ABC/DE and is " << ptree2.preOrder()
            << std::endl;

  std::cout << "Done with Parse Tree test" << std::endl << std::endl;

#ifdef PARSE_IN_ORDER
  std::cout << "Testing In Order Parse Tree" << std::endl << std::endl;

  std::string expression3 = "(A+B)*C+D";
  ParseTree ptree3("");

  ptree3.parseInOrder(expression3);
  std::cout << "Input is (A+B)*C+D" << std::endl;
  std::cout
      << "In Order should be (((A+B)*C)+D) or ((((A)+(B))*(C))+(D)) and is "
      << ptree3.inOrder() << std::endl
      << std::endl;
  std::cout << "Post Order should be AB+C*D+ and is " << ptree3.postOrder()
            << std::endl;
  std::cout << "Pre Order should be +*+ABCD and is " << ptree3.preOrder()
            << std::endl
            << std::endl;

#endif

  return 0;
}
