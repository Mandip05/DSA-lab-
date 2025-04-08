#include <stdio.h>

int sequentialSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i; 
        }
    }
    return -1; 
}

int binarySearch(int arr[], int n, int key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid; 
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; 
}

int main() {
    int n, key;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n], sortedArr[n];
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sortedArr[i] = arr[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sortedArr[j] > sortedArr[j + 1]) {
                int temp = sortedArr[j];
                sortedArr[j] = sortedArr[j + 1];
                sortedArr[j + 1] = temp;
            }
        }
    }
    
    printf("Enter element to search: ");
    scanf("%d", &key);
    
    int seqResult = sequentialSearch(arr, n, key);
    printf("Using Sequential Search: ");
    if (seqResult != -1) {
        printf("Element found at index %d\n", seqResult);
    } else {
        printf("Element not found\n");
    }
   
    int binResult = binarySearch(sortedArr, n, key);
    printf("Using Binary Search: ");
    if (binResult != -1) {
        printf("Element found at index %d (in sorted array)\n", binResult);
    } else {
        printf("Element not found\n");
    }
    getchar();
    getchar();
    
    return 0;
}

