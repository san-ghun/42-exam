// rip-03.c

#include <stdio.h>
#include <unistd.h>

#define MAX_LEN 1000
#define MAX_SOL 100

void find_solutions(char *str, int pos, int open, int close, int to_remove, 
                   char sols[MAX_SOL][MAX_LEN], int *count) {
    if (str[pos] == '\0') {
        if (open == close && *count < MAX_SOL) {
            // Check if solution already exists
            for (int i = 0; i < *count; i++)
                if (strcmp(sols[i], str) == 0)
                    return;
            strcpy(sols[(*count)++], str);
        }
        return;
    }

    if (str[pos] == ' ') {
        find_solutions(str, pos + 1, open, close, to_remove, sols, count);
        return;
    }

    // Keep current parenthesis if valid
    if (str[pos] == '(' || (str[pos] == ')' && open > close)) {
        find_solutions(str, pos + 1, 
                      open + (str[pos] == '('), 
                      close + (str[pos] == ')'), 
                      to_remove, sols, count);
    }

    // Try removing current parenthesis
    if (to_remove > 0) {
        char tmp = str[pos];
        str[pos] = ' ';
        find_solutions(str, pos + 1, open, close, to_remove - 1, sols, count);
        str[pos] = tmp;
    }
}

int count_removals(char *str) {
    int open = 0, extra = 0;
    
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')') {
            if (open == 0)
                extra++;
            else
                open--;
        }
    }
    return extra + open;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(2, "Error: one argument needed\n", 26);
        return 1;
    }

    char input[MAX_LEN];
    char sols[MAX_SOL][MAX_LEN];
    int count = 0;
    
    strcpy(input, argv[1]);
    int to_remove = count_removals(input);
    find_solutions(input, 0, 0, 0, to_remove, sols, &count);

    for (int i = 0; i < count; i++)
        printf("%s\n", sols[i]);
    return 0;
}
