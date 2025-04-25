/*
 * LeetCode Problem 131: Palindrome Partitioning
 * Difficulty: Medium
 *
 * Problem Description:
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning of s.
 *
 * A palindrome is a string that reads the same backward as forward.
 *
 * Examples:
 *
 * Example 1:
 * Input:  s = "aab"
 * Output: [["a","a","b"],["aa","b"]]
 *
 * Example 2:
 * Input:  s = "a"
 * Output: [["a"]]
 *
 * Constraints:
 *   1 <= s.length <= 16
 *   s contains only lowercase English letters.
 */

bool isPalindrome(char *str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

void generatePalindromeTree(char *str, int start, int length,
                            char **currentPartition, int depth, char ****ans, int *ansSize, int **returnColSizes, int *ansSizeCap) {

    if (ans == NULL || returnColSizes == NULL) {
        return;
    }

    if (start == length) { //reached past the end therefore we copy everything in the currentPartition into the answer
        char **newPartition = (char**) malloc (sizeof(char*) * depth);
        for (int i = 0; i < depth; i++) {
            newPartition[i] = strdup(currentPartition[i]);
        }

        // printf("LOL: %d\n", *ansSize);

        char ***tempAns = *ans;
        int *tempReturnColSizes = *returnColSizes;
        tempAns[*ansSize] = newPartition;
        tempReturnColSizes[*ansSize] = depth;
        (*ansSize)++;

        //expand the array by doubling the size so we dont have heap fragmentation
        if (*ansSize == *ansSizeCap) {
            *ansSizeCap *= 2;
            *ans = (char***) realloc(tempAns, sizeof(char**) * (*ansSizeCap)); // ansSize was 0 then became 1 so we need to increase it by a + 1 to make a size 2 array and so on
            *returnColSizes = (int*) realloc(tempReturnColSizes, sizeof(int) * (*ansSizeCap));
        }
        
        return;
    }

    // Generate substrings
    for (int end = start; end < length; end++) {
        // Print substring from index 'start' to 'end'

        char temp[end - start + 2];
        int j = 0;
        for (int i = start; i <= end; i++) {
            temp[j] = str[i];
            j++;
        }
        temp[j] = '\0';

        if (isPalindrome(temp)) {
            // printf("%s\n", temp);
            char *tempDupe = (char*) calloc (end - start + 2, sizeof(char));
            strncpy(tempDupe, temp, strlen(temp) * sizeof(char));
            currentPartition[depth] = tempDupe;

            // Recursively generate children starting AFTER this substring
            generatePalindromeTree(str, end + 1, length, currentPartition, depth + 1, ans, ansSize, returnColSizes, ansSizeCap);
            free(tempDupe);

        }

    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** partition(char* s, int* returnSize, int** returnColumnSizes) {

    // we know that partitioning s by 1 char each will always result in palindromes
    // we know that the max size for a partition is 16 elements from the constraints which is going to be 1 char per element
    // we need to generate every sub string from the string and only choose the ones that are palindromes

    // we need to make a tree similar to a trie where each node is a substring in a partition array and its children are the following palindrom substrings

    if (s == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    // struct treeNode *root = createNode("");

    // generatePalindromeTree(root, s, 0, strlen(s));

    // Make answer
    int ansSize = 0; // also the index
    int ansSizeCap = 1;
    char ***ans = (char***) calloc (1, sizeof(char**));
    int *returnColSizes = (int*) calloc (1,sizeof(int));

    char *currentPartition[16]; // we know 16 is the bigest size a partition can be from the constraints

    generatePalindromeTree(s, 0, strlen(s), currentPartition, 0, &ans, &ansSize, &returnColSizes, &ansSizeCap);
    // dfs(root, currentPartition, 0, &ans, &ansSize, &returnColSizes);

    // Now we need to generate the answer array

    
    *returnColumnSizes = returnColSizes;
    *returnSize = ansSize;
    return ans;
}