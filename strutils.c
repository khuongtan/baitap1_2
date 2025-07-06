#include <stdio.h>
#include <string.h>
#include <ctype.h>  // Required for isspace(), toupper(), tolower(), and isdigit()
#include <stdlib.h> // Required for malloc and free

char* strReverse(char* originalStr) {
    int length = strlen(originalStr);
    // Allocate memory for the new reversed string
    // +1 for the null terminator
    char* reversedStr = (char*)malloc(sizeof(char) * (length + 1));

    // Check if memory allocation was successful
    if (reversedStr == NULL) {
        perror("Memory allocation failed");
        return NULL; // Return NULL to indicate an error
    }

    // Populate the reversed string
    for (int i = 0; i < length; i++) {
        reversedStr[i] = originalStr[length - 1 - i];
    }
    reversedStr[length] = '\0'; // Null-terminate the new string

    return reversedStr; // Return the pointer to the new string
}

char* strTrim(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t length = strlen(str);
    if (length == 0) {
        return NULL; // Empty string, nothing to trim
    }

    // Trim leading whitespace
    int start = 0;
    while (start < length && isspace((unsigned char)str[start])) {
        start++;
    }

    // Trim trailing whitespace
    int end = length - 1;
    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }

    // Shift characters to the beginning
    int i;
    for (i = 0; i <= (end - start); i++) {
        str[i] = str[start + i];
    }
    str[i] = '\0'; // Null-terminate the new string

    return str;
}
