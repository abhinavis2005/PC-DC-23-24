// Hari Hara Naveen
// Vaishnavi Rajesh
// Abhinav I S
// takes arthematic expression and solves it

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>

#include <optional>
#include <stack>
#include <string>

bool is_digit(char i) { return '0' <= i && i <= '9'; }
bool is_white_space(char i) { return i == ' '; }
int divbyzero=0;

int precedence(char i) {
  // assigns numbers or 'priorities' to operations based on which they are
  // compared
  if (i=='/' || i=='*'){
      return 2;
  }
  else if (i=='+' || i=='-'){
      return 1;
  }
  else{
      return 0;
  }
}

int apply_operator(int operand1, int operand2, char arthOperator) {
  // returns operand2-arthOperator-operand1 value
  int val;
  if (arthOperator=='*'){
    val = operand2*operand1;
  }
  else if (arthOperator=='/'){
    if (operand1==0){
        divbyzero=1;
        std::cout<<"Division by zero" << std::endl;
        val = 0;
        //handle division by zero case
    }
    else{
        val = operand2/operand1;
    }
  }
  else if (arthOperator=='+'){
    val = operand2+operand1;
  }
  else if (arthOperator=='-'){
    val = operand2-operand1;
  }
  return val;  
}

void perform_one_operation(std::stack<int> &operandStack,
                           std::stack<char> &operatorStack) {
  // pop the first 2 elements off the operandStack and first element of
  // operatorStack apply operator on them and push the result into operandStack
  int operand1 = operandStack.top();
  operandStack.pop();
  int operand2 = operandStack.top();
  operandStack.pop();
  char Operator = operatorStack.top();
  operatorStack.pop();
  int val = apply_operator(operand1, operand2, Operator);
  operandStack.push(val);
}

int parse_arthematic_expression(std::string &&expression) {
  // parse the expression and return the result
  // add dummy char to the end of the string (for easier implementation,
  // optional) otherwise resolve the elements left on the stacks in the end

  std::stack<char> operatorStack;
  std::stack<int> operandStack;
  expression.append(1,'$');//dummy character
  // tokenize the elements of expression string.
  // ignore white spaces, write a function to construct number from digits
  // push number onto operandStack
  int n = expression.length();
  
  std::optional<std::string> number;//creating number from digits(string)
  for (int i=0; i < n; i++){
    const char token=expression[i];
    if (is_digit(token)){
        if (!number.has_value()){
            number = ""; 
        }
        number->append(1,token);
    }
    else if (!is_white_space(token)){
      if (number.has_value()){
        operandStack.push(std::stoi(*number));
        number.reset();
      }
      while(!operatorStack.empty()){
        if(precedence(token)<=precedence(operatorStack.top())){
            perform_one_operation(operandStack,operatorStack);
        }
        else{
            break;
        }
      } 
      operatorStack.push(token);
    }
    
  }

  // if token is an operation, check the top element of operatorStack and call
  // perform_one_operation if needed. Finally, push operator onto operatorStack

  return operandStack.top();
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    // reading arthematic expression
    divbyzero=0;
    int value = parse_arthematic_expression(std::move(line));
    // Print an error message for division by zero
    if (!divbyzero){
        std::cout << value << std::endl;
    }
  }
}
