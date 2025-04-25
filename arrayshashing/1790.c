/*
 * LeetCode Problem 1790: Check if One String Swap Can Make Strings Equal
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given two strings s1 and s2 of equal length. A string swap is an operation where
 * you choose two indices in a string (not necessarily different) and swap the characters at these indices.
 *
 * Return true if it is possible to make both strings equal by performing at most one string swap 
 * on exactly one of the strings. Otherwise, return false.
 *
 * Examples:
 *
 * Example 1:
 * Input:  s1 = "bank", s2 = "kanb"
 * Output: true
 * Explanation: Swap the first and last characters of s2 to make it equal to s1.
 *
 * Example 2:
 * Input:  s1 = "attack", s2 = "defend"
 * Output: false
 * Explanation: No single swap can make the strings equal.
 *
 * Example 3:
 * Input:  s1 = "kelb", s2 = "kelb"
 * Output: true
 * Explanation: Strings are already equal; no swap needed.
 *
 * Constraints:
 *   1 <= s1.length, s2.length <= 100
 *   s1.length == s2.length
 *   s1 and s2 consist of only lowercase English letters.
 */

bool areAlmostEqual(char* s1, char* s2) {

    if (s1 == NULL || s2 == NULL) {
        return false;
    }
    // we need to scan both strings into frequency arrays and make sure every value in each freq array is equal
    // if any element is not equal then return false

    // then we traverse both strings at the same time comparing characters knowing that they all have the same character frequency
    // if the characters at any index don't match increase the counter by 1, if this counter exceeds 2, then return false
    // why 2? because for bank and kanb there are 2 indices where they dont match but just requries 1 swap

    int freqArrS1[26] = {0};
    int freqArrS2[26] = {0};
    int count = 0;

    // scan the strings
    for (int i = 0; i < strlen(s1); i++) { // both strings are equal length
        freqArrS1[s1[i] - 'a']++;
        freqArrS2[s2[i] - 'a']++;
    }

    // check if the arrays are equal
    for (int i = 0; i < 26; i++) { // both strings are equal length
        if (freqArrS1[i] != freqArrS2[i]) {
            return false;
        }
    }

    // now traverse both strings
    for (int i = 0; i < strlen(s1); i++) { // both strings are equal length
        if (s1[i] != s2[i]) {
            count++;
        }
        if (count > 2) {
            return false;
        }
    }

    return true;
    
}