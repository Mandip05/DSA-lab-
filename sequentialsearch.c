#include <stdio.h>

int sequential_search(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i; // Return index of the key if found
        }
    }
    return -1; // Return -1 if the key is not found
}

int main() {
    int arr[] = {9, 25, 35, 45, 60, 75, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 75; // Key to search for

    int result = sequential_search(arr, n, key);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
