/*
 * LeetCode Problem 78: Subsets
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 *
 * The solution set must not contain duplicate subsets.
 * Return the solution in any order.
 *
 * Examples:
 *
 * Example 1:
 * Input:  nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * Example 2:
 * Input:  nums = [0]
 * Output: [[],[0]]
 *
 * Constraints:
 *   1 <= nums.length <= 10
 *  -10 <= nums[i] <= 10
 *   All the numbers of nums are unique.
 */

// struct Node {
//     struct Node *next;
//     int *arr;
//     int size;
// };

// void insert(struct Node **root, int *newArr, int newArrSize){

//     if (root == NULL) {
//         return;
//     }

//     struct Node *temp = *root;
//     struct Node *newNode = (struct Node*) malloc (sizeof(struct Node));
//     newNode->next = NULL;
//     newNode->arr = newArr;
//     newNode->size = newArrSize;

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

void generateCombinations(int *arr, int n, int index, int data[], int depth, int maxDepth, int **ans, int *ansIndex, int *returnColSizes) {
    if (depth == maxDepth) { // Base case: found a valid combination
        
        //let's make an array and put it into the linked list
        int *newArr = (int*) calloc (maxDepth, sizeof(int));

        for (int i = 0; i < maxDepth; i++) {
            newArr[i] = data[i];
        }
        returnColSizes[*ansIndex] = maxDepth;
        ans[*ansIndex] = newArr;
        (*ansIndex)++;
        // insert(root, newArr, maxDepth);

        return;
    }

    for (int i = index; i < n; i++) {
        data[depth] = arr[i];
        generateCombinations(arr, n, i + 1, data, depth + 1, maxDepth, ans, ansIndex, returnColSizes);
    }
}

// int printList(struct Node *root) {
//     int count = 0;

//     while (root != NULL) {
//         // printf("[");
//         // for (int i = 0; i < root->size; i++) {
//         //     printf("%d, ", root->arr[i]);
//         // }
//         // printf("], ");
//         count++;
//         root = root->next;
//     }

//     return count;
// }

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {

    // we can use a similar approach to the one that generates combinations
    // we will use depths to make the subsets, with the depths ranging from 0 to numsSize
    // we will add to the linked list every subset and then later traverse this linked list to get the final size of the array needed for the answer
    
    // OR
    
    // we can use a formula to find the total amount of subsets and we don't need a linkedlist

    if (nums == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int totalSubsets = 1 << numsSize;  // 2^numsSize subsets
    int** ans = (int**) malloc(totalSubsets * sizeof(int*));
    int *returnColSizes = (int*) calloc (totalSubsets, sizeof(int));
    int data[10] = {0}; // 10 based on bounds
    int ansIndex = 0;

    for (int i = 1; i <= numsSize; i++) {
        generateCombinations(nums, numsSize, 0, data, 0, i, ans, &ansIndex, returnColSizes);
    }

    *returnSize = totalSubsets;
    *returnColumnSizes = returnColSizes;
    return ans;

    // if (nums == NULL) {
    //     *returnSize = 0;
    //     *returnColumnSizes = NULL;
    //     return NULL;
    // }

    // int data[10] = {0};
    // struct Node *root = NULL;

    // insert(&root, NULL, 0); // insert the base subset of []

    // for (int i = 1; i <= numsSize; i++) {
    //     generateCombinations(nums, numsSize, 0, data, 0, i, &root);
    // }
    
    // int ansSize = printList(root);

    // // make the answer array
    // int **ans = (int**) calloc (ansSize, sizeof(int*));
    // int *returnColSizes = (int*) calloc (ansSize, sizeof(int));
    // struct Node *temp = root;

    // int i = 0;
    // while (temp != NULL) {
    //     ans[i] = temp->arr;
    //     returnColSizes[i] = temp->size;
    //     temp = temp->next;
    //     i++;
    // }

    // //free the linked list nodes
    // while (root != NULL) {
    //     temp = root;
    //     root = root->next;
    //     free(temp);
    // }

    // *returnSize = ansSize;
    // *returnColumnSizes = returnColSizes;
    // return ans;
    
}