/*
 * LeetCode Problem 2220: Minimum Bit Flips to Convert Number
 * Difficulty: Easy
 *
 * A bit flip of a number x is choosing a bit in the binary representation of x and flipping it 
 * from either 0 to 1 or 1 to 0.
 *
 * Given two integers start and goal, return the minimum number of bit flips to convert start to goal.
 *
 * Example 1:
 * Input: start = 10, goal = 7
 * Output: 3
 *
 * Example 2:
 * Input: start = 3, goal = 4
 * Output: 3
 *
 * Constraints:
 *   - 0 <= start, goal <= 10^9
 */

// this is the same as problem 461
int minBitFlips(int start, int goal) {

    // we extract the LSB from each number and compare them, if theyre not the same, then increase answer by 1
    // keep doing this until both numbers are 0

    int ans = 0;

    while (start > 0 || goal > 0) {
        bool startLSB = start & 1;
        bool goalLSB = goal & 1;

        if (startLSB ^ goalLSB) {
            ans++;
        }

        goal = goal >> 1;
        start = start >> 1;

    }
    
    return ans;
}