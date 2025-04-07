/*
 * LeetCode Problem: Best Time to Buy and Sell Stock
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an array 'prices' where prices[i] represents the price of a given stock on the i-th day,
 * determine the maximum profit achievable by buying one stock on one day and selling it on a later day.
 *
 * Rules:
 * - You must buy before you sell.
 * - If no profit can be achieved, return 0.
 *
 * Example 1:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6 - 1 = 5.
 *
 * Example 2:
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: No transaction yields profit, so the max profit is 0.
 *
 * Constraints:
 * - 1 <= prices.length <= 10^5
 * - 0 <= prices[i] <= 10^4
 */

int maxProfit(int* prices, int pricesSize) {

    // keep track of the minimum price encountered
    // keep calculating profit each time we move through the array
    // if this profit is greater than the prev max profit encounters, update max profit
    // if we encounter a price that is lower than the minimum encountered so far, update that minimum price

    int ans = 0;
    int min = prices[0];
    int profit = 0;

    for (int i = 1; i < pricesSize; i++) {
        int tempProfit = prices[i] - min;

        if (tempProfit > profit) {
            profit = tempProfit;
        }

        if (prices[i] < min) {
            min = prices[i];
        }

    }
    
    
    return profit;
}