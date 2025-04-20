/*
 * LeetCode Problem 2828: Check if a String Is an Acronym of Words
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an array of strings `words` and a string `s`, check whether `s` is
 * an acronym formed by the first letters of each word in the `words` array.
 *
 * A string `s` is considered an acronym of `words` if:
 *     - s == words[0][0] + words[1][0] + ... + words[n-1][0]
 *
 * Return true if `s` is a valid acronym of `words`, otherwise false.
 *
 * Examples:
 *
 * Example 1:
 * Input: words = ["alice","bob","charlie"], s = "abc"
 * Output: true
 * Explanation: The acronym formed by the first letters is "abc", which matches `s`.
 *
 * Example 2:
 * Input: words = ["an","apple"], s = "a"
 * Output: false
 * Explanation: The acronym formed is "aa", which does not match `s`.
 *
 * Example 3:
 * Input: words = ["never","gonna","give","up","on","you"], s = "ngguoy"
 * Output: true
 * Explanation: The acronym formed is "ngguoy", which matches `s`.
 *
 * Constraints:
 *   - 1 <= words.length <= 100
 *   - 1 <= words[i].length <= 10
 *   - 1 <= s.length <= 100
 *   - Both `words[i]` and `s` consist of lowercase English letters only.
 */

bool isAcronym(char** words, int wordsSize, char* s) {

    // we can do a frequency array of the first characters of each word in words, then do a frequency array for each character in s, these 2 frequency arrays should match
    // actually this won't necessarily work because order matters.
    // instead we just compare every first ccharacter of every word in words to be equal to the each character in s

    if (words == NULL && s == NULL) {
        return true;
    }

    int sLen = strlen(s);

    if (wordsSize != sLen) {
        return false;
    }

    // do the comparison

    for (int i = 0; i < wordsSize; i++) {

        if (words[i][0] != s[i]) {
            return false;
        }

    }

    return true;
    
}