/*
 * LeetCode Problem 238: Product of Array Except Self
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an integer array 'nums', return an array 'answer' such that answer[i] 
 * is equal to the product of all the elements of 'nums' except nums[i].
 *
 * Rules:
 * - The product of any prefix or suffix of 'nums' is guaranteed to fit in a 32-bit integer.
 * - The solution must run in O(n) time complexity.
 * - Division operation is not allowed.
 *
 * Example 1:
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 *
 * Example 2:
 * Input: nums = [-1,1,0,-3,3]
 * Output: [0,0,9,0,0]
 *
 * Constraints:
 * - 2 <= nums.length <= 10^5
 * - -30 <= nums[i] <= 30
 * - The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
 *
 * Follow-up:
 * - Can you solve the problem in O(1) extra space complexity?
 *   (The output array does not count as extra space for space complexity analysis.)
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {

    // since we cant use division we need to construct 2 arrays, prefix and suffix, where prefix[i] is the product of all values before nums[i]
    // similarly, suffix is the product of all values after nums[i]

    if (nums == NULL) {
        *returnSize = 0;
        return NULL;
    }

    if (numsSize == 1) {
        *returnSize = 1;
        return nums;
    }

    int prefix[numsSize], suffix[numsSize];
    int *ans = (int*) malloc(sizeof(int) * numsSize);

    // fill up the prefix and suffix arrays
    int j = numsSize - 1;

    prefix[0] = 1;
    suffix[j] = 1;
    j--;
    for (int i = 1; i < numsSize; i++) {

        prefix[i] = prefix[i-1] * nums[i-1];
        suffix[j] = suffix[j+1] * nums[j+1];
        j--;
    }

    // fill up the answer array
    for (int i = 0; i < numsSize; i++) {

        ans[i] = prefix[i] * suffix[i];
       
    }

    *returnSize = numsSize;
    return ans;
    
}