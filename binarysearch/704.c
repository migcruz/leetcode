/*
 * LeetCode Problem 704: Binary Search
 * Difficulty: Easy
 *
 * Problem Description:
 * Given a sorted array of integers 'nums' in ascending order, and an integer 'target',
 * write a function to search for 'target' in 'nums'. 
 * If 'target' exists, return its index; otherwise, return -1.
 *
 * The solution must run in O(log n) time complexity.
 *
 * Example 1:
 * Input: nums = [-1,0,3,5,9,12], target = 9
 * Output: 4
 * Explanation: The target number 9 exists at index 4 in the array.
 *
 * Example 2:
 * Input: nums = [-1,0,3,5,9,12], target = 2
 * Output: -1
 * Explanation: The number 2 is not present in the array, so return -1.
 *
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -10^4 < nums[i], target < 10^4
 * - All integers in 'nums' are unique.
 * - 'nums' is sorted in ascending order.
 */

int search(int* nums, int numsSize, int target) {
    
    // since the array is already sorted, we can search by starting at the halfway point of the array
    // then we compare if this value is below or higher than the target
    // if it is higher, then we take the middle index between 0 and mid, if lower then the next try is at middle index between mid and end of array

    int left = 0;
    int right = numsSize - 1;
    int mid = (left + right) / 2;

    //try the edge cases
    if (target == nums[0]) {
        return 0;
    }

    if (target == nums[numsSize - 1]) {
        return numsSize - 1;
    }

    while (1) {
        int lastmid = mid;
        if (nums[mid] > target) {
            //try somewhere between left and mid
            right = mid;
            mid = left + (right - left) / 2; // not just (right + left) / 2 to prevent buffer overflow for very large arrays.
            
        }
        else if (nums[mid] < target) {
            //try somewhere between mid and right
            left = mid;
            mid = left + (right - left) / 2;
        }
        else { // this is the answer
            return mid;
        }

        if (mid == lastmid) { //nothing found
            return -1;
        }
    }
    

}