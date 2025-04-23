/*
 * LeetCode Problem 40: Combination Sum II
 * Difficulty: Medium
 *
 * Problem Description:
 * Given a collection of candidate numbers (`candidates`) and a target number (`target`),
 * find all unique combinations in `candidates` where the candidate numbers sum to `target`.
 *
 * Each number in `candidates` may only be used once in the combination.
 * The solution set must not contain duplicate combinations.
 *
 * Examples:
 *
 * Example 1:
 * Input:  candidates = [10,1,2,7,6,1,5], target = 8
 * Output: [[1,1,6], [1,2,5], [1,7], [2,6]]
 *
 * Example 2:
 * Input:  candidates = [2,5,2,1,2], target = 5
 * Output: [[1,2,2], [5]]
 *
 * Constraints:
 *   1 <= candidates.length <= 100
 *   1 <= candidates[i] <= 50
 *   1 <= target <= 30
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
// Generate combinations for an array of integers
void generateCombinations(int *arr, int n, int index, int data[], int depth, int sum, int target, int **ans, int *returnColSizes, int *ansSize) {
    if (sum == target) {

        int *tempArr = (int*) calloc (depth, sizeof(int));
        for (int i = 0; i < depth; i++) {
            tempArr[i] = data[i];
        }
        ans[*ansSize] = tempArr;
        returnColSizes[*ansSize] = depth;
        (*ansSize)++;
        return;
    }
    else if (sum > target) {
        return;
    }
    
    // Recruse through array with backtracking
    for (int i = index; i < n; i++) {
        if (i > index && arr[i] == arr[i-1]) { // found a duplicate element that we already made a combination of (requires the array to be sorted first)
            continue;
        }
        int tempSum = sum + arr[i]; // can't do sum = sum + arr[i] becauser w e need to keep the value of sum the same per recursion call because of backtracking
        data[depth] = arr[i];
        generateCombinations(arr, n, i + 1, data, depth + 1, tempSum, target, ans, returnColSizes, ansSize); // passing i + 1 so that elements are NOT repeated
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {

    // we can use the generate combinations function but since each element can only be used once, we don't need to modify the index being passed
    // to each recursive call
    // we also need to specify a maxDepth that increments similar to the subset probelm 78 (DONT DO THIS IT WILL HIT TLE)
        // instead just do what we did in 39
    // the issue is that not every element is distinct

    // we can sort the candidates array first and then would make non-distinct elements side by side and we can skip them in the for loop
    // you can visualize  this by using a small array like [1, 1, 2] and how it prints with and without the continue logic statement

    if (candidates == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    merge_sort(candidates, 0, candidatesSize - 1);


    int **ans = (int**) calloc (150, sizeof(int*)); //assuming 150 max size of combinations 
    int *returnColSizes = (int*) calloc (150, sizeof(int));
    int ansSize = 0;
    int data[100] = {0};

    generateCombinations(candidates, candidatesSize, 0, data, 0, 0, target, ans, returnColSizes, &ansSize);
    
    *returnSize = ansSize;
    *returnColumnSizes = returnColSizes;
    return ans;
    
}