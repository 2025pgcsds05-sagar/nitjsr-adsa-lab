#include <stdio.h>

void greedyCoinChange(int coins[], int n, int amount) {
    int i, count;

    printf("Coins used:\n");

    // Start from the largest coin
    for (i = n - 1; i >= 0; i--) {
        count = 0;
        // Take coin[i] as many times as possible
        while (amount >= coins[i]) {
            amount -= coins[i];
            count++;
        }
        if (count > 0) {
            printf("%d coin of %d\n", count, coins[i]);
        }
    }
}

int main() {
    // Example coin system (Indian currency)
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 500, 2000};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount;

    printf("Enter the amount: ");
    scanf("%d", &amount);

    greedyCoinChange(coins, n, amount);

    return 0;
}

