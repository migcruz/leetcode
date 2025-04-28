/*
 * LeetCode Problem 3354: Make Array Elements Equal to Zero
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given an integer array `nums`.
 * 
 * - Start by choosing an initial position `curr` where nums[curr] == 0 and a direction (left or right).
 * - Repeat:
 *     - If `curr` is out of bounds, the process ends.
 *     - If nums[curr] == 0, move one step in the current direction.
 *     - Else if nums[curr] > 0:
 *         - Decrement nums[curr] by 1.
 *         - Reverse movement direction.
 *         - Move one step in the new direction.
 * 
 * A selection (starting position and direction) is **valid** if all elements of `nums` become 0 after the process.
 * 
 * Return the number of possible valid selections.
 *
 * Examples:
 *
 * Example 1:
 * Input: nums = [1,0,2,0,3]
 * Output: 2
 * 
 * Example 2:
 * Input: nums = [2,3,4,0,4,1,0]
 * Output: 0
 *
 * Constraints:
 *   1 <= nums.length <= 100
 *   0 <= nums[i] <= 100
 *   There is at least one element where nums[i] == 0
 */

bool verifyZeroes(int *numsCopy, int numsSize) {

    for (int i = 0; i < numsSize; i++) {
        if (numsCopy[i] != 0) {
            return false;
        }
    }
    return true;
}

int countValidSelections(int* nums, int numsSize) {

    // we traverse the array and start the process when nums[curr] == 0, we exit the current loop if curr < 0 or > n - 1.
    // once we exit we check if the array is all 0s, if true then increase ans by 1
    // try again by starting left or right
    // repeat again by resetting nums and finding the next 0

    // this is the brute force solution, we can also optimize further by doing a prefix sum
        // This question is really simple if you know the concept and usage of prefix sum and suffix sum. 
        //At the position where nums[i] == 0, if the prefix sum and suffix sum at that same position are equal (prefix_sum[i] == suffix_sum[i]), increment the selection count by 2 (Case 1).
        // If the absolute difference between the prefix sum and suffix sum at that position is 1 (abs(prefix_sum[i] - suffix_sum[i]) == 1), increment the selection count by 1 (Case 2).

    if (nums == NULL) {
        return 0;
    }

    int *numsCopy = (int*) calloc (numsSize, sizeof(int));
    memcpy(numsCopy, nums, sizeof(int) * numsSize);
    int ans = 0;
    bool goRight = true;

    for (int curr = 0; curr < numsSize; curr++) {

        if (nums[curr] == 0) {

            int i = curr;

            // try going right to start    
            while (i >= 0 && i <= numsSize - 1) {
               
                if (numsCopy[i] > 0) {
                    numsCopy[i]--;
                    // reverse direction
                    goRight = !goRight;
                }
                
                if (goRight) {
                    i++;
                }
                else {
                    i--;
                }
            }
            if (verifyZeroes(numsCopy, numsSize)) {
                ans++;
            }

            // reset numsCopy
            memcpy(numsCopy, nums, sizeof(int) * numsSize);
            i = curr;
            goRight = false;
            // try going left now to start 
            while (i >= 0 && i <= numsSize - 1) {
               
                if (numsCopy[i] > 0) {
                    numsCopy[i]--;
                    // reverse direction
                    goRight = !goRight;
                }
                
                if (goRight) {
                    i++;
                }
                else {
                    i--;
                }
            }
            if (verifyZeroes(numsCopy, numsSize)) {
                ans++;
            }
        }

        goRight = true;
        memcpy(numsCopy, nums, sizeof(int) * numsSize);
    }

    return ans;
    
}