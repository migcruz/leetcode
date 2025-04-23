/*
 * LeetCode Problem 46: Permutations
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an array `nums` of distinct integers, return all possible permutations of the array.
 * You can return the answer in any order.
 *
 * Examples:
 *
 * Example 1:
 * Input:  nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * Example 2:
 * Input:  nums = [0,1]
 * Output: [[0,1],[1,0]]
 *
 * Example 3:
 * Input:  nums = [1]
 * Output: [[1]]
 *
 * Constraints:
 *   1 <= nums.length <= 6
 *  -10 <= nums[i] <= 10
 *   All the integers of `nums` are unique.
 */

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void generatePermutations(int *arr, int left, int right, int **ans, int numsSize, int *count) {
    if (left == right) { // Base case: a complete permutation is formed

        int *tempArr = (int*) calloc (numsSize, sizeof(int));

        for (int i = 0; i < numsSize; i++) {
            tempArr[i] = arr[i];
        }
        ans[*count] = tempArr;
        (*count)++;

        // printf("[");
        // for (int i = 0; i <= right; i++) {
        //     printf("%d", arr[i]);
        //     if (i < right) printf(", ");
        // }
        // printf("]\n");
        return;
    }

    for (int i = left; i <= right; i++) {
        swap(&arr[left], &arr[i]); // Swap to create a new permutation
        generatePermutations(arr, left + 1, right, ans, numsSize, count); // Recursively generate permutations
        swap(&arr[left], &arr[i]); // Backtrack (reverse the swap)
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {

    // the formula for the number of permutations is = n!/ (n - r)!, where r is the amount of elements chosen from n, if n == r then this becomes n!
    // REMEMEBER this only works if every element in the array is distinct

    if (nums == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    // Compute size of answer array
    int ansSize = 1;
    int count = 0;

    for (int i = 2; i <= numsSize; i++) {
        ansSize = ansSize * i;
    }

    int **ans = (int**) calloc (ansSize, sizeof(int*));
    int *returnColSizes = (int*) calloc (ansSize, sizeof(int));
    for (int i = 0; i < ansSize; i++) {
        returnColSizes[i] = numsSize;
    }

    generatePermutations(nums, 0, numsSize - 1, ans, numsSize, &count);

    *returnColumnSizes = returnColSizes;
    *returnSize = ansSize;
    return ans;
    
}