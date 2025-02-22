#include <stdio.h>
#include <string.h>

int main() {
    char input[100], l[10], r[100], temp[50], productions[25][50];
    int i = 0, j = 0, flag = 0, consumed = 0;

    printf("Enter the production (e.g., A->Aa|b): ");
    scanf("%[^->]->%s", l, r);

    while (sscanf(r + consumed, "%[^|]", temp) == 1) {
        if (temp[0] == l[0]) {  // Left recursion detected
            flag = 1;
            sprintf(productions[i++], "%s'->%s%s'", l, temp + 1, l);
        } else {
            sprintf(productions[i++], "%s->%s%s'", l, temp, l);
        }
        consumed += strlen(temp) + 1;
        if (consumed >= strlen(r)) break;
    }

    if (flag == 1) {
        sprintf(productions[i++], "%s'->e", l);
        printf("The productions after eliminating left recursion are:\n");
        for (j = 0; j < i; j++) {
            printf("%s\n", productions[j]);
        }
    } else {
        printf("The given grammar has no left recursion.\n");
    }

    return 0;
}