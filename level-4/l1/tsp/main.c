#include <unistd.h>
#include <math.h>
#include <stdio.h>

#define MAX_CITIES 11
#define INF 1e9

typedef struct {
    float x;
    float y;
} City;

// Global variables
City cities[MAX_CITIES];
int num_cities = 0;
int path[MAX_CITIES];
int best_path[MAX_CITIES];
float min_distance = INF;

// Calculate Euclidean distance between two cities
float distance(City a, City b) {
    return sqrtf(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Calculate total path length
float calculate_path_length() {
    float total = 0;
    for (int i = 0; i < num_cities - 1; i++) {
        total += distance(cities[path[i]], cities[path[i + 1]]);
    }
    // Add distance back to starting city
    total += distance(cities[path[num_cities - 1]], cities[path[0]]);
    return total;
}

// Swap two elements in array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Generate all permutations using Heap's algorithm
void generate_permutations(int k) {
    if (k == 1) {
        float current_distance = calculate_path_length();
        if (current_distance < min_distance) {
            min_distance = current_distance;
            for (int i = 0; i < num_cities; i++) {
                best_path[i] = path[i];
            }
        }
        return;
    }

    for (int i = 0; i < k; i++) {
        generate_permutations(k - 1);
        if (k % 2 == 0) {
            swap(&path[i], &path[k - 1]);
        } else {
            swap(&path[0], &path[k - 1]);
        }
    }
}

int main() {
    // Read city coordinates from stdin
    float x, y;
    while (fscanf(stdin, "%f, %f", &x, &y) == 2 && num_cities < MAX_CITIES) {
        cities[num_cities].x = x;
        cities[num_cities].y = y;
        path[num_cities] = num_cities;  // Initialize path array
        num_cities++;
    }

    if (num_cities == 0) {
        fprintf(stdout, "0.00\n");
        return 0;
    }

    // Generate all possible permutations and find shortest path
    generate_permutations(num_cities);

    // Print result with exactly 2 decimal places
    fprintf(stdout, "%.2f\n", min_distance);

    return 0;
}
