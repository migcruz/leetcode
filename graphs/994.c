/*
 * LeetCode Problem 994: Rotting Oranges
 * Difficulty: Medium
 *
 * Problem Description:
 * You are given an m x n grid where each cell is one of:
 *   - 0: an empty cell
 *   - 1: a fresh orange
 *   - 2: a rotten orange
 *
 * Each minute, fresh oranges adjacent (4-directionally) to a rotten orange become rotten.
 * Return the minimum number of minutes needed for all fresh oranges to become rotten.
 * If it's impossible to rot all oranges, return -1.
 *
 * Example 1:
 * Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 *
 * Example 2:
 * Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
 * Output: -1
 *
 * Example 3:
 * Input: grid = [[0,2]]
 * Output: 0
 *
 * Constraints:
 *   - 1 <= m, n <= 10
 *   - grid[i][j] is 0, 1, or 2
 */

typedef struct Node {
    int row;
    int col;
    struct Node *next;
} Node;

void insert(Node **root, int row, int col) {

    if (root == NULL) {
        return;
    }

    Node *newNode = (Node*) malloc (sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;

    Node *temp = *root;

    if (temp == NULL) {
        *root = newNode;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

Node *dequeue(Node **root) {

    if (root == NULL) {
        return NULL;
    }

    Node *temp = *root;

    if (temp != NULL) {
        *root = temp->next;
    }
    return temp;
}

void bfs (int **grid, int maxRow, int maxCol, int startRow, int startCol, bool visited[][10], Node **queue) {

    if (startRow == maxRow || startCol == maxCol || startRow < 0 || startCol < 0) {
        return;
    }

    if (visited[startRow][startCol] || grid[startRow][startCol] == 0) {
        return;
    }

    //Enqueue the the node
    insert(queue, startRow, startCol);
    visited[startRow][startCol] = true;
}

int orangesRotting(int** grid, int gridSize, int* gridColSize) {

    // this is like the island problem.
    // we will dfs to find orange clusters, if there is a rotting orange in a cluster then the entire cluster will rot
        // we will not DFS until we found a rotten orange
        // if we find a cluster without a rotten orange then return -1
    // we will increase the timer once we return from dfs from every direction

    // on further inspection we should BFS, we need to find all rotten oranges and then enqueue them and then start BFS
    // on each BFS level we increase the timer
    // if there are any fresh oranges in the grid after BFS, return -1

    bool visited[10][10] = {false};
    Node *root = NULL;
    int time = 0;
    bool hasFreshOrange = false;

    // traverse matrix and find rotten oranges
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] == 2) {
                insert(&root, i, j);
                visited[i][j] = true;
            }
            else if (grid[i][j] == 1) {
                hasFreshOrange = true;
            }
        }
    }

    // edge case, if there are no rotten oranges return 0 and if there are only fresh oranges return -1
    if (root == NULL) {
        if (hasFreshOrange) {
            return -1;
        }
        return 0;
    }

    while (root != NULL) {

        // find out how big the queue is currently
        int currLevel = 0;
        Node *temp = root;
        while (temp != NULL) {
            temp = temp->next;
            currLevel++;
        }

        // Dequeue as much as currLevel and do BFS
        for (int i = 0; i < currLevel; i++) {
            temp = dequeue(&root);

            bfs(grid, gridSize, gridColSize[0], temp->row, temp->col + 1, visited, &root); // right
            bfs(grid, gridSize, gridColSize[0], temp->row, temp->col - 1, visited, &root); // left
            bfs(grid, gridSize, gridColSize[0], temp->row - 1, temp->col, visited, &root); // up
            bfs(grid, gridSize, gridColSize[0], temp->row + 1, temp->col, visited, &root); // down
        }
        time++;
    }

    // scan for oranges that have not been rotted
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (!visited[i][j] && grid[i][j] == 1) {
                return -1;
            }
        }
    }


    return time - 1; // -1 since the first nodes shouldnt count when we dequeue since they are the original rotten oranges
}