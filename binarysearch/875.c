/*
 * LeetCode Problem 875: Koko Eating Bananas
 * Difficulty: Medium
 *
 * Problem Description:
 * Koko loves to eat bananas. There are 'n' piles of bananas, where the ith pile 
 * has piles[i] bananas. The guards will return in 'h' hours.
 *
 * Koko can choose her eating speed 'k' bananas per hour. Each hour, she selects 
 * one pile and eats up to 'k' bananas from it. If the pile has fewer than 'k' 
 * bananas, she eats all of them and does nothing for the rest of that hour.
 *
 * Koko wants to finish all the bananas before the guards return. Return the 
 * minimum integer 'k' such that she can eat all the bananas within 'h' hours.
 *
 * Example 1:
 * Input: piles = [3,6,7,11], h = 8
 * Output: 4
 *
 * Example 2:
 * Input: piles = [30,11,23,4,20], h = 5
 * Output: 30
 *
 * Example 3:
 * Input: piles = [30,11,23,4,20], h = 6
 * Output: 23
 *
 * Constraints:
 * - 1 <= piles.length <= 10^4
 * - piles.length <= h <= 10^9
 * - 1 <= piles[i] <= 10^9
 */

 bool canEatAll(int *nums, int numsSize, double k, int h) {
    int ans = true;
    double hoursSoFar = 0;
    for (int i = 0; i < numsSize; i++) {

        double extraHours = ceil((double)(nums[i]) / k);
        // printf("extraHours %f, piles[%d]: %d\r\n", extraHours, i, piles[i]);
        hoursSoFar += extraHours;

        if (hoursSoFar > h) { // need to increase k and try again
            return false;;
        }
    }

    return ans;
}

int minEatingSpeed(int* piles, int pilesSize, int h) {

    // k * h must be >= sum of piles. round up k if not a whole number
    // k is the minimum amount that is viable
    // for every element that is bigger than k, it adds extra hours

    // if we sort the array and find k, that gives us the index where k should be. this index is the amount of hours already consumed
    // therefore h - i, where piles[i] = k, is the amount of hours we have left to increase the answer
    // therefore we need to step up k

    //we know that k <= ans <= max(pilesSize) we just need to do binary search  within this range

    if (piles == NULL) {
        return 0;
    }

    double sum = 0;
    double maxPile = 0;

    for (int i = 0; i < pilesSize; i++) {
        maxPile = (piles[i] > maxPile) ? piles[i] : maxPile;
        sum += piles[i];
    }

    double k = sum / h; // we must round up if it's not a whole number
    k = ceil(k);
    // printf("k %f, sum %f\r\n", k, sum);

    double left = k;
    double right = maxPile;

    // calculate the amount of extra hours needed with current k to finish the piles
    while (left < right) {

        k = left + (right - left) / 2;
        if (canEatAll(piles, pilesSize, k , h)) {// lets try smaller k
            right = k;
            k = left + (right - left) / 2;
        }
        else {// lets try bigger k
            left = k + 1;
            k = left + (right - left) / 2;
        }

        // printf("TRY K: %f\r\n", k);
    }

    // now we need to try both the ceil and floor of k
    k = (int)floor(k);
    if (canEatAll(piles, pilesSize, k , h)) {
        return k;
    }
    else {
        k++;
        return k;
    }
    
}