#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 10000; // Random numbers from 0 to 9999
}

// ---------- Quick Sort ----------
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1, temp;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ---------- Merge Sort ----------
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;

    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

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

// ---------- Heap Sort ----------
void heapify(int arr[], int size, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2, temp;

    if (left < size && arr[left] > arr[largest]) largest = left;
    if (right < size && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        temp = arr[i]; arr[i] = arr[largest]; arr[largest] = temp;
        heapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
    for (int i = size - 1; i > 0; i--) {
        int temp = arr[0]; arr[0] = arr[i]; arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// ---------- Utility ----------
void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
}

void printFirstElements(int arr[], int size, int limit) {
    for (int i = 0; i < size && i < limit; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// ---------- Main Function ----------
int main() {
    int size;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int original[size], quickArr[size], mergeArr[size], heapArr[size];

    srand(time(0));
    generateRandomArray(original, size);
    copyArray(original, quickArr, size);
    copyArray(original, mergeArr, size);
    copyArray(original, heapArr, size);

    printf("\nOriginal array (first 10 elements):\n");
    printFirstElements(original, size, 10);

    // Quick Sort
    clock_t startQuick = clock();
    quickSort(quickArr, 0, size - 1);
    clock_t endQuick = clock();

    // Merge Sort
    clock_t startMerge = clock();
    mergeSort(mergeArr, 0, size - 1);
    clock_t endMerge = clock();

    // Heap Sort
    clock_t startHeap = clock();
    heapSort(heapArr, size);
    clock_t endHeap = clock();

    // Display sorted arrays (first 10 elements only)
    printf("\nSorted with Quick Sort:\n");
    printFirstElements(quickArr, size, 10);

    printf("\nSorted with Merge Sort:\n");
    printFirstElements(mergeArr, size, 10);

    printf("\nSorted with Heap Sort:\n");
    printFirstElements(heapArr, size, 10);

    // Time calculations
    double timeQuick = (double)(endQuick - startQuick) / CLOCKS_PER_SEC;
    double timeMerge = (double)(endMerge - startMerge) / CLOCKS_PER_SEC;
    double timeHeap = (double)(endHeap - startHeap) / CLOCKS_PER_SEC;

    // Result
    printf("\nTime taken by Quick Sort: %.6f seconds", timeQuick);
    printf("\nTime taken by Merge Sort: %.6f seconds", timeMerge);
    printf("\nTime taken by Heap Sort : %.6f seconds\n", timeHeap);

    return 0;
}
