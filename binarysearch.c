#include <stdio.h>

int binary_search(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid; // Key found, return index
        }
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Key not found
}

int main() {
    int arr[] = {9, 25, 30, 45, 60, 75, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 75;
    
    int result = binary_search(arr, 0, n - 1, key);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }
    printf("\n");
    return 0;
}
