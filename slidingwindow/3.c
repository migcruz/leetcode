/*
 * LeetCode Problem 3: Longest Substring Without Repeating Characters
 * Difficulty: Medium
 *
 * Problem Description:
 * Given a string 's', find the length of the longest substring 
 * that does not contain duplicate characters.
 *
 * Rules:
 * - The substring must be contiguous (not a subsequence).
 * - The input string may contain English letters, digits, symbols, and spaces.
 *
 * Example 1:
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The longest substring without repeating characters is "abc", with a length of 3.
 *
 * Example 2:
 * Input: s = "bbbbb"
 * Output: 1
 * Explanation: The longest substring without repeating characters is "b", with a length of 1.
 *
 * Example 3:
 * Input: s = "pwwkew"
 * Output: 3
 * Explanation: The longest substring without repeating characters is "wke", with a length of 3.
 * Note that "pwke" is not a valid answer since it is a subsequence, not a substring.
 *
 * Constraints:
 * - 0 <= s.length <= 5 * 10^4
 * - s consists of English letters, digits, symbols, and spaces.
 */


struct number {
    int id; //this will just be the number
    int count; // we can use this is a flag to skip this number as a start sequence candidate
    UT_hash_handle hh; // makes this struct hashable via uthash https://troydhanson.github.io/uthash/. This is already part of leetcode. It's just a header so there's library to link against for builds.
};

struct number *numberDict = NULL;

bool add_number(int num) {

    struct number *temp = NULL;
    HASH_FIND_INT(numberDict, &num, temp);

    if (temp == NULL) {
        struct number *newNumber = (struct number*) malloc (sizeof(struct number));
        newNumber->id = num;
        newNumber->count = 1;
        HASH_ADD_INT(numberDict, id, newNumber);
        return true;
    }
    else {
        (temp->count)++;
    }

    return false;
}

struct number *get_number(int num) {

    struct number *temp = NULL;
    HASH_FIND_INT(numberDict, &num, temp);
    
    return temp;
}

void delete_number(int num) {
    struct number *temp = get_number(num);

    if (temp != NULL) {
        HASH_DEL(numberDict, temp);  /* user: pointer to deletee */
        free(temp);             /* optional; it's up to you! */
    }
}

int lengthOfLongestSubstring(char * s){

    if (s == NULL) {
        return 0;
    }

    // we will use sliding window
    // we will keep expanding right and we will enter an entry into the hash table
    // if we encounter a char that is already in the table, then we keep increasing left until that character count is equal to 1 again
    // keep track of the max window size encounters as that is the answer

    int left = 0;
    int right = 0;
    int ans = 0;

    for (right = 0; right < strlen(s); right++) {

        add_number(s[right]);
        struct number *temp = get_number(s[right]);

        while ( (temp->count) > 1) { // now we need to decrease the size of the window

            struct number *decrement = get_number(s[left]);
            (decrement->count)--;
            left++;
        }

        int tempAns = (right - left) + 1;
        ans = (tempAns > ans) ? tempAns : ans;

    }

    //clean up table or else other test cases will fail as memory is not cleared with uthash per test case
    for (int i = 0; i < strlen(s); i++) {
        delete_number(s[i]);
    }

    return ans;
}