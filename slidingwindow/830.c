/**
 * LeetCode Problem 830: Positions of Large Groups
 * Difficulty: Easy
 *
 * In a string s of lowercase letters, the characters form consecutive groups
 * of the same letter. A group is identified by an interval [start, end], where
 * start and end are the start and end indices (inclusive) of the group.
 * A group is considered "large" if it has 3 or more characters.
 *
 * Return the intervals of every large group, sorted by the starting index.
 *
 * Examples:
 *
 * Input: s = "abbxxxxzzy"
 * Output: [[3,6]]
 * Explanation: "xxxx" is the only large group with start index 3 and end index 6.
 *
 * Input: s = "abc"
 * Output: []
 * Explanation: No group with 3 or more consecutive identical characters.
 *
 * Input: s = "abcdddeeeeaabbbcd"
 * Output: [[3,5],[6,9],[12,14]]
 * Explanation: The large groups are "ddd" (3-5), "eeee" (6-9), and "bbb" (12-14).
 *
 * Constraints:
 * - 1 <= s.length <= 1000
 * - s consists only of lowercase English letters
 */

struct Node {
    int start;
    int end;
    struct Node *next;
    char *substring;
};

void insertNode (struct Node **root, char *s, int start, int end) {

    if (root == NULL) {
        return;
    }

    struct Node *newNode  = (struct Node*) malloc (sizeof(struct Node));
    newNode->end = end;
    newNode->start = start;
    newNode->substring = (char*) calloc (end - start + 2, sizeof(char)); // need + 2 for NULL terminator
    newNode->next = NULL;

    strncpy(newNode->substring, &s[start], end - start + 1 );
    struct Node *temp = *root;

    if (temp == NULL) { // list is empty
        *root = newNode;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList (struct Node *root) {

    while (root != NULL) {
        printf("%s\r\n", root->substring);
        root = root->next;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** largeGroupPositions(char* s, int* returnSize, int** returnColumnSizes) {

    // lets make a linked list to store the string, start, and end of each substring 
    // we will use slidng window method
    // we will keep incrementing right until we hit a different character
    // we only create a node if  left - right + 1 >= 3

    if (s == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int len = strlen(s);

    int left = 0;
    int right = 0;

    struct Node *root = NULL;

    int subLen = 0;
    int numSubString = 0;

    for (right = 0; right <= len; right++) { // <= because of "aaa" test case

        if (s[right] == s[left]) {
            subLen++;
        }
        else {
            if ( subLen >= 3 ) {// we need to add to the linked list
                // printf("%d\r\n", subLen);
                numSubString++;
                insertNode(&root, s, left, right - 1); //need to reduce right by 1 to get the end index
            }
            subLen = 1;
            left = right;
        }
    }

    //print linked list
    // printList(root);

    // make answer array
    int **ans = (int**) malloc (sizeof(int*) * numSubString);

    //loop through linked list
    struct Node *temp  = root;
    int i = 0;
    while (temp != NULL) {
        int *startEnd = (int*) malloc (sizeof(int) * 2);
        startEnd[0] = temp->start;
        startEnd[1] = temp->end;
        ans[i] = startEnd;

        temp = temp->next;
        i++;
    }

    // make returnColumnSizes
    int *colSizes = (int*) malloc (sizeof(int) * numSubString);

    for (int j = 0; j < numSubString; j++) {
        colSizes[j] = 2;
    }

    *returnColumnSizes = colSizes;
    *returnSize = numSubString;
    return ans;
}