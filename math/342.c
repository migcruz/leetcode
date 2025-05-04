/*
 * LeetCode Problem 342: Power of Four
 * Difficulty: Easy
 *
 * Given an integer n, return true if it is a power of four. Otherwise, return false.
 * An integer n is a power of four if there exists an integer x such that n == 4^x.
 *
 * Example 1:
 * Input: n = 16
 * Output: true
 *
 * Example 2:
 * Input: n = 5
 * Output: false
 *
 * Example 3:
 * Input: n = 1
 * Output: true
 *
 * Constraints:
 *   - -2^31 <= n <= 2^31 - 1
 *
 * Follow up: Could you solve it without loops/recursion?
 */

bool isPowerOfFour(int n) {
    // we can use algebra
    // n = 4^x
    // log(n) = log(4^x)
    // log(n) = x * log(4)
    // x = log(n)/log(4)
    // x = ln(n)/ln(4)
    // log(x) in C is actually ln(), to use base 10 logarithm you can use log10()

    // note that ln(0) is an infinite asymptote so just return false

    // so we will compute x, then plug it back into n = 4^x and verify

    if (n == 0) {
        return false;
    }

    int x = log(n)/log(4);

    int test = pow(4,x);

    if (test == n) {
        return true;
    }
    return false;
}