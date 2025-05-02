/*
 * LeetCode Problem 417: Pacific Atlantic Water Flow
 * Difficulty: Medium
 *
 * There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean.
 * The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the right and bottom edges.
 *
 * You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level
 * of the cell at coordinate (r, c). Rain water can flow to neighboring cells (north, south, east, west)
 * if the neighboring cell's height is less than or equal to the current cell's height.
 *
 * Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow
 * from cell (ri, ci) to both the Pacific and Atlantic oceans.
 *
 * Example 1:
 * Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
 * Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
 *
 * Example 2:
 * Input: heights = [[1]]
 * Output: [[0,0]]
 */

void dfs(int **heights, int maxRow, int maxCol, int rowStart, int colStart, int prev, bool visited[][200], bool *reachedAtlantic, bool *reachedPacific) {

    if (*reachedAtlantic && *reachedPacific) { // skip dfs since we're done
        return;
    }

    if (rowStart == maxRow || colStart == maxCol) {
        *reachedAtlantic = true;
        return;
    }

    if (rowStart < 0 || colStart < 0) {
        *reachedPacific = true;
        return;
    }
    
    int currVal = heights[rowStart][colStart];

    if (visited[rowStart][colStart] || currVal > prev) {
        return;
    }

    visited[rowStart][colStart] = true;

    // dfs in every direction

    dfs(heights, maxRow, maxCol, rowStart, colStart + 1, currVal, visited, reachedAtlantic, reachedPacific);
    dfs(heights, maxRow, maxCol, rowStart, colStart - 1, currVal, visited, reachedAtlantic, reachedPacific);
    dfs(heights, maxRow, maxCol, rowStart - 1, colStart, currVal, visited, reachedAtlantic, reachedPacific);
    dfs(heights, maxRow, maxCol, rowStart + 1, colStart, currVal, visited, reachedAtlantic, reachedPacific);

}

void countCoords(int **heights, int maxRow, int maxCol, bool visited[][200], int ***ans, int *ansSize, int *ansCap, int **returnColSizes) {

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            bool reachedAtlantic = false;
            bool reachedPacific = false;
            dfs(heights, maxRow, maxCol, i, j, heights[i][j], visited, &reachedAtlantic, &reachedPacific);
            
            if (reachedAtlantic && reachedPacific) {
                // add i and j to answer array
                // printf("(%d, %d)\n", i, j);

                int *temp = (int*) calloc (2, sizeof(int));
                temp[0] = i;
                temp[1] = j;

                (*ans)[*ansSize] = temp;
                (*returnColSizes)[*ansSize] = 2;

                (*ansSize)++;

                if (*ansSize == *ansCap) { // resize if needed
                    *ansCap *= 2;

                    *ans = realloc (*ans, sizeof(int*) * (*ansCap));
                    *returnColSizes = realloc (*returnColSizes, sizeof(int*) * (*ansCap));
                }
            }
            memset(visited, 0, 200 * 200 * sizeof(bool)); // set visited array back to false 
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes) {

    // just dfs on every cell and see if it hits the pacific ocean and atlantic ocean. if yes then add to answer array
    // reset the visited matrix each time we try a new cell
    // if the next cell height is greater than previous then backtrack

    // we can improve the time by not resetting the visited matrix afte every loop iteration but resetting the cell to false during backtrack if we did not reach both oceans
    // if we reached both oceans don't set to false during back track
    // this efficiency improvement does NOT work because just because a valid DFS on a node does NOT mean the nodes on that path are also valid if we DFS from them to reach both oceans
    // see the example 1: (1, 2) is a valid node to get to pacific ocean from (1,3) and (1,3) is valid, but (1,2) is not valid since it can't reach the atlantic

    if (heights == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    bool visited[200][200] = {false};
    int **ans = (int**) calloc (1, sizeof(int*));
    int ansSize = 0;
    int ansCap = 1;
    int *returnColSizes = (int*) calloc (1, sizeof(int));

    countCoords(heights, heightsSize, heightsColSize[0], visited, &ans, &ansSize, &ansCap, &returnColSizes);

    *returnColumnSizes = returnColSizes;
    *returnSize = ansSize;
    return ans;
}