/*
 * LeetCode Problem 3120: Count the Number of Special Characters I
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given a string 'word'. A letter is considered special if it appears 
 * in both lowercase and uppercase in the string.
 *
 * Return the number of special letters in 'word'.
 *
 * Example 1:
 * Input: word = "aaAbcBC"
 * Output: 3
 * Explanation: The special characters in word are 'a', 'b', and 'c'.
 *
 * Example 2:
 * Input: word = "abc"
 * Output: 0
 * Explanation: No character in word appears in uppercase.
 *
 * Example 3:
 * Input: word = "abBCab"
 * Output: 1
 * Explanation: The only special character in word is 'b'.
 *
 * Constraints:
 * - 1 <= word.length <= 50
 * - word consists of only lowercase and uppercase English letters
 */

int numberOfSpecialChars(char* word) {

    // we can scan the string once using two frequency arrays for each letter for the uppercase and lower case versions. we increment by one if we see one of these letters
    // if the count for each letter in both frequency arrays is greater than 0, that is a special character and we increase ans by 1

    if (word == NULL) {
        return 0;
    }

    int ans = 0;

    int lowerFreq[26] = {0};
    int upperFreq[26] = {0};
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        
        int index = word[i] - 'a';
        
        //if less than 0 then its a capital letter
        if (index < 0) {
            upperFreq[word[i] - 'A']++;
        }
        else {
            lowerFreq[index]++;
        }

    }

    //now scan both frequency arrays
    for (int i = 0; i < 26; i++) {

        if (upperFreq[i] > 0 && lowerFreq[i] > 0) {
            ans++;
        }

    }

    return ans;
    
    // can do a brute force approach for every character and scan the rest of string to see if there is an upper case or lower case version of it
    // this will TLE though
}