/*
 * LeetCode Problem 79: Word Search
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an m x n grid of characters 'board' and a string 'word', return true if 'word' exists in the grid.
 * The word can be constructed from letters of sequentially adjacent cells, 
 * where "adjacent" cells are those horizontally or vertically neighboring.
 * The same letter cell may not be used more than once.
 *
 * Examples:
 *
 * Example 1:
 * Input:  board = [["A","B","C","E"],
 *                  ["S","F","C","S"],
 *                  ["A","D","E","E"]],
 *         word = "ABCCED"
 * Output: true
 *
 * Example 2:
 * Input:  board = [["A","B","C","E"],
 *                  ["S","F","C","S"],
 *                  ["A","D","E","E"]],
 *         word = "SEE"
 * Output: true
 *
 * Example 3:
 * Input:  board = [["A","B","C","E"],
 *                  ["S","F","C","S"],
 *                  ["A","D","E","E"]],
 *         word = "ABCB"
 * Output: false
 *
 * Constraints:
 *   m == board.length
 *   n == board[i].length
 *   1 <= m, n <= 6
 *   1 <= word.length <= 15
 *   board and word consist of only lowercase and uppercase English letters
 *
 * Follow-up:
 *   Could you apply search pruning techniques to optimize the solution for larger boards?
 */

void wordSearch(char **board, int boardSize, int colSize, char *word, int row, int col, int *wordPtr, bool **visited, bool *ans) {

    // Out of bounds or cell already visited
    if (row < 0 || col < 0 || row >= boardSize || col >= colSize || visited[row][col]) {
        return;
    }

    if (board[row][col] == word[*wordPtr]) {
        visited[row][col] = true;
        (*wordPtr)++;

        if (word[*wordPtr] == '\0') {
            *ans = true;
            return;
        }

        // move RIGHT
        wordSearch(board, boardSize, colSize, word, row, col + 1, wordPtr, visited, ans);

        // move DOWN
        wordSearch(board, boardSize, colSize, word, row + 1, col, wordPtr, visited, ans);

        // move LEFT
        wordSearch(board, boardSize, colSize, word, row, col - 1, wordPtr, visited, ans);

        // move UP
        wordSearch(board, boardSize, colSize, word, row - 1, col, wordPtr, visited, ans);

        // all directions exhausted so we need to backtrack now
        visited[row][col] = false;
        (*wordPtr)--;

        return;
    }
    else {
        return;
    }
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    // we can go UP DOWN LEFT RIGHT for any cell

    // we need to start at 0,0 and keep going up down left or right until we see the first character of word, then we do it again for the next ccharacter
    // if the next character cannot be formed from a direction, we backtrack and try again in a different direction,
    // if we all directions are exhausted then we backtrack again.

    // we can make sure we dont repeat cells by having a visited grid so that when we try to goto a visited cell, we return immediately and discard it
    // if we backtrack to retry another direction we need to unmark the cell as visited

    if (board == NULL) {
        return false;
    }

    int wordPtr = 0;

    bool **visited = (bool**) calloc (boardSize, sizeof(bool*));

    for (int i = 0; i < boardSize; i++) {
        visited[i] = (bool*) calloc (boardColSize[0], sizeof(bool));
    }
    bool ans = false;

    // iterate through every cell to find the starting position
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[0]; j++) {
            wordSearch (board, boardSize, boardColSize[0], word, i, j, &wordPtr, visited, &ans);
        }
    }


    // // first lets make grid
    // for (int i = 0; i < boardSize; i++) {
    //     for (int j = 0; j < boardColSize[0]; j++) {

    //         if (board[i][j] == word[wordPtr]) {
    //             wordPtr++;
    //         }
    //         // printf("%c ", board[i][j]);
    //     }
    //     // printf("\n");
    // }

    return ans;
    
}