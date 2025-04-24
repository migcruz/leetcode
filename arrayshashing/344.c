/*
 * LeetCode Problem 344: Reverse String
 * Difficulty: Easy
 *
 * Problem Description:
 * Write a function that reverses a string. The input string is given as an array of characters `s`.
 * You must modify the input array in-place using O(1) extra memory.
 *
 * Examples:
 *
 * Example 1:
 * Input:  s = ["h","e","l","l","o"]
 * Output: ["o","l","l","e","h"]
 *
 * Example 2:
 * Input:  s = ["H","a","n","n","a","h"]
 * Output: ["h","a","n","n","a","H"]
 *
 * Constraints:
 *   1 <= s.length <= 10^5
 *   s[i] is a printable ASCII character
 */

void reverseString(char* s, int sSize) {

    // we will use two pointers left and right starting at the ends of the string and then swap the other
    // we can use bitwise XOR to swap values without using a temp variable

    if (s == NULL) {
        return;
    }

    int left = 0;
    int right = sSize - 1;

    while (left < right) {

        s[left] = s[left] ^ s[right];
        s[right] = s[left] ^ s[right];
        s[left] = s[left] ^ s[right];

        left++;
        right--;

    }
    
}