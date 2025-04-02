/*
 * LeetCode Problem 141: Linked List Cycle
 * Difficulty: Easy
 *
 * Problem Description:
 * Given the head of a linked list, determine if the linked list has a cycle.
 *
 * A cycle exists if a node in the list can be reached again by continuously 
 * following the 'next' pointer. Internally, 'pos' denotes the index of the 
 * node that the tail's next pointer connects to. However, 'pos' is not 
 * passed as a parameter.
 *
 * Return 'true' if there is a cycle; otherwise, return 'false'.
 *
 * Example
 
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 bool hasCycle(struct ListNode *head) {

    // we'll use Floyd's cycle detection algorithm aka tortoise and hare
    // this is O(N) time complexity and O(1) space complexity

    // we can improve speed by increasing space complexity. We save every index that we have traveresed in the linked list. If we visit one again, then a cycle is detected.
    // this way we dont need to wait for the tortoise and hare to meet up.
    

    struct ListNode *tortoise = head;
    struct ListNode *hare = head;

    // edge cases
    if (head == NULL) {
        return false;
    }

    if (head->next == NULL) {
        return false;
    }

    while (tortoise != NULL && hare != NULL) {

        tortoise = tortoise->next;

        if (hare->next != NULL) { // we need this because hare can be accessing a member of a NULL ptr
            hare = (hare->next)->next;
        }
        else {
            hare = hare->next; //just in case the hare is at the end of the linked list
        }

        if (tortoise == hare) { // cycle detected
            return true;
        }

    }

    return false;
    
}