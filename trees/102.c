/*
 * LeetCode Problem 102: Binary Tree Level Order Traversal
 * Difficulty: Medium
 *
 * Problem Description:
 * Given the root of a binary tree, return the level order traversal of its nodes' values.
 * Level order traversal means visiting nodes from left to right, level by level.
 *
 * Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[3],[9,20],[15,7]]
 * Explanation: First level contains 3, second level contains 9 and 20, third level contains 15 and 7.
 *
 * Example 2:
 * Input: root = [1]
 * Output: [[1]]
 * Explanation: The tree has only one node, so the level order traversal consists of a single list.
 *
 * Example 3:
 * Input: root = []
 * Output: []
 * Explanation: The tree is empty, so the output is an empty list.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 2000].
 * - -1000 <= Node.val <= 1000.
 *
 * Approach:
 * - Use **Breadth-First Search (BFS)** to traverse the tree level by level.
 * - Utilize a **queue** to maintain nodes of the current level.
 * - Store the nodes of each level in a separate list.
 * - Continue until all levels are processed.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 struct queueNode {
    struct queueNode *next;
    struct TreeNode *treePtr;
};

// We need to make a queue which is FIFO.
void insertNode(struct queueNode **node, struct TreeNode *p) {
    if (node == NULL) {
        return;
    }
    
    struct queueNode *temp = *node;
    struct queueNode *newNode = (struct queueNode*) malloc (sizeof(struct queueNode));
    newNode->treePtr = p;
    newNode->next = NULL;

    if (temp == NULL) { // list is empty
        *node = newNode;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // we are at the end of the queue
        temp->next = newNode;
    }
    return;
}

// here we need to pop the top of the queue  and then update the root ptr
struct TreeNode *popFront(struct queueNode **node) {

    if (node == NULL) {
        return NULL;
    }

    struct queueNode *temp = *node;
    struct TreeNode *tempTree;

    *node = temp->next;
    tempTree = temp->treePtr;
    
    free(temp);
    return tempTree;
}

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

    return depth;
    
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {

    //we need to use a BFS algo which to do level traversal which will need a queue
    // we will enqueue the current node then have a while loop where if the list is NOT empty, we pop the top of the queue
    // then we will enqueue that popped node's left and right children assuming theyre NOT NULL
    // for the return values, we will need to find out the depth of the tree which will be the size of the returnarray
    // we also need to find out the amount of elements on each row
    struct queueNode *queue = NULL;
    if (root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    //lets find out the depth (rows) of the tree first using DFS
    int size = maxDepth(root);
    // printf("size %d\r\n", size);

    //allocate memory for the answers
    int **returnArr = (int**)malloc(sizeof(int*) * size);
    *returnColumnSizes = (int*)malloc(sizeof(int) * size); // its being passed by reference so double pointer but they just want a simple 1-D array allocated
    *returnSize = size;

    // insert the first node;
    insertNode(&queue, root);

    for (int j = 0; j < size; j++) { //increment for the next row to be added to return array

        // Count the number of nodes at this level
        // since we only pop nodes
        int levelSize = 0;
        struct queueNode *tempQueue = queue;
        while (tempQueue != NULL) {
            levelSize++;
            tempQueue = tempQueue->next;
        }

        // allocate memory for this row
        returnArr[j] = (int*)malloc(sizeof(int) * levelSize);
        (*returnColumnSizes)[j] = levelSize;

        // keep popping all the nodes in the row and adding their children
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode *temp = popFront(&queue);
            // printf("%d\r\n", temp->val);
            returnArr[j][i] = temp->val;

            if (temp->left != NULL) {
                insertNode(&queue, temp->left);
            }

            if (temp->right != NULL) {
                insertNode(&queue, temp->right);
            }
        }
    }


    return returnArr;
}