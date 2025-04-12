/*
 * LeetCode Problem 382: Linked List Random Node
 * Difficulty: Medium
 *
 * Problem Description:
 * Given a singly linked list, implement a solution that returns a random node's value 
 * such that each node has an equal probability of being selected.
 *
 * Implement the Solution class:
 * - Solution(ListNode* head): Initializes the object with the head of the linked list.
 * - int getRandom(): Returns a random node's value. Each node must be equally likely to be chosen.
 *
 * Example:
 * Input:
 * ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
 * [[[1, 2, 3]], [], [], [], [], []]
 *
 * Output:
 * [null, 1, 3, 2, 2, 3]
 *
 * Explanation:
 * Solution solution = new Solution([1, 2, 3]);
 * solution.getRandom(); // returns 1
 * solution.getRandom(); // returns 3
 * solution.getRandom(); // returns 2
 * solution.getRandom(); // returns 2
 * solution.getRandom(); // returns 3
 * // Each value (1, 2, 3) should be returned with approximately equal probability.
 *
 * Constraints:
 * - The number of nodes in the list is in the range [1, 10^4]
 * - -10^4 <= Node.val <= 10^4
 * - At most 10^4 calls will be made to getRandom()
 *
 * Follow-up:
 * - What if the linked list is extremely large and its length is unknown?
 * - Can you solve it efficiently without using extra space?
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

 int getRandomIndex(int n) {
    return rand() % n; // Generates a number between 0 and n-1
}

typedef struct {

    struct ListNode *head;
    int listSize;
    
} Solution;


Solution* solutionCreate(struct ListNode* head) {

    Solution *newSolution = (Solution*) malloc (sizeof(Solution));
    newSolution->head = head;

    //find out how many elements in the list
    int count = 0;

    while (head != NULL) {
        head = head->next;
        count++;
    }

    newSolution->listSize = count;


    return newSolution;
    
}

int solutionGetRandom(Solution* obj) {

    // let's use the two pass approach because the online judge (OJ) doesn't seem to pass the reservoir sampling approach for generating random numbers
    int index = getRandomIndex(obj->listSize);
    struct ListNode *temp = obj->head;
    int count = 0;

    while (temp != NULL) {

        if (count == index) {
            return temp->val;
        }
        temp = temp->next;
        count++;
    }

    return temp->val;
    // // this is the reservoir sampling method where we don't need to know the size of the linked list
    // struct ListNode* result = obj->head;
    // struct ListNode* current = obj->head;
    // int index = 1;
    // srand(time(NULL)); // Seed RNG

    // while (current != NULL) {
    //     if (rand() % index == 0) { // Pick current node with probability 1/index
    //         result = current;
    //     }
    //     current = current->next;
    //     index++;
    // }

    // return result->val; // Randomly selected node

}

void solutionFree(Solution* obj) {

    struct ListNode *iter = obj->head;

    while (iter != NULL) {

        struct ListNode *temp = iter;

        iter = iter->next;

        free(temp); 
    }

    free(obj);
    
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(head);
 * int param_1 = solutionGetRandom(obj);
 
 * solutionFree(obj);
*/

// TIPS
// Traversing the list twice isn't strictly necessary to guarantee an equally random selection, but it can be useful in some approaches. Here’s how different methods ensure fairness:
// 1. Reservoir Sampling (Single Pass)
// - This method guarantees equal probability without needing to traverse twice.
// - At each node, pick it with probability 1/i, ensuring every node has an equal chance by the end.

// 2. Two-Pass Approach
// - First pass: Count the total number of nodes (n).
// - Second pass: Generate a random index between 0 and n-1, then traverse again to pick that node.

// Why It Works?
// ✔ Every index has an equal probability of being chosen (1/n).
// ✔ It simplifies random selection when n is known (but requires two traversals).
// ✔ The two-pass method is conceptually simpler but may be less efficient compared to reservoir sampling.

