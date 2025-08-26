#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition numbers based on a specific bit
int partition(int arr[], int left, int right, int bit) {
    int i = left, j = right;

    while (i <= j) {
        while (i <= right && ((arr[i] >> bit) & 1) == 0)
            i++;
        while (j >= left && ((arr[j] >> bit) & 1) == 1)
            j--;

        if (i < j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    return i;
}

// Recursive radix exchange sort
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0)
        return;

    int pivot = partition(arr, left, right, bit);

    // Recursively sort both partitions with next lower bit
    radixExchangeSort(arr, left, pivot - 1, bit - 1);
    radixExchangeSort(arr, pivot, right, bit - 1);
}

// Driver code
int main() {
    int arr[] = {7, 3, 2, 6, 10, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // Find max number to determine number of bits
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];

    int maxBit = 0;
    while ((maxVal >> maxBit) > 0) maxBit++;

    radixExchangeSort(arr, 0, n - 1, maxBit - 1);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

