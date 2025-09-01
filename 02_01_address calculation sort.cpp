#include <stdio.h>
#include <stdlib.h>

// Address Calculation Sort
void addressCalculationSort(int arr[], int n, int minVal, int maxVal) {
    int range = maxVal - minVal + 1;
    int *slots = (int *)calloc(range, sizeof(int)); // array of counts

    // Count frequency of each element
    for (int i = 0; i < n; i++) {
        slots[arr[i] - minVal]++;
    }

    // Reconstruct sorted array
    int index = 0;
    for (int i = 0; i < range; i++) {
        while (slots[i] > 0) {
            arr[index++] = i + minVal;
            slots[i]--;
        }
    }

    free(slots);
}

// Driver code
int main() {
    int arr[] = {23, 12, 18, 15, 12, 18};
    int n = sizeof(arr) / sizeof(arr[0]);

    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    addressCalculationSort(arr, n, minVal, maxVal);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

