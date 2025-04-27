/*
 * LeetCode Problem 1678: Goal Parser Interpretation
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given a string `command` consisting of characters "G", "()", and/or "(al)" in some order.
 * The Goal Parser interprets:
 *   - "G" as "G"
 *   - "()" as "o"
 *   - "(al)" as "al"
 *
 * The interpreted strings are concatenated in the original order to form the final result.
 * Return the final interpreted string.
 *
 * Examples:
 *
 * Example 1:
 * Input: command = "G()(al)"
 * Output: "Goal"
 *
 * Example 2:
 * Input: command = "G()()()()(al)"
 * Output: "Gooooal"
 *
 * Example 3:
 * Input: command = "(al)G(al)()()G"
 * Output: "alGalooG"
 *
 * Constraints:
 *   1 <= command.length <= 100
 *   command consists of only "G", "()", and "(al)".
 */

char * interpret(char * command){
    // we need to have two ptrs left and right to parse the string similar to sliding window,
    // if right hits G, we make left catch up and add G to answer
    // if right hits ) we make left catch up to ( then find whats in between right and left, if nothing add o to answer
    // if right - left == 3 then add al to answer

    if (command == NULL) {
        return NULL;
    }

    int len = strlen(command);
    int left = 0;
    int right = 0;
    int ansIndex = 0;

    char *ans = (char*) calloc (100, sizeof(char));

    for (right = 0; right < len; right++) {

        if (command[right] == 'G') {
            ans[ansIndex++] = 'G';
        }
        else if (command[right] == ')') {
            // increase left until ( is encountered

            while (left < right) {
                if (command[left] == '(') {
                    // find distance between left and right
                    if (right - left > 1) {
                        ans[ansIndex++] = 'a';
                        ans[ansIndex++] = 'l';
                    }
                    else {
                        ans[ansIndex++] = 'o';
                    }

                    left = right;
                    break;
                }
                left++;
            }
        }
    }

    return ans;
}