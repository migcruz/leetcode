/*
 * LeetCode Problem 200: Number of Islands
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an m x n 2D binary grid representing a map of '1's (land) and '0's (water),
 * return the number of distinct islands. An island is formed by connecting adjacent
 * lands horizontally or vertically and is surrounded by water.
 *
 * Approach:
 * Use Depth-First Search (DFS) or Breadth-First Search (BFS) to traverse and mark
 * connected land components. Count how many times a new unvisited '1' is found.
 *
 * Example 1:
 * Input:
 * grid = [
 *   ["1","1","1","1","0"],
 *   ["1","1","0","1","0"],
 *   ["1","1","0","0","0"],
 *   ["0","0","0","0","0"]
 * ]
 * Output: 1
 *
 * Example 2:
 * Input:
 * grid = [
 *   ["1","1","0","0","0"],
 *   ["1","1","0","0","0"],
 *   ["0","0","1","0","0"],
 *   ["0","0","0","1","1"]
 * ]
 * Output: 3
 *
 * Constraints:
 *   m == grid.length
 *   n == grid[i].length
 *   1 <= m, n <= 300
 *   grid[i][j] is either '0' or '1'
 */

void dfs(char **grid, int maxRow, int maxCol, int rowStart, int colStart, bool **visited) {

    if (rowStart == maxRow || colStart == maxCol || rowStart < 0 || colStart < 0) {
        return;
    }
    // printf("rowstart: %d, colstart: %d \n", rowStart, colStart);
    if (grid[rowStart][colStart] == '0' || visited[rowStart][colStart]) {
        return;
    }

    visited[rowStart][colStart] = true;

    // now DFS in every direction

    // try right
    dfs(grid, maxRow, maxCol, rowStart, colStart + 1, visited);
    // try left
    dfs(grid, maxRow, maxCol, rowStart, colStart - 1, visited);
    // try up
    dfs(grid, maxRow, maxCol, rowStart - 1, colStart, visited);
    // try down
    dfs(grid, maxRow, maxCol, rowStart + 1, colStart, visited);

}

int countIslands(char **grid, int maxRow, int maxCol, bool **visited) {

    //try dfs on every cell if its not a 0 or if it has not been visited

    int count = 0;

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            if (!visited[i][j] && grid[i][j] != '0') {
                dfs(grid, maxRow, maxCol, i, j, visited);
                count++;
            }
        }
    }
    return count;
}

int numIslands(char** grid, int gridSize, int* gridColSize) {

    // traverse the matrix row by row and if you encounter a 1 do dfs
    // make a visited matrix of the same size
    // return from dfs if it is a 0 or a 1 that has been visited

    if (grid == NULL) {
        return 0;
    }

    // Make matrix
    bool **visited = (bool**) calloc (gridSize, sizeof(bool*));
    for (int i = 0; i < gridSize; i++) {
        visited[i] = (bool*) calloc (gridColSize[0], sizeof(bool));
    }

    int ans = countIslands(grid, gridSize, gridColSize[0], visited);

    return ans;
    
}