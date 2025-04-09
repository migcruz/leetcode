/*
 * LeetCode Problem 70: Climbing Stairs
 * Difficulty: Easy
 * 
 * Problem Description:
 * You are climbing a staircase. It takes 'n' steps to reach the top.
 * 
 * Each time you can either climb 1 or 2 steps. In how many distinct ways 
 * can you climb to the top?
 * 
 * Examples:
 * 
 * Example 1:
 *   Input: n = 2
 *   Output: 2
 *   Explanation: There are two ways to climb to the top.
 *                1. 1 step + 1 step
 *                2. 2 steps
 * 
 * Example 2:
 *   Input: n = 3
 *   Output: 3
 *   Explanation: There are three ways to climb to the top.
 *                1. 1 step + 1 step + 1 step
 *                2. 1 step + 2 steps
 *                3. 2 steps + 1 step
 * 
 * Constraints:
 *   - 1 <= n <= 45
 */

int climbStairs(int n) {
    
    // use dynamic programming approach
    // this gives us the formula: dp[n]=dp[n−1]+dp[n−2]
    // dp[0] = 1, only 1 way to to stay still
    // dp[1] = , take one step
    // dp[2] = dp[1] + dp[0] = 1 + 1 = 2
    // dp[3] = dp[2] + dp[1] = 2 + 1 = 3

    if (n == 1 || n == 0 || n < 0) {
        return 1;
    }

    int dpN1 = 1;
    int dpN2 = 1;
    int ans = dpN1 + dpN2;
    
    for (int i = 2; i <= n; i++) {
        ans = dpN1 + dpN2;
        dpN2 = dpN1;
        dpN1 = ans;

        // printf("dpN1: %d, dpN2: %d, ans: %d \r\n", dpN1, dpN2, ans);
    }

    return ans;
}