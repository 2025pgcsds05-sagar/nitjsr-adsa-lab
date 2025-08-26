#include <stdio.h>

void shellSort(int arr[], int n) {
    // Start with a large gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            // Store the current element
            int temp = arr[i];
            int j;
            
            // Shift earlier gap-sorted elements up until
            // the correct location for temp is found
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            
            // Place temp in its correct location
            arr[j] = temp;
        }
    }
}

int main() {
	int size;
	printf("Enter the number of elements\n");
	scanf("%d",&size);
	
    int arr[size] = {0};
    
    for(int i=0;i<size;i++)
     scanf("%d",&arr[i]);
     
    shellSort(arr, size);
    
    printf("Sorted array is   ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}
