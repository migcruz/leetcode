/*
 * LeetCode Problem 268: Missing Number
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an array nums containing n distinct numbers in the range [0, n],
 * return the only number in the range that is missing from the array.
 *
 * Examples:
 *
 * Example 1:
 * Input:  nums = [3,0,1]
 * Output: 2
 * Explanation:
 *   n = 3, so the numbers should be in the range [0,3].
 *   2 is the missing number.
 *
 * Example 2:
 * Input:  nums = [0,1]
 * Output: 2
 * Explanation:
 *   n = 2, so the numbers should be in the range [0,2].
 *   2 is the missing number.
 *
 * Example 3:
 * Input:  nums = [9,6,4,2,3,5,7,0,1]
 * Output: 8
 * Explanation:
 *   n = 9, so the numbers should be in the range [0,9].
 *   8 is the missing number.
 *
 * Constraints:
 *   n == nums.length
 *   1 <= n <= 10^4
 *   0 <= nums[i] <= n
 *   All the numbers of nums are unique.
 *
 * Follow-up:
 *   Could you implement a solution using only O(1) extra space 
 *   complexity and O(n) runtime complexity?
 */

int missingNumber(int* nums, int numsSize) {

    // let's try solving it using bitwise oeprators
    // we can use XOR similar to finding the non duplicate number
    // we will XOR every element in nums, then we will XOR every number from 0 to numsSize, then we XOR those two to get the missing number
    // essentially we are duplicating every number in nums except the missing number similar to 136

    if (nums == NULL) {
        return 0;
    }

    int numsXOR = 0;
    int numsSizeXOR = 0;
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        numsXOR = numsXOR ^ nums[i];
    }

    for (int i = 0; i < numsSize + 1; i++) {
        numsSizeXOR = numsSizeXOR ^ i;
    }

    ans = numsSizeXOR ^ numsXOR;
    return ans;

    // // we can make a frequency array of size 10^4 + 1 and scan nums
    // // any index with a value of 0 is the missing number

    // if (nums == NULL) {
    //     return 0;
    // }

    // int *freqArr = (int*) calloc (numsSize + 1, sizeof(int));
    // int ans = 0;

    // // scan nums
    // for (int i = 0; i < numsSize; i++) {

    //     freqArr[nums[i]]++;
    // }

    // //find the missing number
    // for (int i = 0; i < numsSize + 1; i++) {

    //     if (freqArr[i] == 0) {
    //         ans = i;
    //     }
    // }

    // free(freqArr);
    // return ans;
    
}