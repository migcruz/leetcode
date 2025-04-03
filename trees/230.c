/*
 * LeetCode Problem 230: Kth Smallest Element in a BST
 * Difficulty: Medium
 *
 * Problem Description:
 * Given the root of a binary search tree (BST) and an integer k,
 * return the kth smallest value (1-indexed) among all the values of the nodes in the tree.
 *
 * Example 1:
 * Input: root = [3,1,4,null,2], k = 1
 * Output: 1
 *
 * Example 2:
 * Input: root = [5,3,6,2,4,null,null,1], k = 3
 * Output: 3
 *
 * Constraints:
 * - The number of nodes in the tree is n, where 1 <= k <= n <= 10^4.
 * - 0 <= Node.val <= 10^4.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 void findKthSmallest(struct TreeNode* root, int k, int *counter, int *ans) {

    if (root == NULL) {
        return;
    }

    // check left node
    findKthSmallest(root->left, k, counter, ans);

    //update the counter by inputting the current node value
    (*counter)++;
    if ( (*counter) == k) {
        *ans = root->val;
        return;
    }

    //check right node after update prev to the current node
    findKthSmallest(root->right, k, counter, ans);

    return;

}

int kthSmallest(struct TreeNode* root, int k) {

    // we will use DFS in order traversal to traverse the BST from smallest to largest values
    // each time we are at the current node in the in order traversal recursive algo, we can increase a coutner by 1. If this counter = k, then that is the kth smallest element
    // this way we do not need an additional data structure to keep track of the values in the BST in a linear order

    if (root == NULL) {
        return 0;
    }
    int counter = 0;
    int ans = 0;

    findKthSmallest(root, k, &counter, &ans);

    return ans; 

    
}