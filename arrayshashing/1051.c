/*
 * LeetCode Problem 1051: Height Checker
 * Difficulty: Easy
 *
 * Problem Description:
 * A school is trying to take an annual photo of all the students. 
 * The students are asked to stand in a single file line in non-decreasing order by height.
 * Let this ordering be represented by the integer array expected, where expected[i] is the 
 * expected height of the i-th student in line.
 *
 * You are given an integer array heights representing the current order 
 * that the students are standing in. Each heights[i] is the height of the i-th student in line.
 *
 * Return the number of indices where heights[i] != expected[i].
 *
 * Examples:
 *
 * Example 1:
 * Input:  heights = [1,1,4,2,1,3]
 * Output: 3
 * Explanation: 
 *   heights:  [1,1,4,2,1,3]
 *   expected: [1,1,1,2,3,4]
 *   Indices 2, 4, and 5 do not match.
 *
 * Example 2:
 * Input:  heights = [5,1,2,3,4]
 * Output: 5
 * Explanation:
 *   heights:  [5,1,2,3,4]
 *   expected: [1,2,3,4,5]
 *   All indices do not match.
 *
 * Example 3:
 * Input:  heights = [1,2,3,4,5]
 * Output: 0
 * Explanation:
 *   heights:  [1,2,3,4,5]
 *   expected: [1,2,3,4,5]
 *   All indices match.
 *
 * Constraints:
 *   1 <= heights.length <= 100
 *   1 <= heights[i] <= 100
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
int heightChecker(int* heights, int heightsSize) {

    // sort heights by increasing order and traverse both arrays and count the number of indices where the elements are not equal
    // since we requrie sorting this is an O(N log N) solution

    if (heights == NULL || heightsSize == 1) {
        return 0;
    }

    int *sortedHeights = (int*) calloc (heightsSize, sizeof(int));
    int ans = 0;

    memcpy(sortedHeights, heights, heightsSize * sizeof(int));

    merge_sort(sortedHeights, 0, heightsSize - 1);

    // for (int i = 0; i < heightsSize; i++) {
    //     printf("%d ", heights[i]);
    // }

    for (int i = 0; i < heightsSize; i++) {
        if (sortedHeights[i] != heights[i]) {
            ans++;
        }
    }

    return ans;
}