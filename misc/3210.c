/*
 * LeetCode Problem 3210: Find the Encrypted String
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given a string 's' and an integer 'k'. Encrypt the string using the following rule:
 * For each character 'c' in 's', replace 'c' with the k-th character after 'c' in the string 
 * (in a cyclic manner, wrapping around to the beginning as needed).
 *
 * Return the encrypted string.
 *
 * Example 1:
 * Input: s = "dart", k = 3
 * Output: "tdar"
 * Explanation:
 *  - i = 0 → 3rd char after 'd' is 't'
 *  - i = 1 → 3rd char after 'a' is 'd'
 *  - i = 2 → 3rd char after 'r' is 'a'
 *  - i = 3 → 3rd char after 't' is 'r'
 *
 * Example 2:
 * Input: s = "aaa", k = 1
 * Output: "aaa"
 * Explanation:
 * All characters are the same, so the result is unchanged.
 *
 * Constraints:
 * - 1 <= s.length <= 100
 * - 1 <= k <= 10^4
 * - s consists only of lowercase English letters
 */

char* getEncryptedString(char* s, int k) {

    // we need to copy the string otherwise we will lose the original characters as we replace each character. this will give us the wrong encryption
    // we can always get the correct kth character after s[i] by doing newIndex = i + k, if newIndex > strlen(s), newIndex = (i + k) % strlen(s)
    // can't use newIndex = (i + k) - strlen(s) because if k is larger than strlen(s) and i is at the end then we go out of bounds.
    if (s == NULL) {
        return NULL;
    }

    int len = strlen(s);
    // printf("%d\r\n", len);

    char *ans = (char*) calloc (len + 1, sizeof(char)); // need + 1 for NULL terminator

    for (int i = 0; i < len; i++) {

        int newIndex = i + k;
        if (newIndex >= len) {
            // printf("LOL\r\n");
            newIndex = (i + k) % len;
        }

        ans[i] = s[newIndex];
    }
    
    return ans;
}