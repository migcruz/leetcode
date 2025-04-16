/*
 * LeetCode Problem 215: Kth Largest Element in an Array
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an integer array `nums` and an integer `k`, return the kth largest element in the array.
 *
 * Note:
 * - The kth largest element refers to the element that would appear in position `k` from the end in a sorted array.
 * - It does not necessarily have to be distinct.
 * - Aim to solve the problem without sorting the entire array if possible.
 *
 * Examples:
 *
 * Example 1:
 *   Input: nums = [3,2,1,5,6,4], k = 2
 *   Output: 5
 *   Explanation: After sorting the array in descending order: [6, 5, 4, 3, 2, 1],
 *                the 2nd largest element is 5.
 *
 * Example 2:
 *   Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 *   Output: 4
 *   Explanation: After sorting the array in descending order: [6, 5, 5, 4, 3, 3, 2, 2, 1],
 *                the 4th largest element is 4.
 *
 * Constraints:
 *   - 1 <= k <= nums.length <= 10^5
 *   - -10^4 <= nums[i] <= 10^4
 */

typedef struct {
    int *heapArr;
    int size;
    int maxSize;
    
} minHeap;

void swap(int *a, int *b) {

    int temp = *a;
    *a = *b;
    *b = temp;

}

void insert(minHeap* heap, int val) {

    if (heap == NULL) {
        return;
    }

    if (heap->size == heap->maxSize) {
        // printf("Heap overflow!\n");
        return;
    }

    // Insert at the end
    (heap->size)++;
    int i = heap->size - 1;
    (heap->heapArr)[i] = val;

    // heapify up
    while (i != 0 && (heap->heapArr)[(i - 1) / 2] > (heap->heapArr)[i]) { // if parent is more, then swap
        swap(&(heap->heapArr)[(i - 1) / 2], &(heap->heapArr)[i]);
        i = (i - 1) / 2;
    }
}

void minHeapify(minHeap *heap, int index) {

    if (heap == NULL) {
        return;
    }

    // make left and right child nodes even if it is an array
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int smallest = index;

    // find out which child is bigger
    if (left < heap->size && (heap->heapArr)[left] < (heap->heapArr)[smallest]) {
        smallest = left;
    }

    if (right < heap->size && (heap->heapArr)[right] < (heap->heapArr)[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&(heap->heapArr)[index], &(heap->heapArr)[smallest]);
        minHeapify(heap, smallest);
    }

}

int extractMin (minHeap *heap) {
    if (heap == NULL || heap->size <= 0) {
        return -10001;
    }

    if (heap->size == 1) {
        (heap->size)--;
        return heap->heapArr[0];
    }

    // extract top element which is max
    int temp = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->size - 1];
    (heap->size)--;
    minHeapify(heap, 0); //reorder heap
    // printf("LOL %d\r\n", temp);
    return temp;

}

int peekTop(minHeap *heap) {

    return heap->heapArr[0];
}

void printHeap(minHeap *heap) {
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->heapArr[i]);
    printf("\n");
}
int findKthLargest(int* nums, int numsSize, int k) {

    // we'll make a max heap and return pop k times
    // OR 
    // we can make a min heap of size k

    if (nums == NULL) {
        return 0;
    }

    minHeap newHeap;
    newHeap.size = 0;
    newHeap.maxSize = k;

    int *newArr = (int*) calloc (k, sizeof(int));
    newHeap.heapArr = newArr;


    // insert elements
    for (int i = 0; i < numsSize; i++) {

        if (newHeap.size < newHeap.maxSize) {
            insert(&newHeap, nums[i]);
        }
        else { // need to compare
            int temp = peekTop(&newHeap);
            if (nums[i] > temp) {
                extractMin(&newHeap);
                insert(&newHeap, nums[i]);
            }
        }
    }

    int ans = peekTop(&newHeap);
    free(newHeap.heapArr);
    return ans;


    
}