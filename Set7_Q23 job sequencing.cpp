#include <stdio.h>

// Function to get maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to implement Job Sequencing with Deadlines
void jobSequencing(int n, int deadline[], int profit[], char jobID[]) {
    int i, j;
    int maxDeadline = 0;

    // Step 1: Find maximum deadline
    for (i = 0; i < n; i++) {
        maxDeadline = max(maxDeadline, deadline[i]);
    }

    // Step 2: Initialize slots as empty
    char result[maxDeadline + 1];  // job ID in each slot
    for (i = 1; i <= maxDeadline; i++) {
        result[i] = '-';
    }

    int totalProfit = 0;

    // Step 3: Greedy approach: choose jobs by profit
    // Bubble sort jobs by descending profit
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (profit[j] < profit[j + 1]) {
                // swap profit
                int tempP = profit[j];
                profit[j] = profit[j + 1];
                profit[j + 1] = tempP;

                // swap deadline
                int tempD = deadline[j];
                deadline[j] = deadline[j + 1];
                deadline[j + 1] = tempD;

                // swap jobID
                char tempJ = jobID[j];
                jobID[j] = jobID[j + 1];
                jobID[j + 1] = tempJ;
            }
        }
    }

    // Step 4: Place jobs in available slots
    for (i = 0; i < n; i++) {
        for (j = deadline[i]; j > 0; j--) {
            if (result[j] == '-') {
                result[j] = jobID[i];
                totalProfit += profit[i];
                break;
            }
        }
    }

    // Step 5: Print result
    printf("Job sequence: ");
    for (i = 1; i <= maxDeadline; i++) {
        if (result[i] != '-') {
            printf("%c ", result[i]);
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

int main() {
    // Example input
    int n = 5;
    char jobID[] = {'A', 'B', 'C', 'D', 'E'};
    int deadline[] = {2, 1, 2, 1, 3};
    int profit[] = {10, 19, 27, 35, 150};

    jobSequencing(n, deadline, profit, jobID);

    return 0;
}

