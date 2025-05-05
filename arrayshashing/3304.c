/*
 * LeetCode Problem 3304: Find the K-th Character in String Game I
 * Difficulty: Easy
 *
 * Alice and Bob are playing a game. Initially, Alice has a string word = "a".
 * You are given a positive integer k.
 *
 * Bob will ask Alice to perform the following operation forever:
 *   - Generate a new string by changing each character in word to its next character 
 *     in the English alphabet, and append it to the original word.
 *
 * For example:
 *   - "c" becomes "cd"
 *   - "zb" becomes "zbac"
 *
 * Return the value of the k-th character in word, after enough operations have been
 * done for word to have at least k characters.
 *
 * Note: The character 'z' changes to 'a'.
 *
 * Example 1:
 * Input: k = 5
 * Output: "b"
 *
 * Example 2:
 * Input: k = 10
 * Output: "c"
 *
 * Constraints:
 *   - 1 <= k <= 500
 */

char kthCharacter(int k) {
    
    // make a max char array of 1000 since k <= 500
    // keep generating substrings and appending it to the string and keep checking if the string length has hit k yet, if it does then return the kth character (actually k - 1 because of 0-indexed)

    char *arr = (char*) calloc (1000, sizeof(char));
    arr[0] = 'a';
    int len = strlen(arr);
    // printf("len: %d\n", len);
    while (1) {

        if (len >= k) {
            break;
        }
        char *temp = (char*)calloc(len, sizeof(char));
        for (int i = 0; i < len; i++) {
            if (arr[i] == 'z'){
                temp[i] = 'a';
            }
            else{
                temp[i] = arr[i] + 1;
            }
        }

        // add this to the original array
        strncpy(&arr[len], temp, len * sizeof(char));
        free(temp);
        len = strlen(arr);
    }

    return arr[k-1];
}