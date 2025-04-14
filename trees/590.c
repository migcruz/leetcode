/*
 * LeetCode Problem 590: N-ary Tree Postorder Traversal
 * Difficulty: Easy
 *
 * Problem Description:
 * Given the root of an N-ary tree, return the postorder traversal of its nodes' values.
 * Postorder traversal is defined as visiting all the children of a node before the node itself.
 *
 * Note:
 * - N-ary Tree input is serialized using level order traversal.
 * - Each group of children is separated by a null value in the input array.
 *
 * Example 1:
 * Input: root = [1,null,3,2,4,null,5,6]
 * Output: [5,6,3,2,4,1]
 *
 * Example 2:
 * Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]
 *
 * Constraints:
 * - The number of nodes is in the range [0, 10^4].
 * - 0 <= Node.val <= 10^4
 * - The height of the N-ary tree is <= 1000.
 *
 * Follow-up:
 * - The recursive solution is straightforward.
 * - Try solving this problem iteratively for better practice with tree traversal logic.
 */

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

// struct ansNode {

//     struct ansNode *next;
//     int val;
// };

// void insertNode (struct ansNode **root, int val) {

//     if (root == NULL) {
//         return;
//     }

//     struct ansNode *temp = *root;
//     struct ansNode *newNode = (struct ansNode*) malloc (sizeof(struct ansNode));
//     newNode->next = NULL;
//     newNode->val = val;

//     if (temp == NULL) {
//         *root = newNode;
//     }
//     else {
//         while (temp->next != NULL) {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//     }
// }


void postOrderHelper(struct Node *root, int *returnSize, int *ansArr) {

    for (int i = 0; i < root->numChildren; i++) {
        postOrderHelper( (root->children)[i], returnSize, ansArr);
    }

    ansArr[*returnSize] = root->val;
    (*returnSize)++;

    // insertNode(ansList, root->val);
    // printf("%d ", root->val);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* postorder(struct Node* root, int* returnSize) {

    // since its post order we need to visit the children nodes first
    // first we need to figure out how many elements needs to be in the array before we can allocate it. unless we just allocate 10^4 elements

    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int size = 0; // cant directly use *returnSize because it might be initialized to an unknown value
    int *ansArr = (int*)calloc(1, sizeof(int) * 10000 );
    postOrderHelper(root, &size, ansArr);

    // struct ansNode *ansList = NULL;
    // postOrderHelper(root, &size, &ansList);

    // int *ansArr = (int*)calloc(1, sizeof(int) * size );

    // fill up the answer array
    // struct ansNode *temp = ansList;

    // for (int i = 0; temp != NULL; i++) {
    //     ansArr[i] = temp->val;
    //     temp = temp->next;
    // }

    *returnSize = size;
    return ansArr;
}