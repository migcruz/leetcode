/*
 * LeetCode Problem 128: Longest Consecutive Sequence
 * Difficulty: Medium
 * 
 * Problem Description:
 * Given an unsorted array of integers 'nums', return the length of the 
 * longest consecutive elements sequence.
 * 
 * Note: You must write an algorithm that runs in O(n) time.
 * 
 * Examples:
 * Example 1:
 * Input: nums = [100, 4, 200, 1, 3, 2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
 * 
 * Example 2:
 * Input: nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
 * Output: 9
 * Explanation: The longest consecutive elements sequence is [0, 1, 2, 3, 4, 5, 6, 7, 8].
 * 
 * Example 3:
 * Input: nums = [1, 0, 1, 2]
 * Output: 3
 * 
 * Constraints:
 * - 0 <= nums.length <= 10^5
 * - -10^9 <= nums[i] <= 10^9
 */

 struct number {
    int id; //this will just be the number
    bool visited; // we can use this is a flag to skip this number as a start sequence candidate
    UT_hash_handle hh; // makes this struct hashable via uthash https://troydhanson.github.io/uthash/. This is already part of leetcode. It's just a header so there's library to link against for builds.
};

struct number *numberDict = NULL;

bool add_number(int num) {

    struct number *temp = NULL;
    HASH_FIND_INT(numberDict, &num, temp);

    if (temp == NULL) {
        struct number *newNumber = (struct number*) malloc (sizeof(struct number));
        newNumber->id = num;
        newNumber->visited = false;
        HASH_ADD_INT(numberDict, id, newNumber);
        return true;
    }

    return false;
}

struct number *get_number(int num) {

    struct number *temp = NULL;
    HASH_FIND_INT(numberDict, &num, temp);
    
    return temp;
}

void delete_number(int num) {
    struct number *temp = get_number(num);

    if (temp != NULL) {
        HASH_DEL(numberDict, temp);  /* user: pointer to deletee */
        free(temp);             /* optional; it's up to you! */
    }
}

int longestConsecutive(int* nums, int numsSize) {

    //add all numbers to a hash table. 
    //Then iterate through nums until you find a number without a predecessor, this will be a number that is at the start of a sequence
    // keep increasing by 1 and check if its in the table, if not, move along the list
    // This should be an O(N) time complexity solution with constant O(1) space complexity.
    int ans = 1;
    struct number *iter;

    if (numsSize == 0) {
        return 0;
    }

    // add all the nums
    for (int i = 0; i < numsSize; i++) {
        add_number(nums[i]);
    }

    for (iter = numberDict; iter != NULL; iter = iter->hh.next) {
        
        int ansTemp = 1;
        struct number *temp = iter;
    
        if (temp->visited) { // each sequence is unique and linearly independent, if it has been visited the no need to try it again.
            continue;
        }

        // find a number without a predecessor
        while (get_number(temp->id - 1) != NULL) {
            temp = get_number(temp->id - 1);
        }

        // check if this new start of sequence has already been tried
        if (temp->visited) {
            continue;
        }

        while (get_number(temp->id + 1) != NULL) {
            temp->visited = true;
            temp = get_number(temp->id + 1);
            ansTemp++;
        }

        // now we reached the max sequence count, save the answer
        ans = (ansTemp > ans) ? ansTemp : ans;

        // each sequence is unique and linearly independent, if a sequence is greater than half the array length
        // then its impossible for a better answer
        if (ans > numsSize / 2) { 
            break;
        }
    }

    //clean up table or else other test cases will fail as memory is not cleared with uthash per test case
    for (int i = 0; i < numsSize; i++) {
        delete_number(nums[i]);
    }

    return ans;
    
}