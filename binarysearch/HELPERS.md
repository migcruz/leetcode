# Helper functions for binary search

## Binary search
```C
// Binary Search Function
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoids potential overflow

        if (arr[mid] == target) {
            return mid;  // Target found, return index
        } else if (arr[mid] < target) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1; // Search left half
        }
    }

    return -1;  // Target not found
}
```