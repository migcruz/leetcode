/*
 * LeetCode Problem 572: Subtree of Another Tree
 * Difficulty: Easy
 *
 * Problem Description:
 * Given the roots of two binary trees, root and subRoot, determine if subRoot 
 * is a subtree of root.
 *
 * A subtree consists of a node in the original tree and all of its descendants.
 * The entire tree itself is considered a valid subtree.
 *
 * Example 1:
 * Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 * Output: true
 * Explanation: The subtree starting at node 4 in the root tree matches subRoot exactly.
 *
 * Example 2:
 * Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
 * Output: false
 * Explanation: The subtree starting at node 4 differs because of an additional node (0).
 *
 * Constraints:
 * - The number of nodes in the root tree is in the range [1, 2000].
 * - The number of nodes in the subRoot tree is in the range [1, 1000].
 * - -10^4 <= root.val <= 10^4
 * - -10^4 <= subRoot.val <= 10^4
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

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {

    // we an use DFS via preorder traversal. Actually on closer inspection we need to use postorder to go to the deepest nodes first.
    // traverse and compare nodes until theyre equal
    // then keep traversing with the subroots children

    // we will use the algo from 100. Same Tree once we encountered 2 matching nodes for the roots of subtree and tree
    if (subRoot == NULL) {
        return true; // a subtree with subroot NULL is always a subtree of tree
    }
    else if (root == NULL && subRoot != NULL) {
        return false; 
    }

    // now lets traverse tree until we find a node if it exists. We need to use a post-order algo so we go the deepest nodes first
    if (isSubtree(root->left, subRoot)) {
        return true;
    }

    if (isSubtree(root->right, subRoot)) {
        return true;
    }

    if (subRoot->val != root->val) {
        return false;
    }
    else { // we found a node thats equal
        return isSameTree(root, subRoot);
    }
    
}