/*
 * LeetCode Problem 76: Minimum Window Substring
 * Difficulty: Hard
 *
 * Problem Description:
 * Given two strings 's' and 't' of lengths 'm' and 'n' respectively, 
 * return the smallest contiguous substring of 's' that contains all 
 * characters in 't' (including duplicates). If no such substring exists, 
 * return an empty string "".
 *
 * The test cases guarantee that there is only one correct answer.
 *
 * Example 1:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 * Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from 't'.
 *
 * Example 2:
 * Input: s = "a", t = "a"
 * Output: "a"
 * Explanation: The entire string 's' is the minimum window.
 *
 * Example 3:
 * Input: s = "a", t = "aa"
 * Output: ""
 * Explanation: Since 't' contains two 'a's, but 's' only has one, 
 * there is no valid substring.
 *
 * Constraints:
 * - m == s.length
 * - n == t.length
 * - 1 <= m, n <= 10^5
 * - 's' and 't' consist of uppercase and lowercase English letters.
 *
 * Follow-up:
 * Can you implement an algorithm that runs in O(m + n) time?
 */

struct Ans {
    int left;
    int size;
};

char* minWindow(char* s, char* t) {

    int s_len = strlen(s);
    int t_len = strlen(t);
    struct Ans ans = {0};

    if (t_len > s_len) {
        return "";
    }


    // we will need a dynamic sliding window of minimum t_len
    // keep increasing window size until we have all chars in t inside the window. This is a possible answer. Now we just need to minimize it. Record this answer as a string
    // start minimizing the window until a character from t is dropped (frequency reaches 0 for the window)
    // if it is dropped, start increasing the window size until we get that missing character inside the window again
    // if right is at the end of the string, and we drop a char in t from the window while left is increasing, undo that and exit the loop.
    // keep track of the window size, if it gets smaller, update the answer

    int sArr[58] = {0}; //58 chars from A-z in ASCII table
    int tArr[58] = {0};

    //scan t
    for (int i = 0; i < t_len; i++) {
        tArr[t[i] - 'A']++;
    }

    int left = 0;
    int right = 0;
    bool flag = false;
    bool flag2 = true;

    while (1) {

        if (!flag) {
            sArr[s[right] - 'A']++; // don't add the last char again over and over now that we're at the end
        }

        while ((right - left + 1) >= t_len && flag2) {

            //start scanning t into window
            for (int i = 0; i < 58; i++) {
                if (tArr[i] > 0) {
                    int sum = sArr[i] - tArr[i];
                    if (sum < 0) { //char does not exist in window
                        flag2 = false; // get out of while loop
                        break;
                    }
                }

                if (i == 57) {// we have an answer

                    if (right - left + 1 < ans.size || ans.size == 0) {
                        ans.left = left;
                        ans.size = right - left + 1;
                    }
                    flag = true;
                }

            }
            
            if (flag) { // start shrinking the array
                sArr[s[left] - 'A']--;
                int sum = sArr[s[left] - 'A'] - tArr[s[left] - 'A'];

                if (sum < 0) { // means that we lost one of the chars in t from the window
                    flag = false; // set to false so we dont increment left anymore until a new solution is found
                }
                left++;
            }
           
        }
        // printf("LOL: %d %d %d %d, tlen: %d, s_len: %d\r\n", left, right, ans.left, ans.size, t_len, s_len);
        right++;
        flag2 = true;
        if (right == s_len) {
            right--;
            flag = true; // now we continue shrinking the window
            if (right - left + 1 <= t_len) {
                break;
            }
        }
    }

    char *final = (char*) calloc (ans.size + 1, sizeof(char)); // need + 1 for null terminator or you get buffer overflow

    strncpy(final, &s[ans.left], ans.size);

    // printf("ans: %s\r\n", final);

    return final;

    
}