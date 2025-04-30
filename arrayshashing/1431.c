/*
 * LeetCode Problem 1431: Kids With the Greatest Number of Candies
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given an array `candies`, where each element represents the number of candies a kid has.
 * You're also given an integer `extraCandies`.
 * Return a boolean array `result` where result[i] is true if giving all the extraCandies to the ith kid 
 * makes them have the greatest (or tied for greatest) number of candies among all kids.
 *
 * Example 1:
 * Input: candies = [2,3,5,1,3], extraCandies = 3
 * Output: [true,true,true,false,true]
 *
 * Example 2:
 * Input: candies = [4,2,1,1,2], extraCandies = 1
 * Output: [true,false,false,false,false]
 *
 * Example 3:
 * Input: candies = [12,1,12], extraCandies = 10
 * Output: [true,false,true]
 *
 * Constraints:
 *   - n == candies.length
 *   - 2 <= n <= 100
 *   - 1 <= candies[i] <= 100
 *   - 1 <= extraCandies <= 50
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {

    // find the biggest number in the array then traverse the array again and add the extra candies to each child, if it's bigger than the
    // biggest number in the array then set to true

    if (candies == NULL) {
        *returnSize = 0;
        return NULL;
    }

    bool *ans = (bool*) calloc (candiesSize, sizeof(bool));
    int biggest = 0;

    for (int i = 0; i < candiesSize; i++) {
        biggest = (candies[i] > biggest) ? candies[i] : biggest;
    }

    for (int i = 0; i < candiesSize; i++) {
        int total = candies[i] + extraCandies;
        if (total >= biggest) {
            ans[i] = true;
        }
    }
    *returnSize = candiesSize;
    return ans;
}