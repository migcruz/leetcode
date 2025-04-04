/*
 * LeetCode Problem 124: Binary Tree Maximum Path Sum
 * Difficulty: Hard
 *
 * Problem Description:
 * Given the root of a binary tree, return the maximum path sum of any non-empty path.
 * A path consists of connected nodes, but does **not** need to pass through the root.
 *
 * Example 1:
 * Input: root = [1,2,3]
 * Output: 6
 * Explanation: The optimal path is 2 -> 1 -> 3 with sum 2 + 1 + 3 = 6.
 *
 * Example 2:
 * Input: root = [-10,9,20,null,null,15,7]
 * Output: 42
 * Explanation: The optimal path is 15 -> 20 -> 7 with sum 15 + 20 + 7 = 42.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [1, 3 * 10^4].
 * - -1000 <= Node.val <= 1000.
 *
 * Complexity:
 * - **Time Complexity:** O(N) (Each node is visited once)
 * - **Space Complexity:** O(H) (Recursive stack depth, H = height of tree)
 */
 
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int maxPathSumHelper(struct TreeNode *root, int *ans) {

    if (root == NULL) {

        return 0;
    }

    int sum = 0;
    int leftSum = maxPathSumHelper(root->left, ans);
    int rightSum = maxPathSumHelper(root->right, ans);

    // handle negative values
    if (rightSum < 0) {
        rightSum = 0; //treat as if they don't even exist
    }

    if (leftSum < 0) {
        leftSum = 0;
    }

    int localAns = leftSum + rightSum + root->val; // whole subtree

    *ans = (localAns > *ans) ? localAns : *ans;


    if (root->val + leftSum > root->val + rightSum) {
        return root->val + leftSum;
    }
    else {
        return root->val + rightSum;
    }
}


int maxPathSum(struct TreeNode* root) {

    // we will use DFS postordertraversal
    // when we get back to the root node of a subtree we will compare if the pathsum of the left or right subtree is greater and then we add that to the current root node of the subtree before
    // we recursively go up the tree
    // at every subtree, the maxpathsum is current + left + right store this in a global variable

    // at each node we will return the greater of current + left || current + right
    if (root == NULL) {
        return 0;
    }
    if (root->right == NULL && root->left == NULL) {
        return root->val;
    }

    int ans = -1001; // beyond the minimum range of ans

    maxPathSumHelper(root, &ans);

    return ans;
    
}