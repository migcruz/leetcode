/*
 * LeetCode Problem 3194: Minimum Average of Smallest and Largest Elements
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given an array `nums` of even length `n`.
 * Initialize an empty array `averages`.
 * 
 * Repeat the following `n / 2` times:
 *   - Remove the smallest element `minElement` and the largest element `maxElement` from `nums`.
 *   - Add their average `(minElement + maxElement) / 2` to `averages`.
 * 
 * Return the minimum value from the `averages` array.
 *
 * Examples:
 *
 * Example 1:
 * Input: nums = [7,8,3,4,15,13,4,1]
 * Output: 5.5
 *
 * Example 2:
 * Input: nums = [1,9,8,3,10,5]
 * Output: 5.5
 *
 * Example 3:
 * Input: nums = [1,2,3,7,8,9]
 * Output: 5.0
 *
 * Constraints:
 *   2 <= n == nums.length <= 50
 *   n is even
 *   1 <= nums[i] <= 50
 */

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int left_size = mid - left + 1;
    int right_size = right - mid;

    int left_arr[left_size], right_arr[right_size];

    // Copy data to temporary arrays
    for (i = 0; i < left_size; i++)
        left_arr[i] = arr[left + i];
    for (j = 0; j < right_size; j++)
        right_arr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0; // Initial index of left array
    j = 0; // Initial index of right array
    k = left; // Initial index of merged array

    while (i < left_size && j < right_size) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left_arr[], if any
    while (i < left_size) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    // Copy remaining elements of right_arr[], if any
    while (j < right_size) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

// Merge Sort function
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Merge sorted halves
        merge(arr, left, mid, right);
    }
}

double minimumAverage(int* nums, int numsSize) {

    if (nums == NULL) {
        return 0;
    }

    // sort nums first then computer the average from both ends of the sorted array using 2 ptrs left right
    // then left++ then right-- while left < right
    // keep a running ans that we only update if we encounter an average that is less

    int left = 0;
    int right = numsSize - 1;
    double ans = 200;

    // merge sort
    merge_sort(nums, left, right);;

    while (left < right) {
        double temp = ((double)nums[left] + (double)nums[right]) / 2;
        left++;
        right--;

        ans = (temp < ans) ? temp : ans;
    }

    return ans;
    
}