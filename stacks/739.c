/*
 * LeetCode Problem 739: Daily Temperatures
 * Difficulty: Medium
 *
 * Problem Description:
 * Given an array of integers 'temperatures' representing the daily temperatures, 
 * return an array 'answer' such that answer[i] is the number of days you have to 
 * wait after the ith day to get a warmer temperature. If there is no future day 
 * for which this is possible, set answer[i] = 0.
 *
 * Example 1:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 *
 * Example 2:
 * Input: temperatures = [30,40,50,60]
 * Output: [1,1,1,0]
 *
 * Example 3:
 * Input: temperatures = [30,60,90]
 * Output: [1,1,0]
 *
 * Constraints:
 * - 1 <= temperatures.length <= 10^5
 * - 30 <= temperatures[i] <= 100
 */

struct Node {

    struct Node *next;
    int temp;
    int index;
};

void popStack(struct Node **root) {

    if (root == NULL) {
        return;
    }

    struct Node *temp = *root;
    *root = temp->next;
    free(temp);

}

void pushStack(struct Node **root, int temperature, int index) {

    if (root == NULL) {
        return;
    }

    struct Node *temp = *root;
    struct Node *newNode = (struct Node*) malloc (sizeof(struct Node));
    newNode->next = NULL;
    newNode->temp = temperature;
    newNode->index = index;

    if (temp == NULL) {
        *root = newNode;
    }
    else {
        newNode->next = *root;
        *root = newNode;
    }

}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {

    // let's try a stack. we will try to enter an element into the stack and we will pop an element if the top of the stack is less temperature than the current element
    // then we will find the difference between the two indices and store that as the answer.
    // the last element of ans is always zero

    struct Node *root = NULL;
    int *ans = (int*)calloc(1, sizeof(int) * temperaturesSize);

    for (int i = 0; i < temperaturesSize; i++) {
        
        if (root == NULL || temperatures[i] <= root->temp) {
            pushStack(&root, temperatures[i], i);
        }
        else {
            while (temperatures[i] > root->temp) {
                // printf("i: %d, rootIndex: %d\r\n", i, root->index);
                ans[root->index] = i - (root->index);
                popStack(&root);
                if (root == NULL) {
                    break;
                }
            }
            pushStack(&root, temperatures[i], i); // push the current temp since no lower one is in the stack
        }
    }
    *returnSize = temperaturesSize;
    return ans;


    //brute force/naive solution is for every element iterate forward until you see a temperature greater than that element, then the index difference is the answer for htat ith element
    // last element of ans is always 0
    // this will hit TLE so we need another approach like a stack

    // int *ans = (int*)calloc(1, sizeof(int) * temperaturesSize);

    // for (int i = 0; i < temperaturesSize; i++) {

    //     int j = 0;
    //     for (j = i + 1; j < temperaturesSize; j++) {
            
    //         if (temperatures[j] > temperatures[i]) {
    //             ans[i] = j - i;
    //             break;
    //         }

    //         if (j == temperaturesSize - 1) {//reached end and theres no answer
    //             ans[i] = 0;
    //             break;
    //         }

    //     }
    // }

    // *returnSize = temperaturesSize;
    // return ans;

    
}