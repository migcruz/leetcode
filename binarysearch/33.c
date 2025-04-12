/*
 * LeetCode Problem 33: Search in Rotated Sorted Array
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an integer array 'nums' sorted in ascending order (with distinct values),
 * it may have been rotated at an unknown pivot index 'k' such that the resulting
 * array is [nums[k], ..., nums[n-1], nums[0], ..., nums[k-1]].
 *
 * Given the rotated array and an integer 'target', return the index of 'target' 
 * if it exists in 'nums', or -1 if it does not.
 *
 * The solution must have O(log n) time complexity.
 *
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 *
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 *
 * Constraints:
 * - 1 <= nums.length <= 5000
 * - -10^4 <= nums[i] <= 10^4
 * - All elements of 'nums' are unique
 * - 'nums' is sorted and possibly rotated
 * - -10^4 <= target <= 10^4
 */

int binarySearch(int *nums, int numsSize, int target, int left, int right) {

    int mid = left + (right - left) / 2; // prevent integer overflow

    while (left < right) {

        if (nums[mid] < target) {// pivot is on the right half
            left = mid + 1;
            mid = left + (right - left) / 2;
        }
        else if (nums[mid] > target){ // pivot is on the left half
            right = mid;
            mid = left + (right - left) / 2;
        }
        else {// found target
            return mid;
        }
    }

    //check one last time in case the array is size 1 or 2
    if (nums[mid] == target) {
        return mid;
    }
    
    return -1; // not found

}

int findPivot(int *nums, int numsSize) {

    int left = 0;
    int right = numsSize - 1;

    int mid = left + (right - left) / 2; // prevent integer overflow

    while (left < right) {

        if (nums[mid] > nums[right]) {// pivot is on the right half
            left = mid + 1;
            mid = left + (right - left) / 2;
        }
        else { // pivot is on the left half
            right = mid;
            mid = left + (right - left) / 2;
        }
    }
    
    return left;

}

int search(int* nums, int numsSize, int target) {
    //distinct values in nums and sorted ascending
    // nums is only possibly rotated
    // if nums[0] > nums[numsSize - 1] then the array is rotated
    // else is it not rotated, if they are equal then all elements in the array are equal, rotated or not

    // if not rotated, then just do binary search
    // if rotated, we need to do binary search on 2 arrays, the left side of k and the right side of k, both would be in ascending order
    // the problem is find out where k is. we can find out where k is by scanning the array but that will lead to a O(n) solution
    // if the array is rotated, the location of the minimum value is the pivot point k

    if (nums == NULL) {
        return -1;
    }

    if (numsSize == 1) {
        if (nums[0] == target) {
            return 0;
        }
        return -1;
    }

    int ans = -1;

    // Check if the array is rotated
    if (nums[0] > nums[numsSize - 1]) {//rotated
        int pivot = findPivot(nums, numsSize);
        // printf("pivot %d\r\n", pivot);

        // check right side of pivot
        ans = binarySearch(nums, numsSize, target, pivot, numsSize - 1);
        if (ans != -1) { // found
            return ans;
        }

        // now lets try the left side of pivot
        ans = binarySearch(nums, numsSize, target, 0, pivot); //draw a sample array to figure out how we came up with the new array sizes

    }
    else {// just do normal binary search
        ans = binarySearch(nums, numsSize, target, 0, numsSize - 1);

    }

    return ans;
    
}