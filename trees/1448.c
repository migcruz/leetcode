/*
 * 1448. Count Good Nodes in Binary Tree
 * Difficulty: Medium
 *
 * Given the root of a binary tree, a node X in the tree is named "good"
 * if in the path from the root to X, there are no nodes with a value 
 * greater than X.
 *
 * Return the number of good nodes in the binary tree.
 *
 * Example 1:
 * Input:  root = [3,1,4,3,null,1,5]
 * Output: 4
 * Explanation:
 * - Root node (3) is always good.
 * - Node 4 -> (3,4) is the maximum value in its path.
 * - Node 5 -> (3,4,5) is the maximum value in its path.
 * - Node 3 -> (3,1,3) is the maximum value in its path.
 *
 * Example 2:
 * Input:  root = [3,3,null,4,2]
 * Output: 3
 * Explanation:
 * - Node 2 -> (3,3,2) is not good, since 3 is greater than it.
 *
 * Example 3:
 * Input:  root = [1]
 * Output: 1
 * Explanation:
 * - The root is always considered good.
 *
 * Constraints:
 * - The number of nodes in the binary tree is in the range [1, 10^5].
 * - Each node's value is between [-10^4, 10^4].
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 int findGoodNodes(struct TreeNode *root, int parentVal) {

    if (root == NULL) {
        return 0;
    }
    int ans = 0;

    // this is a preorder DFS since we evaluate the current node first
    if (root->val >= parentVal) {
        ans++;
        parentVal = root->val;
    }

    ans += findGoodNodes(root->left, parentVal);
    ans += findGoodNodes(root->right, parentVal);

    return ans;
}


int goodNodes(struct TreeNode* root){

    // we can traverse the tree using DFS and pass in the parent's value
    // if the current node is smaller than the parent it is not a good node
    // actually we need to keep a running value to track the biggest node encountered so far instead of passing just the parent's value.

    if (root == NULL) {
        return 0;
    }
    int ans = 1; // we are at root so it is minimum answer of 1

    ans += findGoodNodes(root->left, root->val);
    ans += findGoodNodes(root->right, root->val);

    return ans;
}