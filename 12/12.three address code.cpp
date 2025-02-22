#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Struct to represent a temporary variable
typedef struct {
    char name[5];
    int temp_no;
} TempVar;

// Function to generate temporary variables
TempVar generate_temp(int temp_count) {
    TempVar temp;
    temp.temp_no = temp_count;
    sprintf(temp.name, "t%d", temp_count);
    return temp;
}

// Function to generate Three Address Code (TAC)
void generate_TAC(char* expr) {
    int i, temp_count = 0;
    char stack[MAX][MAX];
    int top = -1;
    
    // Iterate through the expression to generate TAC
    for (i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) {
            continue;
        }

        if (isdigit(expr[i])) {
            // If the character is a digit, push it onto the stack
            char num[2] = {expr[i], '\0'};
            strcpy(stack[++top], num);
        } 
        else if (isalpha(expr[i])) {
            // If the character is a variable, push it onto the stack
            char var[2] = {expr[i], '\0'};
            strcpy(stack[++top], var);
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            // Operator encountered, pop two operands from the stack and generate a temporary variable
            char operand2[MAX], operand1[MAX];
            strcpy(operand2, stack[top--]);
            strcpy(operand1, stack[top--]);

            TempVar temp = generate_temp(temp_count++);

            // Generate TAC for the operation
            printf("%s = %s %c %s\n", temp.name, operand1, expr[i], operand2);

            // Push the result (temporary variable) back onto the stack
            strcpy(stack[++top], temp.name);
        }
    }
}

int main() {
    char expression[MAX];
    
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    
    // Remove newline character from input
    expression[strcspn(expression, "\n")] = '\0';
    
    printf("\nGenerated Three Address Code (TAC):\n");
    generate_TAC(expression);

    return 0;
}
