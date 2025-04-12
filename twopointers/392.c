/*
 * LeetCode Problem 392: Is Subsequence
 * Difficulty: Easy
 *
 * Problem Description:
 * Given two strings 's' and 't', return 'true' if 's' is a subsequence of 't', 
 * or 'false' otherwise.
 *
 * A subsequence of a string is a new string formed from the original string by 
 * deleting some (possibly none) of the characters without changing the relative 
 * order of the remaining characters. 
 * For example, "ace" is a subsequence of "abcde", but "aec" is not.
 *
 * Example 1:
 * Input: s = "abc", t = "ahbgdc"
 * Output: true
 *
 * Example 2:
 * Input: s = "axc", t = "ahbgdc"
 * Output: false
 *
 * Constraints:
 * - 0 <= s.length <= 100
 * - 0 <= t.length <= 10^4
 * - Both 's' and 't' consist only of lowercase English letters
 *
 * Follow-up:
 * If there are a large number of strings 's1', 's2', ..., 'sk' where k >= 10^9, 
 * and you want to check if each 'si' is a subsequence of 't', how would you 
 * optimize your approach?
 */

bool isSubsequence(char* s, char* t) {

    // have two pointers 1 to traverse each string
    // traverse t until the first pointer of s is found, then move the pointer in s to the next char and continue scanning t
    // if the s pointer does not equal to '\0' at the end, return false

    if (s == NULL || t == NULL) {
        return false;
    }

    int tLen = strlen(t);
    int sLen = strlen(s);
    if (sLen > tLen) {
        return false;
    }

    int sPtr = 0;
    for (int i = 0; i < tLen; i++) {

        if (t[i] == s[sPtr]) {
            sPtr++;
        }
    }

    if (s[sPtr] != '\0') {
        return false;
    }
    else {
        return true;
    }
    
}