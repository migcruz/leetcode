/*
 * LeetCode Problem 1046: Last Stone Weight
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given an array of integers `stones` where `stones[i]` is the weight of the i-th stone.
 *
 * A game is played with the stones. On each turn:
 *   - Choose the two heaviest stones x and y (where x <= y).
 *   - If x == y, both stones are destroyed.
 *   - If x != y, the stone with weight x is destroyed and the stone with weight y is replaced by y - x.
 * 
 * This process repeats until there is at most one stone left.
 * Return the weight of the last remaining stone. If all stones are destroyed, return 0.
 *
 * Examples:
 *
 * Example 1:
 *   Input: stones = [2,7,4,1,8,1]
 *   Output: 1
 *   Explanation:
 *     - Combine 7 and 8 → 1 → [2,4,1,1,1]
 *     - Combine 2 and 4 → 2 → [2,1,1,1]
 *     - Combine 2 and 1 → 1 → [1,1,1]
 *     - Combine 1 and 1 → 0 → [1]
 *     - One stone remains with weight 1.
 *
 * Example 2:
 *   Input: stones = [1]
 *   Output: 1
 *
 * Constraints:
 *   - 1 <= stones.length <= 30
 *   - 1 <= stones[i] <= 1000
 */

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

int lastStoneWeight(int* stones, int stonesSize) {
    // we an use a max heap
    // we extract the top 2 stones in weight and perform a weight comparison
    // if both stones are destroyed do nothing
    // if stone y remains, calc new weight and add it back to the max heap
    // the answer should be the root of the maxHeap at the end when length of maxHeap is 1

    // edge cases
    if (stones == NULL) {
        return 0;
    }

    if (stonesSize == 1) {
        return stones[0];
    }

    // Make heap
    MaxHeap heap;
    heap.size = 0;
    heap.maxSize = stonesSize;

    int *heapArr = (int*) calloc (stonesSize, sizeof(int));
    heap.arr = heapArr;

    for (int i = 0; i < stonesSize; i++) {
        insert(&heap, stones[i]);

    }
    printHeap(&heap);

    while (heap.size > 1) {
        int y = extractMax(&heap); // y is the heaviest stone
        int x = extractMax(&heap);

        if (y > x) {
            y -= x;
            insert(&heap, y);
        }
    }

    int ans = heap.arr[0];

    if (heap.size == 0) {
        ans = 0;
    }


    free(heap.arr);
    return ans;
}