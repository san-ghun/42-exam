#include <unistd.h>
#include <stdlib.h>

// Helper function to convert int to string and write it
void write_number(int n)
{
    if (n == 0)
    {
        write(1, "0", 1);
        return;
    }
    
    char    buffer[12];  // Enough for 32-bit int
    int     i = 0;
    int     is_negative = 0;
    
    if (n < 0)
    {
        is_negative = 1;
        n = -n;
    }
    
    // Convert number to string by getting digits in reverse
    while (n > 0)
    {
        buffer[i++] = '0' + (n % 10);
        n /= 10;
    }
    
    if (is_negative)
        buffer[i++] = '-';
        
    // Write digits in correct order
    while (i > 0)
        write(1, &buffer[--i], 1);
}

// Print current combination
void print_combination(int *numbers, int *used, int size)
{
    int first = 1;
    for (int i = 0; i < size; i++)
    {
        if (used[i])
        {
            if (!first)
                write(1, " ", 1);
            write_number(numbers[i]);
            first = 0;
        }
    }
    write(1, "\n", 1);
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
        return (1);
        
    // Parse target sum and array size
    int target = atoi(av[1]);
    int size = ac - 2;
    
    // Allocate and initialize arrays
    int *numbers = malloc(sizeof(int) * size);
    int *used = malloc(sizeof(int) * size);
    if (!numbers || !used)
        return (1);
    
    // Parse input numbers and initialize used array
    for (int i = 0; i < size; i++)
    {
        numbers[i] = atoi(av[i + 2]);
        used[i] = 0;
    }
    
    // Find all combinations
    find_combinations(numbers, used, size, target, 0);
    
    // Clean up
    free(numbers);
    free(used);
    return (0);
}
