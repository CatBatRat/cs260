//
//  Parser.cpp
//  Parser
//
//  Created by Jim Bailey on 5/1/18.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include "Parser.hpp"
#include <stack>

/*
 * helper function
 *    return true for operators
 *    false otherwise
 */
bool Parser::isOperator(char value) {
  switch (value) {
  case PLUS:
  case MINUS:
  case MULT:
  case DIV:
    return true;
  default:
    return false;
  }
}

/*
 * helper function
 *    return true for operands
 *    false otherwise
 */
bool Parser::isOperand(char value) { return isalnum(value); }

/*
 * helper function
 *
 * return true if operator1 higher precedence than operator2
 *
 */
bool Parser::higherPrec(char oper1, char oper2) {
  return getPrec(oper1) > getPrec(oper2);
}

/*
 * helper function for higherPrec
 *
 * return weight of operator
 */
int Parser::getPrec(char oper) {
  int prec = -1;
  switch (oper) {
  case PLUS:
  case MINUS:
    prec = 1;
  case MULT:
  case DIV:
    prec = 2;
  }
  return prec;
}

/*
 * This function takes a postfix expression and returns
 * an infix equivalent.
 *
 * input string should have single letters operands
 * allowed operators are +, -, *, /
 *
 * Algorithm:
 *  Operand -- push on stack
 *  Operator -- Create string (left_hand_side operator right_hand_side) and push
 * on stack End of input, pop and return
 */
std::string Parser::postFix_to_inFix(std::string postFix) {
  std::stack<std::string> theStack;

  for (unsigned int i = 0; i < postFix.length(); i++) {
    char next = postFix[i];
    if (isOperand(next)) {
      std::string buffer = "";
      buffer += next;
      theStack.push(buffer);
    } else if (isOperator(next)) {
      std::string rightHandSide = theStack.top();
      theStack.pop();
      std::string leftHandSide = theStack.top();
      theStack.pop();
      std::string buffer = "";
      buffer += LPAREN;
      buffer += leftHandSide;
      buffer += next;
      buffer += rightHandSide;
      buffer += RPAREN;
      theStack.push(buffer);
    }
    // ignore invalid data
  }
  return theStack.top();
}

/*
 * This function takes an infix expression and returns
 * a postfix equivalent.
 *
 * input string should have single letters operands
 * allowed operators are +, -, *, /
 * parens are used for disambiguity
 *
 * Algorithm:
 *  Operand -- output
 *  L Paren -- push on stack
 *  R Paren -- pop and output result until L Paren
 *  operator
 *       while stack not empty
 *           pop
 *              if L Paren, push
 *              if operator with higher precedence, push back
 *              if operator with lower precedence, output
 *       push operator
 *
 *  End of input, pop any remaining items and return result
 */
std::string Parser::inFix_to_postFix(std::string inFix) {
  std::stack<char> theStack;
  std::string buffer = "";

  for (unsigned int i = 0; i < inFix.length(); i++) {
    char next = inFix[i];

    // skip over white space
    if (next == SPACE) {
      continue;
    }
    // output all operands
    else if (isOperand(next)) {
      buffer += next;
    }
    // push opening parens
    else if (next == LPAREN) {
      theStack.push(next);
    }
    // closing paren
    // pop and output until matching opening paren
    else if (next == RPAREN) {
      while (!theStack.empty()) {
        char value = theStack.top();
        theStack.pop();
        if (value == LPAREN) {
          break;
        } else {
          buffer += value;
        }
      }
    }
    // operator
    // pop and output anything on stack
    //   until opening paren or higher precedence
    // push this one on stack
    else if (isOperator(next)) {
      while (!theStack.empty()) {
        char value = theStack.top();
        theStack.pop();
        if (value == LPAREN) {
          theStack.push(value);
          break;
        } else {
          if (higherPrec(value, next)) {
            theStack.push(value);
            break;
          } else {
            buffer += value;
          }
        }
      }
      theStack.push(next);
    }
  }

  // get any remaining operators on stack
  while (!theStack.empty()) {
    buffer += theStack.top();
    theStack.pop();
  }

  // return the result
  return buffer;
}
