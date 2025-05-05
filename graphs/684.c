/*
 * LeetCode Problem 684: Redundant Connection
 * Difficulty: Medium
 *
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 *
 * You are given a graph that started as a tree with n nodes labeled from 1 to n,
 * with one additional edge added. The added edge has two different vertices chosen
 * from 1 to n, and was not an edge that already existed. The graph is represented as
 * an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge
 * between nodes ai and bi in the graph.
 *
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes.
 * If there are multiple answers, return the answer that occurs last in the input.
 *
 * Example 1:
 * Input: edges = [[1,2],[1,3],[2,3]]
 * Output: [2,3]
 *
 * Example 2:
 * Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
 * Output: [1,4]
 *
 * Constraints:
 *   - n == edges.length
 *   - 3 <= n <= 1000
 *   - edges[i].length == 2
 *   - 1 <= ai < bi <= edges.length
 *   - ai != bi
 *   - There are no repeated edges.
 *   - The given graph is connected.
 */

// Structure for adjacency list nodes
typedef struct Node {
    bool visited;
    uint16_t val;
    uint16_t dfsChild;
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

    // Add src as a child to dest
    Node *destNode = nodeArr[dest];
    destNode->children[destNode->childrenSize] = src;
    destNode->childrenSize += 1;
    if (destNode->childrenSize == destNode->maxChildrenSize) {// increase size
        destNode->maxChildrenSize *= 2;
        destNode->children = realloc(destNode->children, destNode->maxChildrenSize * sizeof(int));
    }
}

void printAllChildren(Node **nodeArr, int size) {
    for (int i = 1; i < size; i++) {
        printf("Node: %d - ", i);
        printf("[");
        // iterate through all children
        for (int j = 0; j < nodeArr[i]->childrenSize; j++) {
            printf("%d, ", nodeArr[nodeArr[i]->children[j]]->val);
        }
        printf("]\n");
    }
}

bool DFS(Node **nodeArr, int index, int prev, int loopVals[], int *loopValsIndex) {

    if (nodeArr[index] == NULL) {
        return false;
    }
    if (nodeArr[index]->visited) {
        if (nodeArr[index]->dfsChild != prev) { // found cycle
            // we will use the last element of loopVals and find its first instance in loopVals, theen set visited to false for all values before that first instance
            loopVals[*loopValsIndex] = index;
            return true;
        }
        return false;
    }

    nodeArr[index]->visited = true;
    loopVals[*loopValsIndex] = index;
    (*loopValsIndex)++;

    // DFS on children
    for (int i = 0; i < nodeArr[index]->childrenSize; i++) {
        bool loopFound = false;
        nodeArr[index]->dfsChild = nodeArr[index]->children[i];
        loopFound = DFS(nodeArr, nodeArr[index]->children[i], index, loopVals, loopValsIndex);
        if (loopFound) {
            return true;
        }
    }

    // this node is not part of the cycle
    nodeArr[index]->visited = false;
    (*loopValsIndex)--;
    loopVals[*loopValsIndex] = 0;
    return false;
}

void findLoop(Node **nodeArr, int size) {

    if (nodeArr == NULL) {
        return;
    }

    int loopVals[size];
    int loopValsIndex = 0;

    for (int i = 1; i < size; i++) {
        // Do DFS on this node if it has NOT been visited
        if (!(nodeArr[i]->visited)) {
            bool loopFound = false;
            loopFound = DFS(nodeArr, i, i, loopVals, &loopValsIndex);
            if (loopFound) {
                break;
            }
        }
    }

    // Set all other nodes not in the loop/cycle to not visited as they are not going to be candidate nodes to be removed
    for (int i = 0; i < 1000; i++) {
        if (loopVals[i] == loopVals[loopValsIndex]){
            // printf("loopVals[%d] = %d, %d\n", i, loopVals[i]);
            for (int j = 0; j < i; j++) {
                nodeArr[loopVals[j]]->visited = false;
            }
            break;
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {

    // we will use a similar approach to 1319
    // each time were about to dfs on a child, we will set the current node's dfs child property to be what is about to be dfsed
    // if we hit any node thats already been visited from another node that is not that visited nodes dfs child, then we found a loop and we exit
    // during backtracking (after all dfs is done for a node) we remove that node from the visited list

    // once we exit from the entire dfs, we just need to check backwards from the input edges to see if any of the nodes in the edge pairs are visited nodes,
    // if yes, remove that one
    // we will need an array to only keep track of nodes in the cycle and only set those nodes in the cycle to visited

    if (edges == NULL) {
        *returnSize = 0;
        return NULL;
    }

    Node **nodeArr = (Node**) calloc (edgesSize + 1, sizeof(Node*)); // +1 because the node values start at 1
    int *ans = (int*) calloc (2, sizeof(int));

    // fill nodeArr
    for (int i = 1; i < edgesSize + 1; i++) {
        Node *newNode = (Node*) malloc (sizeof(Node));
        newNode->visited = false;
        newNode->val = i;
        newNode->dfsChild = 0;
        newNode->maxChildrenSize = 1;
        newNode->childrenSize = 0;
        newNode->children = (uint16_t*) calloc (1, sizeof(uint16_t)); // we know that the max children of any node is n - 1 - DONT DO THIS OR YOU WILL HIT MLE

        nodeArr[i] = newNode;
    }

    // Now we need to assign children to each node
    for (int i = 0; i < edgesSize; i++) {
        addChildren(nodeArr, edges[i][0], edges[i][1]);
    }

    // printAllChildren(nodeArr, edgesSize + 1); // Sanity check that the graph is constructed properly
 
    // // Now do DFS to find all clusters
    findLoop(nodeArr, edgesSize + 1);

    //print all visited nodes for sanity check
    // for (int i = 1; i < edgesSize + 1; i++) {
    //     if (nodeArr[i]->visited) {
    //         printf("%d ", i);
    //     }
    // }
    // printf("\n");

    // now iterate through edges backwards and if both values are visited nodes then we return that pair
    for (int i = edgesSize - 1; i >= 0; i--) {
        if (nodeArr[edges[i][0]]->visited && nodeArr[edges[i][1]]->visited) {
            ans[0] = edges[i][0];
            ans[1] = edges[i][1];
            break;
        }
    }

    *returnSize = 2;
    return ans;
}