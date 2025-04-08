/*
 * LeetCode Problem 53: Maximum Subarray
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an integer array 'nums', find the contiguous subarray with the largest sum
 * and return its sum.
 *
 * Rules:
 * - The subarray must be contiguous.
 * - The sum of the subarray must be maximized.
 *
 * Example 1:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: The subarray [4,-1,2,1] has the largest sum 6.
 *
 * Example 2:
 * Input: nums = [1]
 * Output: 1
 * Explanation: The subarray [1] has the largest sum 1.
 *
 * Example 3:
 * Input: nums = [5,4,-1,7,8]
 * Output: 23
 * Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
 *
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 *
 * Follow-up:
 * - If you have figured out the O(n) solution, try coding another solution using the 
 *   divide and conquer approach, which is more subtle.
 */

// int maxCrossingSum(int nums[], int left, int mid, int right) {
//     int leftSum = -10001, rightSum = -10001;
//     int sum = 0;

//     // Scan left side
//     for (int i = mid; i >= left; i--) {
//         sum += nums[i];
//         if (sum > leftSum) leftSum = sum;
//     }

//     sum = 0;
//     // Scan right side
//     for (int i = mid + 1; i <= right; i++) {
//         sum += nums[i];
//         if (sum > rightSum) rightSum = sum;
//     }

//     return leftSum + rightSum;
// }

// // Recursive function for divide and conquer
// int maxSubArrayDivideAndConquer(int nums[], int left, int right) {
//     if (left == right) return nums[left]; // Base case (single element)

//     int mid = left + (right - left) / 2;

//     int leftMax = maxSubArrayDivideAndConquer(nums, left, mid); // Left subarray
//     int rightMax = maxSubArrayDivideAndConquer(nums, mid + 1, right); // Right subarray
//     int crossMax = maxCrossingSum(nums, left, mid, right); // Max crossing sum

//     int maxVal;
//     if (leftMax > rightMax) { 
//         // leftMax is larger than rightMax, now compare with crossMax
//         if (leftMax > crossMax) {
//             maxVal = leftMax;
//         } else {
//             maxVal = crossMax;
//         }
//     } else { 
//         // rightMax is larger than leftMax, now compare with crossMax
//         if (rightMax > crossMax) {
//             maxVal = rightMax;
//         } else {
//             maxVal = crossMax;
//         }
//     }

//     return maxVal;

//     // return (leftMax > rightMax) ? ((leftMax > crossMax) ? leftMax : crossMax) :
//     //                               ((rightMax > crossMax) ? rightMax : crossMax);
// }

// int maxSubArray(int* nums, int numsSize) {

//     // let's use divide and conquer

//     if (nums == NULL || numsSize == 0) {
//         return 0;
//     }

//     if (numsSize == 1) {
//         return nums[0];
//     }

//     int maxSum = maxSubArrayDivideAndConquer(nums, 0, numsSize - 1);
//     return maxSum;
// }

// Kadane's algorithm approach

// Mathematical Explanation
// If a window sum is negative, starting fresh gives a better chance of finding a higher sum in upcoming numbers.

// A negative sum essentially means the current subarray is hurting future growth rather than improving it.

// Resetting the sum ensures only positive sums carry forward while negative segments are discarded.

// Kadane’s Intuition
// ✔ If extending the current subarray improves the sum → Keep extending. ✔ If extending worsens the sum (sum goes negative) → Drop the current subarray and start new from the next element. ✔ Always track the highest sum found.

// Would you like a breakdown of how this compares to a brute-force approach? 🚀

// why not just reset if you encounter a negative number? cant you still get a larger sum by extending the window to find a bigger positive number even if the current sum is negative?
// Great thinking! You're absolutely right that a negative number alone doesn’t necessarily mean we should reset the window. Instead, we should reset only when the entire window sum becomes negative.

// Why Not Reset on Just a Negative Number?
// A single negative number doesn’t necessarily make the sum worse—if the previous sum is strongly positive, the subarray could still recover and grow.

// Resetting too aggressively would mean losing potentially valuable elements that could contribute to a larger sum when extended further.

// Why Reset When the Total Window Sum Is Negative?
// If the cumulative sum is negative, extending it further can’t help—the sum will always start lower than just picking the next number fresh.

// A negative sum drags down future growth, so starting fresh increases the chances of a better subarray.

int maxSubArray(int* nums, int numsSize) {

    // let's use kadane's algorithm

    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    if (numsSize == 1) {
        return nums[0];
    }

    int maxSum = nums[0]; // Store max sum found
    int currentSum = nums[0]; // Sum of current subarray

    for (int i = 1; i < numsSize; i++) {
        // Shrink window dynamically if sum is negative
        if (currentSum < 0) {
            currentSum = nums[i];
        } else {
            currentSum += nums[i]; // Expand window
        }

        maxSum = (currentSum > maxSum) ? currentSum : maxSum;
    }

    return maxSum;
    
}