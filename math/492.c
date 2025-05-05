/*
 * LeetCode Problem 492: Construct the Rectangle
 * Difficulty: Easy
 *
 * A web developer needs to know how to design a web page's size.
 * So, given a specific rectangular web page’s area, your job is to design
 * a rectangular web page whose length L and width W satisfy the following:
 *
 *   - The area of the rectangular web page you designed must equal the given area.
 *   - The width W should not be larger than the length L (i.e., L >= W).
 *   - The difference between length L and width W should be as small as possible.
 *
 * Return an array [L, W] where L and W are the length and width of the web page you designed.
 *
 * Example 1:
 * Input: area = 4
 * Output: [2,2]
 * Explanation: The target area is 4. Possible pairs: [1,4], [2,2], [4,1].
 *              [2,2] satisfies both L >= W and minimal difference.
 *
 * Example 2:
 * Input: area = 37
 * Output: [37,1]
 *
 * Example 3:
 * Input: area = 122122
 * Output: [427,286]
 *
 * Constraints:
 *   - 1 <= area <= 10^7
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructRectangle(int area, int* returnSize) {

    // we start with the sqrt of area as W since W <= sqrt(Area), here we pretend L = W and do L*W. If this product is less than area
    // we will decrease W and try again, if the new product is less than area we increase L and try again, if the new product is more than area, we decrease W and so on

    int W = sqrt(area);
    int L = W;
    int product = L*W;

    while (product != area) {

        if (product < area) {
            L++;
        }
        else if (product > area) {
            W--;
        }

        product = L*W;
    }

    int *ans = (int*) calloc (2, sizeof(int));
    ans[0] = L;
    ans[1] = W;

    *returnSize = 2;
    return ans;
}