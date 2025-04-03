/*
 * LeetCode Problem 110: Balanced Binary Tree
 * Difficulty: Easy
 *
 * Problem Description:
 * Given the root of a binary tree, determine if the tree is balanced.
 *
 * A binary tree is considered balanced if the height difference between 
 * its left and right subtrees is at most 1 for every node.
 *
 * Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: true
 * Explanation: The tree maintains a balanced structure.
 *
 * Example 2:
 * Input: root = [1,2,2,3,3,null,null,4,4]
 * Output: false
 * Explanation: The left subtree has greater depth than the right subtree, 
 * exceeding the allowed height difference of 1.
 *
 * Example 3:
 * Input: root = []
 * Output: true
 * Explanation: An empty tree is considered balanced.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 5000].
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

bool ans = true;
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

    if (abs(leftDepth - rightDepth) > 1) {
        ans = false;
    }

    return depth;
     
}
 
bool isBalanced(struct TreeNode* root) {
 
    //find the maxDepth of left and right, if the difference in the depth is greater than 1, the tree is unbalanced so return false, otherwise return true
 
    ans = true;
    if (root == NULL) {
        return true;
      }

    int rightDepth = 0;
    int leftDepth = 0;

    leftDepth = maxDepth(root->left);
    rightDepth = maxDepth(root->right);

    if (abs(leftDepth - rightDepth) > 1) {
        ans = false;
    }

    return ans;
 
     
}