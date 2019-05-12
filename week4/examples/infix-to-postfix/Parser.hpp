//
//  Parser.hpp
//  Parser
//
//  Created by Jim Bailey on 5/1/18.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <string>

class Parser {
public:
    static std::string postFix_to_inFix(std::string postFix);
    static std::string inFix_to_postFix(std::string inFix);
    
private:
    static bool isOperator(char value);
    static bool isOperand(char value);
    static bool higherPrec(char oper1, char oper2);
    static int getPrec(char oper);
    
    static const char LPAREN = '(';
    static const char RPAREN = ')';
    static const char PLUS = '+';
    static const char MINUS = '-';
    static const char MULT = '*';
    static const char DIV = '/';
    static const char SPACE = ' ';
};

#endif /* Parser_hpp */
