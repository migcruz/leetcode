/*
 * LeetCode Problem 28: Find the Index of the First Occurrence in a String
 * Difficulty: Easy
 *
 * Problem Description:
 * Given two strings 'needle' and 'haystack', return the index of the first occurrence 
 * of 'needle' in 'haystack', or -1 if 'needle' is not found.
 *
 * Rules:
 * - The search must be performed on contiguous substrings.
 * - If 'needle' appears multiple times, return the index of its first occurrence.
 * - If 'needle' is not part of 'haystack', return -1.
 *
 * Example 1:
 * Input: haystack = "sadbutsad", needle = "sad"
 * Output: 0
 * Explanation: "sad" occurs at index 0 and 6.
 * The first occurrence is at index 0, so we return 0.
 *
 * Example 2:
 * Input: haystack = "leetcode", needle = "leeto"
 * Output: -1
 * Explanation: "leeto" did not occur in "leetcode", so we return -1.
 *
 * Constraints:
 * - 1 <= haystack.length, needle.length <= 10^4
 * - 'haystack' and 'needle' consist of only lowercase English characters.
 */

int strStr(char* haystack, char* needle) {

    //iterate through haystack until the first char of needle is found
    // then do strcmp with the amount of bytes being the length of needle
    // if true return the index of haystack

    int haystackLen = strlen(haystack);
    int needleLen = strlen(needle);
    int ans = -1;

    for (int i = 0; i < haystackLen; i++) {

        if (haystack[i] == needle[0]) { // first char matches
            int ret = strncmp(&haystack[i], needle, needleLen);

            if (ret == 0) {
                return i;
            }
        }
    }

    return -1;
    
}