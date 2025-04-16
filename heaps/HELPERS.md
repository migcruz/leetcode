# Helper functions for Heaps

## Min Heap
```C
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int maxSize;
} MinHeap;

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify down (used after deletion)
void minHeapify(MinHeap *heap, int index) {
    int left = 2 * index + 1; // left child
    int right = 2 * index + 2; // right child
    int smallest = index;
    
    // figure out which child is the smallest
    if (left < heap->size && heap->arr[left] < heap->arr[smallest])
        smallest = left;
    if (right < heap->size && heap->arr[right] < heap->arr[smallest])
        smallest = right;
    
    if (smallest != index) { // means index was NOT the smallest
        swap(&heap->arr[index], &heap->arr[smallest]);
        minHeapify(heap, smallest);
    }
}

// Function to insert an element into the MinHeap
void insert(MinHeap *heap, int value) {
    if (heap->size == heap->maxSize) {
        printf("Heap overflow!\n");
        return;
    }

    // Insert at the end
    (heap->size)++;
    int i = heap->size - 1;
    heap->arr[i] = value;

    // Heapify up to maintain min heap property
    while (i != 0 && heap->arr[(i - 1) / 2] > heap->arr[i]) { // move element up by swapping with parent if parent is greater
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the minimum element (root) from MinHeap
int extractMin(MinHeap *heap) {
    if (heap->size <= 0) // empty heap
        return -1;
    if (heap->size == 1) { // only 1 element so no need to bubble down
        heap->size--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1]; // bring end of heap to become root
    heap->size--;
    minHeapify(heap, 0); // now we must rearrange the heap

    return root;
}

// Function to print the heap elements
void printHeap(MinHeap *heap) {
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);
    printf("\n");
}

int main() {
    MinHeap heap;
    heap.size = 0;
    
    int nums[] = {46, 51, 21, 31, 13, 31, 10, 16, 41, 11, 8, 71};
    int len = sizeof(nums)/sizeof(nums[0]);
    
    // make the heap array
    int *heapArr = (int*) calloc (len, sizeof(int));
    heap.arr = heapArr;
    heap.maxSize = len;
    
    for (int i = 0; i < len; i++) {
        insert(&heap, nums[i]);
    }

    printf("MinHeap Elements: ");
    printHeap(&heap);

    printf("Extracted Min: %d\n", extractMin(&heap));
    printf("Heap after extraction: ");
    printHeap(&heap);
    
    free(heap.arr);

    return 0;
}
```
## Max Heap
```C
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int maxSize;
} MaxHeap;

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify down (used after deletion)
void maxHeapify(MaxHeap *heap, int index) {
    int left = 2 * index + 1; // left child
    int right = 2 * index + 2; // right child
    int largest = index;
    
    // figure out which child is the largest
    if (left < heap->size && heap->arr[left] > heap->arr[largest])
        largest = left;
    if (right < heap->size && heap->arr[right] > heap->arr[largest])
        largest = right;
    
    if (largest != index) { // means index was NOT the largest
        swap(&heap->arr[index], &heap->arr[largest]);
        maxHeapify(heap, largest);
    }
}

// Function to insert an element into the MaxHeap
void insert(MaxHeap *heap, int value) {
    if (heap->size == heap->maxSize) {
        printf("Heap overflow!\n");
        return;
    }

    // Insert at the end
    (heap->size)++;
    int i = heap->size - 1;
    heap->arr[i] = value;

    // Heapify up to maintain max heap property
    while (i != 0 && heap->arr[(i - 1) / 2] < heap->arr[i]) { // move element up by swapping with parent if parent is less
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the maximum element (root) from MaxHeap
int extractMax(MaxHeap *heap) {
    if (heap->size <= 0) // empty heap
        return -1;
    if (heap->size == 1) { // only 1 element so no need to bubble up
        heap->size--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1]; // bring end of heap to become root
    heap->size--;
    maxHeapify(heap, 0); // now we must rearrange the heap

    return root;
}

// Function to print the heap elements
void printHeap(MaxHeap *heap) {
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);
    printf("\n");
}

int main() {
    MaxHeap heap;
    heap.size = 0;
    
    int nums[] = {46, 51, 21, 31, 13, 31, 10, 16, 41, 11, 8, 71};
    int len = sizeof(nums)/sizeof(nums[0]);
    
    // make the heap array
    int *heapArr = (int*) calloc (len, sizeof(int));
    heap.arr = heapArr;
    heap.maxSize = len;
    
    for (int i = 0; i < len; i++) {
        insert(&heap, nums[i]);
    }

    printf("MaxHeap Elements: ");
    printHeap(&heap);

    printf("Extracted Min: %d\n", extractMax(&heap));
    printf("Heap after extraction: ");
    printHeap(&heap);
    
    free(heap.arr);

    return 0;
}
```