"""
LeetCode Problem 853: Car Fleet
Difficulty: Medium

Problem Description:
There are 'n' cars positioned at various miles away from the starting point (mile 0),
each traveling toward a given mile 'target'.

You are given two integer arrays:
- `position[i]`: Starting mile of the i-th car.
- `speed[i]`: Speed of the i-th car in miles per hour.

Rules:
- A car **cannot pass** another car.
- It can **catch up** and then move at the **minimum speed** of any car in the fleet.
- A fleet consists of **one or more cars moving together**.
- If a car reaches the target as part of a fleet, it remains in the fleet.

Goal:
Return the **number of car fleets** that will arrive at the destination.

Example 1:
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
  - The cars at positions 10 and 8 merge at mile 12 to form a fleet.
  - The car at position 0 never catches another fleet.
  - The cars at positions 5 and 3 merge at mile 6 and continue at speed 1.

Example 2:
Input: target = 10, position = [3], speed = [3]
Output: 1
Explanation:
  - A single car always forms a fleet by itself.

Example 3:
Input: target = 100, position = [0,2,4], speed = [4,2,1]
Output: 1
Explanation:
  - Cars at positions 0 and 2 merge at mile 4.
  - The car at position 4 catches up later, forming one fleet.

Constraints:
- 1 <= n <= 10^5
- 0 < target <= 10^6
- 0 <= position[i] < target
- All values in `position` are unique.
- 0 < speed[i] <= 10^6
"""

class Solution(object):
    def carFleet(self, target, position, speed):
        """
        :type target: int
        :type position: List[int]
        :type speed: List[int]
        :rtype: int
        """

        # we can solve this using y = mx + b
        # the max fleet count that can arrive is if speed[i]*t + position[i] >= target, assuming a t value even exists for this to be true
        # we can run a for loop to find this t but since we know that the minimum speed is 1, they will all reach the target

        # each time a fleet merges with a car, decrease the answer

        # we can figure out when two cars will meet using speed[i]*t + position[i] = speed[j]*t + position[j]
        # which simplifies to t = abs( (position[j] - position[i]) / (speed[i] - speed[j]) )
        # if speed[i]*t + position[i] <= target these two will form a fleet, we decrement ans and treat this fleet as one car, choosing the lower speed to be its new speed and their meeting point
        # as the new starting point

        # OR

        # calc every cars time required to reach target and add it to the stack if it is greater than the current top of the stack, it means that they did NOT meet up and is a separate fleet.

        cars = sorted(zip(position, speed), reverse=True)  # Sort by position (descending)
        # print(cars)
        stack = []

        for pos, spd in cars:
            time = float(target - pos) / spd # Time to reach target
            # print(time)
            if not stack or time > stack[-1]:  # New fleet forms if time is greater
                stack.append(time)

        return len(stack)  # Number of fleets
