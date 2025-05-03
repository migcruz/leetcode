/*
 * LeetCode Problem 207: Course Schedule
 * Difficulty: Medium
 *
 * There are a total of numCourses courses labeled from 0 to numCourses - 1.
 * You are given an array prerequisites where prerequisites[i] = [ai, bi]
 * means you must take course bi before course ai.
 *
 * Return true if it is possible to finish all courses, otherwise return false.
 *
 * Example 1:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 *
 * Example 2:
 * Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
 * Output: false
 *
 * Constraints:
 *   - 1 <= numCourses <= 2000
 *   - 0 <= prerequisites.length <= 5000
 *   - prerequisites[i].length == 2
 *   - 0 <= ai, bi < numCourses
 *   - All the pairs prerequisites[i] are unique
 */

// Structure for adjacency list nodes
typedef struct Node {
    bool visited;
    uint16_t val;
    uint16_t maxChildrenSize;
    uint16_t childrenSize;
    uint16_t *children; // contains indexes in the array of Noddes
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

int DFS(Node **nodeArr, int index, bool visited[], bool *loopDetected) {

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

        courseCount += DFS(nodeArr, nodeArr[index]->children[i], visited, loopDetected);
    }
    visited[index] = false; // reset to false when backtracking so we don't get a false positive on loop detected i.e [0,1], [0,2], [1,2]. 2 will be a false positive loop
    courseCount++;
    return courseCount;
}

bool countCourses(Node **nodeArr, int size, int courses) {

    if (nodeArr == NULL) {
        return 0;
    }

    int coursesToTake = 0;
    bool loopDetected = false;

    for (int i = 0; i < size; i++) {
        // Do DFS on this node if it has NOT been visited
        if (nodeArr[i] != NULL && !(nodeArr[i]->visited)) {
            bool visited[2000] = {false};
            coursesToTake += DFS(nodeArr, i, visited, &loopDetected);
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

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    
    // if you are forced to revisit a course then return false (i.e. a cycle in the directional graph)
    // the highest level course will have its preReqs as children
    // use dfs but only increase the counter indicating that you took that course after completing dfs for that node so that we count the prereqs first
    // store the nodes in an array and we will do dfs on each of them
    // use visited array to make sure we dont repeat courses and to detect loops, reset this array afetr every fresh DFS run
    // use another array or a struct member to keep track if node is visited so we dont double count it

    if (prerequisites == NULL) {
        return false;
    }

    Node **nodeArr = (Node**) calloc (2000, sizeof(Node*)); // max size of prerequisitesSize * 2 in case there are 2 unique courses per entry

    // fill nodeArr
    for (int i = 0; i < prerequisitesSize; i++) {
        for (int j = 0; j < 2; j++) {
            if (nodeArr[prerequisites[i][j]] == NULL) { // only create a new node if it exists
                Node *newNode = (Node*) malloc (sizeof(Node));
                newNode->visited = false;
                newNode->val = prerequisites[i][j];
                newNode->maxChildrenSize = 1;
                newNode->childrenSize = 0;
                newNode->children = (uint16_t*) calloc (1, sizeof(uint16_t)); // we know that the max children of any node is n - 1 - DONT DO THIS OR YOU WILL HIT MLE
                nodeArr[prerequisites[i][j]] = newNode;
            }
        }
    }

    // add the children
    for (int i = 0; i < prerequisitesSize; i++) { // add the prereq as the children
        addChildren(nodeArr, prerequisites[i][0], prerequisites[i][1]);
    }

    // printAllChildren(nodeArr, 2000); // Sanity check that the graph is constructed properly

    bool ans = countCourses(nodeArr, 2000, numCourses);

    return ans;
}