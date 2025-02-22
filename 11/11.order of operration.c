#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Function to evaluate the expression inside parentheses
double evaluateExpression(char* expr);

// Function to perform the operation with two operands
double performOperation(double left, double right, char operator) {
    switch (operator) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        case '^': return pow(left, right); // Exponentiation
        default: return 0;
    }
}

// Function to evaluate a mathematical expression based on PEMDAS
double evaluate(char* expr) {
    int length = strlen(expr);
    double result = 0;
    char operator = '+';
    double currentOperand = 0;
    double operands[100]; // Stack for operands
    int operandIndex = 0;

    for (int i = 0; i < length; i++) {
        char c = expr[i];

        if (isdigit(c)) {
            currentOperand = currentOperand * 10 + (c - '0'); // Construct the current number

        } else if (c == '(') {
            // Handle parentheses: Evaluate the expression inside the parentheses
            int parenthesesCount = 1;
            int startIndex = i + 1;
            while (parenthesesCount > 0) {
                i++;
                if (expr[i] == '(') parenthesesCount++;
                else if (expr[i] == ')') parenthesesCount--;
            }
            char subExpression[i - startIndex + 1];
            strncpy(subExpression, expr + startIndex, i - startIndex);
            subExpression[i - startIndex] = '\0';

            currentOperand = evaluate(subExpression); // Evaluate the sub-expression in parentheses
        }

        if ((c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || i == length - 1) && !isspace(c)) {
            // Once we encounter an operator or reach the end, process the current number

            if (operator == '+' || operator == '-') {
                operands[operandIndex++] = currentOperand * (operator == '+' ? 1 : -1);
            } else if (operator == '*' || operator == '/') {
                double prevOperand = operands[operandIndex - 1];
                operands[operandIndex - 1] = performOperation(prevOperand, currentOperand, operator);
            } else if (operator == '^') {
                double prevOperand = operands[operandIndex - 1];
                operands[operandIndex - 1] = performOperation(prevOperand, currentOperand, operator);
            }

            // Reset the operator and current operand
            operator = c;
            currentOperand = 0;
        }
    }

    // Sum up all the operands (first addition/subtraction pass)
    double finalResult = 0;
    for (int i = 0; i < operandIndex; i++) {
        finalResult += operands[i];
    }

    return finalResult;
}

int main() {
    char expression[100];

    printf("Enter a mathematical expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;  // Remove the trailing newline character

    double result = evaluate(expression);
    printf("Result: %.2lf\n", result);

    return 0;
}
