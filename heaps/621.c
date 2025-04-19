/*
 * LeetCode Problem 621: Task Scheduler
 * Difficulty: Medium
 *
 * Problem Description:
 * You are given an array of CPU tasks, each labeled with a letter from A to Z, 
 * and a non-negative integer n. Each CPU interval can either be idle or run one task.
 * 
 * Tasks may be completed in any order, but the same task must be separated 
 * by at least `n` intervals from its previous execution.
 * 
 * Return the minimum number of CPU intervals required to finish all tasks.
 *
 * Examples:
 *
 * Example 1:
 *   Input: tasks = ["A","A","A","B","B","B"], n = 2
 *   Output: 8
 *   Explanation: One valid sequence is:
 *                A -> B -> idle -> A -> B -> idle -> A -> B
 *
 * Example 2:
 *   Input: tasks = ["A","C","A","B","D","B"], n = 1
 *   Output: 6
 *   Explanation: One valid sequence is:
 *                A -> B -> C -> D -> A -> B
 *
 * Example 3:
 *   Input: tasks = ["A","A","A", "B","B","B"], n = 3
 *   Output: 10
 *   Explanation: One valid sequence is:
 *                A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B
 *
 * Constraints:
 *   - 1 <= tasks.length <= 10^4
 *   - tasks[i] is an uppercase English letter
 *   - 0 <= n <= 100
 */

struct Node {
    char task;
    int count;
};

typedef struct {
    struct Node *heapArr;
    int size;
    int maxSize;
} maxHeap;

// Swaps two heap elements
void swap(struct Node *a, struct Node *b) {
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify down (maintains max-heap property)
void heapifyDown(maxHeap *heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->heapArr[left].count > heap->heapArr[largest].count) {
        largest = left;
    }
    if (right < heap->size && heap->heapArr[right].count > heap->heapArr[largest].count) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap->heapArr[i], &heap->heapArr[largest]);
        heapifyDown(heap, largest);
    }
}

// Insert a task into the max heap
void insert(maxHeap *heap, char task, int count) {

    if (heap == NULL) {
        return;
    }

    if (heap->size >= heap->maxSize) {
        return;
    }

    // Insert at the end
    struct Node newTask;
    newTask.task = task;
    newTask.count = count;

    (heap->size)++;
    int i = heap->size - 1;
    (heap->heapArr)[i] = newTask;

    // heapify up based on highest priority (tasks with the most number of elements)
    while (i != 0 && heap->heapArr[(i - 1) / 2].count < heap->heapArr[i].count) { // parents count is less so swap
        swap(&heap->heapArr[(i - 1) / 2], &heap->heapArr[i]);
        i = (i - 1) / 2;
    }
}

// Extract the max task from the heap
struct Node extractMax(maxHeap *heap) {

    if (heap->size == 0) {
        return (struct Node){'\0', 0}; // NULL node
    }

    struct Node maxTask = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);

    return maxTask;
}

// Task Scheduler Function
int leastInterval(char* tasks, int tasksSize, int n) {

    // we can make a max heap that acts as a priority queue
    // we can prioritize tasks using a frequency array
    // we can also use a timeoutArr to keep track of the timeout on each task

    // for example the first A that gets put into heap has a prio of 0 and we increment the freqArr[0] by 1, the next A that gets processed gets a prio 1 and we repeat
    if (tasks == NULL) {
        return 0;
    }

    int freq[26] = {0};

    // Count task frequencies
    for (int i = 0; i < tasksSize; i++) {
        freq[tasks[i] - 'A']++;
    }

    // Initialize max heap
    maxHeap taskHeap;
    taskHeap.size = 0;
    taskHeap.maxSize = 26;
    taskHeap.heapArr = (struct Node*) malloc(26 * sizeof(struct Node)); //

    if (!taskHeap.heapArr) return 0;

    // Insert tasks into heap
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            insert(&taskHeap, i + 'A', freq[i]);
        }
    }

    int ans = 0;

    // How Idle Cycles Are Accounted For
    // - Processing a batch of tasks for up to n + 1 cycles
    //      - You extract the maximum task frequency and schedule up to n + 1 tasks.
    //      - If enough tasks exist to fill all slots, there's no idle time.

    // - When tasks run out before filling n + 1 cycles
    //      - If fewer tasks are available than the required cooldown (n), some slots remain empty, meaning we must idle before repeating the same tasks.
    //      - The formula:  ans += (taskHeap.size > 0) ? n + 1 : cycle;  ensures that full cycles (n + 1) are counted when tasks still remain, 
    //          and only the actual work (cycle) is counted when finishing up


    while (taskHeap.size > 0) {
        int cycle = 0;
        struct Node cooldownQueue[n + 1]; // Cooldown queue
        int queueSize = 0;

        for (int i = 0; i <= n; i++) {
            if (taskHeap.size == 0) {
                break;
            }
            
            struct Node currTask = extractMax(&taskHeap);
            currTask.count--;

            if (currTask.count > 0) {
                cooldownQueue[queueSize] = currTask; // Store task for reinsertion later
                queueSize++;
            }

            cycle++;
        }

        // Reinsert tasks in queue after cooldown
        for (int i = 0; i < queueSize; i++) {
            insert(&taskHeap, cooldownQueue[i].task, cooldownQueue[i].count);
        }

        ans += (taskHeap.size > 0) ? n + 1 : cycle;
    }

    free(taskHeap.heapArr);
    return ans;
}
