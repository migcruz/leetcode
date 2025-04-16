/*
 * LeetCode Problem 2549: Count Distinct Numbers on Board
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given a positive integer n, initially placed on a board.
 * Every day for 10^9 days, you perform the following operation:
 *   - For each number x currently on the board, find all integers 1 <= i <= n
 *     such that x % i == 1.
 *   - Add each such i to the board (if not already present).
 *
 * Once a number appears on the board, it remains until the end.
 * After 10^9 days, return the number of distinct integers present on the board.
 *
 * Notes:
 *   - % stands for the modulo operation. For example, 14 % 3 is 2.
 *
 * Examples:
 *
 * Example 1:
 *   Input: n = 5
 *   Output: 4
 *   Explanation:
 *     - Day 0: [5]
 *     - Day 1: Add 2 and 4 since 5 % 2 == 1 and 5 % 4 == 1 → [2, 4, 5]
 *     - Day 2: Add 3 because 4 % 3 == 1 → [2, 3, 4, 5]
 *     - No new additions afterward. Final count = 4.
 *
 * Example 2:
 *   Input: n = 3
 *   Output: 2
 *   Explanation:
 *     - Day 0: [3]
 *     - Day 1: Add 2 since 3 % 2 == 1 → [2, 3]
 *     - No new additions afterward. Final count = 2.
 *
 * Constraints:
 *   - 1 <= n <= 100
 */

int distinctIntegers(int n) {

    // we can make a frequency array since  1 <= n <= 100
    // set the freqArr[i] = 1 if i is going to be put on the board
    // we will traverse the freqArr and only try to find new numbers using numbers that are already in the frequency arr and keep increment the modulo down

    int freqArr[101] = {0};

    freqArr[n] = 1; // put n on the board
    int ans = 0;

    for (int i = 100; i > 0; i--) {

        if (freqArr[i] > 0) {// found a number on the board
            // printf("%d\n", i);
            for (int j = i; j > 0; j--) {
                if ( i % j == 1) { // found a new number to put on the board
                    freqArr[j] = 1;
                }
            }
        }
    }

    // scan the freqArr for distinc numbers
    for (int i = 0; i < 101; i++) {
        if (freqArr[i] > 0) {
            // printf("LOL %d\n", i);
            ans++;
        }
    }
    
    return ans;
}