/*
 * LeetCode Problem 35: Search Insert Position
 * Difficulty: Easy
 *
 * Problem Description:
 * Given a sorted array of distinct integers and a target value, return the index 
 * if the target is found. If the target is not found, return the index where it 
 * would be inserted in order.
 *
 * Rules:
 * - The input array is sorted in ascending order.
 * - The search must be performed in O(log n) runtime complexity.
 * - If the target exists in the array, return its index.
 * - If the target does not exist, return the index where it should be inserted.
 *
 * Example 1:
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 *
 * Example 2:
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 *
 * Example 3:
 * Input: nums = [1,3,5,6], target = 7
 * Output: 4
 *
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -10^4 <= nums[i] <= 10^4
 * - The array contains distinct values sorted in ascending order.
 * - -10^4 <= target <= 10^4
 */

int binarySearch(int *nums, int numsSize, int left, int right, int target, int lastMid) {

    int mid = lastMid;

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

    if (mid == lastMid) { //nothing found
        return mid;
    }

    return binarySearch(nums, numsSize, left, right, target, mid);


}

int searchInsert(int* nums, int numsSize, int target) {

    // since the array is already sorted, then we can just do binary search
    // if not found return the last index of binary search

    //try the edge cases
    if (target == nums[0]) {
        return 0;
    }

    if (target == nums[numsSize - 1]) {
        return numsSize - 1;
    }

    int left = 0;
    int right = numsSize - 1;
    int mid = left + (right - left) / 2;

    int ans = binarySearch(nums, numsSize, left, right, target, mid);

    while (nums[ans] > target) {
        ans--;
        if (ans < 0) {
            ans = 0;
            return ans;
        }
    }

    while (nums[ans] < target) {
        ans++;
        if (ans == numsSize) {
            return ans;
        }
    }

    return ans;
    
}