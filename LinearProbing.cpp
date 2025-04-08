#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TABLE_SIZE 10007
#define REPEAT 1000   // Reduced to prevent freezing
#define ARRAY_SIZE 50000  // Reduced to prevent memory issues
#define EMPTY -1

int hashTable[TABLE_SIZE];

// Sequential Search
int sequentialSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// Binary Search
int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Bubble Sort
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Generate Random Array
void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
}

// Hash Function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Linear Probing Insert
void linearProbingInsert(int value) {
    int index = hashFunction(value);
    int start = index;
    while (hashTable[index] != EMPTY) {
        index = (index + 1) % TABLE_SIZE;
        if (index == start) return; // Prevent infinite loop
    }
    hashTable[index] = value;
}

// Linear Probing Search
int linearProbingSearch(int value) {
    int index = hashFunction(value);
    int start = index;
    while (hashTable[index] != EMPTY) {
        if (hashTable[index] == value) {
            return index;  // Found
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start) return -1; // Prevent infinite loop
    }
    return -1; // Not found
}

// Measure Execution Time
double measureTime(int (*searchFunction)(int[], int, int), int arr[], int size, int target) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < REPEAT; i++) {
        searchFunction(arr, size, target);
    }

    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart / REPEAT; // Average time
}

int main() {
    int unsortedArr[ARRAY_SIZE], sortedArr[ARRAY_SIZE];
    generateRandomArray(unsortedArr, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sortedArr[i] = unsortedArr[i];
    }
    
    printf("Sorting started...\n"); fflush(stdout);
    bubbleSort(sortedArr, ARRAY_SIZE);
    printf("Sorting completed.\n"); fflush(stdout);
    
    double seqTimeUnsorted = measureTime(sequentialSearch, unsortedArr, ARRAY_SIZE, 50);
    double seqTimeSorted = measureTime(sequentialSearch, sortedArr, ARRAY_SIZE, 50);
    double binTimeSorted = measureTime(binarySearch, sortedArr, ARRAY_SIZE, 50);

    // Initialize Hash Table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }
    printf("Inserting into hash table...\n"); fflush(stdout);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        linearProbingInsert(unsortedArr[i]);
    }
    printf("Insertion completed.\n"); fflush(stdout);
    
    // Measure Hash Table Search Time
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < REPEAT; i++) {
        linearProbingSearch(50);
    }

    QueryPerformanceCounter(&end);
    double hashSearchTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart / REPEAT;
    
    printf("Sequential Search on Unsorted Array: %.10f seconds\n", seqTimeUnsorted);
    printf("Sequential Search on Sorted Array: %.10f seconds\n", seqTimeSorted);
    printf("Binary Search on Sorted Array: %.10f seconds\n", binTimeSorted);
    printf("Hash Table Search (Linear Probing): %.10f seconds\n", hashSearchTime);
    
    getchar();
    return 0;
}

