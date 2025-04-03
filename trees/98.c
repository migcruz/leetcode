/*
 * 98. Validate Binary Search Tree
 * Difficulty: Medium
 *
 * Given the root of a binary tree, determine if it is a valid Binary Search Tree (BST).
 *
 * A valid BST is defined as follows:
 * - The left subtree of a node contains only nodes with values less than the node's value.
 * - The right subtree of a node contains only nodes with values greater than the node's value.
 * - Both left and right subtrees must also be valid binary search trees.
 *
 * Example 1:
 * Input:  root = [2,1,3]
 * Output: true
 *
 * Example 2:
 * Input:  root = [5,1,4,null,null,3,6]
 * Output: false
 * Explanation: The root node's value is 5, but its right child's value is 4, violating BST rules.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [1, 10^4].
 * - Each node's value is in the range [-2^31, 2^31 - 1].
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// struct BSTNode {
//     struct BSTNode *next;
//     int val;
// };

// void insertNode(struct BSTNode **node, int val) {

//     struct BSTNode *temp = *node;
//     struct BSTNode *newNode = (struct BSTNode*) malloc (sizeof(struct BSTNode));
//     newNode->val = val;
//     newNode->next = NULL;

//     if (temp == NULL) {// list is empty

//         *node = newNode;
//     }
//     else {
//         while(temp->next != NULL) {
//             temp = temp->next;
//         }

//         temp->next = newNode;
//     }

//     return;
// }


// void DFSInOrder(struct TreeNode* root, struct BSTNode **node) {

//     if (root == NULL) {
//         return;
//     }

//     DFSInOrder(root->left, node);
//     insertNode(node, root->val);
//     DFSInOrder(root->right, node);

// }

bool DFSInOrder(struct TreeNode* root, struct TreeNode **prev) {

    if (root == NULL) {
        return true;
    }

    // check left node
    if (!DFSInOrder(root->left, prev)) {
        return false;
    }

    // validate the current node by comparing to prev
    if (*prev != NULL && root->val <= (*prev)->val) {
        return false;
    }

    //update prev
    *prev = root;

    //check right node after update prev to the current node
    if (!DFSInOrder(root->right, prev)) {
        return false;
    }

    return true;

}

bool isValidBST(struct TreeNode* root) {
    
    //we can use a DFS in order traversal (left < root < right) to make sure that the tree is a BST
    // fetch every node in the tree and put it an array or linked list, if the its not sorted in ascending order then return false
    // OR we can keep track of the previous node (imagine you flatten the tree using DFS inorder) as we go through the DFS recursively. This will be faster and have O(h) space
    // where h is the max depth of the BST. No need to allocate extra space with a linked list or array which will make the solution have O(h+N) space

    if (root == NULL) {
        return true;
    }

    struct TreeNode *prev = NULL;

    return DFSInOrder(root, &prev);


    // This is the solution using the extra linkedlist array method

    // if (root == NULL) {
    //     return true;
    // }

    // bool ans = true;
    // struct BSTNode *list = NULL;

    // DFSInOrder(root, &list);

    // // now we will traverse the linked list
    // struct BSTNode *temp = list;
    // while (temp->next != NULL) {
    //     // printf("LOL: %d \r\n", temp->val);
    //     if ((temp->next)->val <= temp->val) {
    //         return false;
    //     }

    //     temp = temp->next;
    // }

    // return ans;
}