/*
 * LeetCode Problem 973: K Closest Points to Origin
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane
 * and an integer k, return the k closest points to the origin (0, 0).
 *
 * The distance between two points on the X-Y plane is the Euclidean distance:
 *   distance = sqrt((x1 - x2)^2 + (y1 - y2)^2)
 * Since we are only comparing distances, the square root can be omitted for optimization.
 *
 * You may return the answer in any order. The answer is guaranteed to be unique
 * (except for the order that it is in).
 *
 * Examples:
 *
 * Example 1:
 *   Input: points = [[1,3],[-2,2]], k = 1
 *   Output: [[-2,2]]
 *   Explanation:
 *     - Distance from (1, 3) to origin = sqrt(10)
 *     - Distance from (-2, 2) to origin = sqrt(8)
 *     - Since sqrt(8) < sqrt(10), we return [[-2,2]].
 *
 * Example 2:
 *   Input: points = [[3,3],[5,-1],[-2,4]], k = 2
 *   Output: [[3,3],[-2,4]]
 *   Explanation:
 *     - The two closest points to the origin are (3,3) and (-2,4).
 *     - The output order may vary (e.g., [[-2,4],[3,3]] is also valid).
 *
 * Constraints:
 *   - 1 <= k <= points.length <= 10^4
 *   - -10^4 <= xi, yi <= 10^4
 */

typedef struct {
    int **arr;
    int size;
    int maxSize;
} MinHeap;

// Function to swap two elements
void swap(int **a, int **b) { // we're swapping the subarray addresses
    int *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify down (used after deletion)
void minHeapify(MinHeap *heap, int index) {
    int left = 2 * index + 1; // left child
    int right = 2 * index + 2; // right child
    int smallest = index;
    
    // figure out which child has the smallest euclidean distance to the origin
    double euclidSmallest = sqrt( pow(heap->arr[smallest][1], 2) + pow(heap->arr[smallest][0], 2) );

    if (left < heap->size) {
        double euclidLeft = sqrt( pow(heap->arr[left][1], 2) + pow(heap->arr[left][0], 2) );
        if (euclidLeft < euclidSmallest) {
            smallest = left;
        }
    }
    euclidSmallest = sqrt( pow(heap->arr[smallest][1], 2) + pow(heap->arr[smallest][0], 2) ); // calc it again incase smallest changed

    if (right < heap->size) {
        double euclidRight = sqrt( pow(heap->arr[right][1], 2) + pow(heap->arr[right][0], 2) );
        if (euclidRight < euclidSmallest) {
            smallest = right;
        }
    }
    
    if (smallest != index) { // means index was NOT the smallest
        swap(&heap->arr[index], &heap->arr[smallest]);
        minHeapify(heap, smallest);
    }
}

// Function to insert an element into the MinHeap
void insert(MinHeap *heap, int *value) {
    if (heap->size == heap->maxSize) {
        printf("Heap overflow!\n");
        return;
    }

    // Insert at the end
    int *tempArr = (int*) calloc (2, sizeof(int));
    memcpy(tempArr, value, 2 * sizeof(int));
    (heap->size)++;
    int i = heap->size - 1;
    heap->arr[i] = tempArr;

    // Heapify up to maintain min heap property
    double euclidParent = sqrt( pow(heap->arr[(i - 1) / 2][1], 2) + pow(heap->arr[(i - 1) / 2][0], 2) );
    double euclidI = sqrt( pow(heap->arr[i][1], 2) + pow(heap->arr[i][0], 2) );

    while (i != 0 && euclidParent > euclidI) { // move element up by swapping with parent if parent is greater
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2; 
        euclidParent = sqrt( pow(heap->arr[(i - 1) / 2][1], 2) + pow(heap->arr[(i - 1) / 2][0], 2) ); //update euclidParent to be the parent of the new i value
        // no need to update euclidI because of the swap
    }
}

// Function to extract the minimum element (root) from MinHeap
int *extractMin(MinHeap *heap) {
    if (heap->size <= 0) // empty heap
        return NULL;
    if (heap->size == 1) { // only 1 element so no need to bubble down
        heap->size--;
        return heap->arr[0];
    }

    int *root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1]; // bring end of heap to become root
    // heap->arr[heap->size - 1] = NULL;
    heap->size--;
    minHeapify(heap, 0); // now we must rearrange the heap

    return root;
}

// Function to print the heap elements
void printHeap(MinHeap *heap) {
    for (int i = 0; i < heap->size; i++)
        printf("(%d, %d) ", heap->arr[i][0], heap->arr[i][1]);
    printf("\n");
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kClosest(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes) {

    // make a min heap and extract the top 3 coordinates
    // the trouble is that we need to store the euclidean distances (aka hypotenuse) for the min heap but we need to map them to the coordinates
    // that means we need to modify the minheap implementation when comparing values to calc the euclidean distances first between parent and child nodes
    // then we decide based on that to swap

    if (points == NULL) {
        *returnColumnSizes = NULL;
        *returnSize = 0;
        return NULL;
    }

    MinHeap heap;
    heap.size = 0;
    heap.maxSize = pointsSize;

    int **heapArr = (int**) calloc (heap.maxSize, sizeof(int*));
    heap.arr = heapArr;

    // fill in heapArr
    for (int i = 0; i < heap.maxSize; i++) {
        insert(&heap, points[i]);
    }

    // printHeap(&heap);

    //Now we extract k elements

    int **ans = (int**) malloc (sizeof(int*) * k);
    for (int i = 0; i < k; i++) {
        ans[i] = extractMin(&heap);
        // printf("(%d, %d)\n", ans[i][0], ans[i][1]);
    }

    int *returnColSizes = (int*) calloc (k, sizeof(int));
    for (int j = 0; j < k; j++) {
        returnColSizes[j] = 2;
    }
    // memset(returnColSizes, 2, k * sizeof(int)); // don't use memset because you're actually setting each byte to 2 and not each element in the array to integer 2

    *returnSize = k;
    *returnColumnSizes = returnColSizes;
    return ans;
    
    // *returnColumnSizes = NULL;
    // *returnSize = 0;
    // return NULL;
}