/*
 * 199. Binary Tree Right Side View
 * Difficulty: Medium
 *
 * Given the root of a binary tree, imagine yourself standing on the right side of it.
 * Return the values of the nodes you can see, ordered from top to bottom.
 *
 * Example 1:
 * Input:  root = [1,2,3,null,5,null,4]
 * Output: [1,3,4]
 * Explanation: The rightmost nodes at each level are 1, 3, and 4.
 *
 * Example 2:
 * Input:  root = [1,2,3,4,null,null,null,5]
 * Output: [1,3,4,5]
 * Explanation: The rightmost nodes at each level are 1, 3, 4, and 5.
 *
 * Example 3:
 * Input:  root = [1,null,3]
 * Output: [1,3]
 *
 * Example 4:
 * Input:  root = []
 * Output: []
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 100].
 * - Each node's value is in the range [-100, 100].
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize) {
    
    //we need to find out the right most node in each row and keep adding those to the answer array
    //we can use BFS to traverse each row and only add the last node in each row to the answer array

    struct queueNode *queue = NULL;
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    // let's find out the amount of rows of the tree
    int size = maxDepth(root);
    // printf("size: %d\r\n", size);

    int *returnArr = (int*) malloc (sizeof(int) * size);
    *returnSize = size;

    //insert the first node
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

        // keep popping all the nodes in the row and adding their children
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode *temp = popFront(&queue);
            // printf("%d\r\n", temp->val);
            if (i == levelSize - 1) { // we are at the right most node in this row
                returnArr[j] = temp->val;
            }

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