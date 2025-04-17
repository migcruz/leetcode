/*
 * LeetCode Problem 2855: Minimum Right Shifts to Sort the Array
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given a 0-indexed array `nums` of length `n` containing distinct positive integers.
 * Your task is to determine the minimum number of right shifts required to sort `nums` in 
 * non-decreasing order. If it is not possible to sort the array by performing right shifts, 
 * return -1.
 *
 * A right shift moves the element at index `i` to index `(i + 1) % n` for all indices.
 *
 * Examples:
 *
 * Example 1:
 *   Input: nums = [3, 4, 5, 1, 2]
 *   Output: 2
 *   Explanation:
 *     - After 1st shift: [2, 3, 4, 5, 1]
 *     - After 2nd shift: [1, 2, 3, 4, 5] → sorted
 *
 * Example 2:
 *   Input: nums = [1, 3, 5]
 *   Output: 0
 *   Explanation: The array is already sorted; no shifts needed.
 *
 * Example 3:
 *   Input: nums = [2, 1, 4]
 *   Output: -1
 *   Explanation: No number of right shifts will result in a sorted array.
 *
 * Constraints:
 *   - 1 <= nums.length <= 100
 *   - 1 <= nums[i] <= 100
 *   - All elements in nums are distinct.
 */

// int binarySearch(int *nums, int numsSize, int left, int right) {

//     // we actually want to return left when it comes to using binary search for pivot points

//     int mid = left + (right - left) / 2;
    
//     while (left < right) { // not <= because we're interested in finding the values of left

//         if (nums[mid] > nums[right]) { // haven't found pivot point yet
//             left = mid + 1;
//             mid = left + (right - left) / 2; // updated mid after so we calculate it 1 last time ebfore leaving while loop

//         }
//         else {
//             right = mid; // ot mid - 1 because we're interested in finding the values of left
//             mid = left + (right - left) / 2;
//         }
//     }
//     return left;

// }

int minimumRightShifts(int* nums, int numsSize) {

    // use binary search for the pivot point
    // find the difference between the pivot point index and to the end of the array
    // then add 1 adn that should be in teh answer ( or just do arrLen - pivotindex)

    //OR
    // just do linear in the array

    // edge cases to consider:

    // if the pivot index is zero, the means the array is already sorted

    // check the pivot index if its not at the end of the array and ocmpare the first and last elements of the array. if the last element is larger than the first, return - 1

    // if there is another pivot point in the array then return -1

    // if the nums[pivotIndex] > nums[0] return -1


    int pivotCount = 0;
    int pivotIndex = 0;
    int ans = 0;
    int prev = 0;

    for (int i = 0; i < numsSize; i++) {

        if (nums[i] < prev) {
            pivotCount++;
            pivotIndex = i;
        }

        prev = nums[i];
    }
    // printf("pivotIndex: %d\n", pivotIndex);
    if (pivotCount > 1) {
        return - 1;
    }
    else if (pivotIndex == 0) { // array already sorted
        return ans;
    }
    else if (pivotIndex != numsSize - 1 && nums[0] < nums[numsSize - 1]) {
        return -1;
    }
    else if (nums[pivotIndex] > nums[0]) {
        return - 1;
    }

    ans = numsSize - pivotIndex;
    return ans;



    // if (nums == NULL || numsSize == 1) {
    //     return 0;
    // } 
    // int ans = 0;
    // int pivotIndex = binarySearch(nums, numsSize, 0 , numsSize - 1);
    // printf("pivotIndex: %d\n", pivotIndex);

    // if (pivotIndex == 0) {// array already sorted
    //     return ans;
    // }
    // else if (pivotIndex != numsSize - 1 && nums[0] < nums[numsSize - 1]) {
    //     return -1;
    // }
    // else if (pivotIndex != numsSize - 1) {
    //     // check for another pivot point
    //     int newPivot = binarySearch(nums, numsSize, pivotIndex + 1, numsSize - 1);
    //     if (newPivot != pivotIndex + 1) {
    //         return - 1;
    //     }
    // }

    // ans = numsSize - pivotIndex;

    // return ans;

}