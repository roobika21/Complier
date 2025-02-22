#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    int i = 0, j = 0, x = 0, n;
    void *p, *add[5];
    char ch, srch, b[15], d[15], c;

    printf("Expression terminated by $: ");
    while ((c = getchar()) != '$') {
        b[i] = c;
        i++;
    }
    b[i] = '\0';  // Null-terminate the string
    n = i - 1;

    printf("Given Expression: ");
    for (i = 0; i <= n; i++) {
        printf("%c", b[i]);
    }

    printf("\nSymbol Table\n");
    printf("Symbol\tAddress\t\tType\n");

    while (j <= n) {
        c = b[j];

        if (isalpha(c)) {  // Check if character is an identifier
            p = malloc(sizeof(char));  // Allocate memory correctly
            if (!p) {
                printf("Memory allocation failed\n");
                return 1;
            }
            add[x] = p;
            d[x] = c;
            printf("%c\t%p\tIdentifier\n", c, p);
            x++;
            j++;
        } else {  // Check if character is an operator
            ch = c;
            if (ch == '+' || ch == '-' || ch == '*' || ch == '=') {
                p = malloc(sizeof(char));  // Correct memory allocation
                if (!p) {
                    printf("Memory allocation failed\n");
                    return 1;
                }
                add[x] = p;
                d[x] = ch;
                printf("%c\t%p\tOperator\n", ch, p);
                x++;
                j++;
            }
        }
    }

    // Free allocated memory
    for (i = 0; i < x; i++) {
        free(add[i]);
    }

    return 0;
}
