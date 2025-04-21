/*
 * LeetCode Problem 136: Single Number
 * Difficulty: Easy
 *
 * Problem Description:
 * Given a non-empty array of integers `nums`, every element appears exactly twice except for one.
 * Find the element that appears only once.
 *
 * You must implement a solution with linear runtime complexity (O(n))
 * and use only constant extra space (O(1)).
 *
 * Examples:
 *
 * Example 1:
 * Input: nums = [2, 2, 1]
 * Output: 1
 * Explanation:
 * The number 1 appears only once, all others appear twice.
 *
 * Example 2:
 * Input: nums = [4, 1, 2, 1, 2]
 * Output: 4
 * Explanation:
 * 4 appears once, others appear twice.
 *
 * Example 3:
 * Input: nums = [1]
 * Output: 1
 * Explanation:
 * Only one element in the array.
 *
 * Constraints:
 *   - 1 <= nums.length <= 3 * 10^4
 *   - -3 * 10^4 <= nums[i] <= 3 * 10^4
 *   - Each element in the array appears exactly twice, except for one element that appears once.
 */

int singleNumber(int* nums, int numsSize) {

    // cant sort because that would be a non linear solution
    // we know that XOR a ^ a = 0
    // we know that XOR is commutative (order of operations don't matter)
    // so if we keep XORing every element we will eventually be simplified down to 0 ^ 0 ^ 0... ^ ans = 0 ^ ans = ans

    int ans = 0;

    if (nums == NULL) {
        return 0;
    }

    if (numsSize == 1) {
        return nums[0];
    }

    for (int i = 0; i < numsSize; i++) {
        
        ans ^= nums[i];
    }

    return ans;
    
}