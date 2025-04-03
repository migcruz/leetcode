/*
 * LeetCode Problem 104: Maximum Depth of Binary Tree
 * Difficulty: Easy
 *
 * Problem Description:
 * Given the root of a binary tree, return its maximum depth.
 *
 * The maximum depth of a binary tree is the number of nodes along the longest 
 * path from the root down to the farthest leaf node.
 *
 * Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 3
 * Explanation: The longest path is from node 3 to node 7, passing through three nodes.
 *
 * Example 2:
 * Input: root = [1,null,2]
 * Output: 2
 * Explanation: The longest path contains two nodes (1 → 2).
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 10^4].
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

int maxDepth(struct TreeNode* root) {
    
    // we can keep counting the max depth by checking at each node its left and right children to see if they're NULL, if not, then increase the counter

    int rightDepth = 0;
    int leftDepth = 0;
    int depth = 0;

    if (root == NULL) {
        return 0;
    }
    depth++; // the current node is valid so add 1 depth automatically

    // find the depth of the children recursively
    leftDepth = maxDepth(root->left);
    rightDepth = maxDepth(root->right);

    if (leftDepth > rightDepth) {
        depth += leftDepth;
    }
    else {
        depth += rightDepth;
    }

    return depth;
    
}