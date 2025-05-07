/*
 * LeetCode Problem 1005: Maximize Sum Of Array After K Negations
 * Difficulty: Easy
 *
 * Given an integer array nums and an integer k, modify the array in the following way:
 *   - Choose an index i and replace nums[i] with -nums[i].
 * You must apply this process exactly k times. You may choose the same index multiple times.
 *
 * Return the largest possible sum of the array after k modifications.
 *
 * Example 1:
 * Input: nums = [4,2,3], k = 1
 * Output: 5
 * Explanation: Choose index 1 and nums becomes [4,-2,3].
 *
 * Example 2:
 * Input: nums = [3,-1,0,2], k = 3
 * Output: 6
 * Explanation: Choose indices (1, 2, 2) and nums becomes [3,1,0,2].
 *
 * Example 3:
 * Input: nums = [2,-3,-1,5,-4], k = 2
 * Output: 13
 * Explanation: Choose indices (1, 4) and nums becomes [2,3,-1,5,4].
 *
 * Constraints:
 *   - 1 <= nums.length <= 10^4
 *   - -100 <= nums[i] <= 100
 *   - 1 <= k <= 10^4
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
int largestSumAfterKNegations(int* nums, int numsSize, int k) {

    // find the smallest numbers in the array and flip it's sign so it will either reduce the sum by a little or a add a big previously negative
    // number to the sum

    // to do this we can do a merge sort to have the smallest numbers at the front
    // we will d othis operation if the number is negative and goto the next element for the operation to be repeated
    // if we hit a 0 or greater number we will apply the remaining k operations on that number only 

    if (nums == NULL) {
        return 0;
    }

    int ans = 0;
    int kCount = k;
    merge_sort(nums, 0, numsSize - 1);

    // for (int i = 0; i < numsSize; i++) {
    //     printf("%d ", nums[i]);
    // }
    // printf("\n");

    int i = 0;
    bool flag = true;
    while (kCount > 0) {

        if (nums[i] >= 0) {
            flag = false;
            if (i > 0 && abs(nums[i-1]) < nums[i]) { // edge case -8 -5 -5 -3 -2 3 
                i--; // just stay at the last negative number
            }
        }

        nums[i] = -1 * nums[i];
        kCount--;
        if (flag && i < numsSize - 1) {
            i++;
        }
    }

    // sum the array

    for (int i = 0; i < numsSize; i++) {
        ans += nums[i];
    }

    return ans;
}