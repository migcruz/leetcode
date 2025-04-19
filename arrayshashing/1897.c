/*
 * LeetCode Problem 1897: Redistribute Characters to Make All Strings Equal
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an array of strings `words`, determine if you can make all strings equal
 * by redistributing characters between them. Each operation lets you:
 * - Pick two different indices i and j,
 * - Move a character from words[i] to any position in words[j].
 *
 * Return true if it's possible to make all strings equal, otherwise return false.
 *
 * Key Insight:
 * If the total count of each character across all strings is divisible by the
 * number of strings, then it's possible to distribute characters equally.
 *
 * Examples:
 *
 * Example 1:
 *   Input: words = ["abc","aabc","bc"]
 *   Output: true
 *   Explanation:
 *     Move one 'a' from words[1] to words[2] -> words becomes ["abc", "abc", "abc"]
 *     All strings are now equal.
 *
 * Example 2:
 *   Input: words = ["ab","a"]
 *   Output: false
 *   Explanation:
 *     It's not possible to redistribute characters to make both strings equal.
 *
 * Constraints:
 *   - 1 <= words.length <= 100
 *   - 1 <= words[i].length <= 100
 *   - Each word consists of lowercase English letters only
 */

bool makeEqual(char** words, int wordsSize) {

    // we just do a frequency array and divide every frequency for each letter by wordsSize, if there is a remainder then return false

    if (words == NULL) {
        return false;
    }

    bool ans = true;

    int freqArr[26] = {0};

    // scan every letter of every word
    for (int i = 0; i < wordsSize; i++) {
        int len = strlen(words[i]);
        for (int j = 0; j < len; j++) {
            freqArr[words[i][j] - 'a']++;
        }
    }

    // scan the freqArr
    for (int i = 0; i < 26; i++) {
        if (freqArr[i] % wordsSize != 0) {
            ans = false;
            break;
        }
    }

    return ans;
    
}