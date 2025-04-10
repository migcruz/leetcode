/*
 * LeetCode Problem 1232: Check If It Is a Straight Line
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given an array 'coordinates', where coordinates[i] = [x, y] 
 * represents the coordinate of a point. Check if these points make a 
 * straight line in the XY plane.
 *
 * Return 'true' if all points lie on a straight line; otherwise, return 'false'.
 *
 * Example 1:
 * Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
 * Output: true
 *
 * Example 2:
 * Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
 * Output: false
 *
 * Constraints:
 * - 2 <= coordinates.length <= 1000
 * - coordinates[i].length == 2
 * - -10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
 * - coordinates contains no duplicate point.
 */

bool checkStraightLine(int** coordinates, int coordinatesSize, int* coordinatesColSize) {
    
    // to figure out its a straight line, the slope must be constant i.e. y2-y1/x2-x1
    // we can use a dynamic programming approach where we save the previous points slope and compare with current

    if (coordinates == NULL) {
        return false;
    }

    int denominator = coordinates[1][0] - coordinates[0][0];
    float prevSlope;
    if (denominator == 0) { // straight line vertical up
        prevSlope = 999999999;
    }
    else {
        prevSlope = (float)(coordinates[1][1] - coordinates[0][1]) / (coordinates[1][0] - coordinates[0][0]);
    }

    for (int i = 2; i < coordinatesSize; i++) {

        denominator = coordinates[i][0] - coordinates[i-1][0];
        float currSlope;
        if (denominator == 0) { // straight line vertical up
            currSlope = 999999999;
        }
        else {
           currSlope = (float)(coordinates[i][1] - coordinates[i-1][1]) / denominator;

        }

        if (currSlope != prevSlope) {
            return false;
        }
        
        prevSlope = currSlope;
    }

    return true;

}