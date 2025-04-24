/*
 * LeetCode Problem 90: Subsets II
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an integer array `nums` that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Examples:
 *
 * Example 1:
 * Input:  nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 *
 * Example 2:
 * Input:  nums = [0]
 * Output: [[],[0]]
 *
 * Constraints:
 *   1 <= nums.length <= 10
 *  -10 <= nums[i] <= 10
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
void generateCombinations(int *arr, int n, int index, int data[], int depth, int maxDepth, int **ans, int *ansIndex, int *returnColSizes) {
    if (depth == maxDepth) { // Base case: found a valid combination
        
        //let's make an array and put it into the linked list
        int *newArr = (int*) calloc (maxDepth, sizeof(int));

        for (int i = 0; i < maxDepth; i++) {
            newArr[i] = data[i];
        }
        returnColSizes[*ansIndex] = maxDepth;
        ans[*ansIndex] = newArr;
        (*ansIndex)++;
        // insert(root, newArr, maxDepth);

        return;
    }

    for (int i = index; i < n; i++) {
        if (i > index && arr[i] == arr[i-1]) {
            continue;
        }
        data[depth] = arr[i];
        generateCombinations(arr, n, i + 1, data, depth + 1, maxDepth, ans, ansIndex, returnColSizes);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsetsWithDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {

    // we can use the solution with 78 but sicne there are repeated elements, we need to sort the array first
    // the solution is a mix of 40 and 78

    if (nums == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int totalSubsets = 1 << numsSize;  // 2^numsSize subsets this is the MAX possible, in reality we will have less than this since there are repeated elements
    int** ans = (int**) malloc(totalSubsets * sizeof(int*));
    int *returnColSizes = (int*) calloc (totalSubsets, sizeof(int));
    int data[10] = {0}; // 10 based on bounds
    int ansIndex = 1;

    //sort the array
    merge_sort(nums, 0 , numsSize - 1);
    ans[0] = NULL; //empty set
    for (int i = 1; i <= numsSize; i++) {
        generateCombinations(nums, numsSize, 0, data, 0, i, ans, &ansIndex, returnColSizes);
    }

    *returnSize = ansIndex;
    *returnColumnSizes = returnColSizes;
    return ans;
    
}