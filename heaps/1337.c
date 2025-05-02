/*
 * LeetCode Problem 1337: The K Weakest Rows in a Matrix
 * Difficulty: Easy
 *
 * You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing civilians). 
 * The soldiers are positioned in front of the civilians. That is, all the 1's will appear to the left of all the 0's in each row.
 *
 * A row i is weaker than a row j if one of the following is true:
 *   - The number of soldiers in row i is less than the number of soldiers in row j.
 *   - Both rows have the same number of soldiers and i < j.
 *
 * Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.
 *
 * Example 1:
 * Input: mat = [[1,1,0,0,0],
 *               [1,1,1,1,0],
 *               [1,0,0,0,0],
 *               [1,1,0,0,0],
 *               [1,1,1,1,1]], k = 3
 * Output: [2,0,3]
 *
 * Example 2:
 * Input: mat = [[1,0,0,0],
 *               [1,1,1,1],
 *               [1,0,0,0],
 *               [1,0,0,0]], k = 2
 * Output: [0,2]
 *
 * Constraints:
 *   - m == mat.length
 *   - n == mat[i].length
 *   - 2 <= n, m <= 100
 *   - 1 <= k <= m
 *   - matrix[i][j] is either 0 or 1
 */

typedef struct minHeap {
    int size;
    int maxSize;
    int heapArr[100]; // stores indexes of mat
} minHeap;

typedef struct maxHeap {
    int size;
    int maxSize;
    int heapArr[100]; // stores indexes of mat
} maxHeap;

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(minHeap *heap, int index, int soldiers[]) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int smallest = index;

    // find out which child is bigger
    if (left < heap->size && soldiers[heap->heapArr[left]] < soldiers[heap->heapArr[smallest]]) {
        smallest = left;
    }
    if (right < heap->size && soldiers[heap->heapArr[right]] < soldiers[heap->heapArr[smallest]]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&(heap->heapArr[smallest]), &(heap->heapArr[index]));
        minHeapify(heap, smallest, soldiers); // push it down further recursively
    }
}

void maxHeapify(maxHeap *heap, int index, int soldiers[]) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int biggest = index;

    // find out which child is bigger
    if (left < heap->size) {
        if (soldiers[heap->heapArr[left]] > soldiers[heap->heapArr[biggest]]) { // if the index at left has more soldiers, swap no matter what
            biggest = left;
        }
        else if (soldiers[heap->heapArr[left]] == soldiers[heap->heapArr[biggest]] && // if the index at left has same soldiers as parent, only swap if the index at left is greater
                 heap->heapArr[left] > heap->heapArr[biggest]) {
            biggest = left;
        }
    }
    if (right < heap->size) {
        if (soldiers[heap->heapArr[right]] > soldiers[heap->heapArr[biggest]]) { // if the index at right has more soldiers, swap no matter what
            biggest = right;
        }
        else if (soldiers[heap->heapArr[right]] == soldiers[heap->heapArr[biggest]] && // if the index at right has same soldiers as parent, only swap if the index at right is greater
                 heap->heapArr[right] > heap->heapArr[biggest]) {
            biggest = right;
        }
    }

    if (biggest != index) {
        swap(&(heap->heapArr[biggest]), &(heap->heapArr[index]));
        maxHeapify(heap, biggest, soldiers); // push it down further recursively
    }
}

int extractMin(minHeap *heap, int soldiers[]) {
    if (heap == NULL || heap->size <= 0) {
        return -1;
    }

    if (heap->size == 1) {
        heap->size -= 1;
        return heap->heapArr[0];
    }

    // take the last element and put it at the top of the heap
    int temp = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->size - 1];
    heap->size -= 1;
    minHeapify(heap, 0, soldiers);

    return temp;
}

int extractMax(maxHeap *heap, int soldiers[]) {
    if (heap == NULL || heap->size <= 0) {
        return -1;
    }

    if (heap->size == 1) {
        heap->size -= 1;
        return heap->heapArr[0];
    }

    // take the last element and put it at the top of the heap
    int temp = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->size - 1];
    heap->size -= 1;
    maxHeapify(heap, 0, soldiers);

    return temp;
}

void insertMin(minHeap *heap, int val, int soldiers[]) {

    if (heap == NULL) {
        return;
    }
    if (heap->size == heap->maxSize) {
        return;
    }
    
    // insert at the end
    heap->heapArr[heap->size] = val;
    int i = heap->size;
    (heap->size)++;

    // heapify up
    while (i != 0 && soldiers[heap->heapArr[(i - 1) / 2]] > soldiers[heap->heapArr[i]]) {
        swap(&(heap->heapArr[(i - 1) / 2]), &(heap->heapArr[i]));
        i = (i - 1) / 2;
    }
}

