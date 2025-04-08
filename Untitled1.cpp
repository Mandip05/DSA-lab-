#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 100     // Hash table ?? size
#define DATA_SIZE 1000     // Dataset ?? size

// Linked list ?? node structure
typedef struct Node {
    int key;
    struct Node* next;
} Node;

// Hash table (array of pointers to Node)
Node* hashTable[TABLE_SIZE];

// ???? node ?????? function
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Hash function: simple mod operation
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Hash table ?? key insert ????? (chaining method ?????? ???)
void insert(int key) {
    int index = hashFunction(key);
    Node* newNode = createNode(key);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Hash table ?? sequential search ????? function
int search(int key) {
    int index = hashFunction(key);
    Node* current = hashTable[index];
    while (current != NULL) {
        if (current->key == key)
            return 1;  // ?????
        current = current->next;
    }
    return 0;  // ???? ????
}

// Bubble sort (O(n^2), beginner-level sorting)
void bubbleSort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Binary search (array sorted ???? ????)
int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == target)
            return 1;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;
}

// Random data generate ????? function
void generateData(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 100000;  // Random number 0 to 99999
}

// ????? function
int main() {
    int data[DATA_SIZE], sortedData[DATA_SIZE];
    int target, found;
    clock_t start, end;
    double time_taken;

    srand(time(NULL));  // Random seed

    // Data generate ?????????
    generateData(data, DATA_SIZE);

    // Hash table ?? ??? ???? insert ?????????
    for (int i = 0; i < DATA_SIZE; i++)
        insert(data[i]);

    // ?? random value target ?? ????? ?????
    target = data[rand() % DATA_SIZE];

    // Sequential Search in Hash Table
    start = clock();
    found = search(target);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sequential Search in Hash Table: Found = %s, Time = %f sec\n", found ? "Yes" : "No", time_taken);

    // Bubble Sort
    for (int i = 0; i < DATA_SIZE; i++)
        sortedData[i] = data[i];  // Original data ?? copy

    start = clock();
    bubbleSort(sortedData, DATA_SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort Time: %f sec\n", time_taken);

    // Binary Search (sorted array ??)
    start = clock();
    found = binarySearch(sortedData, DATA_SIZE, target);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Binary Search: Found = %s, Time = %f sec\n", found ? "Yes" : "No", time_taken);

    return 0;
}

