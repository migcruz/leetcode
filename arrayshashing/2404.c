/*
 * LeetCode Problem 2404: Most Frequent Even Element
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an integer array 'nums', return the most frequent even element.
 *
 * If there is a tie for frequency, return the smallest such element.
 * If there is no even element in the array, return -1.
 *
 * Example 1:
 * Input: nums = [0,1,2,2,4,4,1]
 * Output: 2
 * Explanation: The even elements are 0, 2, and 4. Of these, 2 and 4 appear 
 * most frequently. We return the smallest one, which is 2.
 *
 * Example 2:
 * Input: nums = [4,4,4,9,2,4]
 * Output: 4
 * Explanation: 4 is the even element that appears the most.
 *
 * Example 3:
 * Input: nums = [29,47,21,41,13,37,25,7]
 * Output: -1
 * Explanation: There are no even elements in the array.
 *
 * Constraints:
 * - 1 <= nums.length <= 2000
 * - 0 <= nums[i] <= 10^5
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

int mostFrequentEven(int* nums, int numsSize) {

    //sort the array first
    // check if element is even, if so start counting, stop counting when number changes and update ans
    // this will be O(N log N)

    // OR

    // do a hash map approach since theres only a max 2000 elements and keep track of the counts that way.
    // this would be O(N) time complexity
    
    if (nums == NULL) {
        return -1;
    }

    int ans = -1;
    int count = 0;
    int ansCount = 0;
    bool flag = false;
    int prevNumber = 0;

    merge_sort(nums, 0, numsSize - 1);

    for (int i = 0; i < numsSize; i++) {

        if (nums[i] != prevNumber) {
            count = 0; //reset
        }

        if (nums[i] % 2 == 0) {//found even
            count++;
        }

        if (count > ansCount) {
            ansCount = count;
            ans = nums[i];
        }

        prevNumber = nums[i];

    }

    return ans;
    
}