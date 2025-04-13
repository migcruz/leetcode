/*
 * LeetCode Problem 1539: Kth Missing Positive Number
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given a sorted array 'arr' of positive integers in strictly increasing order,
 * and an integer 'k'. The task is to return the k-th positive integer that is missing from the array.
 *
 * Example 1:
 * Input: arr = [2, 3, 4, 7, 11], k = 5
 * Output: 9
 * Explanation:
 * - The missing positive integers are: [1, 5, 6, 8, 9, 10, 12, ...]
 * - The 5th missing number is 9.
 *
 * Example 2:
 * Input: arr = [1, 2, 3, 4], k = 2
 * Output: 6
 * Explanation:
 * - The missing positive integers are: [5, 6, 7, ...]
 * - The 2nd missing number is 6.
 *
 * Constraints:
 * - 1 <= arr.length <= 1000
 * - 1 <= arr[i] <= 1000
 * - 1 <= k <= 1000
 * - arr is strictly increasing (arr[i] < arr[j] for i < j)
 *
 * Follow-Up:
 * - Can you solve this in less than O(n) time complexity?
 */

int findKthPositive(int* arr, int arrSize, int k) {
    // make a frequency array storing the frequencies of every intger. Since there are no duplicates and is strictly increasing, we jsut need to check the kth element
    // in the frequency array whose value is 0 and return the index

    if (arr == NULL) {
        return 0;
    }

    int ans = -1;
    int count = 0;

    int freqArr[2001] = {0}; // 2001 because we will ignore index 0 and we will double the domain range just in case the first element is 1000


    for (int i = 0; i < arrSize; i++) { // scann array

        freqArr[arr[i]]++;
    }

    // scan freqArr
    for (int i = 1; i < 2001; i++) { // scann array

        if (freqArr[i] == 0) {
            // printf("i: %d\r\n", i);
            count++;
        }

        if (count == k) {
            ans = i;
            break;
        }
    }

    return ans;
}