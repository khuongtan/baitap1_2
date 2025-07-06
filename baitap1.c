#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Required for malloc and free
#include <ctype.h>  // Required for isspace(), toupper(), tolower(), and isdigit()
#include "strutils.h"
#include "strutils_adv.h"

/* =============== Main function for user interface =========================================================================*/
int main() {
    char original_input[100]; // Buffer to store the user's input string
    char choice;

    printf("Please enter a string (max 99 characters): ");
    if (fgets(original_input, sizeof(original_input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove the trailing newline character that fgets might include
    original_input[strcspn(original_input, "\n")] = '\0';

    printf("You entered: \"%s\"\n", original_input);

ModifyAgain:
    printf("\nWhat would you like to do with this string?\n");
    printf("Press 'R' to Reverse the string\n");
    printf("Press 'T' to Trim leading/trailing whitespace\n");
    printf("Press 'U' to convert to ALL UPPERCASE\n");
    printf("Press 'L' to convert to ALL lowercase\n");
    printf("Press 'F' to capitalize First Letter of Each Word\n");
    printf("Press 'N' to Trim all Numbers\n");
    printf("Press 'E' to exit\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    if (choice == 'R' || choice == 'r') {
        char* reversed = strReverse(original_input);

        if (reversed != NULL) {
            printf("Reversed string: \"%s\"\n", reversed);
            strcpy(original_input,reversed);   // copy lai de hanh dong tiep theo khong nhap lieu moi
            free(reversed);
        } else {
            printf("Error: Could not reverse string or memory allocation failed.\n");
        }
    } else if (choice == 'T' || choice == 't') {
        printf("Original string before trim: \"%s\"\n", original_input);
        strTrim(original_input);
        printf("String after trim: \"%s\"\n", original_input);
    } else if (choice == 'U' || choice == 'u') {
        printf("Original string before uppercase: \"%s\"\n", original_input);
        strAllUpper(original_input);
        printf("String after uppercase: \"%s\"\n", original_input);
    } else if (choice == 'L' || choice == 'l') {
        printf("Original string before lowercase: \"%s\"\n", original_input);
        strAllLower(original_input);
        printf("String after lowercase: \"%s\"\n", original_input);
    } else if (choice == 'F' || choice == 'f') {
        printf("Original string before capitalizing first letters: \"%s\"\n", original_input);
        strFirstLetterUpper(original_input);
        printf("String after capitalizing first letters: \"%s\"\n", original_input);
    } else if (choice == 'N' || choice == 'n') {
        printf("Original string before trimming numbers: \"%s\"\n", original_input);
        strTrimNumber(original_input);
        printf("String after trimming numbers: \"%s\"\n", original_input);
    }else if (choice == 'E' || choice == 'e') {
        printf("Thank you, Hen gap lai\n");
        return 0;
    }
    else {
        printf("Invalid choice. No action performed.\n");
    }

    printf("What to do next? Press 'C' to continue or any Key to exit:");
    scanf(" %c", &choice);

    if (choice == 'C' || choice == 'c') {
        goto ModifyAgain;
    }
    return 0;
}