/*
 * LeetCode Problem 1816: Truncate Sentence
 * Difficulty: Easy
 *
 * Problem Description:
 * A sentence is a list of words separated by a single space, with no leading or trailing spaces.
 * Each word consists of only uppercase and lowercase English letters (no punctuation).
 *
 * You are given a sentence `s` and an integer `k`. You need to return a truncated version of `s`
 * such that it contains only the first `k` words from the original sentence.
 *
 * Examples:
 *
 * Example 1:
 * Input: s = "Hello how are you Contestant", k = 4
 * Output: "Hello how are you"
 * Explanation:
 * The first 4 words are ["Hello", "how", "are", "you"].
 * Returning those words results in "Hello how are you".
 *
 * Example 2:
 * Input: s = "What is the solution to this problem", k = 4
 * Output: "What is the solution"
 * Explanation:
 * The first 4 words are ["What", "is", "the", "solution"].
 *
 * Example 3:
 * Input: s = "chopper is not a tanuki", k = 5
 * Output: "chopper is not a tanuki"
 * Explanation:
 * The sentence contains exactly 5 words. No truncation is needed.
 *
 * Constraints:
 *   - 1 <= s.length <= 500
 *   - k is in the range [1, the number of words in s]
 *   - s consists of only uppercase and lowercase English letters and spaces
 *   - Words in s are separated by a single space
 *   - No leading or trailing spaces in s
 */

char* truncateSentence(char* s, int k) {

    // we will copy every char from s into ans until the kth space is encountered

    if (s == NULL) {
        return NULL;
    }

    int len = strlen(s);

    char *ans = (char*) calloc (len + 1, sizeof(char)); // filled with null terminators

    //fill up ans
    int kCount = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            kCount++;
            if (kCount == k) {
                break;
            }
        }
        ans[i] = s[i];

    }

    return ans;
}