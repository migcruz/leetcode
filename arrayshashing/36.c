/*
 * LeetCode Problem 36: Valid Sudoku
 * Difficulty: Medium
 *
 * Problem Description:
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be 
 * validated according to the following rules:
 *
 * - Each row must contain the digits 1-9 without repetition.
 * - Each column must contain the digits 1-9 without repetition.
 * - Each of the nine 3 x 3 sub-boxes must contain the digits 1-9 without repetition.
 *
 * Notes:
 * - A Sudoku board (partially filled) can be valid but not necessarily solvable.
 * - Only the filled cells (i.e., not '.') are subject to the validation rules.
 *
 * Example 1:
 * Input: board = 
 * [["5","3",".",".","7",".",".",".","."]
 * ,["6",".",".","1","9","5",".",".","."]
 * ,[".","9","8",".",".",".",".","6","."]
 * ,["8",".",".",".","6",".",".",".","3"]
 * ,["4",".",".","8",".","3",".",".","1"]
 * ,["7",".",".",".","2",".",".",".","6"]
 * ,[".","6",".",".",".",".","2","8","."]
 * ,[".",".",".","4","1","9",".",".","5"]
 * ,[".",".",".",".","8",".",".","7","9"]]
 * Output: true
 *
 * Example 2:
 * Input: board = 
 * [["8","3",".",".","7",".",".",".","."]
 * ,["6",".",".","1","9","5",".",".","."]
 * ,[".","9","8",".",".",".",".","6","."]
 * ,["8",".",".",".","6",".",".",".","3"]
 * ,["4",".",".","8",".","3",".",".","1"]
 * ,["7",".",".",".","2",".",".",".","6"]
 * ,[".","6",".",".",".",".","2","8","."]
 * ,[".",".",".","4","1","9",".",".","5"]
 * ,[".",".",".",".","8",".",".","7","9"]]
 * Output: false
 * Explanation: Two '8's appear in the same 3x3 sub-box (top-left).
 *
 * Constraints:
 * - board.length == 9
 * - board[i].length == 9
 * - board[i][j] is a digit '1'-'9' or '.'
 */

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    // check every row and every column and every sub-boxes if theres a duplicate of a number, if there is then its NOT a valid sudoku

    // we can do this with a frequency array for every row, col, sub box, if the frequency of a number becomes greater than 1
    //then there is a repitition, clear the frequency array

    if (board == NULL) {
        return false;
    }

    int freqArr[10] = {0}; // 0 will be dots

    // scan rows first
    for (int i = 0; i < boardSize; i++) {

        for (int j = 0; j < boardSize; j++) {
            
            if (board[i][j] != '.') {
                freqArr[board[i][j] - '0']++;
                if (freqArr[board[i][j] - '0'] > 1) {
                    // printf("ROWS coords: %d, %d  val: %d\r\n", i, j, board[i][j] - '0');
                    return false;
                }
            }
        }
        memset(freqArr, 0, 10 * sizeof(int));
    }

    // scan columns
    for (int i = 0; i < boardSize; i++) {

        for (int j = 0; j < boardSize; j++) {
            
            if (board[j][i] != '.') {
                freqArr[board[j][i] - '0']++;
                if (freqArr[board[j][i] - '0'] > 1) {
                    // printf("COLS coords: %d, %d  val: %d\r\n", j, i, board[i][j] - '0');
                    return false;
                }
            }
        }
        memset(freqArr, 0, sizeof(freqArr));
    }

    // check sub boxes

    for (int row = 0; row < boardSize; row += 3) {

        // calcs one sub box row
        for (int col = 0; col < boardSize; col += 3) {

            // calcs one sub box
            for (int i = row; i < row + 3; i++) {

                for (int j = col; j < col + 3; j++) {
                    
                    if (board[i][j] != '.') {
                        freqArr[board[i][j] - '0']++;
                        if (freqArr[board[i][j] - '0'] > 1) {
                            // printf("SUB BOX coords: %d, %d  val: %d\r\n", i, j, board[i][j] - '0');
                            return false;
                        }
                    }
                }
            }
            memset(freqArr, 0, 10 * sizeof(int));
        }
    }
    return true;
}