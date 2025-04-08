/*
 * LeetCode Problem 42: Trapping Rain Water
 * Difficulty: Hard
 *
 * Problem Description:
 * Given 'n' non-negative integers representing an elevation map where the width of each bar is 1, 
 * compute how much water can be trapped after raining.
 *
 * Rules:
 * - Water is collected between the bars where lower elevation levels exist.
 * - The height array represents elevation, and trapped water is calculated between peaks.
 * - The solution must efficiently compute the amount of trapped water.
 *
 * Example 1:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. 
 * In this case, 6 units of rainwater (blue section) are trapped.
 *
 * Example 2:
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 *
 * Constraints:
 * - n == height.length
 * - 1 <= n <= 2 * 10^4
 * - 0 <= height[i] <= 10^5
 */

int trap(int* height, int heightSize) {

    // we will have 2 ptrs left and right. right advances until it finds an index where height[right] >= height[left]. Then we calc height[left] * (right - left - 1).
    // then we subtract any values between left and right from this sum. Then we add the result to ans.
    // then we have left meet up with right and repeat. if right does not find a height is greater or equal to height[left], we note this index and try the same method but going from the right
    // we use this index to indicate this is where the max height is
    
    // imagine this algo as if we're trying to find the max height and then adding up all the water on both left and right sides of the max height like a mountain

    int left = 0;
    int right = 0;
    int ans = 0;
    int maxHeightIndex = 0;
    bool flag = false;

    while (left != heightSize - 1) {

        if (right == heightSize - 1 && height[right] < height[left]) { // we found the tallest element, now we need to try adding water from the right side direction

            maxHeightIndex = left;
            left = right;
            flag = true;
            break;
        }

        if (height[right] >= height[left] && right != left) {// calc water
            int tempAns =  height[left] * (right - left - 1);


            // subtract if needed
            for (int i = left + 1; i < right; i++) {
                tempAns = tempAns - height[i];
            }
            ans += tempAns;
            left = right;
        }
        right++;
    }

    //now lets try the same method but starting from the right end until maxHeightIndex but the roles of left and right are switched
    // this happense if the max height is somewhere in the middle of the array
    while (right != maxHeightIndex && flag) {

        if (height[left] >= height[right] && right != left) {// calc water
            int tempAns =  height[right] * (right - left - 1); // now right is going to be the equal or less height than left

            // subtract if needed
            for (int i = left + 1; i < right; i++) {
                tempAns = tempAns - height[i];
            }
            ans += tempAns;
            right = left;
        }
        left--;
    }

    return ans;
    
}