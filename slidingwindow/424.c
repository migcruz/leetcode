/*
 * LeetCode Problem 424: Longest Repeating Character Replacement
 * Difficulty: Medium
 *
 * Problem Description:
 * Given a string 's' and an integer 'k', you can replace up to 'k' characters 
 * in 's' with any other uppercase English letter. The goal is to determine 
 * the length of the longest substring that contains only one repeating character 
 * after performing these replacement operations.
 *
 * Example 1:
 * Input: s = "ABAB", k = 2
 * Output: 4
 * Explanation: Replace two 'A's with 'B's or vice versa to form "BBBB" or "AAAA".
 *
 * Example 2:
 * Input: s = "AABABBA", k = 1
 * Output: 4
 * Explanation: Replace one 'A' to form "AABBBBA", creating the longest repeating substring "BBBB".
 *
 * Constraints:
 * - 1 <= s.length <= 10^5
 * - 's' consists only of uppercase English letters.
 * - 0 <= k <= s.length
 */

int characterReplacement(char* s, int k) {

    int freq[26] = {0};       // Frequency array for 'A' to 'Z'
    int maxFreq = 0;          // Track the max frequency of a single character in the window
    int left = 0;             // Start of the sliding window
    int result = 0;           // Maximum substring length

    for (int right = 0; s[right] != '\0'; right++) {
        // Increment frequency of the current character
        freq[s[right] - 'A']++;
        // Track the maximum frequency of any character in the window
        // each time the window increases to the right, we add a counter for that char. Here we will always have the biggest answer
        maxFreq = maxFreq > freq[s[right] - 'A'] ? maxFreq : freq[s[right] - 'A'];

        // If the window is invalid (too many replacements needed), shrink it. Otherwise keep growing the window
        while ((right - left + 1) - maxFreq > k) {
            freq[s[left] - 'A']--;  // Remove the leftmost character from the window
            left++;                 // Shrink the window
        }

        // Update the result (maximum window size seen so far). The max window size is the answer because that's the biggest window while having exactly 0 replacements
        result = result > (right - left + 1) ? result : (right - left + 1);  // (+1 because of zero indexing)
    }

    return result;
    
}