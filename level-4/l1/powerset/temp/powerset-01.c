#include <stdio.h>
#include <stdlib.h>

// Structure to store our current state while finding combinations
typedef struct {
    int* numbers;       // Input array of numbers
    int* current_set;   // Current combination being built
    int target_sum;     // Target sum we're looking for
    int size;          // Size of input array
} SubsetContext;

// Print current combination that sums to target
void print_combination(int* combination, int size) {
    printf("Found combination: ");
    for (int i = 0; i < size; i++) {
        if (combination[i] != 0) {
            printf("%d ", combination[i]);
        }
    }
    printf("\n");
}

// Calculate sum of current combination
int get_current_sum(int* combination, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += combination[i];
    }
    return sum;
}

// Recursive function to find all combinations
void find_combinations(SubsetContext* ctx, int position) {
    // Check if current combination sums to target
    int current_sum = get_current_sum(ctx->current_set, ctx->size);
    
    // If we found a valid combination, print it
    if (current_sum == ctx->target_sum) {
        print_combination(ctx->current_set, ctx->size);
    }
    
    // If we've gone past the target sum or reached end of array, stop this branch
    if (current_sum > ctx->target_sum || position >= ctx->size) {
        return;
    }
    
    // Try including each remaining number
    for (int i = position; i < ctx->size; i++) {
        // Include current number in combination
        ctx->current_set[i] = ctx->numbers[i];
        
        // Recursively try to find more numbers to add
        find_combinations(ctx, i + 1);
        
        // Remove current number (backtrack) to try different combinations
        ctx->current_set[i] = 0;
    }
}

int main(int argc, char* argv[]) {
    // Check if we have enough arguments
    if (argc < 3) {
        printf("Usage: %s target_sum number1 number2 ...\n", argv[0]);
        return 1;
    }
    
    // Parse command line arguments
    int target_sum = atoi(argv[1]);
    int size = argc - 2;
    
    // Allocate arrays
    int* numbers = malloc(size * sizeof(int));
    int* current_set = calloc(size, sizeof(int));  // Initialize to zeros
    
    // Parse numbers from arguments
    for (int i = 0; i < size; i++) {
        numbers[i] = atoi(argv[i + 2]);
    }
    
    // Print input information
    printf("Looking for combinations that sum to: %d\n", target_sum);
    printf("Input numbers: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
    
    // Create context structure to hold our variables
    SubsetContext ctx = {
        .numbers = numbers,
        .current_set = current_set,
        .target_sum = target_sum,
        .size = size
    };
    
    // Start finding combinations
    find_combinations(&ctx, 0);
    
    // Clean up
    free(numbers);
    free(current_set);
    
    return 0;
}

