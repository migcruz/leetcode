/*
 * LeetCode Problem 695: Max Area of Island
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an m x n binary matrix grid representing a map of 0s (water) and 1s (land),
 * return the maximum area of an island. An island is formed by connecting adjacent
 * lands horizontally or vertically (4-directional). Assume all grid edges are water.
 *
 * The area of an island is the total number of 1s in the connected component.
 * If there is no island, return 0.
 *
 * Example 1:
 * Input:
 * grid = [
 *   [0,0,1,0,0,0,0,1,0,0,0,0,0],
 *   [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *   [0,1,1,0,1,0,0,0,0,0,0,0,0],
 *   [0,1,0,0,1,1,0,0,1,0,1,0,0],
 *   [0,1,0,0,1,1,0,0,1,1,1,0,0],
 *   [0,0,0,0,0,0,0,0,0,0,1,0,0],
 *   [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *   [0,0,0,0,0,0,0,1,1,0,0,0,0]
 * ]
 * Output: 6
 *
 * Example 2:
 * Input: grid = [[0,0,0,0,0,0,0,0]]
 * Output: 0
 *
 * Constraints:
 *   m == grid.length
 *   n == grid[i].length
 *   1 <= m, n <= 50
 *   grid[i][j] is either 0 (water) or 1 (land)
 */

void dfs(int **grid, int maxRow, int maxCol, int rowStart, int colStart, bool **visited, int *islandSize) {

    if (rowStart == maxRow || colStart == maxCol || rowStart < 0 || colStart < 0) {
        return;
    }
    // printf("rowstart: %d, colstart: %d \n", rowStart, colStart);
    if (grid[rowStart][colStart] == 0 || visited[rowStart][colStart]) {
        return;
    }

    visited[rowStart][colStart] = true;
    (*islandSize)++;

    // now DFS in every direction

    // try right
    dfs(grid, maxRow, maxCol, rowStart, colStart + 1, visited, islandSize);
    // try left
    dfs(grid, maxRow, maxCol, rowStart, colStart - 1, visited, islandSize);
    // try up
    dfs(grid, maxRow, maxCol, rowStart - 1, colStart, visited, islandSize);
    // try down
    dfs(grid, maxRow, maxCol, rowStart + 1, colStart, visited, islandSize);

}

int countIslands(int **grid, int maxRow, int maxCol, bool **visited) {

    //try dfs on every cell if its not a 0 or if it has not been visited

    int count = 0;

    int biggestIslandSize = 0;

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            if (!visited[i][j] && grid[i][j] != 0) {
                int tempIslandSize = 0;
                dfs(grid, maxRow, maxCol, i, j, visited, &tempIslandSize);
                count++;
                biggestIslandSize = (tempIslandSize > biggestIslandSize) ? tempIslandSize : biggestIslandSize;
            }
        }
    }
    return biggestIslandSize;
}
int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize) {

    // use the same algo as 200 to find the number of island but just keep counting the number of 1s during dfs
    // then have a running total that gets updated fi the number of 1s on one island are more than we encountered so far

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