/*
 * LeetCode Problem 66: Plus One
 * Difficulty: Easy
 * 
 * Problem Description:
 * You are given a large integer represented as an integer array 'digits', 
 * where each digits[i] is the ith digit of the integer. The digits are ordered 
 * from most significant to least significant in left-to-right order. 
 * The large integer does not contain any leading 0's.
 * 
 * Increment the large integer by one and return the resulting array of digits.
 * 
 * Examples:
 * 
 * Example 1:
 *   Input: digits = [1, 2, 3]
 *   Output: [1, 2, 4]
 *   Explanation: The array represents the integer 123.
 *                Incrementing by one gives 123 + 1 = 124.
 *                Thus, the result should be [1, 2, 4].
 * 
 * Example 2:
 *   Input: digits = [4, 3, 2, 1]
 *   Output: [4, 3, 2, 2]
 *   Explanation: The array represents the integer 4321.
 *                Incrementing by one gives 4321 + 1 = 4322.
 *                Thus, the result should be [4, 3, 2, 2].
 * 
 * Example 3:
 *   Input: digits = [9]
 *   Output: [1, 0]
 *   Explanation: The array represents the integer 9.
 *                Incrementing by one gives 9 + 1 = 10.
 *                Thus, the result should be [1, 0].
 * 
 * Constraints:
 *   - 1 <= digits.length <= 100
 *   - 0 <= digits[i] <= 9
 *   - digits does not contain any leading 0's.
 */

// int countDigits(int num) {
//     int temp = num;
//     int count = 0;
//     if (temp == 0) return 1; // Special case for 0
//     while (temp > 0) {
//         temp /= 10;  // Remove the last digit
//         count++;
//     }
//     return count;
// }


// void extractDigits(int num, int *ans, int *index) { // this will extract the most significant digit first via recursion
//     if (num == 0) return;  // Base case
//     extractDigits(num / 10, ans, index);  // Process the most significant digits first
//     ans[*index] = num % 10; // remove everything except the last digit per recursion
//     (*index)++;
// }

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {

    // ACTUAL ANSWER: we need to add 1 to the last element. If it is a 9, set it to 0 and goto the prev element and add 1 to it and repeat
    // if we get to the first element and its a 9 and we have to add 1 to it, we need to resize the array, then put every element in digits into the answer array
    // we need to do this because of the constraints since the number can be bigger than a long int
    bool flag = false;
    int newSize = digitsSize;
    int *ansArr = NULL;
    for (int i = digitsSize - 1; i >= 0; i--) {
        
        if (digits[i] != 9) {
            digits[i]++;
            break;

        }
        else {
            digits[i] = 0;
            if (i == 0) {
                flag = true; // need to resize
            }
        }

    }

    if (flag) {
        newSize = digitsSize + 1;
        ansArr = (int*) malloc (sizeof(int) * newSize);
        ansArr[0] = 1;
        memcpy(&ansArr[1], digits, digitsSize * sizeof(int));
    }
    else {
        ansArr = (int*) malloc (sizeof(int) * newSize);
        memcpy(ansArr, digits, digitsSize * sizeof(int));
    }

    *returnSize = newSize;
    return ansArr;


    // convert the numbers to an integer per digit by multiplying each number by 10^(digitsSize-1)
    // then add, then find out how many digits the new number is so we can allocate the appropriate amount
    // then add every digit into the answer array

    // OR
    // just do number to string converions method

    // int num = 0;
    // int j = digitsSize - 1;

    // for (int i = 0; i < digitsSize; i++) {
    //     num += digits[i] * pow(10,j);
    //     j--;
    // }

    // printf("LOL: %d\r\n", num);

    // //increment by 1 and find out how many digits this new number has
    // num++;
    // int ansArrSize = countDigits(num);
    // printf("%d \r\n", ansArrSize);
    // int *ansArr = (int*) malloc (sizeof(int) * ansArrSize);
    // int index = 0;
    // extractDigits(num, ansArr, &index);

    // *returnSize = ansArrSize;
    // return ansArr;
    
}