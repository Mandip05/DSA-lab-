#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TABLE_SIZE 10009
#define REPEAT 10000   // Increased to measure time more accurately
#define ARRAY_SIZE 10000  // Test with 10,000 for now, can be increased later
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

// Quadratic Probing Insert
void quadraticProbingInsert(int value) {
    int index = hashFunction(value);
    int i = 1;
    while (hashTable[index] != EMPTY) {
        index = (index + i * i) % TABLE_SIZE;
        i++;
    }
    hashTable[index] = value;
}

// Quadratic Probing Search
int quadraticProbingSearch(int value) {
    int index = hashFunction(value);
    int i = 1;
    while (hashTable[index] != EMPTY) {
        if (hashTable[index] == value) {
            return index;
        }
        index = (index + i * i) % TABLE_SIZE;
        i++;
    }
    return -1;
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
    
    // Sort the array for binary search
    bubbleSort(sortedArr, ARRAY_SIZE);
    
    // Measure the execution times
    double seqTimeUnsorted = measureTime(sequentialSearch, unsortedArr, ARRAY_SIZE, 50);
    double seqTimeSorted = measureTime(sequentialSearch, sortedArr, ARRAY_SIZE, 50);
    double binTimeSorted = measureTime(binarySearch, sortedArr, ARRAY_SIZE, 50);

    // Initialize Hash Table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        quadraticProbingInsert(unsortedArr[i]);
    }

    // Measure Hash Table Search Time
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < REPEAT; i++) {
        quadraticProbingSearch(50);
    }

    QueryPerformanceCounter(&end);
    double hashSearchTimeQuadratic = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart / REPEAT;

    // Print the execution times to the console
    printf("Sequential Search on Unsorted Array: %.10f seconds\n", seqTimeUnsorted);
    printf("Sequential Search on Sorted Array: %.10f seconds\n", seqTimeSorted);
    printf("Binary Search on Sorted Array: %.10f seconds\n", binTimeSorted);
    printf("Hash Table Search (Quadratic Probing): %.10f seconds\n", hashSearchTimeQuadratic);

    // Ensure the console stays open before it closes
    printf("\nPress any key to exit...\n");
    getchar(); // Wait for user input before exiting
    return 0;
}
