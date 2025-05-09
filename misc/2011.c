/*
 * LeetCode Problem 2011: Final Value of Variable After Performing Operations
 * Difficulty: Easy
 *
 * There is a programming language with only four operations and one variable X:
 *     ++X and X++ increments the value of the variable X by 1.
 *     --X and X-- decrements the value of the variable X by 1.
 *
 * Initially, the value of X is 0.
 *
 * Given an array of strings operations containing a list of operations,
 * return the final value of X after performing all the operations.
 *
 * Example 1:
 * Input: operations = ["--X","X++","X++"]
 * Output: 1
 * Explanation:
 *   Initially, X = 0
 *   --X: X = -1
 *   X++: X = 0
 *   X++: X = 1
 *
 * Example 2:
 * Input: operations = ["++X","++X","X++"]
 * Output: 3
 * Explanation:
 *   Initially, X = 0
 *   ++X: X = 1
 *   ++X: X = 2
 *   X++: X = 3
 *
 * Example 3:
 * Input: operations = ["X++","++X","--X","X--"]
 * Output: 0
 * Explanation:
 *   Initially, X = 0
 *   X++: X = 1
 *   ++X: X = 2
 *   --X: X = 1
 *   X--: X = 0
 */

int finalValueAfterOperations(char** operations, int operationsSize) {
    
    // parse every string and apply the operation as told

    if (operations == NULL) {
        return 0;
    }

    int x = 0;

    for (int i = 0; i < operationsSize; i++) {
        if (strcmp(operations[i], "++X") == 0 || strcmp(operations[i], "X++") == 0) {
            x++;
        }
        else if (strcmp(operations[i], "--X") == 0 || strcmp(operations[i], "X--") == 0) {
            x--;
        }
    }

    return x;
}