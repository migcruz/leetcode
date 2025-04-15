"""
LeetCode Problem 2085: Count Common Words With One Occurrence
Difficulty: Easy

Problem Description:
Given two string arrays words1 and words2, return the number of strings that 
appear exactly once in each of the two arrays.

Examples:

Example 1:
    Input: 
        words1 = ["leetcode","is","amazing","as","is"]
        words2 = ["amazing","leetcode","is"]
    Output: 2
    Explanation:
        - "leetcode" appears exactly once in both arrays. Count it.
        - "amazing" appears exactly once in both arrays. Count it.
        - "is" appears twice in words1. Skip it.
        - "as" appears only in words1. Skip it.
        Total count = 2.

Example 2:
    Input: 
        words1 = ["b","bb","bbb"]
        words2 = ["a","aa","aaa"]
    Output: 0
    Explanation:
        - No words appear in both arrays.

Example 3:
    Input: 
        words1 = ["a","ab"]
        words2 = ["a","a","a","ab"]
    Output: 1
    Explanation:
        - "ab" appears exactly once in both arrays. Count it.
        - "a" appears once in words1 but more than once in words2. Skip it.

Constraints:
    - 1 <= words1.length, words2.length <= 1000
    - 1 <= words1[i].length, words2[j].length <= 30
    - Each word consists only of lowercase English letters.
"""

class Word(object):
    def __init__(self):
        self.word1 = 0
        self.word2 = 0

class Solution(object):
    def countWords(self, words1, words2):
        """
        :type words1: List[str]
        :type words2: List[str]
        :rtype: int
        """

        # we can do a brute force approach by comparing each string in each array to every string in the other array
        # we need to check for each string in each array that it only appears once in their home array as well

        # OR

        # we can make a hash map where we count how many times a string appears in words1 and words2. Then we just count the nodes
        # where Node->count1 == 1 and Node->count2 == 1
        # just scan words1 and make an entry for every word
        # then just scan words2 and only process words that exist in the hashmap already

        wordCount = {}
        ans = 0
        for word in words1:
            if word in wordCount:
                wordCount[word].word1 += 1
            else:
                newWord = Word()
                newWord.word1 = 1
                wordCount[word] = newWord
        
        for word in words2:
            if word in wordCount:
                wordCount[word].word2 += 1
            # else:
            #     newWord = Word()
            #     newWord.word2 = 1
            #     wordCount[word] = newWord

        for key, val in wordCount.items():
            if val.word1 == 1 and val.word2 == 1:
                ans += 1

        return ans
        