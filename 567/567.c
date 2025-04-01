/*
 * LeetCode Problem 567: Permutation in String
 * Difficulty: Medium
 *
 * Problem Description:
 * Given two strings 's1' and 's2', return 'true' if 's2' contains 
 * a permutation of 's1' as a substring, otherwise return 'false'.
 *
 * In other words, return 'true' if any permutation of 's1' appears 
 * as a contiguous sequence inside 's2'.
 *
 * Example 1:
 * Input: s1 = "ab", s2 = "eidbaooo"
 * Output: true
 * Explanation: 's2' contains one permutation of 's1' ("ba").
 *
 * Example 2:
 * Input: s1 = "ab", s2 = "eidboaoo"
 * Output: false
 *
 * Constraints:
 * - 1 <= s1.length, s2.length <= 10^4
 * - s1 and s2 consist of only lowercase English letters.
 */

bool checkInclusion(char* s1, char* s2) {

    //use sliding window of size s1len, slide it across if a char in the freqArray < 0. s2[left] resets to 0 when it is dropped from the window.
    // then restart scanning all of s1 in the window.

    int s1len = strlen(s1);
    int s2len = strlen(s2);

    if (s1len > s2len) {// length of substring is longer than actual string so return
        return false;
    }

    int s2charArr[26] = {0};
    int s1charArr[26] = {0};
    int left = 0;

    //scan s1

    for (int i = 0; i < s1len; i++) {
        s1charArr[s1[i] - 'a']++;
    }

    for (int right = 0; right < s2len; right++) {

        s2charArr[s2[right] - 'a']++;

        while ((right - left + 1) >= s1len) { // need to shrink window

            for (int i = 0; i < 26; i++) { // check every letter
                
                if (s1charArr[i] > 0) { // only check for letters that are in s1
                    int sum = s2charArr[i] - s1charArr[i];
                    if (sum != 0) {
                        break;
                    }
                }
                if (i == 25) {
                    return true;
                }

            }

            s2charArr[s2[left] - 'a']--;  // Remove the leftmost character from the window
            left++;                 // Shrink the window
        }
 
    }

    return false;

    //find all permutations of s1, each time the window slides, compare every permutation to the substring in the window, if one exists return true
    // this solution will give TLE (time limit exceeded). There are too many permutations for long s1 substrings.
}