#include <stdio.h>
#include <stdlib.h>

// Print current combination
void print_combination(int *numbers, int *used, int size)
{
    int first = 1;
    for (int i = 0; i < size; i++)
    {
        if (used[i])
        {
            if (!first)
                printf(" ");
            printf("%d", numbers[i]);
            first = 0;
        }
    }
    printf("\n");
}

// Calculate sum of current combination
int get_sum(int *numbers, int *used, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        if (used[i])
            sum += numbers[i];
    return sum;
}

// Recursive function to find combinations
void find_combinations(int *numbers, int *used, int size, int target, int pos)
{
    // If we found a valid sum, print the combination
    if (get_sum(numbers, used, size) == target)
        print_combination(numbers, used, size);
    
    // Try remaining numbers
    for (int i = pos; i < size; i++)
    {
        if (!used[i])
        {
            used[i] = 1;  // Include current number
            find_combinations(numbers, used, size, target, i + 1);
            used[i] = 0;  // Backtrack
        }
    }
}

int main(int ac, char **av)
{
    // Basic input validation
    if (ac < 3)
    {
        printf("Usage: %s target_sum number1 number2 ...\n", av[0]);
        return (1);
    }
        
    // Parse target sum and array size
    int target = atoi(av[1]);
    int size = ac - 2;
    
    // Allocate and initialize arrays
    int *numbers = malloc(sizeof(int) * size);
    int *used = malloc(sizeof(int) * size);
    if (!numbers || !used)
    {
        printf("Memory allocation failed\n");
        return (1);
    }
    
    // Parse input numbers and initialize used array
    for (int i = 0; i < size; i++)
    {
        numbers[i] = atoi(av[i + 2]);
        used[i] = 0;
    }
    
    // Print input information
    printf("Target sum: %d\n", target);
    printf("Numbers: ");
    for (int i = 0; i < size; i++)
        printf("%d ", numbers[i]);
    printf("\n\nCombinations:\n");
    
    // Find all combinations
    find_combinations(numbers, used, size, target, 0);
    
    // Clean up
    free(numbers);
    free(used);
    return (0);
}
