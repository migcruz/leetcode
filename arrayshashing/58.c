/*
 * LeetCode Problem 58: Length of Last Word
 * Difficulty: Easy
 *
 * Problem Description:
 * Given a string 's' consisting of words and spaces, return the length of the last word in the string.
 * A word is defined as a maximal contiguous sequence of non-space characters.
 *
 * Rules:
 * - Ignore trailing spaces before identifying the last word.
 * - The last word consists of only English letters.
 * - Return the length of the last word found.
 *
 * Example 1:
 * Input: s = "Hello World"
 * Output: 5
 * Explanation: The last word is "World" with length 5.
 *
 * Example 2:
 * Input: s = "   fly me   to   the moon  "
 * Output: 4
 * Explanation: The last word is "moon" with length 4.
 *
 * Example 3:
 * Input: s = "luffy is still joyboy"
 * Output: 6
 * Explanation: The last word is "joyboy" with length 6.
 *
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - s consists of only English letters and spaces (' ').
 * - There will be at least one word in 's'.
 */

int lengthOfLastWord(char* s) {
    // start counting as long as the current char is not a space or null terminator. stop counting if we encounter the space or null terminator
    // but start from the end and count backwards

    if (s == NULL) {
        return 0;
    }

    int len = strlen(s);
    int ans = 0;
    bool flag = false;

    for (int i = len - 1; i >= 0; i--) {

        if (s[i] == ' ' && flag){
            break;
        }

        if (s[i] != '\0' && s[i] != ' ') {// start counting
            flag = true;
            ans++;
        }

    }

    return ans;
    
}