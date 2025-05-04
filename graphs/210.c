/*
 * LeetCode Problem 210: Course Schedule II
 * Difficulty: Medium
 *
 * There are a total of numCourses courses labeled from 0 to numCourses - 1.
 * You are given an array prerequisites where prerequisites[i] = [ai, bi]
 * indicates that you must take course bi first if you want to take course ai.
 *
 * Return the ordering of courses you should take to finish all courses.
 * If there are many valid answers, return any of them.
 * If it is impossible to finish all courses, return an empty array.
 *
 * Example 1:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: [0,1]
 *
 * Example 2:
 * Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,2,1,3]
 *
 * Example 3:
 * Input: numCourses = 1, prerequisites = []
 * Output: [0]
 *
 * Constraints:
 *   - 1 <= numCourses <= 2000
 *   - 0 <= prerequisites.length <= numCourses * (numCourses - 1)
 *   - prerequisites[i].length == 2
 *   - 0 <= ai, bi < numCourses
 *   - ai != bi
 *   - All the pairs [ai, bi] are distinct
 */

// Structure for adjacency list nodes
typedef struct Node {
    bool visited;
    uint16_t val;
    uint16_t maxChildrenSize;
    uint16_t childrenSize;
    uint16_t *children; // contains indexes in the array of Nodes
} Node;

void addChildren(Node **nodeArr, int src, int dest) {

    if (nodeArr == NULL) {
        return;
    }

    // Add dest as a child to src
    Node *srcNode = nodeArr[src];
    srcNode->children[srcNode->childrenSize] = dest;
    srcNode->childrenSize += 1;
    if (srcNode->childrenSize == srcNode->maxChildrenSize) {// increase size
        srcNode->maxChildrenSize *= 2;
        srcNode->children = realloc(srcNode->children, srcNode->maxChildrenSize * sizeof(int));
    }
}

int DFS(Node **nodeArr, int index, bool visited[], bool *loopDetected, int **ansArr, int *ansSize) {

    if (nodeArr[index] == NULL) {
        return 0;
    }

    if (visited[index]) {
        *loopDetected = true;
    }

    if (nodeArr[index]->visited) {
        return 0;
    }

    nodeArr[index]->visited = true;
    visited[index] = true;

    int courseCount = 0;

    // DFS on children
    for (int i = 0; i < nodeArr[index]->childrenSize; i++) {

        courseCount += DFS(nodeArr, nodeArr[index]->children[i], visited, loopDetected, ansArr, ansSize);
    }
    visited[index] = false; // reset to false when backtracking so we don't get a false positive on loop detected i.e [0,1], [0,2], [1,2]. 2 will be a false positive loop
    courseCount++;

    (*ansArr)[*ansSize] = index;
    (*ansSize)++;

    return courseCount;
}

bool countCourses(Node **nodeArr, int size, int courses, int **ansArr, int *ansSize) {

    if (nodeArr == NULL) {
        return 0;
    }

    int coursesToTake = 0;
    bool loopDetected = false;

    for (int i = 0; i < size; i++) {
        // Do DFS on this node if it has NOT been visited
        if (nodeArr[i] != NULL && !(nodeArr[i]->visited)) {
            bool visited[2000] = {false};
            coursesToTake += DFS(nodeArr, i, visited, &loopDetected, ansArr, ansSize);
            if (loopDetected) {
                // printf("loopdetected at %d\n", i);
                return false;
            }
        }
    }

    // printf("coursesToTake: %d\n", coursesToTake);

    if (coursesToTake <= courses) {
        return true;
    }

    return false;
}

void printAllChildren(Node **nodeArr, int size) {
    for (int i = 0; i < size; i++) {
        if (nodeArr[i] != NULL) {
            printf("Node: %d - ", i);
            printf("[");
            // iterate through all children
            for (int j = 0; j < nodeArr[i]->childrenSize; j++) {
                printf("%d, ", nodeArr[nodeArr[i]->children[j]]->val);
            }
            printf("]\n");
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize) {
    
    // we'll use course schedule I to help with this problem (problem 207)
    // we will add every preReq course to a course as their children
    // then we will dfs and add the children first in the array as we recurse on the way up

    if (prerequisites == NULL) {
        return NULL;
    }

    Node **nodeArr = (Node**) calloc (2000, sizeof(Node*)); // max size of prerequisitesSize * 2 in case there are 2 unique courses per entry
    int ansSize = 0;
    int *ansArr = (int*) calloc (2000, sizeof(int)); // just set to 2000 so we dont have to resize

    // fill nodeArr 
    for (int i = 0; i < numCourses; i++) {
        Node *newNode = (Node*) malloc (sizeof(Node));
        newNode->visited = false;
        newNode->val = i;
        newNode->maxChildrenSize = 1;
        newNode->childrenSize = 0;
        newNode->children = (uint16_t*) calloc (1, sizeof(uint16_t)); // we know that the max children of any node is n - 1 - DONT DO THIS OR YOU WILL HIT MLE
        nodeArr[i] = newNode;
    }

    // add the children
    for (int i = 0; i < prerequisitesSize; i++) { // add the prereq as the children
        addChildren(nodeArr, prerequisites[i][0], prerequisites[i][1]);
    }

    // printAllChildren(nodeArr, 2000); // Sanity check that the graph is constructed properly

    bool isPossible = countCourses(nodeArr, 2000, numCourses, &ansArr, &ansSize);

    if (!isPossible) {
        *returnSize = 0;
        return NULL;
    }

    *returnSize = ansSize;
    return ansArr;
}