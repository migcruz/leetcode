/*
 * LeetCode Problem 20: Valid Parentheses
 * Difficulty: Easy
 *
 * Problem Description:
 * Given a string `s` containing only the characters '(', ')', '{', '}', '[' and ']', 
 * determine if the input string is **valid**.
 *
 * A valid string must satisfy the following conditions:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket must have a corresponding open bracket of the same type.
 *
 * Example 1:
 * Input: s = "()"
 * Output: true
 * Explanation: The parentheses are correctly paired and ordered.
 *
 * Example 2:
 * Input: s = "()[]{}"
 * Output: true
 * Explanation: Multiple types of brackets are correctly paired and ordered.
 *
 * Example 3:
 * Input: s = "(]"
 * Output: false
 * Explanation: The brackets are mismatched.
 *
 * Example 4:
 * Input: s = "([])"
 * Output: true
 * Explanation: Nested brackets are correctly structured.
 *
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - `s` consists only of the characters '()[]{}'.
 */

struct Node {
    struct Node *next;
    char val;
};


void pushStack (struct Node **root, char val) {

    struct Node *temp = *root;

    if (temp == NULL) { //empty list
        struct Node *newNode = (struct Node*) malloc (sizeof(struct Node));
        newNode->val = val;
        newNode->next = NULL;
        *root = newNode;
        return;
    }
    else {
        // Need to add to the top of the list
        struct Node *newNode = (struct Node*) malloc (sizeof(struct Node));
        newNode->val = val;
        newNode->next = temp;

        *root = newNode;
        return;
    }
}

void printStack (struct Node *root, char *s) {

    while (root != NULL) {

        printf ("%s: %c\r\n", s, root->val);
        root = root->next;
    }

    return;

}

struct Node *popStack (struct Node **root) {

    struct Node *temp = *root;

    *root = temp->next;
    
    return temp;

}

bool isValid(char* s) {

    //we'll traverse the string and add to the stack DS each time an open parentheses is encountered. if we encounter a close parentheses, we pop from the stack and evaluate if its valid

    bool ans = true;

    struct Node *openStack = NULL;

    int len = strlen(s);
    if (len == 1) {
        return false;
    }
    

    printf("s length: %d\r\n", len);
    for (int i = 0; i < len; i++) {

        if (s[i] == '(' || s[i] == '[' || s[i] == '{'){
            pushStack(&openStack, s[i]);
            ans = false;
        } 
        else {
            struct Node *a;

            if (openStack == NULL) {
                return false;
            }
            a = popStack(&openStack);

            if (a->val == '{' && s[i] != '}') {
                return false;
            }
            else if (a->val == '[' && s[i] != ']') {
                return false;
            }
            else if (a->val == '(' && s[i] != ')') {
                return false;
            }
            else if (a == NULL) {
                return false;
            }

            if (a != NULL) {
                free(a);
            }

            ans = true;
        }       
    }

    if (openStack != NULL) {  //openstack should be empty at this point
        return false;
    }


    return ans;
}
