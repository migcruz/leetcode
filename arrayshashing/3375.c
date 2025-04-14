/**
 * LeetCode Problem 3375: Minimum Operations to Make Array Values Equal to K
 * Difficulty: Easy
 *
 * You are given an integer array nums and an integer k.
 *
 * An integer h is called valid if all values in the array that are strictly
 * greater than h are identical.
 *
 * You are allowed to perform the following operation:
 * - Select a valid integer h for the current array.
 * - For each index i where nums[i] > h, set nums[i] = h.
 *
 * Return the minimum number of operations required to make every element in nums equal to k.
 * If it is impossible to do so, return -1.
 *
 * Examples:
 *
 * Input: nums = [5,2,5,4,5], k = 2
 * Output: 2
 * Explanation: Perform operations using h = 4 and then h = 2.
 *
 * Input: nums = [2,1,2], k = 2
 * Output: -1
 * Explanation: It is impossible to make all elements equal to 2.
 *
 * Input: nums = [9,7,5,3], k = 1
 * Output: 4
 * Explanation: Perform operations in the order h = 7, 5, 3, and 1.
 *
 * Constraints:
 * - 1 <= nums.length <= 100
 * - 1 <= nums[i] <= 100
 * - 1 <= k <= 100
 */

int minOperations(int* nums, int numsSize, int k) {
    // this is word salad but apparently just need to find out how many distinct integers are greater than k
    // do a frequency array scan of nums
    // edge case, if the minimum element in nums is less than k return -1

    if (nums == NULL) {
        return -1;
    }

    int count = 0;
    int min = 100;
    int freqArr[101] = {0};// we will ignore 0 since its not in the range
    
    for (int i = 0; i < numsSize; i++) {

        if (nums[i] > k) {
            freqArr[nums[i]]++;
        }

        min = (nums[i] < min) ? nums[i] : min;

    }

    if (min < k) {
        return -1;
    }

    //scan frequency array for numbers with freq greater than zero
    for (int i = 0; i < 101; i++) {
        if (freqArr[i] > 0) {
            count++;
        }
    }

    return count;

    
}