/*
 * LeetCode Problem 17: Letter Combinations of a Phone Number
 * Difficulty: Medium
 *
 * Problem Description:
 * Given a string containing digits from 2-9 inclusive, return all possible 
 * letter combinations that the number could represent. Return the answer in any order.
 *
 * A mapping of digits to letters (just like on the telephone buttons) is provided.
 * Note that digit '1' does not map to any letters.
 *
 * Examples:
 *
 * Example 1:
 * Input:  digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Example 2:
 * Input:  digits = ""
 * Output: []
 *
 * Example 3:
 * Input:  digits = "2"
 * Output: ["a","b","c"]
 *
 * Constraints:
 *   0 <= digits.length <= 4
 *   digits[i] is a digit in the range ['2', '9'].
 */

char *numberToLetters[10] = {
    "",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz",
};

void generateCombinations(char *digits, int digitsLength, int depth, char data[], char ***ans, int *ansSize, int *ansSizeCap) {

    if (depth == digitsLength) { // reached a valid combination

        printf("%s\n", data);
        char *newCombination = (char*) calloc (depth, sizeof(char));
        
        (*ans)[*ansSize] = strdup(data);
        (*ansSize)++;

        if (*ansSize == *ansSizeCap) { // need to resize the answer array

            *ansSizeCap *= 2;
            *ans = realloc (*ans, sizeof(char*) * (*ansSizeCap));
        }

        return;
    }

    char *letters = numberToLetters[digits[depth] - '0'];

    for (int i = 0; i < strlen(letters); i++) {

        data[depth] = letters[i];
        generateCombinations(digits, digitsLength, depth + 1, data, ans, ansSize, ansSizeCap);
    }

}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {

    // the length of the digits is how long each substring should be
    // for example "23" maps tp "abcdef" we need to generate substring of length 2 from this string but only 1 from abc and 1 from def
    // since we need to respect the order, we can't use permutations 
    // we will make a temp array to store valid answers called data that we will fill in with 1 character from each key press

    if (digits == NULL) {
        *returnSize = 0;
        return NULL;
    }

    if (strcmp(digits, "") == 0) {
        *returnSize = 0;
        return NULL;
    }

    int len = strlen(digits);
    char data[5] = {0}; // max length 4 from the constraints and extra for null terminator
    int ansSize = 0;
    int ansSizeCap = 1;
    char **ans = (char**) calloc (1, sizeof(char*));

    generateCombinations(digits, len, 0, data, &ans, &ansSize, &ansSizeCap);

    *returnSize = ansSize;
    return ans;
    
}