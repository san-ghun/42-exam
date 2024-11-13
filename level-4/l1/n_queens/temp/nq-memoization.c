#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold memoization tables for different types of checks
typedef struct {
    int **rows;         // Cache for row conflicts
    int **diag1;        // Cache for diagonal conflicts (top-left to bottom-right)
    int **diag2;        // Cache for diagonal conflicts (top-right to bottom-left)
} MemoCache;

// Initialize memoization cache
MemoCache* init_memo_cache(int n)
{
    MemoCache *cache = (MemoCache*)malloc(sizeof(MemoCache));
    if (!cache)
        return NULL;

    // Allocate memory for row checks
    cache->rows = (int**)malloc(n * sizeof(int*));
    if (!cache->rows)
    {
        free(cache);
        return NULL;
    }

    // Allocate memory for first diagonal checks
    cache->diag1 = (int**)malloc(n * sizeof(int*));
    if (!cache->diag1)
    {
        free(cache->rows);
        free(cache);
        return NULL;
    }

    // Allocate memory for second diagonal checks
    cache->diag2 = (int**)malloc(n * sizeof(int*));
    if (!cache->diag2)
    {
        free(cache->diag1);
        free(cache->rows);
        free(cache);
        return NULL;
    }

    // Initialize all cache tables
    for (int i = 0; i < n; i++)
    {
        cache->rows[i] = (int*)calloc(n, sizeof(int));
        cache->diag1[i] = (int*)calloc(n, sizeof(int));
        cache->diag2[i] = (int*)calloc(n, sizeof(int));
        if (!cache->rows[i] || !cache->diag1[i] || !cache->diag2[i])
        {
            // Clean up on allocation failure
            for (int j = 0; j <= i; j++)
            {
                free(cache->rows[j]);
                free(cache->diag1[j]);
                free(cache->diag2[j]);
            }
            free(cache->rows);
            free(cache->diag1);
            free(cache->diag2);
            free(cache);
            return NULL;
        }
    }
    return cache;
}

// Free memoization cache
void free_memo_cache(MemoCache *cache, int n)
{
    if (!cache)
        return;

    for (int i = 0; i < n; i++)
    {
        free(cache->rows[i]);
        free(cache->diag1[i]);
        free(cache->diag2[i]);
    }
    free(cache->rows);
    free(cache->diag1);
    free(cache->diag2);
    free(cache);
}

// Print the solution
void print_solution(int *board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

// Update cache when placing or removing a queen
void update_cache(MemoCache *cache, int row, int col, int n, int value)
{
    cache->rows[row][col] = value;
    
    // Update diagonal caches
    // For diagonal from top-left to bottom-right
    int diag1_idx = row - col + n - 1;
    if (diag1_idx >= 0 && diag1_idx < n)
        cache->diag1[row][diag1_idx] = value;
    
    // For diagonal from top-right to bottom-left
    int diag2_idx = row + col;
    if (diag2_idx >= 0 && diag2_idx < n)
        cache->diag2[row][diag2_idx] = value;
}

// Check if position is safe using memoization cache
int is_safe(MemoCache *cache, int row, int col, int n)
{
    // Check row conflicts
    for (int i = 0; i < col; i++)
        if (cache->rows[row][i])
            return 0;

    // Check diagonal conflicts
    int diag1_idx = row - col + n - 1;
    int diag2_idx = row + col;

    // Check first diagonal
    if (diag1_idx >= 0 && diag1_idx < n)
        for (int i = 0; i < col; i++)
            if (cache->diag1[row][diag1_idx])
                return 0;

    // Check second diagonal
    if (diag2_idx >= 0 && diag2_idx < n)
        for (int i = 0; i < col; i++)
            if (cache->diag2[row][diag2_idx])
                return 0;

    return 1;
}

// Recursive function to solve N Queens with memoization
void solve_n_queens(int *board, int col, int n, MemoCache *cache)
{
    if (col >= n)
    {
        print_solution(board, n);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (is_safe(cache, i, col, n))
        {
            board[i] = col;
            update_cache(cache, i, col, n, 1);  // Mark position as occupied

            solve_n_queens(board, col + 1, n, cache);

            board[i] = -1;
            update_cache(cache, i, col, n, 0);  // Mark position as free
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

    // Initialize board
    int *board = (int *)malloc(n * sizeof(int));
    if (!board)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
        board[i] = -1;

    // Initialize memoization cache
    MemoCache *cache = init_memo_cache(n);
    if (!cache)
    {
        free(board);
        printf("Memory allocation failed for cache\n");
        return 1;
    }

    solve_n_queens(board, 0, n, cache);

    // Cleanup
    free_memo_cache(cache, n);
    free(board);
    return 0;
}
