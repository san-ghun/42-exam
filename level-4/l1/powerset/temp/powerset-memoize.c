#include <unistd.h>
#include <stdlib.h>

void write_number(int n)
{
    if (n == 0)
    {
        write(1, "0", 1);
        return;
    }
    
    char    buffer[12];
    int     i = 0;
    
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    
    while (n > 0)
    {
        buffer[i++] = '0' + (n % 10);
        n /= 10;
    }
    
    while (i > 0)
        write(1, &buffer[--i], 1);
}

void print_subset(int *arr, int *used, int n)
{
    int first = 1;
    for (int i = 0; i < n; i++)
    {
        if (used[i])
        {
            if (!first)
                write(1, " ", 1);
            write_number(arr[i]);
            first = 0;
        }
    }
    write(1, "\n", 1);
}

// Key function for memoization
// Returns 1 if subset with given sum is possible from pos onwards
int has_subset_sum(int *arr, int pos, int target, int n, int **memo)
{
    // Base cases
    if (target == 0)
        return 1;
    if (pos >= n || target < 0)
        return 0;
        
    // Check if already computed
    if (memo[pos][target] != -1)
        return memo[pos][target];
        
    // Try including current element
    int include = has_subset_sum(arr, pos + 1, target - arr[pos], n, memo);
    // Try excluding current element
    int exclude = has_subset_sum(arr, pos + 1, target, n, memo);
    
    // Store result in memo table
    memo[pos][target] = include || exclude;
    return memo[pos][target];
}

void print_all_subsets(int *arr, int *used, int pos, int target, int n, int **memo)
{
    // If we found a valid sum
    if (target == 0)
    {
        print_subset(arr, used, n);
        return;
    }
    
    // If we've reached end or sum not possible
    if (pos >= n || target < 0)
        return;
        
    // Check memo table before proceeding
    if (!has_subset_sum(arr, pos, target, n, memo))
        return;
        
    // Include current element if it leads to solution
    if (target >= arr[pos])
    {
        used[pos] = 1;
        print_all_subsets(arr, used, pos + 1, target - arr[pos], n, memo);
        used[pos] = 0;  // Backtrack
    }
    
    // Exclude current element
    print_all_subsets(arr, used, pos + 1, target, n, memo);
}

int main(int ac, char **av)
{
    if (ac < 3)
        return 1;
        
    int target = atoi(av[1]);
    int n = ac - 2;
    
    // Allocate arrays
    int *arr = malloc(sizeof(int) * n);
    int *used = calloc(n, sizeof(int));
    if (!arr || !used)
        return 1;
    
    // Parse input numbers
    for (int i = 0; i < n; i++)
        arr[i] = atoi(av[i + 2]);
    
    // Create memoization table
    int **memo = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
    {
        memo[i] = malloc(sizeof(int) * (target + 1));
        // Initialize with -1 (not computed)
        for (int j = 0; j <= target; j++)
            memo[i][j] = -1;
    }
    
    // Find and print all subsets
    print_all_subsets(arr, used, 0, target, n, memo);
    
    // Cleanup
    free(arr);
    free(used);
    for (int i = 0; i < n; i++)
        free(memo[i]);
    free(memo);
    
    return 0;
}
