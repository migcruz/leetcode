/*
 * LeetCode Problem 74: Search a 2D Matrix
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an m x n integer matrix 'matrix' with the following properties:
 * 1. Each row is sorted in non-decreasing order.
 * 2. The first integer of each row is greater than the last integer of the previous row.
 *
 * Given an integer 'target', return 'true' if target exists in the matrix, 
 * otherwise return 'false'.
 *
 * The solution must run in O(log(m * n)) time complexity.
 *
 * Example 1:
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
 * Output: true
 * Explanation: The number 3 exists in the matrix.
 *
 * Example 2:
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
 * Output: false
 * Explanation: The number 13 is not present in the matrix.
 *
 * Constraints:
 * - m == matrix.length
 * - n == matrix[i].length
 * - 1 <= m, n <= 100
 * - -10^4 <= matrix[i][j], target <= 10^4
 */

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {

    // we can concatenate each row which will give us a sorted array. then do binary search

    // we can also do a double binary search. Find out which row the target should be in using binary search, then use binary search on that row.

    //concatenate the rows
    int numsSize = matrixSize * matrixColSize[0];
    int k = 0;
    int *nums = (int*) malloc (sizeof(int) * numsSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[0]; j++) {
            nums[k] = matrix[i][j];
            k++;
        }
    }

    printf("LOL: %d \r\n", nums[0]);
    // now do binary search
    int left = 0;
    int right = numsSize - 1;
    int mid = (left + right) / 2;

    //try the edge cases
    if (target == nums[0]) {
        free(nums);
        return true;
    }

    if (target == nums[numsSize - 1]) {
        free(nums);
        return true;
    }

    while (1) {
        int lastmid = mid;
        if (nums[mid] > target) {
            //try somewhere between left and mid
            right = mid;
            mid = left + (right - left) / 2;
            
        }
        else if (nums[mid] < target) {
            //try somewhere between mid and right
            left = mid;
            mid = left + (right - left) / 2;
        }
        else { // this is the answer
            free(nums);
            return true;
        }

        if (mid == lastmid) { //nothing found
            free(nums);
            return false;
        }
    }
    
}