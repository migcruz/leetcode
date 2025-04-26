/*
 * LeetCode Problem 693: Binary Number with Alternating Bits
 * Difficulty: Easy
 *
 * Problem Description:
 * Given a positive integer `n`, check whether its binary representation has alternating bits.
 * Alternating bits mean that no two adjacent bits are the same (i.e., 0 and 1 alternate).
 *
 * Examples:
 *
 * Example 1:
 * Input:  n = 5
 * Output: true
 * Explanation: 5 in binary is 101, which alternates between 1 and 0.
 *
 * Example 2:
 * Input:  n = 7
 * Output: false
 * Explanation: 7 in binary is 111, which does not alternate.
 *
 * Example 3:
 * Input:  n = 11
 * Output: false
 * Explanation: 11 in binary is 1011, where adjacent bits are not always alternating.
 *
 * Constraints:
 *   1 <= n <= 2^31 - 1
 */

bool hasAlternatingBits(int n) {

    // we can AND the current number with 0b1 then shift n to the right by 1 and the result should be the opposite of the previous answer
    // so that means we can do a dynamic programming approach where dp[n] = !dp[n-1]

    bool dpN1 = n & 0b1;

    while (n > 0) {

        n >>= 1;
         bool dpN = n & 0b1;

        if (dpN != !dpN1) {
            return false;
        }

        dpN1 = dpN;

    }
    return true;
    
}