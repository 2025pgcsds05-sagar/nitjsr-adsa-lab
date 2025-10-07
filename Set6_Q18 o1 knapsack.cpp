#include <stdio.h>

// Function to return maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 0/1 Knapsack using DP
int knapsack(int W, int wt[], int val[], int n) {
    int dp[n+1][W+1];

    // Build table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i-1] <= w)
                dp[i][w] = max(val[i-1] + dp[i-1][w - wt[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    // return maximum value
    return dp[n][W];
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {1, 25, 45};
    int W = 50;   // Knapsack capacity
    int n = sizeof(val) / sizeof(val[0]);

    printf("Maximum value in Knapsack = %d\n", knapsack(W, wt, val, n));
    return 0;
}

