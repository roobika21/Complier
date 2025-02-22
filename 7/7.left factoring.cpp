#include <stdio.h>
#include <string.h>

int main() {
    char gram[100], lhs[10], rhs[100], part1[50], part2[50];
    char modifiedGram[50], newGram[50];
    int i, j = 0, k = 0, pos = 0;

    printf("Enter Production (e.g., A->abcde|abxyz): ");
    fgets(gram, sizeof(gram), stdin);
    gram[strcspn(gram, "\n")] = 0; 

    
    sscanf(gram, "%9[^->]->%99s", lhs, rhs);

    
    for (i = 0; rhs[i] != '|' && rhs[i] != '\0'; i++)
        part1[i] = rhs[i];
    part1[i] = '\0';

    if (rhs[i] == '|')
        strcpy(part2, rhs + i + 1);
    else
        part2[0] = '\0';

    
    for (i = 0; part1[i] && part2[i]; i++) {
        if (part1[i] == part2[i]) {
            modifiedGram[k++] = part1[i];
            pos = i + 1;
        } else {
            break;
        }
    }
    modifiedGram[k] = '\0'; 

    if (k == 0) {
        printf("No common prefix found. No left factoring needed.\n");
        return 0;
    }

   
    sprintf(modifiedGram + k, "%s'", lhs);  
    k += strlen(lhs) + 1;

    j = 0;
    if (pos < strlen(part1)) {
        sprintf(newGram, "%s'->%s", lhs, part1 + pos);
        j = strlen(newGram);
    }
    if (pos < strlen(part2)) {
        if (j > 0) newGram[j++] = '|';  
        sprintf(newGram + j, "%s", part2 + pos);
    }

   
    printf("\n%s->%s\n", lhs, modifiedGram);
    printf("%s\n", newGram);

    return 0;
}
