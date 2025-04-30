/*
 * LeetCode Problem 1380: Lucky Numbers in a Matrix
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an m x n matrix of distinct integers, return all "lucky numbers" in any order.
 * A lucky number is defined as an element that is:
 *   - the minimum in its row
 *   - and the maximum in its column.
 *
 * Example 1:
 * Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
 * Output: [15]
 * Explanation: 15 is the minimum in its row and maximum in its column.
 *
 * Example 2:
 * Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
 * Output: [12]
 *
 * Example 3:
 * Input: matrix = [[7,8],[1,2]]
 * Output: [7]
 *
 * Constraints:
 *   - m == matrix.length
 *   - n == matrix[i].length
 *   - 1 <= m, n <= 50
 *   - 1 <= matrix[i][j] <= 10^5
 *   - All elements are distinct
 */

bool isLucky(int **matrix, int rowSize, int colSize, int row, int col, int val) {

    // check cols
    for (int k = 0; k < colSize; k++) {
        if (matrix[row][k] < val) {
            return false;
        }
    }

    // check row
    for (int k = 0; k < rowSize; k++) {
        if (matrix[k][col] > val) {
            return false;
        }
    }

    return true;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* luckyNumbers(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {

    if (matrix == NULL) {
        *returnSize = 0;
        return NULL;
    }

    // we perform the lucky number check in every cell of the matrix

    int size = (matrixSize < matrixColSize[0]) ? matrixSize : matrixColSize[0]; // the smallest of the two will be the max size of the answer
    // printf("%d\n", size);
    int ansSize = 0;
    int *ans = (int*) calloc (size, sizeof(int));

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[0]; j++) {

            int newAns = matrix[i][j];

            if (isLucky(matrix, matrixSize, matrixColSize[0], i, j, newAns)) {
                ans[ansSize] = newAns;
                ansSize++;
            }
        }
    }

    *returnSize = ansSize;
    return ans;
}