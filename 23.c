#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random array
void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; // random numbers between 0 and 9999
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ----------- Quick Sort -------------

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // swap arr[i+1] and arr[high]
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ----------- Merge Sort -------------

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ----------- Main Program -------------

int main() {
    int size;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr1[size], arr2[size];
    srand(time(0));  // Seed for randomness

    generateRandomArray(arr1, size);

    // Copy arr1 into arr2 for fair comparison
    for (int i = 0; i < size; i++) arr2[i] = arr1[i];

    printf("\nOriginal array (first 10 elements only):\n");
    for (int i = 0; i < size && i < 10; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // Timing Quick Sort
    clock_t start1 = clock();
    quickSort(arr1, 0, size - 1);
    clock_t end1 = clock();

    // Timing Merge Sort
    clock_t start2 = clock();
    mergeSort(arr2, 0, size - 1);
    clock_t end2 = clock();

    printf("\nSorted with Quick Sort (first 10 elements):\n");
    for (int i = 0; i < size && i < 10; i++) {
        printf("%d ", arr1[i]);
    }

    printf("\n\nSorted with Merge Sort (first 10 elements):\n");
    for (int i = 0; i < size && i < 10; i++) {
        printf("%d ", arr2[i]);
    }

    double timeQuick = (double)(end1 - start1) / CLOCKS_PER_SEC;
    double timeMerge = (double)(end2 - start2) / CLOCKS_PER_SEC;

    printf("\n\nTime taken by Quick Sort: %.6f seconds", timeQuick);
    printf("\nTime taken by Merge Sort: %.6f seconds\n", timeMerge);

    return 0;
}
