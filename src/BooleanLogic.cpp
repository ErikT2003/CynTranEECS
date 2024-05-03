#include "BooleanLogic.h"
#include <iostream>
#include <string>
#include <stack>
#include <map>
using namespace std;
bool BooleanLogic::unknown_var_error_check(char var) {
  if (!(var == '(' || var == ')' || var == '&' || var == '|' || var == '!' || var == '@' || var == '$' || var == 'F' || var == 'T' || var == ' '))
  {
    cout << "Invalid Symbol: "<< var << endl;
    return false;
  }
  else 
  {
    return true;
  }
}

bool BooleanLogic::parenthese_error_check(string expr) {
  stack<char> temp; 
  for (int i = 0; i < expr.length(); i++) {
      if (!(unknown_var_error_check(expr[i]))) {
        cout << expr << " is invalid";
        exit(1);
      }
      else if (temp.empty() && !(expr[i] == '(' || expr[i] == ')')) {
          continue;
      }
      else if (temp.empty() && (expr[i] == '(' || expr[i] == ')')) {
        temp.push(expr[i]);
      }
      else if (temp.top() == '(' && expr[i] == ')') {
        temp.pop();
      }
      else if (expr[i] == '(' || expr[i] == ')'){
        temp.push(expr[i]);
      }
  }
  if (temp.empty()) {
    return true;
  }
  return false;
}

bool BooleanLogic::evaluateBoolean(char op, bool operand1, bool operand2) {
    switch (op) {
        case '&':
            return operand1 && operand2; // AND
        case '|':
            return operand1 || operand2; // OR
        case '!':
            return !operand1; // NOT
        case '$':
            return operand1 != operand2; // XOR
        case '@':
            return !(operand1 && operand2); // NAND
        default:
            return false;
    }
}

bool BooleanLogic::evaluateExpression(string expr) {
    stack<bool> values; // Stack to store values
    stack<char> ops; // Stacks to store operators
    map<char, int> precedence; //Map to store operator
    precedence['|'] = 1; // OR
    precedence['&'] = 2; // AND
    precedence['$'] = 3; // XOR
    precedence['!'] = 4; // NOT
    precedence['@'] = 5; // NAND

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (c == ' ') {
            continue; // Skip whitespace
        } else if (c == 'T') {
            values.push(true); // Push true onto the operand stack
        } else if (c == 'F') {
            values.push(false); // Push false onto the operand stack
        } else if (c == '(') {
            ops.push(c); // Push '(' onto the operator stack
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char op = ops.top();
                ops.pop();
                if (op == '!') {
                    // Handle unary operator
                    bool operand = values.top();
                    values.pop();
                    values.push(!operand); // Apply NOT operator
                } else {
                    // Handle binary operator
                    bool operand2 = values.top();
                    values.pop();
                    bool operand1 = values.top();
                    values.pop();
                    values.push(evaluateBoolean(op, operand1, operand2)); // Evaluate binary operator
                }
            }
            ops.pop(); // Pop '('
        } else if (c == '&' || c == '|' || c == '!' || c == '$' || c == '@') {
            while (!ops.empty() && precedence[c] <= precedence[ops.top()] && ops.top() != '(') {
                char op = ops.top();
                ops.pop();
                if (op == '!') {
                    // Handle unary operator
                    bool operand = values.top();
                    values.pop();
                    values.push(!operand); // Apply NOT operator
                } else {
                    // Handle binary operator
                    bool operand2 = values.top();
                    values.pop();
                    bool operand1 = values.top();
                    values.pop();
                    values.push(evaluateBoolean(op, operand1, operand2)); // Evaluate binary operator
                }
            }
            ops.push(c); // Push current operator onto operator stack
        }
    }

    // Evaluate remaining operators
    while (!ops.empty()) {
        char op = ops.top();
        ops.pop();
        if (op == '!') {
            // Handle unary operator
            bool operand = values.top();
            values.pop();
            values.push(!operand); // Apply NOT operator
        } else {
            // Handle binary operator
            bool operand2 = values.top();
            values.pop();
            bool operand1 = values.top();
            values.pop();
            values.push(evaluateBoolean(op, operand1, operand2)); // Evaluate binary operator
        }
    }

    return values.top(); // Result of expression evaluation
}


int main()
{
  BooleanLogic myObj;
  std:: string expr;
  std::cout <<"Enter a boolean expression: ";
  std::getline(std::cin, expr);

  if (myObj.parenthese_error_check(expr)) {
      if (myObj.evaluateExpression(expr)) {
          cout << "Expression evaluates to true." << endl;
      } else {
          cout << "Expression evaluates to false." << endl;
      }
  } else {
      cout << "Unbalanced parentheses error." << endl;
  }
  return 0;
}