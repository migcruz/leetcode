/*
 * LeetCode Problem 2788: Split Strings by Separator
 * Difficulty: Easy
 *
 * Problem Description:
 * Given an array of strings `words` and a character `separator`, split each string 
 * in `words` by `separator`. Return an array of non-empty strings formed after the splits.
 *
 * Notes:
 * - The `separator` determines where to split but is not included in the result.
 * - Each word can split into more than two parts.
 * - Exclude all empty strings in the result.
 * - Preserve the order of the original strings.
 *
 * Examples:
 *
 * Example 1:
 * Input:  words = ["one.two.three","four.five","six"], separator = '.'
 * Output: ["one","two","three","four","five","six"]
 *
 * Example 2:
 * Input:  words = ["$easy$","$problem$"], separator = '$'
 * Output: ["easy","problem"]
 *
 * Example 3:
 * Input:  words = ["|||"], separator = '|'
 * Output: []
 *
 * Constraints:
 *   1 <= words.length <= 100
 *   1 <= words[i].length <= 20
 *   Each character in words[i] is either:
 *     - a lowercase English letter or
 *     - one of the characters: '.', ',', '|', '$', '#', '@'
 *   `separator` is one of the characters: '.', ',', '|', '$', '#', '@'
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** splitWordsBySeparator(char** words, int wordsSize, char separator, int* returnSize) {

    // we will use strtok on each word to generate the tokens an then add it to the answer array that will be resized dynamically

    if (words == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int ansSize = 0;
    int ansSizeCap = 1;
    char **ans = (char**) calloc (100, sizeof(char*));

    for (int i = 0; i < wordsSize; i++) {

        char *token = strtok(words[i], &separator); // need teh reference of oeprator to pass as a string as not as a char

        while (token != NULL) {
            // printf("%s\n", token);
            ans[ansSize] = strdup(token);
            ansSize++;

            if (ansSize == ansSizeCap) {
                ansSizeCap *= 2;

                ans = realloc(ans, sizeof(char*) * ansSizeCap);
            }

            token = strtok(NULL, &separator);
        }
    }

    *returnSize = ansSize;
    return ans;
}