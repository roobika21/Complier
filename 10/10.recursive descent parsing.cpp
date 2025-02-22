#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char lookahead; // Lookahead symbol

// Forward declaration of functions
void expr();
void term();
void factor();

void error() {
    printf("Syntax error\n");
    exit(1);
}

// Function to get the next character
void getNextChar() {
    lookahead = getchar();
}

// Function to match the expected character
void match(char expected) {
    if (lookahead == expected) {
        getNextChar();
    } else {
        error();
    }
}

// Factor -> ( expr ) | number
void factor() {
    if (isdigit(lookahead)) {
        // If it's a number, consume the character
        while (isdigit(lookahead)) {
            getNextChar();
        }
    } else if (lookahead == '(') {
        // If it's '(', expect an expression, then match ')'
        match('(');
        expr();  // Calls expr() here, which is now declared earlier
        match(')');
    } else {
        error();
    }
}

// Term -> factor | term * factor
void term() {
    factor();
    while (lookahead == '*') {
        match('*');
        factor();
    }
}

// Expr -> term | expr + term
void expr() {
    term();
    while (lookahead == '+') {
        match('+');
        term();
    }
}

int main() {
    getNextChar(); // Get the first character
    expr();        // Start parsing the expression

    if (lookahead == '\n' || lookahead == EOF) {
        printf("Parsing successful\n");
    } else {
        error();
    }

    return 0;
}
