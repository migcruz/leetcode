/*
 * LeetCode Problem 338: Counting Bits
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an integer n, return an array ans of length n + 1 such that 
 * for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 *
 * Examples:
 *
 * Example 1:
 * Input: n = 2
 * Output: [0,1,1]
 * Explanation:
 * 0 --> 0
 * 1 --> 1
 * 2 --> 10
 *
 * Example 2:
 * Input: n = 5
 * Output: [0,1,1,2,1,2]
 * Explanation:
 * 0 --> 0
 * 1 --> 1
 * 2 --> 10
 * 3 --> 11
 * 4 --> 100
 * 5 --> 101
 *
 * Constraints:
 *   0 <= n <= 10^5
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize) {

    // every even number will have the same number of 1s as itself divided by 2. For example, 4 and 2 have the same # of 1s and 6 and 3 have the same # of 1s
    // also for every odd number, the number of 1s is the the same as the previous number + 1
    // therefore we can use a dp approach to solve 

    // dp[n] = dp[n/2] if n is even
    // dp[n] = dp[n-1] + 1 if n is odd
    

    int *ans = (int*) calloc (n + 1, sizeof(int));
    *returnSize = n + 1;
    ans[0] = 0;

    if (n == 0) {
        return ans;
    }
    ans[1] = 1;

    for (int i = 2; i < n + 1; i++) {

        if ( i % 2 == 0) {
            ans[i] = ans[i/2];
        }
        else {
            ans[i] = ans[i-1] + 1;
        }

    }
    return ans;



    // for every i we will AND it with 0b1 and then shift it to the right by 1 until it is zero
    // every successful AND operation increase the counter
    // however this solution is not as efficient

    // if (n == 0) {
    //     *returnSize = 0;
    //     return NULL;
    // }

    // int *ans = (int*) calloc (n + 1, sizeof(int));

    // for (int i = 0; i < n + 1; i++) {
    //     int count = 0;
    //     int j = i;
    //     while (j != 0) {
    //         int temp = j & 0b1;
    //         if (temp) {
    //             count++;
    //         }
    //         j = j >> 1;
    //     }
    //     ans[i] = count;

    // }
    // *returnSize = n + 1;
    // return ans;
    
}