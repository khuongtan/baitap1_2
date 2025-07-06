#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Required for malloc and free
#include <ctype.h>  // Required for isspace(), toupper(), tolower(), and isdigit()



char* strAllUpper(char *str) {
    if (str == NULL) {
        return NULL; // Handle null input string
    }

    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }
    return str; // Return the pointer to the modified string
}

char* strAllLower(char *str) {
    if (str == NULL) {
        return NULL; // Handle null input string
    }

    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
    return str; // Return the pointer to the modified string
}

char* strFirstLetterUpper(char *str) {
    if (str == NULL) {
        return NULL;
    }

    int newWord = 1; // Flag to indicate if the next character is the start of a new word

    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace((unsigned char)str[i])) {
            newWord = 1; // Current character is whitespace, so next non-whitespace is a new word
        } else if (newWord) {
            str[i] = (char)toupper((unsigned char)str[i]); // Capitalize the first letter of the word
            newWord = 0; // Reset flag, as we are now inside a word
        }
        // If newWord is 0 and it's not a space, do nothing (keep current case)
    }
    return str; // Return the pointer to the modified string
}

char* strTrimNumber(char *str) {
    if (str == NULL) {
        return NULL;
    }

    int src_idx = 0; // Index for reading from the original string
    int dest_idx = 0; // Index for writing to the modified string

    while (str[src_idx] != '\0') {
        if (!isdigit((unsigned char)str[src_idx])) {
            // If the character is NOT a digit, copy it to the current destination position
            str[dest_idx] = str[src_idx];
            dest_idx++; // Move destination index forward
        }
        src_idx++; // Always move source index forward
    }
    str[dest_idx] = '\0'; // Null-terminate the modified string

    return str; // Return the pointer to the modified string
}
