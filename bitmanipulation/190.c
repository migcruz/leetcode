/*
 * LeetCode Problem 190: Reverse Bits
 * Difficulty: Easy
 *
 * Problem Description:
 * Reverse bits of a given 32 bits unsigned integer.
 *
 * Note:
 * In some languages (e.g., Java), there is no unsigned integer type.
 * The integer's internal binary representation remains the same, regardless of sign.
 *
 * Examples:
 *
 * Example 1:
 * Input:  n = 00000010100101000001111010011100
 * Output:    964176192 (00111001011110000010100101000000)
 * Explanation: The input represents the unsigned integer 43261596.
 * The output represents 964176192 with its bits reversed.
 *
 * Example 2:
 * Input:  n = 11111111111111111111111111111101
 * Output:   3221225471 (10111111111111111111111111111111)
 * Explanation: The input represents the unsigned integer 4294967293.
 * The output represents 3221225471 with its bits reversed.
 *
 * Constraints:
 *   The input must be a binary string of length 32
 */

uint32_t reverseBits(uint32_t n) {

    // we will isolate the LSB of the number by ANDing it with 0b1
    // then we add that bit to the reversed number
    // then we shift the reversed number by 1 to the left
    // then we shift n by 1 to the right for the next bit

    // looks like we need to shift a total of 32 times no matter what

    uint32_t ans = 0;

    int count = 0;

    for (int i = 0; i < 32; i++) {

        uint8_t temp = n & 0b1;
        ans = ans << 1; // need to shift first so that for the last bit we do NOT shift AFTER adding it
        ans += temp; // can also do ans |= (n & 0b1)
        
        n = n >> 1;
    }

    return ans;
    
}