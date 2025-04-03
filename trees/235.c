/*
 * LeetCode Problem 235: Lowest Common Ancestor of a Binary Search Tree
 * Difficulty: Medium
 *
 * Problem Description:
 * Given the root of a Binary Search Tree (BST) and two nodes, p and q, 
 * determine the Lowest Common Ancestor (LCA) of these nodes.
 *
 * Definition:
 * The LCA of two nodes p and q is the lowest node in the BST that has both p and q 
 * as descendants. A node is allowed to be a descendant of itself.
 *
 * Example 1:
 * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
 * Output: 6
 * Explanation: The LCA of nodes 2 and 8 is 6.
 *
 * Example 2:
 * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
 * Output: 2
 * Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself.
 *
 * Example 3:
 * Input: root = [2,1], p = 2, q = 1
 * Output: 2
 * Explanation: The LCA of nodes 2 and 1 is 2.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [2, 10^5].
 * - -10^9 <= Node.val <= 10^9.
 * - All Node values are unique.
 * - p != q, and both p and q exist in the BST.
 *
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {

    // since this is a BST where values of left < root < right, we can use to comppare p and q to left and right
    // if both p and q are greater than current, then search in the right
    // if both p and q are smaller than current, then search in the left
    // if 1 of p or q is less than current and the other is greater, then the current node is the LCA

    // by defualt let's assume the current node is the LCA
    struct TreeNode *temp = root;

    //edge cases
    if (root == NULL) {
        return NULL;
    }
    
    if (p->val > root->val && q->val > root->val) {
        temp = lowestCommonAncestor(root->right, p, q);
    }
    else if (p->val < root->val && q->val < root->val) {
        temp = lowestCommonAncestor(root->left, p, q);
    }

    return temp;
    
}