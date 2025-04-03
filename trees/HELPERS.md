# Helper functions and algos for trees

## Finding the max depth of a tree (the amount of rows/levels)
```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

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
```

## Invert a binary tree
```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* invertTree(struct TreeNode* root) {

    // we need to swap the left and right children recursively

    if (root == NULL) {
        return NULL;
    } 

    struct TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    invertTree (root->left);
    invertTree (root->right);

    return root;
}
```

## Get number of elements in a tree
```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int getTreeSize(struct TreeNode *root) {

    if (root == NULL) {
        return 0;
    }
    int size = 1;

    size +=getTreeSize(root->left);
    size +=getTreeSize(root->right);

    return size;
}
```