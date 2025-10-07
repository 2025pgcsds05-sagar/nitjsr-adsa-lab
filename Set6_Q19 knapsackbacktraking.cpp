#include <stdio.h>

int n;                 // number of items
int capacity;          // knapsack capacity
int weights[100];      // weights of items
int values[100];       // values of items
int include[100];      // current set
int best_set[100];     // best set found
int max_profit = 0;    // best profit so far

// Backtracking function
void knapsack_backtrack(int i, int current_weight, int current_value) {
    if (current_weight > capacity) {
        return; // prune this branch
    }

    // update best solution
    if (current_value > max_profit) {
        max_profit = current_value;
        for (int j = 0; j < n; j++) {
            best_set[j] = include[j];
        }
    }

    // if all items are considered
    if (i == n) {
        return;
    }

    // include item i
    include[i] = 1;
    knapsack_backtrack(i + 1, current_weight + weights[i], current_value + values[i]);

    // exclude item i
    include[i] = 0;
    knapsack_backtrack(i + 1, current_weight, current_value);
}

int main() {
    // Example input
    n = 4;
    capacity = 6;
    int w[4] = {2, 3, 4, 5};
    int v[4] = {3, 4, 5, 6};

    for (int i = 0; i < n; i++) {
        weights[i] = w[i];
        values[i] = v[i];
    }

    // Run backtracking
    knapsack_backtrack(0, 0, 0);

    // Output result
    printf("Maximum Profit: %d\n", max_profit);
    printf("Selected Items: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", best_set[i]);
    }
    printf("\n");

    return 0;
}

