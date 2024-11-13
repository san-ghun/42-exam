#include <stdio.h>
#include <unistd.h>

#define MAX_LEN 1000
#define MAX_SOLUTIONS 100

void find_combinations(char *str, int pos, int open, int close, int remove_count, 
                      char solutions[MAX_SOLUTIONS][MAX_LEN], int *sol_count) {
    // Base case: reached end of string
    if (str[pos] == '\0') {
        if (open == close && *sol_count < MAX_SOLUTIONS) {
            // Valid solution found, add to solutions array if not already present
            int i;
            for (i = 0; i < *sol_count; i++) {
                if (strcmp(solutions[i], str) == 0)
                    return;
            }
            strcpy(solutions[*sol_count], str);
            (*sol_count)++;
        }
        return;
    }

    // Skip if it's already a space
    if (str[pos] == ' ') {
        find_combinations(str, pos + 1, open, close, remove_count, solutions, sol_count);
        return;
    }

    // Try keeping current character
    if (str[pos] == '(') {
        find_combinations(str, pos + 1, open + 1, close, remove_count, solutions, sol_count);
    } else if (str[pos] == ')') {
        if (open > close) {
            find_combinations(str, pos + 1, open, close + 1, remove_count, solutions, sol_count);
        }
    }

    // Try removing current character if we still can remove some
    if (remove_count > 0) {
        char temp = str[pos];
        str[pos] = ' ';
        find_combinations(str, pos + 1, open, close, remove_count - 1, solutions, sol_count);
        str[pos] = temp;
    }
}

int min_removals_needed(const char *str) {
    int open = 0;
    int balance = 0;
    int i;

    // First pass: count unmatched closing parentheses
    for (i = 0; str[i]; i++) {
        if (str[i] == '(')
            balance++;
        else if (str[i] == ')') {
            if (balance == 0)
                open++;
            else
                balance--;
        }
    }
    
    // Add remaining unmatched opening parentheses
    return open + balance;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(2, "Error: provide one argument\n", 27);
        return 1;
    }

    char input[MAX_LEN];
    char solutions[MAX_SOLUTIONS][MAX_LEN];
    int sol_count = 0;
    
    // Copy input and verify it contains only valid characters
    int i;
    for (i = 0; argv[1][i] && i < MAX_LEN - 1; i++) {
        if (argv[1][i] != '(' && argv[1][i] != ')') {
            write(2, "Error: invalid character in input\n", 32);
            return 1;
        }
        input[i] = argv[1][i];
    }
    input[i] = '\0';

    // Find minimum number of removals needed
    int min_remove = min_removals_needed(input);
    
    // Find all possible solutions
    find_combinations(input, 0, 0, 0, min_remove, solutions, &sol_count);

    // Print solutions
    for (i = 0; i < sol_count; i++) {
        printf("%s\n", solutions[i]);
    }

    return 0;
}
