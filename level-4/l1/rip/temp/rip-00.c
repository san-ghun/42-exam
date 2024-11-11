#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This program finds valid balanced parentheses by removing invalid ones.
 * A valid parentheses string has:
 * 1. Equal number of opening and closing parentheses
 * 2. At any point, number of closing parentheses doesn't exceed opening ones
 */

// Helper function to check if a parentheses string is valid
int is_valid_parentheses(const char *str) {
    int count = 0;  // Keep track of balance: +1 for '(', -1 for ')'
    
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(') {
            count++;
        } else if (str[i] == ')') {
            count--;
        }
        // If count becomes negative, we have more ')' than '(' at this point
        if (count < 0) {
            return 0;  // Invalid
        }
    }
    // Valid only if we have equal number of '(' and ')'
    return count == 0;
}

// Function to remove a character at given index from string
void remove_char(char *str, int index) {
    while (str[index]) {
        str[index] = str[index + 1];
        index++;
    }
}

// Main function to solve the parentheses problem
void solve_parentheses(char *str) {
    int len = strlen(str);
    char *working_str = strdup(str);  // Create a working copy
    
    // Try removing each character one by one
    for (int i = 0; i < len; i++) {
        if (working_str[i] != '(' && working_str[i] != ')') {
            continue;  // Skip non-parentheses characters
        }
        
        // Make a temporary string without current character
        char *temp = strdup(working_str);
        remove_char(temp, i);
        
        // If valid combination found, print it
        if (is_valid_parentheses(temp)) {
            printf("Valid combination: %s\n", temp);
        }
        
        free(temp);
    }
    
    free(working_str);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"parentheses_string\"\n", argv[0]);
        printf("Example: %s \"(())\"\n", argv[0]);
        return 1;
    }
    
    // First check if input is already valid
    if (is_valid_parentheses(argv[1])) {
        printf("Input is already valid: %s\n", argv[1]);
        return 0;
    }
    
    printf("Finding valid combinations for: %s\n", argv[1]);
    solve_parentheses(argv[1]);
    
    return 0;
}
