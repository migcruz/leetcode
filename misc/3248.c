/*
 * LeetCode Problem 3248: Snake in Matrix
 * Difficulty: Easy
 *
 * Problem Description:
 * There is a snake in an n x n matrix grid that can move in four directions: "UP", "RIGHT", "DOWN", and "LEFT".
 * Each cell in the grid is represented by its position: grid[i][j] = (i * n) + j.
 * The snake starts at cell 0 and follows a sequence of movement commands.
 * It is guaranteed that the snake remains within the grid throughout its movement.
 * 
 * Return the final position of the cell where the snake ends after executing all commands.
 *
 * Examples:
 *
 * Example 1:
 * Input:  n = 2, commands = ["RIGHT", "DOWN"]
 * Output: 3
 * Explanation:
 * Grid:
 * 0 1
 * 2 3
 * Snake moves: 0 -> 1 -> 3
 *
 * Example 2:
 * Input:  n = 3, commands = ["DOWN", "RIGHT", "UP"]
 * Output: 1
 * Explanation:
 * Grid:
 * 0 1 2
 * 3 4 5
 * 6 7 8
 * Snake moves: 0 -> 3 -> 4 -> 1
 *
 * Constraints:
 *   2 <= n <= 10
 *   1 <= commands.length <= 100
 *   commands consists only of "UP", "RIGHT", "DOWN", and "LEFT"
 *   The snake will not move outside the grid boundaries
 */

int finalPositionOfSnake(int n, char** commands, int commandsSize) {

    if (commands == NULL) {
        return 0;
    }

    // we parse the commands and calculate the new position of the snake on the grid

    int i = 0;
    int j = 0;
    int ans = 0;

    for (int k = 0; k < commandsSize; k++) {

        char *command = commands[k];

        if (strcmp(command, "UP") == 0) {
            i--;
        }
        else if (strcmp(command, "DOWN") == 0) {
            i++;
        }
        else if (strcmp(command, "RIGHT") == 0) {
            j++;
        }
        else if (strcmp(command, "LEFT") == 0) {
            j--;
        }
    }

    ans = (i*n) + j;
    
    return ans;
}