/*
 * LeetCode Problem 39: Combination Sum
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an array of distinct integers `candidates` and a target integer `target`,
 * return a list of all unique combinations of `candidates` where the chosen numbers sum to `target`.
 *
 * You may return the combinations in any order.
 * The same number may be chosen from `candidates` an unlimited number of times.
 * Two combinations are unique if the frequency of at least one of the chosen numbers is different.
 *
 * The number of unique combinations that sum up to the target is guaranteed to be less than 150.
 *
 * Examples:
 *
 * Example 1:
 * Input:  candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 * Explanation: 2 + 2 + 3 = 7 and 7 = 7. These are the only valid combinations.
 *
 * Example 2:
 * Input:  candidates = [2,3,5], target = 8
 * Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Example 3:
 * Input:  candidates = [2], target = 1
 * Output: []
 *
 * Constraints:
 *   1 <= candidates.length <= 30
 *   2 <= candidates[i] <= 40
 *   All elements of candidates are distinct.
 *   1 <= target <= 40
 */

// Generate combinations for an array of integers
void generateCombinations(int *arr, int n, int index, int data[], int depth, int sum, int target, int **ans, int *returnColSizes, int *ansSize) {
    if (sum == target) { // let recursion continue, increasing the depth of recursion until sum >= target

        int *tempArr = (int*) calloc (depth, sizeof(int));
        for (int i = 0; i < depth; i++) {
            tempArr[i] = data[i];
        }
        ans[*ansSize] = tempArr;
        returnColSizes[*ansSize] = depth;
        (*ansSize)++;
        return;

        // printf("[");
        // for (int i = 0; i < maxDepth; i++) {
        //     printf("%d, ", data[i]);
        // }
        // printf("]\n");
    }
    else if (sum > target) { // no need to continue with further depth
        return;
    }
    
    // Recruse through array with backtracking
    for (int i = index; i < n; i++) {
        int tempSum = sum + arr[i]; // can't do sum = sum + arr[i] becauser w e need to keep the value of sum the same per recursion call because of backtracking
        data[depth] = arr[i];
        generateCombinations(arr, n, i, data, depth + 1, tempSum, target, ans, returnColSizes, ansSize); // passing i instead of i + 1 so that elements can be repeated
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {

    //we can use the generate combinations function but we need to modify it so that it can repeat elements
    // pass i instead of i + 1 on the generateCombinations recursion call
    // since we do not know the maxDepth beforehand and the depth(size) of a combination can exceed the input array size, we have to keep recursing
    // until we are equal to the target or exceed it

    if (candidates == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    int **ans = (int**) calloc (150, sizeof(int*)); // max size of 150 from constraints;
    int *returColSizes = (int*) calloc (150, sizeof(int));
    int ansSize = 0;

    int data[30] = {0}; // 30 should be enough from the constraints since 1 <= target <= 40 and candidates[i] is >= 2

    generateCombinations(candidates, candidatesSize, 0, data, 0, 0, target, ans, returColSizes, &ansSize);

    *returnColumnSizes = returColSizes;
    *returnSize = ansSize;
    return ans;
    
}