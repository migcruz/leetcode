/*
 * LeetCode Problem 746: Min Cost Climbing Stairs
 * Difficulty: Easy
 * 
 * Problem Description:
 * You are given an integer array `cost` where `cost[i]` is the cost of the i-th step on a staircase.
 * Once you pay the cost, you can either climb one or two steps.
 * 
 * You can start from step index 0 or step index 1.
 * Return the minimum cost to reach the top of the floor (beyond the last step).
 * 
 * Examples:
 * 
 * Example 1:
 *   Input: cost = [10,15,20]
 *   Output: 15
 *   Explanation:
 *     Start at index 1.
 *     - Pay 15 and climb two steps to the top.
 *     Total cost is 15.
 * 
 * Example 2:
 *   Input: cost = [1,100,1,1,1,100,1,1,100,1]
 *   Output: 6
 *   Explanation:
 *     Start at index 0.
 *     - Pay 1 → climb two steps to index 2.
 *     - Pay 1 → climb two steps to index 4.
 *     - Pay 1 → climb two steps to index 6.
 *     - Pay 1 → climb one step to index 7.
 *     - Pay 1 → climb two steps to index 9.
 *     - Pay 1 → climb one step to the top.
 *     Total cost is 6.
 * 
 * Constraints:
 *   - 2 <= cost.length <= 1000
 *   - 0 <= cost[i] <= 999
 */

int minCostClimbingStairs(int* cost, int costSize) {

    // we can use a dynamic programming approach
    // dp[n] = dp[n-1] + cost[n] or 
    // dp[n] = dp[n-2] + cost[n]

    // we just need to reach to the step that is cost[costSize - 1] or cost[costSize - 2], which ever is smaller is the answer

    if (cost == NULL) {
        return 0;
    }
    // start at index 0
    int dpN2 = cost[0];
    int dpN1 = cost[1];

    int dpN = 0;

    //edge cases
    if (costSize == 2){
        // choose the least of the two elements
        dpN = (cost[0] > cost[1]) ? cost[1] : cost[0];
        return dpN;
    }

    if (costSize == 3) {
        dpN = (cost[0] + cost[2] > cost[1]) ? cost[1] : cost[0] + cost[2];
        return dpN;
    }

    for (int i = 2 ; i < costSize; i++) {
        
        int tmp2 = dpN2 + cost[i];
        int tmp1 = dpN1 + cost[i];

        dpN = (tmp2 > tmp1) ? tmp1 : tmp2;

        if (i == costSize - 1) {
            // dont update dpN1 and dpN2 since w'ere at the end and we want to preserve those answers
            break;
        }
        
        dpN2 = dpN1;
        dpN1 = dpN;
    }

    // now that we're out of the array, lets compare dpN vs dpN1

    if (dpN < dpN1) {
        return dpN;
    }
    else {
        return dpN1;
    }
}