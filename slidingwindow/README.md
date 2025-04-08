# Sliding Window Technique

## Overview
The **sliding window** technique is an efficient approach used in **array** and **string processing** problems where a subset of elements needs to be evaluated dynamically. Instead of recalculating values from scratch on every iteration, the window shifts across the input while adjusting relevant computations.

This method is commonly used in:
- Finding subarrays that meet a condition.
- Optimizing performance in contiguous data structures.
- Solving problems that involve **fixed-size** or **variable-size** windows.

## Identifying Sliding Window Problems
A problem might require the **sliding window** approach if:
✔ You are working with **arrays** or **strings**.  
✔ You need to find **subarrays or substrings** that meet a condition.  
✔ The problem requires **continuous** or **contiguous** elements.  
✔ Recalculating from scratch in each step would be inefficient.  
✔ The problem has constraints that suggest **linear or near-linear complexity is required**.  

### **Examples of Sliding Window Problems**
1. **Fixed-Size Window**
   - Maximum sum of a subarray of size `k`.
   - Highest average of a subarray of `k` elements.
   - Finding a substring that matches a given pattern length.

2. **Variable-Size Window**
   - Smallest subarray sum ≥ a given value.

2. **Variable-Size Window with another data structure**
   - Longest substring without repeating characters.
   - Longest substring with no more than k distinct characters
   - Finding the maximum length of consecutive ones in a binary array.
   - String permutations

## Time & Space Complexity
### **Time Complexity**
| Window Type | Complexity | Explanation |
|------------|------------|-------------|
| Fixed-size | **O(N)** | Each element is added once and removed once (constant work per step). |
| Variable-size | **O(N)** | The window expands and contracts dynamically while traversing the array. |

### **Space Complexity**
| Case | Complexity | Explanation |
|------|------------|-------------|
| No extra storage | **O(1)** | Only pointers and temporary variables are used. |
| Auxiliary storage (hash sets, frequency arrays) | **O(K)** | Needed for storing elements in some problems, where K is the window size. |

## Example Code (Fixed-Size Sliding Window)
```python
def max_sum_subarray(arr, k):
    max_sum = float('-inf')
    window_sum = sum(arr[:k])  # Initial window sum
    for i in range(len(arr) - k):
        window_sum = window_sum - arr[i] + arr[i + k]  # Slide the window
        max_sum = max(max_sum, window_sum)
    return max_sum
```
---
# References
- Sliding window youtube: https://www.youtube.com/watch?v=MK-NZ4hN7rs
