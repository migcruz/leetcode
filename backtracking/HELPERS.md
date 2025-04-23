# Helper functions for backtracking

## Generate all possible combinations (maxDepth is the combination size)
```C
// Generate combinations for an array of integers
void generateCombinations(int arr[], int n, int index, int data[], int depth, int maxDepth) {
    if (depth == maxDepth) { // Base case: found a valid combination
        printf("(%d, %d, %d)\n", data[0], data[1], data[2]);
        return;
    }

    for (int i = index; i < n; i++) {
        data[depth] = arr[i];
        generateCombinations(arr, n, i + 1, data, depth + 1);
    }
}

generateCombinations(arr, n, 0, data, 0, 3);
```