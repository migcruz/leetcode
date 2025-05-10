/*
 * LeetCode Problem 3423: Maximum Difference Between Adjacent Elements in a Circular Array
 * Difficulty: Easy
 *
 * Given a circular array nums, find the maximum absolute difference between adjacent elements.
 *
 * Note: In a circular array, the first and last elements are adjacent.
 *
 * Example 1:
 * Input: nums = [1,2,4]
 * Output: 3
 * Explanation: Because nums is circular, nums[0] and nums[2] are adjacent.
 * They have the maximum absolute difference of |4 - 1| = 3.
 *
 * Example 2:
 * Input: nums = [-5,-10,-5]
 * Output: 5
 * Explanation: The adjacent elements nums[0] and nums[1] have the maximum absolute difference of |-5 - (-10)| = 5.
 *
 * Constraints:
 *   2 <= nums.length <= 100
 *   -100 <= nums[i] <= 100
 */

int maxAdjacentDistance(int* nums, int numsSize) {

    // have two pointers left and right and compute the absolute difference, keep track of the biggest difference
    // if left == numsSize - 1. make sure right is using index zero

    if (nums == NULL) {
        return 0;
    }

    int left = 0;
    int right = 1;
    int ans = 0;

    for (right = 1; right <= numsSize; right++) {
        int temp;
        if (right == numsSize) { //wraparound
            temp = abs(nums[0] - nums[left]);
        }
        else {
            temp = abs(nums[right] - nums[left]);
        }
        ans = (temp > ans) ? temp : ans;
        left++;
    }

    return ans;
}