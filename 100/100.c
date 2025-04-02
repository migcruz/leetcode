/*
 * LeetCode Problem 100: Same Tree
 * Difficulty: Easy
 *
 * Problem Description:
 * Given the roots of two binary trees, p and q, determine if they are the same.
 *
 * Two binary trees are considered the same if they are structurally identical 
 * and all corresponding nodes have the same values.
 *
 * Example 1:
 * Input: p = [1,2,3], q = [1,2,3]
 * Output: true
 * Explanation: Both trees have the same structure and node values.
 *
 * Example 2:
 * Input: p = [1,2], q = [1,null,2]
 * Output: false
 * Explanation: The structure of the trees differs (one has a right child, the other does not).
 *
 * Example 3:
 * Input: p = [1,2,1], q = [1,1,2]
 * Output: false
 * Explanation: The values in the nodes differ.
 *
 * Constraints:
 * - The number of nodes in both trees is in the range [0, 100].
 * - -10^4 <= Node.val <= 10^4
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {

    // since both the height, balance, and values of each node in the trees need to be the same. We can just query every node for each tree and compare values.
    // getting the depth, diameter, and height are necessary but not sufficient characteristics
    // comparing the values of each node in both trees is both necessary and sufficient
    // we can use a traversal method and compare the values at each node

    // pre-order traversal is a DFS algo. We will chekc the current node first before checking the children nodes
    // check for NULL cases
    if (p == NULL && q == NULL) {
        return true;
    }
    else if (p == NULL || q == NULL) { // only p xor q will be NULL
        return false;
    }

    // check values of current node
    if (p->val != q->val) {
        return false;
    }

    // check values of children nodes
    if (!isSameTree(p->left, q->left)) {
        return false;
    }

    if (!isSameTree(p->right, q->right)) {
        return false;
    }

    return true;
}