/*
 * LeetCode Problem 543: Diameter of Binary Tree
 * Difficulty: Easy
 *
 * Problem Description:
 * Given the root of a binary tree, return the length of its diameter.
 *
 * The diameter of a binary tree is defined as the longest path between 
 * any two nodes in the tree. This path may or may not pass through the root.
 *
 * The length of a path is represented by the number of edges between nodes.
 *
 * Example 1:
 * Input: root = [1,2,3,4,5]
 * Output: 3
 * Explanation: The longest path is either [4 → 2 → 1 → 3] or [5 → 2 → 1 → 3], 
 * and its length is 3 edges.
 *
 * Example 2:
 * Input: root = [1,2]
 * Output: 1
 * Explanation: The longest path consists of one edge connecting nodes 1 and 2.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [1, 10^4].
 * - -100 <= Node.val <= 100
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

 int ans = 0;

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
 
     ans = (leftDepth + rightDepth > ans) ? leftDepth + rightDepth : ans;
 
     return depth; // minus because we are counting edges not nodes
     
 }
 
 int diameterOfBinaryTree(struct TreeNode* root) {
 
     // find the depth of each of the left and right children and add them together
     // if this sum is larger than current sum, update the sum.
     
     ans = 0; // need to reset the global variable for every test case
     if (root == NULL) {
         return 0;
     }
 
     int rightDepth = 0;
     int leftDepth = 0;
 
     leftDepth = maxDepth(root->left);
     rightDepth = maxDepth(root->right);
 
     ans = (leftDepth + rightDepth > ans) ? leftDepth + rightDepth : ans;
 
     return ans;
 
     
 }