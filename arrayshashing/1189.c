/*
 * LeetCode Problem 1189: Maximum Number of Balloons
 * Difficulty: Easy
 *
 * Given a string text, return the maximum number of instances 
 * of the word "balloon" that can be formed using the characters of text.
 * Each character in text may be used at most once.
 *
 * Example 1:
 * Input: text = "nlaebolko"
 * Output: 1
 *
 * Example 2:
 * Input: text = "loonbalxballpoon"
 * Output: 2
 *
 * Example 3:
 * Input: text = "leetcode"
 * Output: 0
 *
 * Constraints:
 *   - 1 <= text.length <= 10^4
 *   - text consists of lowercase English letters only
 */

// Note that this is the same as problem 2287
int maxNumberOfBalloons(char* text) {

    // use a frequency array to scan for the letters in balloon
    // we will then divide each frequency of each cahracter in balloon by what is needed to form 'balloon', the lowest of this number is the answer

    if (text == NULL) {
        return 0;
    }

    int len = strlen(text);
    int freqArr[26] = {0};
    int ans = 0;

    // scan the string
    for (int i = 0; i < len; i++) {
        freqArr[text[i] - 'a']++;
    }

    int numB = freqArr['b' - 'a'];
    int numA = freqArr['a' - 'a'];
    int numL = freqArr['l' - 'a'] / 2;
    int numO = freqArr['o' - 'a'] / 2;
    int numN = freqArr['n' - 'a'];

    // pick the lowest of these counts (as long as all of them are at least 1)
    if (numB < 1 || numA < 1 || numL < 1 || numO < 1 || numN < 1) {
        return 0;
    }
    else {
        ans = numB;
        ans = (numA < ans) ? numA : ans;
        ans = (numL < ans) ? numL : ans;
        ans = (numO < ans) ? numO : ans;
        ans = (numN < ans) ? numN : ans;

        return ans;
    }
}