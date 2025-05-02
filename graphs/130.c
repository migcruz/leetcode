/*
 * LeetCode Problem 130: Surrounded Regions
 * Difficulty: Medium
 *
 * You are given an m x n matrix board containing letters 'X' and 'O'.
 * Capture all regions that are completely surrounded by 'X'.
 *
 * A region is a group of connected 'O' cells (connected horizontally or vertically).
 * A region is surrounded if none of its cells are on the edge of the board.
 * To capture a surrounded region, replace all 'O's in that region with 'X's in-place.
 *
 * Example 1:
 * Input: board = [["X","X","X","X"],
 *                 ["X","O","O","X"],
 *                 ["X","X","O","X"],
 *                 ["X","O","X","X"]]
 * Output: [["X","X","X","X"],
 *          ["X","X","X","X"],
 *          ["X","X","X","X"],
 *          ["X","O","X","X"]]
 *
 * Example 2:
 * Input: board = [["X"]]
 * Output: [["X"]]
 *
 * Constraints:
 *   - 1 <= m, n <= 200
 *   - board[i][j] is 'X' or 'O'
 */

bool dfs(char **board, int maxRow, int maxCol, int rowStart, int colStart, bool visited[][200], int coordArr[][2], int *coordArrSize) {

    if (visited[rowStart][colStart] || board[rowStart][colStart] == 'X') { // make sure this is first 
        return true;
    }

    if (rowStart == maxRow - 1 || colStart == maxCol - 1 || rowStart == 0 || colStart == 0) { // make sure this is the second check
        return false;
    }

    visited[rowStart][colStart] = true;

    // dfs in all directions
    bool right = dfs(board, maxRow, maxCol, rowStart, colStart + 1, visited, coordArr, coordArrSize);
    bool left = dfs(board, maxRow, maxCol, rowStart, colStart - 1, visited, coordArr, coordArrSize);
    bool up = dfs(board, maxRow, maxCol, rowStart - 1, colStart, visited, coordArr, coordArrSize);
    bool down = dfs(board, maxRow, maxCol, rowStart + 1, colStart, visited, coordArr, coordArrSize);
    
    coordArr[*coordArrSize][0] = rowStart;
    coordArr[*coordArrSize][1] = colStart;
    (*coordArrSize)++;

    if (right && left && up && down) {
        return true;
    }
    else {
        return false;
    }
}

void replaceRegions(char **board, int maxRow, int maxCol, bool visited[][200]) {

    for (int i = 1; i < maxRow - 1; i++) {
        for (int j = 1; j < maxCol - 1; j++) {

            if (board[i][j] != 'X' && !visited[i][j]) {
                // printf("LOL, %d, %d\n", i, j);
                int coordArr[maxRow * maxCol][2];
                int coordArrSize = 0;
                bool valid = dfs(board, maxRow, maxCol, i, j, visited, coordArr, &coordArrSize);
                
                if (valid) {
                    for (int k = 0; k < coordArrSize; k++) {
                        board[coordArr[k][0]][coordArr[k][1]] = 'X';
                    }
                }
            }
        }
    }
}

void solve(char** board, int boardSize, int* boardColSize) {

    // do dfs like in problem 200 num islands except we ignore cells on the edge of the board
    // if during dfs we go to a cell that is at the border, then that region is invalid
    // if we DFS in all directions all we hit is X, then that is a valid region
    // we return true on each dfs if we hit an X or a visited node
    // if all directions are true then we set the current node to X

    // since we can't set to X during backtrack we need an array to keep track of all visited node coords
    // if the region is valid we change all coords in the array to X

    if (board == NULL) {
        return;
    }

    bool visited[200][200] = {false};

    replaceRegions(board, boardSize, boardColSize[0], visited);
}