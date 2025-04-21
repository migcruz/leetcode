/*
 * LeetCode Problem 191: Number of 1 Bits
 * Difficulty: Easy
 *
 * Problem Description:
 * Given a positive integer n, write a function that returns the number of '1' bits
 * in its binary representation (also known as the Hamming weight).
 *
 * Examples:
 *
 * Example 1:
 * Input: n = 11
 * Output: 3
 * Explanation:
 * The input binary string 1011 has a total of three set bits.
 *
 * Example 2:
 * Input: n = 128
 * Output: 1
 * Explanation:
 * The input binary string 10000000 has a total of one set bit.
 *
 * Example 3:
 * Input: n = 2147483645
 * Output: 30
 * Explanation:
 * The input binary string 1111111111111111111111111111101 has a total of thirty set bits.
 *
 * Constraints:
 *   1 <= n <= 2^31 - 1
 */

int hammingWeight(int n) {

    // shift the number to the right by 1 and then AND it with 0b1, if its a 1 then increase counter

    int ans = 0;

    while (n != 0) {

        int temp = n & 0b1;
        if (temp) {
            ans++;
        }

        n >>= 1;

    }

    return ans;
    
}