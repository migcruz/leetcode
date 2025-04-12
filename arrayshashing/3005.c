/*
 * LeetCode Problem 3005: Count Elements With Maximum Frequency
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given an array 'nums' consisting of positive integers.
 * Return the total number of occurrences of all elements that have the maximum frequency in the array.
 *
 * The frequency of an element is the number of times it appears in the array.
 *
 * Example 1:
 * Input: nums = [1,2,2,3,1,4]
 * Output: 4
 * Explanation:
 * - Elements 1 and 2 both appear 2 times (maximum frequency).
 * - Total occurrences of these elements = 2 + 2 = 4.
 *
 * Example 2:
 * Input: nums = [1,2,3,4,5]
 * Output: 5
 * Explanation:
 * - All elements appear once (maximum frequency = 1).
 * - Total occurrences = 1 + 1 + 1 + 1 + 1 = 5.
 *
 * Constraints:
 * - 1 <= nums.length <= 100
 * - 1 <= nums[i] <= 100
 */

int maxFrequencyElements(int* nums, int numsSize) {
    // traverse the array while storing the frequencies then traverse the frequency array and to find out what the max frequency is
    // then we traverse the frequency array again to find out how many elements have this max frequency value then multiply that with maxFreq to get the total

    // alternatively we can just keep track of the max frequency encountered so far and keep updating that when traversing the original array. Then we traverse 
    // the frequency array and find out how many elements have this value. then multiply that with maxFreq to get the total

    if (nums == NULL) {
        return 0;
    }

    int freqArr[101] = {0}; // 101 because we will ignore index 0
    int j = 1;
    int ans = 0;
    int maxFreq = 0;

    for (int i = 0; i < numsSize; i++) {

        freqArr[nums[i]]++;
        maxFreq = (freqArr[nums[i]] > maxFreq) ? freqArr[nums[i]] : maxFreq;

    }

    // scan frequency array
    for (int i = 0; i < 101; i++) {

        if (freqArr[i] == maxFreq) {
            ans++;
        }

    }

    ans = ans * maxFreq;

    return ans;
    
}