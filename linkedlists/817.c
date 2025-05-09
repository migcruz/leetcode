/*
 * LeetCode Problem 817: Linked List Components
 * Difficulty: Medium
 *
 * You are given the head of a linked list containing unique integer values and an integer array nums
 * that is a subset of the linked list values.
 *
 * Return the number of connected components in nums where two values are connected if they appear
 * consecutively in the linked list.
 *
 * Example 1:
 * Input: head = [0,1,2,3], nums = [0,1,3]
 * Output: 2
 * Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected components.
 *
 * Example 2:
 * Input: head = [0,1,2,3,4], nums = [0,3,1,4]
 * Output: 2
 * Explanation: 0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.
 *
 * Constraints:
 *   The number of nodes in the linked list is n.
 *   1 <= n <= 10^4
 *   0 <= Node.val < n
 *   All the values Node.val are unique.
 *   1 <= nums.length <= n
 *   0 <= nums[i] < n
 *   All the values of nums are unique.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
int numComponents(struct ListNode* head, int* nums, int numsSize) {

    // confusing problem, just count each time you finish a component AND if the end of that component exists in nums
    if (head == NULL || nums == NULL) {
        return 0;
    }

    bool numsDict[10000] = {false};
    for (int i = 0; i < numsSize; i++) {
        numsDict[nums[i]] = true;
    }

    int ans = 0;

    struct ListNode *temp = head;
    while (temp != NULL) {
        if (numsDict[temp->val] &&
            (temp->next == NULL || !numsDict[temp->next->val])) { // means the next node is NOT in nums so we're at the end of a component
            ans++;
        }
        // printf("%d\n", temp->val);
        temp = temp->next;
    }
    return ans;
}