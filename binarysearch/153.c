/*
 * LeetCode Problem 153: Find Minimum in Rotated Sorted Array
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an array 'nums' of length 'n' that is sorted in ascending order and 
 * then rotated between 1 and 'n' times, find the minimum element in the array.
 *
 * Rotation Example:
 * - Original sorted array: [0,1,2,4,5,6,7]
 * - Rotated 4 times: [4,5,6,7,0,1,2]
 * - Rotated 7 times: [0,1,2,4,5,6,7] (same as original)
 * 
 * A rotation of 1 time moves the last element to the front.
 * 
 * You must write an algorithm that runs in O(log n) time.
 *
 * Example 1:
 * Input: nums = [3,4,5,1,2]
 * Output: 1
 * Explanation: The original sorted array was [1,2,3,4,5], rotated 3 times.
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2]
 * Output: 0
 * Explanation: The original sorted array was [0,1,2,4,5,6,7], rotated 4 times.
 *
 * Example 3:
 * Input: nums = [11,13,15,17]
 * Output: 11
 * Explanation: The original sorted array was [11,13,15,17], rotated 4 times.
 *
 * Constraints:
 * - n == nums.length
 * - 1 <= n <= 5000
 * - -5000 <= nums[i] <= 5000
 * - All integers in 'nums' are unique.
 * - 'nums' is sorted and rotated between 1 and n times.
 */

int findMin(int* nums, int numsSize) {

    // if rotation == numsSize then nums is the same as original
    // nums[0] > nums[numsSize-1] if rotation was greater than 0 but less than numsSize
    // we can use this to check the trivial solution, otherwise we use binary search knowing that num[numsSize - 1] is the first answer candidate
    // then we just need to find a number smaller and keep updating the answer while we do binary search.

    if (nums[0] < nums[numsSize - 1]) {
        return nums[0];
    }

    int ans = nums[numsSize - 1]; // current best answer
    int left = 0;
    int right = numsSize - 1;
    int mid = (left + right) / 2;
    // lets use the binary search to find the smallest number

     while (1) {
        int lastmid = mid;
        if (nums[mid] > ans) {
            //try somewhere between mid and right
            left = mid;
            mid = left + (right - left) / 2;
            
        }
        else if (nums[mid] < ans) {
            //try somewhere between left and mid
            ans = nums[mid];
            right = mid;
            mid = left + (right - left) / 2;
        }

        if (mid == lastmid) { //nothing else found
            return ans;
        }
    }    
}