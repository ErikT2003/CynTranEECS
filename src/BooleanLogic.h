#ifndef BOOLEANLOGIC_H
#define BOOLEANLOGIC_H

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class BooleanLogic {
  public:
    bool parenthese_error_check(string expr);
    bool unknown_var_error_check(char var);
    bool evaluateBoolean(char op, bool operand1, bool operand2);
    bool evaluateExpression(string expr);
};

#endif 