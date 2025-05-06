/*
 * LeetCode Problem 3099: Harshad Number
 * Difficulty: Easy
 *
 * An integer divisible by the sum of its digits is called a Harshad number.
 * You are given an integer x. Return the sum of the digits of x if x is a Harshad number,
 * otherwise return -1.
 *
 * Example 1:
 * Input: x = 18
 * Output: 9
 * Explanation: The sum of digits is 9. Since 18 is divisible by 9, return 9.
 *
 * Example 2:
 * Input: x = 23
 * Output: -1
 * Explanation: The sum of digits is 5. Since 23 is not divisible by 5, return -1.
 *
 * Constraints:
 *   - 1 <= x <= 100
 */

void extractDigits(int num, int *sum) { // this will extract the most significant digit first via recursion
    if (num == 0) return;  // Base case
    extractDigits(num / 10, sum);  // Process the most significant digits first
    *sum += num % 10; // remove everything except the last digit per recursion
}

int sumOfTheDigitsOfHarshadNumber(int x) {

    // we need to extract each digit and add them
    // we need to divide by 10 recursively and get the remainder to get the last digit

    // can also convert to a string and add each char number using sum += xString[i] - '0'

    int sum = 0;

    extractDigits(x, &sum);

    if (x % sum == 0) {
        return sum;
    }

    // printf("sum: %d\n");
    
    return -1;
}