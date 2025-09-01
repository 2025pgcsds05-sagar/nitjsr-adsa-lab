#include <stdio.h>
#include <stdlib.h>

// Function to perform Counting Sort
void countingSort(int arr[], int n) {
    // Find the maximum element to determine range
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    // Create count array of size max+1 and initialize to 0
    int *count = (int *)calloc(max + 1, sizeof(int));

    // Create output array
    int *output = (int *)malloc(n * sizeof(int));

    // Count occurrences of each element
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // Modify count array to store cumulative sum
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Build the output array (process in reverse for stability)
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy output array to original array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    // Free allocated memory
    free(count);
    free(output);
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    countingSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
