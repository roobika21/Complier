#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 100  // Maximum length for the identifier

// Function to check if the identifier is valid
int is_valid_identifier(char *identifier) {
    // The identifier must not be empty
    if (identifier[0] == '\0') {
        return 0;
    }

    // Check if the first character is a letter or underscore
    if (!isalpha(identifier[0]) && identifier[0] != '_') {
        return 0;
    }

    // Check if all subsequent characters are letters, digits, or underscores
    for (int i = 1; identifier[i] != '\0'; i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '_') {
            return 0;
        }
    }

    // The identifier is valid
    return 1;
}

int main() {
    char identifier[MAX_LENGTH];

    // Taking input from the user
    printf("Enter the identifier to validate: ");
    fgets(identifier, MAX_LENGTH, stdin);

    // Remove newline character if present (fgets includes it)
    identifier[strcspn(identifier, "\n")] = '\0';

    // Check the validity of the identifier
    if (is_valid_identifier(identifier)) {
        printf("'%s' is a valid identifier.\n", identifier);
    } else {
        printf("'%s' is not a valid identifier.\n", identifier);
    }

    return 0;
}
