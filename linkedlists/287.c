/**
 * LeetCode Problem 287: Find the Duplicate Number
 * Difficulty: Medium
 *
 * Given an array nums containing n + 1 integers where each integer is in the range [1, n] inclusive,
 * there is exactly one duplicated number in the array.
 *
 * Return the repeated number.
 *
 * You must solve the problem without modifying the input array and using only constant extra space.
 *
 * Examples:
 *
 * Input: nums = [1,3,4,2,2]
 * Output: 2
 *
 * Input: nums = [3,1,3,4,2]
 * Output: 3
 *
 * Input: nums = [3,3,3,3,3]
 * Output: 3
 *
 * Constraints:
 * - 1 <= n <= 10^5
 * - nums.length == n + 1
 * - 1 <= nums[i] <= n
 * - All the integers in nums appear only once except for one that appears two or more times.
 *
 * Follow-up:
 * - How can we prove that at least one duplicate must exist?
 * - Can you solve this problem in linear runtime complexity?
 */

int findDuplicate(int* nums, int numsSize) {

    // Brute force: for each i, iterate through the array if the ith element is duplicated, if not, i++ and repeat. Trivial solution

    // //edge case, since we have access to the first and last element immediately we can compare and if they're the same, that's the answer

    if (nums[0] == nums[numsSize - 1]) {
        return nums[0];
    }

    // Tortoise and Hare implementation, used for detecting linked list loops and duplicates in arrays and cycles in graphs
    // on every iteration tortoise gets updated to tortoise = nums[tortoise]
    // on every iteration hare gets updated to hare = nums[nums[hare]]. that is hare, iterates at twice the speed
    // Time complexity: O(n), space complexity: O(1);
    int tortoise = 0;
    int hare = 0;
    while(1) {
        tortoise = nums[tortoise];
        hare = nums[nums[hare]];

        if (hare == tortoise) {
            // reset the tortoise to the beginning of the array
            tortoise = 0;

            //check if the tortoise and hare values are the same,. Tortoise and hare algo only guarantees finding a cycle if it exists, it cannot guarnatee finding duplicates
            if (nums[hare] == nums[tortoise]) {
                return nums[tortoise];
            }
            // now both hare and tortoise move at the same speed, the hare is stuck in the cycle
            while (1) {
                tortoise = nums[tortoise];
                hare = nums[hare];
                if (nums[hare] == nums[tortoise]) { // duplicate detected since hare != tortoise as theyre moving at the same speed
                    return nums[tortoise];
                }
            }
        }
    }
    
}