/*
 * LeetCode Problem 703: Kth Largest Element in a Stream
 * Difficulty: Easy
 *
 * Problem Description:
 * You are part of a university admissions office and need to keep track of the 
 * kth highest test score from applicants in real-time. This helps determine 
 * cut-off marks for interviews and admissions dynamically as new applicants 
 * submit their scores.
 * 
 * You are tasked to implement a class that maintains a stream of integers and 
 * returns the kth largest element after each insertion.
 * 
 * Implement the KthLargest class:
 *   - KthLargest(int k, int[] nums): Initializes the object with the integer k 
 *     and the stream of integers nums.
 *   - int add(int val): Adds a new value val to the stream and returns the 
 *     kth largest element in the stream so far.
 * 
 * Examples:
 * 
 * Example 1:
 *   Input: 
 *     ["KthLargest", "add", "add", "add", "add", "add"]
 *     [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
 *   Output:
 *     [null, 4, 5, 5, 8, 8]
 *   Explanation:
 *     KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
 *     kthLargest.add(3);  // returns 4
 *     kthLargest.add(5);  // returns 5
 *     kthLargest.add(10); // returns 5
 *     kthLargest.add(9);  // returns 8
 *     kthLargest.add(4);  // returns 8
 *
 * Example 2:
 *   Input:
 *     ["KthLargest", "add", "add", "add", "add"]
 *     [[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]
 *   Output:
 *     [null, 7, 7, 7, 8]
 *
 * Constraints:
 *   - 0 <= nums.length <= 10^4
 *   - 1 <= k <= nums.length + 1
 *   - -10^4 <= nums[i], val <= 10^4
 *   - At most 10^4 calls will be made to the add() function.
 */

typedef struct {
    int *heapArr;
    int size;
    int maxSize;
    
} KthLargest;

void swap(int *a, int *b) {

    int temp = *a;
    *a = *b;
    *b = temp;

}

void insert(KthLargest* obj, int val) {

    if (obj == NULL) {
        return;
    }

    if (obj->size == obj->maxSize) {
        // printf("Heap overflow!\n");
        return;
    }

    // Insert at the end
    (obj->size)++;
    int i = obj->size - 1;
    (obj->heapArr)[i] = val;

    // heapify up
    while (i != 0 && (obj->heapArr)[(i - 1) / 2] > (obj->heapArr)[i]) { // if parent is more, then swap
        swap(&(obj->heapArr)[(i - 1) / 2], &(obj->heapArr)[i]);
        i = (i - 1) / 2;
    }
}

void minHeapify(KthLargest *obj, int index) {

    if (obj == NULL) {
        return;
    }

    // make left and right child nodes even if it is an array
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int smallest = index;

    // find out which child is bigger
    if (left < obj->size && (obj->heapArr)[left] < (obj->heapArr)[smallest]) {
        smallest = left;
    }

    if (right < obj->size && (obj->heapArr)[right] < (obj->heapArr)[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&(obj->heapArr)[index], &(obj->heapArr)[smallest]);
        minHeapify(obj, smallest);
    }

}

int extractMin (KthLargest *obj) {
    if (obj == NULL || obj->size <= 0) {
        return -10001;
    }

    if (obj->size == 1) {
        (obj->size)--;
        return obj->heapArr[0];
    }

    // extract top element which is max
    int temp = obj->heapArr[0];
    obj->heapArr[0] = obj->heapArr[obj->size - 1];
    (obj->size)--;
    minHeapify(obj, 0); //reorder heap
    // printf("LOL %d\r\n", temp);
    return temp;

}

int peekTop(KthLargest *obj) {

    return obj->heapArr[0];
}

void printHeap(KthLargest *heap) {
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->heapArr[i]);
    printf("\n");
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {

    // we can make a max heap
    // we will pop the top k elements, the kth element's value gets returned and then they get put back into the heap
    // max size will be 10,000 elements

    // actually the above is wrong. We should use a min heap of size k, if any new value is less than the top of minheap, ignore it, 
    // if its higher, extract the root and insert the new val

    // initialize heap
    KthLargest *newHeap = (KthLargest*) malloc (sizeof(KthLargest));
    newHeap->size = 0;
    newHeap->maxSize = k;
    int *newArr = (int*) calloc (newHeap->maxSize, sizeof(int));
    newHeap->heapArr = newArr;

    //fill in heap
    for (int i = 0; i < numsSize; i++) {

        if (i >= k) { //now we might have to kick the root out
            int temp = peekTop(newHeap);
            if (nums[i] > temp) {
                extractMin(newHeap);
                insert(newHeap, nums[i]);
            }
        }
        insert(newHeap, nums[i]);
    }
    
    // printHeap(newHeap);
    return newHeap;
    
}

int kthLargestAdd(KthLargest* obj, int val) {

    if (obj == NULL) {
        return -10001;
    }

    int ret = -10001;

    // Handles case if the initial list is empty
    if (obj->size < obj->maxSize) {
        insert(obj, val);
    }
    else {
        int temp = peekTop(obj);
        if (val > temp) {
            extractMin(obj);
            insert(obj, val);
        }
    }

    ret = peekTop(obj);

    // Max heap implementation that hits TLE 

    // int count = 0;
    // int ret = -10001;
    // insert(obj, val);

    // // now we need to extract the kth value
    // int tempArr[10000] = {0};

    // for (count = 0; count < obj->k; count++) {
    //     int temp = extractMax(obj);
    //     // printf("LOL %d\r\n", temp);
    //     tempArr[count] = temp;
    // }
    // ret = tempArr[count - 1]; // - 1 because we had to increment count before leaving for loop
    // // printf("KEK %d, k: %d\r\n", ret, obj->k);

    // //reinsert the elements
    // for (int i = 0; i < count; i++) {
    //     insert(obj, tempArr[i]);
    // }

    return ret;
   
}

void kthLargestFree(KthLargest* obj) {
    free(obj->heapArr);
    free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/