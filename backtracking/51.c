/*
 * LeetCode Problem 51: N-Queens
 * Difficulty: Hard
 *
 * Problem Description:
 * The N-Queens puzzle involves placing `n` queens on an `n x n` chessboard
 * so that no two queens attack each other.
 *
 * Given an integer `n`, return all distinct solutions to the N-Queens puzzle.
 * Each solution must be a list of strings representing the board configuration.
 * 'Q' indicates a queen and '.' indicates an empty space.
 *
 * Examples:
 *
 * Example 1:
 * Input: n = 4
 * Output: [[".Q..","...Q","Q...","..Q."],
 *          ["..Q.","Q...","...Q",".Q.."]]
 * Explanation: There are two distinct solutions for the 4-queens puzzle.
 *
 * Example 2:
 * Input: n = 1
 * Output: [["Q"]]
 *
 * Constraints:
 *   1 <= n <= 9
 */

void printMatrix(char matrix[][9], int n) {
    // Print the matrix
    for (int i = 0; i < n; i++) {
        // printf("%s\n", matrix[i]);
        for (int j = 0; j < n; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");  // Newline after each row
    }
}

bool isQueenValidLUT(bool cols[], bool diag1[], bool diag2[], int n,  int row, int col) {

    if (cols[col] || diag1[row - col + n - 1] || diag2[row + col]) { // queen found
        return false;
    }

    return true;

}

// bool isQueenValid(char matrix[][9], int n,  int row, int col) {

//     char tempMatrix[9][9];  // Local copy
//     memcpy(tempMatrix, matrix, sizeof(tempMatrix));  // Copy original matrix

//     // scan current board for current queens and make X's
//     for (int i = 0; i < n; i++) {

//         for (int j = 0; j < n; j++) {

//             if (tempMatrix[i][j] == 'Q') {
//                 // mark Xs on the current row
//                 for (int k = 0; k < n; k++) {
                    
//                     if (k != j) {
//                         tempMatrix[i][k] = 'X';
//                     }
//                 }

//                 // mark Xs on the current col
//                 for (int k = 0; k < n; k++) {
                    
//                     if (k != i) {
//                         tempMatrix[k][j] = 'X';
//                     }
//                 }

//                 // Mark Xs on the diagonals
//                 for (int k = 1; k < n; k++) {
//                     // Top-left diagonal
//                     if (i - k >= 0 && j - k >= 0) {
//                         tempMatrix[i - k][j - k] = 'X';
//                     }
                    
//                     // Top-right diagonal
//                     if (i - k >= 0 && j + k < n) {
//                         tempMatrix[i - k][j + k] = 'X';
//                     }
                    
//                     // Bottom-left diagonal
//                     if (i + k < n && j - k >= 0) {
//                         tempMatrix[i + k][j - k] = 'X';
//                     }
                    
//                     // Bottom-right diagonal
//                     if (i + k < n && j + k < n) {
//                         tempMatrix[i + k][j + k] = 'X';
//                     }
//                 }

//                 break; // no more other queens on this row
//             }
//         }
//     }

//     if (tempMatrix[row][col] == 'X' || tempMatrix[row][col] == 'Q' || cols[col] == true) {
//         return false;
//     }

//     return true;

// }

void dfs(int n, char matrix[][9], bool cols[], bool diag1[], bool diag2[], 
            int rowStart, int colStart, int numQueens, char ****ans, int *ansSize, int *ansSizeCap, int **returnColSizes) {

    if (numQueens == n) {
        // printMatrix (matrix, n);
        // printf("---------\n");

        char **newAns = (char**) calloc (n, sizeof(char*));

        for (int i = 0; i < n; i++) { // the strings in the matrix are not null terminated so dont use strdup or strndup
            char *temp = (char*) calloc (n + 1, (sizeof(char)));
            strncpy(temp, matrix[i], n * sizeof(char));
            newAns[i] = temp;
        }

        (*ans)[*ansSize] = newAns;
        (*returnColSizes)[*ansSize] = n;
        (*ansSize)++;

        if (*ansSize == *ansSizeCap) {
            *ansSizeCap *= 2;

            *ans = realloc(*ans, sizeof(char***) * (*ansSizeCap));
            *returnColSizes = realloc(*returnColSizes, sizeof(int*) * (*ansSizeCap));
        }
        return;
    }

    // just need to iterate over columns since we goto another depth level (row) in dfs
    for (int j = colStart; j < n; j++) {

        // test if queen is valid
        if (isQueenValidLUT(cols, diag1, diag2, n, rowStart, j)) {
        // if (isQueenValid(matrix, n, i, j)) {
            
            matrix[rowStart][j] = 'Q';
            cols[j] = true;
            diag1[rowStart - j + n - 1] = true;
            diag2[rowStart + j] = true;

            // printMatrix (matrix, n);

            dfs(n, matrix, cols, diag1, diag2, rowStart + 1, 0, numQueens + 1, ans, ansSize, ansSizeCap, returnColSizes); // i + 1 to skip to next row and reset colStart to 0

            matrix[rowStart][j] = '.'; // remove queen
            cols[j] = false;
            diag1[rowStart - j + n - 1] = false;
            diag2[rowStart + j] = false;
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {

    // use DFS to place queens and back track if it the queen is placed somewhere that is invalid
    // if a queen is placed in a valid position, go down a level in the DFS, and continue from where you left off from the previous queen
    // we can just try squares from left to right and going down
        // this is actually in efficient since we know that there can only be 1 queen per row and 1 queen per column, use this to cut down the search space
        // otherwise you will hit TLE with n = 9. Just jump down to the next row for the next dfs.

    // we need to pass a char** board array that contains the positions and initialize to all .'s
    // only mark as Q if the queen spot is valid, if we backtrack out of it reset back to .

    // once all 4 queens are placed and are valid insert into the answer array

    // we will need a helper function to validate if a queen's spot is valid
        // we can do this by the helper function having a copy of the current board matrix, we will mark invalid positions with an X

        // this is actually expensive and while it does work we can just use a LUT for columns and the \ / diagonals, we will count the diagonals from left to right
        // since we don't need to place queens on the same row this will give us O(1) TC for valdiating a queen's position

    // lets make the dfs method first and print out an answer without worrying about constructing the answer array
    // given the problem, the search space is nxn with a depth of 4 since we have 4 queens to place
    // since we need to pick up from the next cell after placing a queen for dfs, we need to have a start index as we go further down in depth

    if (n == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }


    char matrix[9][9] = { 
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'}, 
        {'.','.','.','.','.','.','.','.','.'} 
    };

    bool cols[9] = {false};       // columns occupied
    bool diag1[17] = {false};    // \ diagonals 17 max diagonals on a 9x9 board
    bool diag2[17] = {false};    // / diagonals

    int ansSize = 0;
    int ansSizeCap = 1;
    char ***ans = (char***) calloc (1, sizeof(char**));
    int *returnColSizes = (int*) calloc (1, sizeof(int));

    dfs(n, matrix, cols, diag1, diag2, 0, 0, 0, &ans, &ansSize, &ansSizeCap, &returnColSizes);

    *returnSize = ansSize;
    *returnColumnSizes = returnColSizes;
    return ans;
}