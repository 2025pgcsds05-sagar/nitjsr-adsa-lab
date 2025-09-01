#include <stdio.h>
#include <stdlib.h>

// Structure for a node in a bucket (linked list style)
struct Node {
    float data;
    struct Node* next;
};

// Function to insert an element into a bucket (sorted insertion)
void insertSorted(struct Node** bucket, float value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // Insert in sorted order
    if (*bucket == NULL || (*bucket)->data >= value) {
        newNode->next = *bucket;
        *bucket = newNode;
    } else {
        struct Node* current = *bucket;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to perform bucket sort
void bucketSort(float arr[], int n) {
    // Create n empty buckets
    struct Node** buckets = (struct Node**)malloc(n * sizeof(struct Node*));
    for (int i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    // Put array elements into buckets
    for (int i = 0; i < n; i++) {
        int index = (int)(arr[i] * n);  // Mapping
        if (index >= n) index = n - 1;  // Fix for edge case (arr[i] == 1.0)
        insertSorted(&buckets[index], arr[i]);
    }

    // Concatenate buckets back into the array
    int idx = 0;
    for (int i = 0; i < n; i++) {
        struct Node* node = buckets[i];
        while (node != NULL) {
            arr[idx++] = node->data;
            node = node->next;
        }
    }

    // Free buckets
    for (int i = 0; i < n; i++) {
        struct Node* node = buckets[i];
        while (node != NULL) {
            struct Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(buckets);
}

// Driver code
int main() {
    float arr[] = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");

    bucketSort(arr, n);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");

    return 0;
}

