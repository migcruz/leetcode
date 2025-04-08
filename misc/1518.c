/*
 * LeetCode Problem 1518: Water Bottles
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given 'numBottles' full water bottles. Drinking a bottle turns it into an empty bottle.
 * You can exchange 'numExchange' empty bottles for one full water bottle from the market.
 * Determine the maximum number of water bottles you can drink.
 *
 * Rules:
 * - Each full bottle consumed turns into an empty bottle.
 * - If 'numExchange' empty bottles are collected, they can be exchanged for one full bottle.
 * - The goal is to maximize the number of water bottles that can be consumed.
 *
 * Example 1:
 * Input: numBottles = 9, numExchange = 3
 * Output: 13
 * Explanation: 
 * - Start with 9 full bottles.
 * - After drinking 9 bottles, you have 9 empty bottles.
 * - Exchange 3 empty bottles to get 3 full bottles.
 * - Drink 3 more bottles (now have 3 empty bottles).
 * - Exchange 3 empty bottles for 1 full bottle.
 * - Drink the last bottle.
 * - Total bottles consumed: 9 + 3 + 1 = 13.
 *
 * Example 2:
 * Input: numBottles = 15, numExchange = 4
 * Output: 19
 * Explanation:
 * - Start with 15 full bottles.
 * - Drink 15 bottles, obtaining 15 empty bottles.
 * - Exchange 4 empty bottles for 3 full bottles.
 * - Drink those 3 bottles (now have 3 empty bottles).
 * - Exchange 4 empty bottles for 1 full bottle.
 * - Drink the final bottle.
 * - Total bottles consumed: 15 + 3 + 1 = 19.
 *
 * Constraints:
 * - 1 <= numBottles <= 100
 * - 2 <= numExchange <= 100
 */

int numWaterBottles(int numBottles, int numExchange) {

    int emptyBottles = 0;
    int ans = 0;

    while (numBottles != 0) {

        numBottles--;
        emptyBottles++;
        ans++;

        if (emptyBottles == numExchange) {
            emptyBottles = 0;
            numBottles++;
        }
    }

    return ans;
    
}