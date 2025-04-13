/*
 * LeetCode Problem 1736: Latest Time by Replacing Hidden Digits
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given a string 'time' in the format "hh:mm", where some digits may be hidden (represented by '?').
 * The goal is to replace each '?' with a digit such that the resulting time is the latest valid time
 * between "00:00" and "23:59".
 *
 * Return the latest valid time you can get by replacing the hidden digits.
 *
 * Example 1:
 * Input: time = "2?:?0"
 * Output: "23:50"
 * Explanation:
 * - The latest hour starting with '2' is "23"
 * - The latest minute ending with '0' is "50"
 *
 * Example 2:
 * Input: time = "0?:3?"
 * Output: "09:39"
 *
 * Example 3:
 * Input: time = "1?:22"
 * Output: "19:22"
 *
 * Constraints:
 * - time is in the format "hh:mm"
 * - It is guaranteed that you can produce a valid time from the given string
 */

char* maximumTime(char* time) {
    // for the hour digits, if the first digit is a 2 the max digit value for the 2nc digit is 3 otherwise the max digit for the second digit is 9
    // the max value for the 1st digit in hours is 2

    //for the minute digits, the max digit for the 1st digit is always 5 and the max digit for the 2nd digit is always 9

    if (time == NULL) {
        return NULL;
    }

    int len = strlen(time);

    char *ans = (char*) calloc (len + 1, sizeof(char));


    // scan time for first question mark
    for (int i = 0; i < len; i++) {

        if (time[i] == '?') {

            if (i == 0 && (time[1] <= '3' || time[1] == '?')) {
                ans[i] = '2';
            }
            else if (i == 0 && time[1] > '3') {
                ans[i] = '1';
            }
            else if (i == 1 && ans[0] == '2') {
                ans[i] = '3';
            }
            else if (i == 1) {
                ans[i] = '9';
            }

            else if (i == 3) { // minutes
                ans[i] = '5';
            }

             else if (i == 4) { // minutes
                ans[i] = '9';
            }
        }
        else {
            ans[i] = time[i];
        }
        

    }

    return ans;
    
}