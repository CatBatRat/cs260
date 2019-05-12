//
//  main.cpp
//  Parser
//
//  Created by Jim Bailey on 5/1/18.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include <iostream>

#include "Parser.hpp"

int main()
{

    std::string expression1 = "AB+CD-*";
    std::cout << "Converting " << expression1 << std::endl;
    std::cout << " result is " << Parser::postFix_to_inFix(expression1) << std::endl
              << std::endl;

    std::string expression2 = "(A+B)*(C+D)";
    std::cout << "Converting " << expression2 << std::endl;
    std::cout << " result is " << Parser::inFix_to_postFix(expression2) << std::endl
              << std::endl;

    std::string expression3 = "(A+B)*(C+D)/(E-F-G)";
    std::cout << "Converting " << expression3 << std::endl;
    std::cout << " result is " << Parser::inFix_to_postFix(expression3) << std::endl
              << std::endl;

    return 0;
}
