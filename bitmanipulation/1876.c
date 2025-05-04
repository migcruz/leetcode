/*
 * LeetCode Problem 1876: Substrings of Size Three with Distinct Characters
 * Difficulty: Easy
 *
 * A string is good if there are no repeated characters.
 * Given a string s, return the number of good substrings of length three in s.
 * Note that if there are multiple occurrences of the same substring, each is counted.
 * A substring is a contiguous sequence of characters in a string.
 *
 * Example 1:
 * Input: s = "xyzzaz"
 * Output: 1
 *
 * Example 2:
 * Input: s = "aababcabc"
 * Output: 4
 *
 * Constraints:
 *   - 1 <= s.length <= 100
 *   - s consists of lowercase English letters
 */

int countGoodSubstrings(char* s) {

    // XOR all 3 characters. if the result is not either of the characters and 0 then theyre all unique and increase answer by 1
    if (s == NULL) {
        return 0;
    }

    int len = strlen(s);
    if (len < 3) {
        return 0;
    }

    int left = 0;
    int right = left;
    int ans = 0;

    for (right = 2; right < len; right++) {
        int temp = s[right] ^ s[right - 1] ^ s[right - 2];
        if (temp != s[right] && temp != s[right - 1] && temp != s[right - 2] && temp != 0) {
            ans++;
        }
    }

    return ans;
}