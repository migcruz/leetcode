/*
 * LeetCode Problem 92: Reverse Linked List II
 * Difficulty: Medium
 *
 * Given the head of a singly linked list and two integers left and right where left <= right,
 * reverse the nodes of the list from position left to position right, and return the reversed list.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], left = 2, right = 4
 * Output: [1,4,3,2,5]
 *
 * Example 2:
 * Input: head = [5], left = 1, right = 1
 * Output: [5]
 *
 * Constraints:
 *   The number of nodes in the list is n.
 *   1 <= n <= 500
 *   -500 <= Node.val <= 500
 *   1 <= left <= right <= n
 *
 * Follow up: Could you do it in one pass?
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

 struct ListNode *reverseList(struct ListNode *startNode, int countMax) {

    int count = 0;

    struct ListNode *current = startNode;
    struct ListNode *next = NULL;
    struct ListNode *prev = NULL;

    while (count <= countMax && countMax > 0) { //ignore if left == right
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    startNode->next = current;

    return prev; // we will assign this to be the next of the previous node before we started the reversal
}


struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {

    // use the reverse linked list function but we need to specify the node that the new tail of the reversed section will point to
    // in the standard linked list reversal function we assume we reverse the whole list so the left and right bounds are both NULL

    if (head == NULL) {
        return NULL;
    }

    struct ListNode *prev = NULL;
    struct ListNode *curr = head;
    int count = 1;
    int countMax = right - left;

    while (curr != NULL) {

        if (count == left && countMax > 0) {
            struct ListNode *temp = reverseList(curr, countMax);
            if (prev != NULL) {
                prev->next = temp;
            }
            else { // that means temp is the new head of the linked list
                head = temp;
            }
        }

        prev = curr;
        curr = curr->next;
        count++;
    }

    // print the linked list
    // curr = head;
    // while (curr != NULL) {
    //     printf("%d ", curr->val);
    //     curr = curr->next;
    // }
    // printf("\n");

    return head;

    // we can also just copy all the nodes to an array and swap the values in the array and then reconstruct the linked list
    
}