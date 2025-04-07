/*
 * LeetCode Problem 27: Remove Element
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an integer array 'nums' and an integer 'val', remove all occurrences 
 * of 'val' in 'nums' in-place. The order of elements may be changed.
 * Return the number of elements in 'nums' that are not equal to 'val'.
 *
 * Rules:
 * - The first 'k' elements of 'nums' should contain elements that are not equal to 'val'.
 * - The remaining elements in 'nums' are not important.
 * - Return 'k', the count of elements that are not equal to 'val'.
 *
 * Custom Judge:
 * The solution will be validated with assertions that ensure:
 * - 'k' matches the expected count.
 * - The first 'k' elements in 'nums' match the expected output after sorting.
 *
 * Example 1:
 * Input: nums = [3,2,2,3], val = 3
 * Output: 2, nums = [2,2,_,_]
 * Explanation: The function should return k = 2, with the first two elements of nums being 2.
 *
 * Example 2:
 * Input: nums = [0,1,2,2,3,0,4,2], val = 2
 * Output: 5, nums = [0,1,4,0,3,_,_,_]
 * Explanation: The function should return k = 5, containing 0, 0, 1, 3, and 4.
 * Note: The elements may appear in any order.
 *
 * Constraints:
 * - 0 <= nums.length <= 100
 * - 0 <= nums[i] <= 50
 * - 0 <= val <= 100
 */

// Function to merge two halves
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

int removeElement(int* nums, int numsSize, int val) {

    // go through the array and increase k each time there is an element that is not val. If val is encountered, replace it with a bigger number than 100 so we can sort it later and all instances of val will be at the right side of the array
    
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != val) {
            ans++;
        }
        else {
            nums[i] = 101; // greater than max values of nums[i] so we can sort later
        }

    }

    // sort array
    merge_sort(nums, 0, numsSize - 1);

    return ans;
}