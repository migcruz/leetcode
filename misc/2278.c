/*
 * LeetCode Problem 2278: Percentage of Letter in String
 * Difficulty: Easy
 *
 * Problem Description:
 * Given a string `s` and a character `letter`, return the percentage of characters
 * in `s` that are equal to `letter`, rounded down to the nearest whole percent.
 *
 * Formula:
 *   percentage = (count of `letter` in `s` * 100) / length of `s`
 *   Round the result down to the nearest integer.
 *
 * Examples:
 *
 * Example 1:
 * Input: s = "foobar", letter = 'o'
 * Output: 33
 * Explanation: 2 occurrences of 'o' in 6 characters => floor(2 / 6 * 100) = 33
 *
 * Example 2:
 * Input: s = "jjjj", letter = 'k'
 * Output: 0
 * Explanation: 'k' does not appear, so percentage is 0%
 *
 * Constraints:
 *   1 <= s.length <= 100
 *   s consists of lowercase English letters
 *   letter is a lowercase English letter
 */

int percentageLetter(char* s, char letter) {

    // scan the string for letter increasing the frequency each time
    // then divide this frequency by the string length * 100

    if (s == NULL) {
        return 0;
    }

    int len = strlen(s);
    double freq = 0;
    int ans = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == letter) {
            freq++;
        }
    }

    ans = (freq / len) * 100;

    return ans;
    
}