void insertMax(maxHeap *heap, int val, int soldiers[]) {

    if (heap == NULL) {
        return;
    }
    if (heap->size == heap->maxSize) {
        return;
    }
    
    // insert at the end
    heap->heapArr[heap->size] = val;
    int i = heap->size;
    (heap->size)++;

    // heapify up
    while (i != 0) {

        if (soldiers[heap->heapArr[(i - 1) / 2]] < soldiers[heap->heapArr[i]]) { // if the index at i has more soldiers, swap no matter what
            swap(&(heap->heapArr[(i - 1) / 2]), &(heap->heapArr[i]));
            i = (i - 1) / 2;
        }
        else if (soldiers[heap->heapArr[(i - 1) / 2]] == soldiers[heap->heapArr[i]] && // if the index at i has same soldiers as parent, only swap if the index at i is greater
                 heap->heapArr[(i - 1) / 2] < heap->heapArr[i]) {
            swap(&(heap->heapArr[(i - 1) / 2]), &(heap->heapArr[i]));
            i = (i - 1) / 2;
        }
        else {
            break;
        }
    }
}

void printHeapMin(minHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->heapArr[i]);
    }
    printf("\n");
}

void printHeapMax(maxHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->heapArr[i]);
    }
    printf("\n");
}

int peekTopMax(maxHeap *heap) {
    if (heap == NULL) {
        return -1;
    }
    return heap->heapArr[0];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* kWeakestRows(int** mat, int matSize, int* matColSize, int k, int* returnSize) {

    // well use a min heap and enter every row with the weakest row being at the top
    // we will use an array of size matSize to store row nodes that will contain the index and number of 1s in that row
    // the weakest rows will be at the top, we pop the top and if there exists rows that are stronger than it after we add it to answer array

    // we need a second heap of size k, we will use a maxHeap, we will store answers from the original heap into this maxHeap, when it reaches size k
    // we will comapre the new entry to the top to see if it is weaker (if the soldiers[new] <= soldiers[top] && new <= top)
    // we will then fill the answer array in reverse order i.e ans[k-1] = maxHeap[0]

    // the first minHeap is not necessary as we can just sort the array of rows based on numbier of soldiers but that is O(N log N) as oppose d to using a min heap which is O(N)

    minHeap newHeap = {
        .size = 0,
        .maxSize = 100,
        .heapArr = {101},
    };

    maxHeap ansHeap = {
        .size = 0,
        .maxSize = k,
        .heapArr = {101},
    };

    int soldiers[100] = {0};

    int *ans = (int*) calloc (k, sizeof(int));
    int ansSize = 0;

    // count how many soldiers are in each row
    for (int i = 0; i < matSize; i++) {
        int numSoldiers = 0;
        for (int j = 0; j < matColSize[0]; j++) {
            if (mat[i][j] == 1) {
                numSoldiers++;
            }
        }
        soldiers[i] = numSoldiers;
    }

    // insert row to heap and the row with the least soldiers should be at the top of the heap;
    for (int i = 0; i < matSize; i++) {
        insertMin(&newHeap, i, soldiers);
    }

    // printHeapMin(&newHeap); // sanity check

    // Insert elements into maxHeap
    while (newHeap.size > 0) {
        int newAns = extractMin(&newHeap, soldiers);
        if (ansHeap.size < ansHeap.maxSize) {
            insertMax(&ansHeap, newAns, soldiers);
        }
        else {
            int top = peekTopMax(&ansHeap);

            if (soldiers[newAns] <= soldiers[top] && newAns <= top) {
                int deleteTop = extractMax(&ansHeap, soldiers);
                insertMax(&ansHeap, newAns, soldiers);
            }
        }
        // printf("newHeap: ");
        // printHeapMin(&newHeap); // sanity check

        // printf("ansHeap: ");
        // printHeapMax(&ansHeap); // sanity check
    }

    // printHeapMax(&ansHeap);

    // Now fill in the answer array
    int ansIndex = k - 1;
    while (ansHeap.size > 0) {
        int temp = extractMax(&ansHeap, soldiers);
        ans[ansIndex] = temp;
        ansIndex--;
    }

    *returnSize = k;
    return ans;
}