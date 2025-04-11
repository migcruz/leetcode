/*
 * LeetCode Problem 2455: Average Value of Even Numbers That Are Divisible by Three
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an integer array 'nums' of positive integers, return the average value 
 * of all even integers that are divisible by 3.
 *
 * The average of 'n' elements is defined as the sum of those elements divided 
 * by 'n', rounded down to the nearest integer.
 *
 * Example 1:
 * Input: nums = [1,3,6,10,12,15]
 * Output: 9
 * Explanation: 6 and 12 are even numbers divisible by 3. (6 + 12) / 2 = 9.
 *
 * Example 2:
 * Input: nums = [1,2,4,7,10]
 * Output: 0
 * Explanation: No numbers meet the condition, so the result is 0.
 *
 * Constraints:
 * - 1 <= nums.length <= 1000
 * - 1 <= nums[i] <= 1000
 */

int averageValue(int* nums, int numsSize) {

    //division in C already rounds down
    // check every answer thats divisible by 3 in the array, and keep a running total sum, also keep track of how many elements are divisible by 3
    // then compute average

    if (nums == NULL) {
        return 0;
    }

    int sum = 0;
    int count = 0;
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {

        if (nums[i] % 3 == 0 && nums[i] % 2 == 0) {// divisible by 3
            sum += nums[i];
            count++;
        }

    }

    if (count == 0) {
        return 0;
    }

    ans = sum / count;

    return ans;
    
}