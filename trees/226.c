/*
 * LeetCode Problem 226: Invert Binary Tree
 * Difficulty: Easy
 *
 * Problem Description:
 * Given the root of a binary tree, invert the tree by swapping left and right 
 * children recursively, and return its root.
 *
 * Example 1:
 * Input: root = [4,2,7,1,3,6,9]
 * Output: [4,7,2,9,6,3,1]
 * Explanation: Left and right subtrees are swapped at every node.
 *
 * Example 2:
 * Input: root = [2,1,3]
 * Output: [2,3,1]
 * Explanation: Left and right children of node 2 are swapped.
 *
 * Example 3:
 * Input: root = []
 * Output: []
 * Explanation: An empty tree remains unchanged.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 100].
 * - -100 <= Node.val <= 100
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* invertTree(struct TreeNode* root) {

    // we need to swap the left and right children recursively

    if (root == NULL) {
        return NULL;
    } 

    struct TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    invertTree (root->left);
    invertTree (root->right);

    return root;
}