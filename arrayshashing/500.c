/*
 * LeetCode Problem 500: Keyboard Row
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an array of strings `words`, return the words that can be typed using
 * letters of the alphabet on only one row of an American keyboard.
 * 
 * Note: The strings are case-insensitive. Both lowercase and uppercase versions
 * of a letter are treated as if they are on the same row.
 *
 * The rows on an American keyboard are:
 *   - Row 1: "qwertyuiop"
 *   - Row 2: "asdfghjkl"
 *   - Row 3: "zxcvbnm"
 *
 * Examples:
 *
 * Example 1:
 *   Input: words = ["Hello", "Alaska", "Dad", "Peace"]
 *   Output: ["Alaska", "Dad"]
 *   Explanation: Only "Alaska" and "Dad" use letters from a single row.
 *
 * Example 2:
 *   Input: words = ["omk"]
 *   Output: []
 *   Explanation: No word can be typed using letters from just one row.
 *
 * Example 3:
 *   Input: words = ["adsdf", "sfd"]
 *   Output: ["adsdf", "sfd"]
 *   Explanation: Both words use only letters from the second row.
 *
 * Constraints:
 *   - 1 <= words.length <= 20
 *   - 1 <= words[i].length <= 100
 *   - Each word consists of only English letters (a-z, A-Z)
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** words, int wordsSize, int* returnSize) {

    // we can use a frequency array for each word and match it with frequency arrays for each keyboard row 
    // we just need to set it to 1 for each word and then mask it with each row's frequency arrays
    //convert lwoer case to capitals when entering into the frequency array

    if (words == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int wordFreqArr[26] = {0};

    int qwertyFreqArr[26] = {0};
    int asdfFreqArr[26] = {0};
    int zxcvFreqArr[26] = {0};

    int wordIndices[20] = {20};
    int count = 0;

    // Make qwerty arr
    qwertyFreqArr['Q' - 'A'] = 1;
    qwertyFreqArr['W' - 'A'] = 1;
    qwertyFreqArr['E' - 'A'] = 1;
    qwertyFreqArr['R' - 'A'] = 1;
    qwertyFreqArr['T' - 'A'] = 1;
    qwertyFreqArr['Y' - 'A'] = 1;
    qwertyFreqArr['U' - 'A'] = 1;
    qwertyFreqArr['I' - 'A'] = 1;
    qwertyFreqArr['O' - 'A'] = 1;
    qwertyFreqArr['P' - 'A'] = 1;

    // Make asdfFreqArr
    asdfFreqArr['A' - 'A'] = 1;
    asdfFreqArr['S' - 'A'] = 1;
    asdfFreqArr['D' - 'A'] = 1;
    asdfFreqArr['F' - 'A'] = 1;
    asdfFreqArr['G' - 'A'] = 1;
    asdfFreqArr['H' - 'A'] = 1;
    asdfFreqArr['J' - 'A'] = 1;
    asdfFreqArr['K' - 'A'] = 1;
    asdfFreqArr['L' - 'A'] = 1;
    asdfFreqArr['W' - 'A'] = 1;

    // Make zxcvFreqArr
    zxcvFreqArr['Z' - 'A'] = 1;
    zxcvFreqArr['X' - 'A'] = 1;
    zxcvFreqArr['C' - 'A'] = 1;
    zxcvFreqArr['V' - 'A'] = 1;
    zxcvFreqArr['B' - 'A'] = 1;
    zxcvFreqArr['N' - 'A'] = 1;
    zxcvFreqArr['M' - 'A'] = 1;

    for (int i = 0; i < wordsSize; i++) {
        
        // scan the word
        // printf("word: %s\n", words[i]);
        int len = strlen(words[i]);
        for (int j = 0; j < len; j++) {

            int temp = words[i][j];

            // convert to upper case
            temp = (temp > 90) ? temp - 32 : temp;

            wordFreqArr[temp - 'A'] = 1;

        }

        // now compare with the frequency array for each row
        for (int j = 0; j < 26; j++) {

            if (wordFreqArr[j] == 1 && wordFreqArr[j] != qwertyFreqArr[j]) {
                // printf("%c\n", j + 'A');
                break;
            }

            if (j == 25) {// found an answer
                wordIndices[count] = i;
                count++;
            }

        }

        for (int j = 0; j < 26; j++) {

            if (wordFreqArr[j] == 1 && wordFreqArr[j] != asdfFreqArr[j]) {
                // printf("%c\n", j + 'A');
                break;
            }

            if (j == 25) {// found an answer
                wordIndices[count] = i;
                count++;
            }

        }

        for (int j = 0; j < 26; j++) {

            if (wordFreqArr[j] == 1 && wordFreqArr[j] != zxcvFreqArr[j]) {
                // printf("%c\n", j + 'A');
                break;
            }

            if (j == 25) {// found an answer
                wordIndices[count] = i;
                count++;
            }

        }
        // try next word
        memset(wordFreqArr, 0, 26 * sizeof(int));
    }

    // printf("count %d\n", count);

    // Make the return arr
    char **ans = (char**) calloc (count, sizeof(char*));

    // copy each validword
    int k = 0;
    for (int i = 0; i < count; i++) { // only count up to valid indices

        int tempLen = strlen(words[wordIndices[i]]);
        char *tempWord = (char*) calloc (tempLen + 1, sizeof(char));

        strncpy(tempWord, words[wordIndices[i]], tempLen * sizeof(char));
        ans[k] = tempWord;
        k++;
    }

    
    *returnSize = count;
    return ans;
    
}