/*
 * LeetCode Problem 1796: Second Largest Digit in a String
 * Difficulty: Easy
 *
 * Given an alphanumeric string s, return the second largest numerical digit that appears in s,
 * or -1 if it does not exist.
 *
 * An alphanumeric string is a string consisting of lowercase English letters and digits.
 *
 * Example 1:
 * Input: s = "dfa12321afd"
 * Output: 2
 * Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
 *
 * Example 2:
 * Input: s = "abc1111"
 * Output: -1
 * Explanation: The digits that appear in s are [1]. There is no second largest digit.
 *
 * Constraints:
 *   - 1 <= s.length <= 500
 *   - s consists of only lowercase English letters and digits.
 */

int secondHighest(char* s) {

    // assuming the input string is all asci characters we can use a frequency array and just inspect the range for '0' to '9'
    // then return the 2nd largest of those

    if (s == NULL) {
        return -1;
    }

    int len = strlen(s);
    int ans = -1;
    int count = 0;
    int temp = 10;

    int freqArr[10] = {0};

    for (int i = 0; i < len; i++) {
        if (s[i] < 97) {
            freqArr[s[i] - '0']++;
        }
    }

    // find second largest
    for (int i = 9; i >= 0; i--) {
        if (count < 2 && freqArr[i] > 0) {
            printf("LOL %d\n", i);
            temp = (temp > i) ? i : temp;
            count++;
        }
    }

    if (count == 2) {
        ans = temp;
    }
    
    return ans;
}