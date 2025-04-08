#include <stdio.h>

// Function to implement Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap elements
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    int arr[] = {2, 1, 76, 28, 12, 32, 90, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, n);
    
    printf("Selection Sort: \n");

    for (int i = 0; i < n; i++) {
        printf(" %d\n", arr[i]);
    }
    getchar();
    getchar();

    return 0;
}

