// nq-01.c - using 2D array

#include <stdio.h>
#include <stdlib.h>

void print_solution(int **board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j])
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

int is_safe(int **board, int row, int col, int n)
{
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Check this row on right side
    for (i = col + 1; i < n; i++)
        if (board[row][i])
            return 0;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Check lower diagonal on left side
    for (i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j])
            return 0;

    // Check upper diagonal on right side
    for (i = row, j = col; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return 0;

    // Check lower diagonal on right side
    for (i = row, j = col; i < n && j < n; i++, j++)
        if (board[i][j])
            return 0;

    return 1;
}

void solve_n_queens(int **board, int col, int n)
{
    // Base case: If all queens are placed, print the solution
    if (col >= n)
    {
        print_solution(board, n);
        return;
    }

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < n; i++)
    {
        // Check if queen can be placed on board[i][col]
        if (is_safe(board, i, col, n))
        {
            // Place this queen in board[i][col]
            board[i][col] = 1;

            // Recur to place rest of the queens
            solve_n_queens(board, col + 1, n);

            // If placing queen in board[i][col] doesn't lead to a solution,
            // then remove queen from board[i][col]
            board[i][col] = 0; // BACKTRACK
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s number_of_queens\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0)
    {
        printf("Please enter a positive number\n");
        return 1;
    }

    // Allocate memory for 2D array
    int **board = (int **)malloc(n * sizeof(int *));
    if (!board)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        board[i] = (int *)malloc(n * sizeof(int));
        if (!board[i])
        {
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++)
                free(board[j]);
            free(board);
            printf("Memory allocation failed\n");
            return 1;
        }
        // Initialize all positions to 0
        for (int j = 0; j < n; j++)
            board[i][j] = 0;
    }

    solve_n_queens(board, 0, n);

    // Free allocated memory
    for (int i = 0; i < n; i++)
        free(board[i]);
    free(board);

    return 0;
}
