/*
 * LeetCode Problem 812: Largest Triangle Area
 * Difficulty: Easy
 *
 * Problem Description:
 * You are given an array `points` consisting of points on the 2D Cartesian plane.
 * Each point is represented as points[i] = [xi, yi].
 *
 * Return the area of the largest triangle that can be formed by any three different points.
 * The result should be accepted if it's within 1e-5 of the actual answer.
 *
 * Examples:
 *
 * Example 1:
 * Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
 * Output: 2.00000
 * Explanation: Among all triangles that can be formed, the triangle with vertices
 * (0,2), (2,0), and (0,0) has the largest area of 2.
 *
 * Example 2:
 * Input: points = [[1,0],[0,0],[0,1]]
 * Output: 0.50000
 * Explanation: This triangle has area 0.5.
 *
 * Constraints:
 *   - 3 <= points.length <= 50
 *   - -50 <= xi, yi <= 50
 *   - All the points are unique
 *
 * Notes:
 *   - The area of a triangle given coordinates (x1,y1), (x2,y2), (x3,y3)
 *     can be computed using the formula:
 *
 *       area = 0.5 * abs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2))
 */


// brute force 
//  void findCombinations(int arr[], int n) {
//      for (int i = 0; i < n - 2; i++) {
//          for (int j = i + 1; j < n - 1; j++) {
//              for (int k = j + 1; k < n; k++) {
//                  printf("(%d, %d, %d)\n", arr[i], arr[j], arr[k]); // Unique triplet
//              }
//          }
//      }
//  }

void generateCombinations(int **arr, int n, int index, int data[3][2], int depth, double *area) {
    if (depth == 3) { // Base case: found a valid combination
        int x1 = data[0][0];
        int x2 = data[1][0];
        int x3 = data[2][0];

        int y1 = data[0][1];
        int y2 = data[1][1];
        int y3 = data[2][1];

        double tempArea = fabs(0.5 * ( x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2))); // need to use fabs for floats
        double ans = *area;

        ans = (tempArea > ans) ? tempArea : ans;
        *area = ans;
        // printf("%lf\n", tempArea);
        return;
    }

    for (int i = index; i < n; i++) {
        data[depth][0] = arr[i][0];
        data[depth][1] = arr[i][1];
        // memcpy(data[depth], arr[i], 2 * sizeof(int)); // need to do this or we will do a double free accidentally
        generateCombinations(arr, n, i + 1, data, depth + 1, area);
    }
}

double largestTriangleArea(int** points, int pointsSize, int* pointsColSize) {

    // we can use brute force or backtracking to generate all possible combinations of 3 points from the array.
    // then we use the shoelace formula to calculate the biggest area: Area=0.5∗|x1​⋅(y2​−y3​)+x2​⋅(y3​−y1​)+x3​⋅(y1​−y2​)|

    // # of combinations = n!/(r!(n-r)!)

    if (points == NULL) {
        return 0;
    }

    double ans = 0;
    int data[3][2];
    // int **data = (int**) calloc (3, sizeof(int*));
    // for (int i = 0; i < 3; i++) {
    //     data[i] = (int*) calloc (2, sizeof(int));
    // }

    generateCombinations(points, pointsSize, 0, data, 0, &ans);

    // for (int i = 0; i < 3; i++) {
    //     if (data[i] != NULL) {
    //         free(data[i]);
    //     }
    // }

    // free(data);

    return ans;

}