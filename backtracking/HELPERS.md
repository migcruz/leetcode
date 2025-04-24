# Helper functions for backtracking

## Generate all possible combinations (maxDepth is the combination size) (distinct elements only)
```C
// Generate combinations for an array of integers (distinct elements only)
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
## Generate all possible combinations (maxDepth is the combination size) (with repeated elements)
### sort first then apply below
```C
// Generate combinations for an array of integers
void generateCombinations(int arr[], int n, int index, int data[], int depth, int maxDepth) {
    if (depth == maxDepth) { // Base case: found a valid combination
        printf("(%d, %d, %d)\n", data[0], data[1], data[2]);
        return;
    }

    for (int i = index; i < n; i++) {
        if (i > index && arr[i] == arr[i-1]) {
            continue; // this section only works if the array is already sorted
        }
        data[depth] = arr[i];
        generateCombinations(arr, n, i + 1, data, depth + 1);
    }
}

generateCombinations(arr, n, 0, data, 0, 3);
```
## Generate all permutations (distinct elements only)
```C
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void generatePermutations(int arr[], int left, int right) {
    if (left == right) { // Base case: a complete permutation is formed
        printf("[");
        for (int i = 0; i <= right; i++) {
            printf("%d", arr[i]);
            if (i < right) printf(", ");
        }
        printf("]\n");
        return;
    }

    for (int i = left; i <= right; i++) {
        swap(&arr[left], &arr[i]); // Swap to create a new permutation
        generatePermutations(arr, left + 1, right); // Recursively generate permutations
        swap(&arr[left], &arr[i]); // Backtrack
    }
}

generatePermutations(arr, 0, n - 1);
```