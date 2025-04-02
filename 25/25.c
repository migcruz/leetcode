/*
 * LeetCode Problem 25: Reverse Nodes in k-Group
 * Difficulty: Hard
 *
 * Problem Description:
 * Given the head of a linked list, reverse the nodes in groups of size 'k',
 * and return the modified linked list.
 *
 * Rules:
 * - 'k' is a positive integer and is less than or equal to the length of the linked list.
 * - If the number of nodes is not a multiple of 'k', the remaining nodes at the end should remain unchanged.
 * - The values in the nodes cannot be altered—only the nodes themselves may be rearranged.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 * Explanation: Nodes are reversed in pairs.
 *
 * Example 2:
 * Input: head = [1,2,3,4,5], k = 3
 * Output: [3,2,1,4,5]
 * Explanation: The first three nodes are reversed, but the last two remain unchanged.
 *
 * Constraints:
 * - The number of nodes in the list is 'n'.
 * - 1 <= k <= n <= 5000
 * - 0 <= Node.val <= 1000
 *
 * Follow-up:
 * - Can you solve the problem using O(1) extra memory space?
 */


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

 struct ListNode* reverseList(struct ListNode* head, int k, struct ListNode *lastNext) {

    struct ListNode* prev = lastNext;
    struct ListNode* current = head;
    struct ListNode* next = NULL;
    int i = 0;

    while (i != k) {
        next = current->next;  // Save next node
        current->next = prev;  // Reverse pointer
        prev = current;        // Move prev forward
        current = next;        // Move current forward
        i++;
    }
    return prev;  // return the head of the newely reversed sequence
    
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {

    //we can make an array of the linkedlist nodes and then do the swaps within this array in k chunks. This will be an O(N+N+N) = O(N) solution
    // first we traverse the linked list to get the size needed to allocate for the array, then we traverse it again to put the nodes into the array
    // then we traverse the array to do swaps.
    // This will also be O(N) space complexity

    // Instead let's try to do it in O(1) complexity. This means we cannot use arrays or other data structures. We only use variables like pointers
    // let's try reversing the linked lists in batches use the linked list reversal algo. We also need to find out the length of the linkedlist
    // We also need to find out how many groups of size K can fit in this length
    // since we are reversing within a linked list, we need to get the element after the last element to be reversed
    // if k = 1 then we return the linked list without modification
    // we will need 3 pointers. the current head of the original sequence (oldhead), the pointer after this sequence, and then the new head of the current sequence after reversal 

    int listSize = 0;
    int numK = 0;
    struct ListNode* ans = head;
    struct ListNode* temp = head;
    struct ListNode* lastNext = head;

    // edge case of k = 1
    if (k == 1) {
        return head;
    }
    //find out how many elements are in this linked list
    while (temp != NULL) {
        temp = temp->next;
        listSize++;
    }
    // this is how many groups of k can be reversed
    numK = listSize / k;

    // find the node after the last element to be reversed
    for (int i = 0; i < k; i++) {
        lastNext = lastNext->next; // also the head of the next sequence before reversal
    }
    ans = reverseList(head, k, lastNext);

    for (int i = 1; i < numK; i++) { // starts at 1 because we reversed it already once to get the new head
        temp = head; // save the old head
        head = lastNext; // update head to be the head of new sequence to be reversed
        for (int j = 0; j < k; j++) { // find the next node after the sequence
            lastNext = lastNext->next;
            if (lastNext == NULL) {
                break;
            }
        }
        struct ListNode *newHead = reverseList(head, k, lastNext); // iter is the new head of the reversed sequence

        temp->next = newHead; // make the old head of the previous sequence point to the new head of the reversed sequence
    }

    return ans;
    
}