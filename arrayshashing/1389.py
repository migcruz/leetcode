"""
LeetCode Problem 1389: Create Target Array in the Given Order
Difficulty: Easy

Problem Description:
You are given two integer arrays, nums and index. You need to build a target array by inserting each element
of nums into the target array at the corresponding position specified by index.

Rules:
- Initialize an empty target array.
- Iterate through nums and index from left to right.
- For each i, insert nums[i] at index[i] in the target array.
- Repeat this process until all elements are inserted.

Return the resulting target array.

It is guaranteed that all insertion operations will be valid.

Examples:

Example 1:
Input: nums = [0,1,2,3,4], index = [0,1,2,2,1]
Output: [0,4,1,3,2]
Explanation:
Step-by-step insertions:
  - Insert 0 at index 0 → [0]
  - Insert 1 at index 1 → [0, 1]
  - Insert 2 at index 2 → [0, 1, 2]
  - Insert 3 at index 2 → [0, 1, 3, 2]
  - Insert 4 at index 1 → [0, 4, 1, 3, 2]

Example 2:
Input: nums = [1,2,3,4,0], index = [0,1,2,3,0]
Output: [0,1,2,3,4]
Explanation:
Step-by-step insertions:
  - Insert 1 at index 0 → [1]
  - Insert 2 at index 1 → [1, 2]
  - Insert 3 at index 2 → [1, 2, 3]
  - Insert 4 at index 3 → [1, 2, 3, 4]
  - Insert 0 at index 0 → [0, 1, 2, 3, 4]

Example 3:
Input: nums = [1], index = [0]
Output: [1]

Constraints:
- 1 <= nums.length, index.length <= 100
- nums.length == index.length
- 0 <= nums[i] <= 100
- 0 <= index[i] <= i
"""

class Solution(object):
    def createTargetArray(self, nums, index):
        """
        :type nums: List[int]
        :type index: List[int]
        :rtype: List[int]
        """

        # we should use python to take care of the element shifting after insertion instead of C

        ans = []

        for num, idx in zip(nums, index):
            ans.insert(idx, num)
        
        return ans