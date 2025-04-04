/*
 * LeetCode Problem 150: Evaluate Reverse Polish Notation
 * Difficulty: Medium
 *
 * Problem Description:
 * You are given an array of strings `tokens` that represents an arithmetic expression 
 * in Reverse Polish Notation (RPN). Evaluate the expression and return the result as an integer.
 *
 * Notes:
 * - The valid operators are '+', '-', '*', and '/'.
 * - Each operand may be an integer or another expression.
 * - The division between two integers always truncates toward zero.
 * - There will be no division by zero.
 * - The input is always a valid arithmetic expression in RPN.
 * - The answer and all intermediate calculations fit in a 32-bit integer.
 *
 * Example 1:
 * Input: tokens = ["2","1","+","3","*"]
 * Output: 9
 * Explanation: ((2 + 1) * 3) = 9.
 *
 * Example 2:
 * Input: tokens = ["4","13","5","/","+"]
 * Output: 6
 * Explanation: (4 + (13 / 5)) = 6.
 *
 * Example 3:
 * Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
 * Output: 22
 * Explanation:
 * ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
 * = ((10 * (6 / (12 * -11))) + 17) + 5
 * = ((10 * (6 / -132)) + 17) + 5
 * = ((10 * 0) + 17) + 5
 * = (0 + 17) + 5
 * = 17 + 5
 * = 22.
 *
 * Constraints:
 * - 1 <= tokens.length <= 10^4
 * - `tokens[i]` is either an operator: "+", "-", "*", "/", or an integer in the range [-200, 200].
 */

// struct Node {
//     struct Node *next;
//     int val;
// };


// void pushStack(struct Node **node, int val){

//     struct Node *temp = *node;

//     struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->next = NULL;

//     //convert string to
//     newNode->val = val;

//     if (temp == NULL) {
//         *node = newNode;
//     }
//     else{
//         newNode->next = temp;
//         *node = newNode;
//     }

//     return;
// }

// int popStack(struct Node **head) {

//     struct Node *temp = *head;

//     *head = temp->next;

//     int val = temp->val;

//     free(temp);

//     return val;
// }

int evalRPN(char** tokens, int tokensSize) {

    if (tokens == NULL) {
        return 0;
    }

    if (tokensSize == 1) {
        return atoi(tokens[0]);
    }
    
    // we will push stack every number encounetered, when an operand is encountered we pop 2 from the stock and perform the operation, then we pushstack the result of this operation until
    // we encounter a new operand and repeat.

    // when popping from the stack in RPN, the 2nd item to be popped will be the first term in the operation
    // we can also just use an array stack with an index to keep track of the top of the stack which will be faster performance

    struct Node *root = NULL;
    int stack[tokensSize];
    int result;
    int top = -1;

    for (int i = 0; i < tokensSize; i++) {

        if (isdigit(tokens[i][0]) || (tokens[i][0] == '-' && isdigit(tokens[i][1]))) {
            int val = atoi(tokens[i]);
            // pushStack(&root, val);
            stack[++top] = val;
        }
        else {// operand encountered
            int a = stack[top--];
            int b = stack[top--];

            if (tokens[i][0] == '+') {
                result = b + a;
                stack[++top] = result;
            }
            else if (tokens[i][0] == '-') {
                result = b - a;
                stack[++top] = result;
            }
            else if (tokens[i][0] == '*') {
                result = b * a;
                stack[++top] = result;
            }
            else if (tokens[i][0] == '/') {
                result = b / a;
                stack[++top] = result;
            }
        }

    }

    return result;
    
}