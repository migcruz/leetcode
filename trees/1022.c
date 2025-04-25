/*
 * LeetCode Problem 1022: Sum of Root To Leaf Binary Numbers
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given the root of a binary tree where each node has a value 0 or 1.
 * Each root-to-leaf path represents a binary number starting with the most significant bit.
 *
 * For example, the path 0 -> 1 -> 1 -> 0 -> 1 represents the binary number 01101, which is 13.
 *
 * For all leaves in the tree, consider the numbers represented by the path from the root to that leaf.
 * Return the sum of these numbers.
 *
 * The test cases are generated so that the answer fits in a 32-bit integer.
 *
 * Examples:
 *
 * Example 1:
 * Input:  root = [1,0,1,0,1,0,1]
 * Output: 22
 * Explanation: 
 *   Paths:
 *     1->0->0 = 100 = 4
 *     1->0->1 = 101 = 5
 *     1->1->0 = 110 = 6
 *     1->1->1 = 111 = 7
 *   Total = 4 + 5 + 6 + 7 = 22
 *
 * Example 2:
 * Input:  root = [0]
 * Output: 0
 *
 * Constraints:
 *   The number of nodes in the tree is in the range [1, 1000].
 *   Node.val is either 0 or 1.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 void dfsPreOrder(struct TreeNode *root, int runningPathTotal, int *ans) {

    if (root == NULL) {
        return;
    }

    runningPathTotal = (runningPathTotal << 1) + root->val;

    dfsPreOrder(root->left, runningPathTotal, ans);
    dfsPreOrder(root->right, runningPathTotal, ans);

    if (root->left == NULL && root->right == NULL) { // only add to the answer at the leaf nodes
        printf("pathSum: %d\n", runningPathTotal);
        *ans += runningPathTotal;
    }

}
int sumRootToLeaf(struct TreeNode* root) {

    //we just need to do DFS preorder traversal
    // well pass down a running path total down to the children node, and we shift this total to the left depending on the depth, then we add the current Node's value and pass it down
    // if we hit a NULL node, then we add this pathtotal to the answer

    if (root == NULL) {
        return 0;
    }

    int ans = 0;

    dfsPreOrder (root, 0, &ans);

    return ans;
    
}