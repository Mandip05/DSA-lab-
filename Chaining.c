#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 10099

struct Node {
    int data;
    struct Node* next;
};

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
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
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

// Insert into Chaining Hash Table
void insertChaining(struct Node* hashTable[], int size, int value) {
    int index = value % size;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Search in Chaining Hash Table
int searchChaining(struct Node* hashTable[], int size, int target) {
    int index = target % size;
    struct Node* current = hashTable[index];
    while (current != NULL) {
        if (current->data == target) return 1; // found
        current = current->next;
    }
    return 0; // not found
}

// Measure Execution Time
double measureTime(int (*searchFunction)(int[], int, int), int arr[], int size, int target) {
    clock_t start = clock();
    searchFunction(arr, size, target);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    int size = 10000;
    int target = 50;
    srand(time(NULL));

    int unsortedArr[size];
    int sortedArr[size];
    generateRandomArray(unsortedArr, size);

    // Copy and sort array for binary search
    for (int i = 0; i < size; i++) {
        sortedArr[i] = unsortedArr[i];
    }
    bubbleSort(sortedArr, size);

    // Sequential Search (Unsorted)
    double seqTimeUnsorted = measureTime(sequentialSearch, unsortedArr, size, target);

    // Sequential Search (Sorted)
    double seqTimeSorted = measureTime(sequentialSearch, sortedArr, size, target);

    // Binary Search
    double binTimeSorted = measureTime(binarySearch, sortedArr, size, target);

    // Initialize Hash Table with Chaining
    struct Node* hashTableChaining[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTableChaining[i] = NULL;
    }

    // Insertion Time for Chaining
    clock_t start = clock();
    for (int i = 0; i < size; i++) {
        insertChaining(hashTableChaining, TABLE_SIZE, unsortedArr[i]);
    }
    clock_t end = clock();
    double chainingInsertTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Search Time for Chaining
    start = clock();
    searchChaining(hashTableChaining, TABLE_SIZE, target);
    end = clock();
    double chainingSearchTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Output Results
    printf("Sequential Search on Unsorted Array: Time taken: %.6f seconds\n", seqTimeUnsorted);
    printf("Sequential Search on Sorted Array:   Time taken: %.6f seconds\n", seqTimeSorted);
    printf("Binary Search on Sorted Array:       Time taken: %.6f seconds\n", binTimeSorted);
    printf("Hash Table (Chaining) Insert Time:   %.6f seconds\n", chainingInsertTime);
    printf("Hash Table (Chaining) Search Time:   %.6f seconds\n", chainingSearchTime);

    // Pause before exit
    printf("\nPress Enter to exit...");
    getchar();
    getchar();

    return 0;
}
