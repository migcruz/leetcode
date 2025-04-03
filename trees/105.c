/*
 * LeetCode Problem 105: Construct Binary Tree from Preorder and Inorder Traversal
 * Difficulty: Medium
 *
 * Problem Description:
 * Given two integer arrays, preorder and inorder, where:
 * - preorder represents the preorder traversal of a binary tree.
 * - inorder represents the inorder traversal of the same tree.
 * Construct and return the binary tree.
 *
 * Example 1:
 * Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * Output: [3,9,20,null,null,15,7]
 *
 * Example 2:
 * Input: preorder = [-1], inorder = [-1]
 * Output: [-1]
 *
 * Constraints:
 * - 1 <= preorder.length <= 3000
 * - inorder.length == preorder.length
 * - -3000 <= preorder[i], inorder[i] <= 3000
 * - preorder and inorder consist of unique values.
 * - Each value in inorder also appears in preorder.
 * - preorder is guaranteed to be the preorder traversal of the tree.
 * - inorder is guaranteed to be the inorder traversal of the tree.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct number {
    int id; //this will just be the number
    int inOrderIndex; 
    UT_hash_handle hh; // makes this struct hashable via uthash https://troydhanson.github.io/uthash/. This is already part of leetcode. It's just a header so there's library to link against for builds.
};

struct number *numberDict = NULL;

void add_number(int num, int inOrderIndex) {

    struct number *temp = NULL;
    HASH_FIND_INT(numberDict, &num, temp);

    if (temp == NULL) {
        struct number *newNumber = (struct number*) malloc (sizeof(struct number));
        newNumber->id = num;
        newNumber->inOrderIndex = inOrderIndex;
        HASH_ADD_INT(numberDict, id, newNumber);
    }
    return;
}

struct number *get_number(int num) {

    struct number *temp = NULL;
    HASH_FIND_INT(numberDict, &num, temp);
    
    return temp;
}

void delete_number(int num) {
    struct number *temp = get_number(num);

    if (temp != NULL) {
        HASH_DEL(numberDict, temp);  /* user: pointer to deletee */
        free(temp);             /* optional; it's up to you! */
    }
}

int get_inOrderIndex(int num) {
    struct number *temp = NULL;
    HASH_FIND_INT(numberDict, &num, temp);

    if (temp == NULL) {
        return -1;
    }

    return temp->inOrderIndex;
}

// Recursive function to build the binary tree using index boundaries
struct TreeNode* buildTreeHelper(int* preorder, int* inorder, int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    // Get the current root from preorder traversal
    int rootVal = preorder[*preIndex];
    (*preIndex)++;

    // Create a new node for this root
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootVal;
    root->left = NULL;
    root->right = NULL;

    // Lookup inorder index using hash map
    int inorderIndex = get_inOrderIndex(rootVal);
    // printf("instart: %d, inorderIndex %d, inEnd: %d\r\n", inStart, inorderIndex, inEnd);

    // Recursively build left and right subtrees using correct partitions
    // we will build the left subtree from the current node by using index bounds from inOrder to the left of the current node's inOrder index
    root->left = buildTreeHelper(preorder, inorder, inStart, inorderIndex - 1, preIndex);

    // we will build the right subtree from the current node by using index bounds from inOrder to the right of the current node's inOrder index
    root->right = buildTreeHelper(preorder, inorder, inorderIndex + 1, inEnd, preIndex);

    return root;
}
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {

    // the first element of the preorder array is the root
    // all elements before this value in the inorder array are on the left side of the tree, the elements after it are on the right side of the tree. we should save this index of the root
    // in the inorder array

    // the first element of the inorder array is the left most node
    // the last element of the inroder array is NOT necessarily the right most node

    // we can build each subtree recursively via post DFS as we travel recursively down to the left and right subtrees first before assigning them to the parent subtree and then returning
    // that parent up recursively
    
    //let's add every value in the preorder array to the hash map
    for (int i = 0; i < inorderSize; i++) {
        add_number(inorder[i], i);
    }

    // Initialize preorder index tracker
    int preIndex = 0;
    struct TreeNode* root = buildTreeHelper(preorder, inorder, 0, inorderSize - 1, &preIndex);

    //clean up table or else other test cases will fail as memory is not cleared with uthash per test case
    for (int i = 0; i < inorderSize; i++) {
        delete_number(inorder[i]);
    }

    return root;
    
}