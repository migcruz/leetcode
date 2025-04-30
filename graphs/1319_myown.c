/*
 * LeetCode Problem 1319: Number of Operations to Make Network Connected
 * Difficulty: Medium
 *
 * Problem Description:
 * You are given 'n' computers numbered from 0 to n - 1 and a list of existing connections.
 * Each connection connects two computers directly.
 * You can extract a cable from an existing connection and place it between any pair of
 * disconnected computers to connect them.
 *
 * Return the minimum number of operations required to connect all computers.
 * If it's not possible to connect all computers, return -1.
 *
 * Example 1:
 * Input: n = 4, connections = [[0,1],[0,2],[1,2]]
 * Output: 1
 * Explanation:
 * - Remove the cable between 1 and 2, and connect 1 and 3.
 *
 * Example 2:
 * Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
 * Output: 2
 *
 * Example 3:
 * Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
 * Output: -1
 * Explanation:
 * - Not enough cables to connect all computers.
 *
 * Constraints:
 * - 1 <= n <= 10^5
 * - 1 <= connections.length <= min(n * (n - 1) / 2, 10^5)
 * - connections[i].length == 2
 * - 0 <= ai, bi < n
 * - ai != bi
 * - No duplicate or redundant connections exist.
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
    for (int i = 0; i < size; i++) {
        printf("Node: %d - ", i);
        printf("[");
        // iterate through all children
        for (int j = 0; j < nodeArr[i]->childrenSize; j++) {
            printf("%d, ", nodeArr[nodeArr[i]->children[j]]->val);
        }
        printf("]\n");
    }
}

void DFS(Node **nodeArr, int index) {

    if (nodeArr[index] == NULL) {
        return;
    }
    if (nodeArr[index]->visited) {
        return;
    }

    nodeArr[index]->visited = true;

    // DFS on children
    for (int i = 0; i < nodeArr[index]->childrenSize; i++) {
        DFS(nodeArr, nodeArr[index]->children[i]);
    }
}

int countClusters(Node **nodeArr, int size) {

    if (nodeArr == NULL) {
        return 0;
    }

    int clusters = 0;

    for (int i = 0; i < size; i++) {
        // Do DFS on this node if it has NOT been visited
        if (!(nodeArr[i]->visited)) {
            DFS(nodeArr, i);
            clusters++;
        }
    }
    return clusters;
}

int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize) {

    // as long as connectionsSize >= n - 1, there will an answer
    // let's figure out how many computers are NOT connected at all, that should be the answer
    // the previous is not necessarily true, if thers a group of computers who are connected but are not connected to the rest of the network. They will count as connected but
    // will require 1 connection be connected to the 0 computer

    // we can conclude the every connected computer has at least 2 connections except the last and first computer (these have 1) if you arrange them linearly

    // we will need to use DFS to identify computer clusters. Each cluster can be treated as one computer. The answer is number of clusters - 1.

    // to construct the graph we need to have a list of all the nodes so that they can referred to when we start assigning children to nodes
    // we will then add the nodes from each connection as children to each other
    // then we will DFS to count the number of clusters, marking each node as visisted during DFS
    // once we recurse fully from a cluster, we increase the cluster count by 1 and try DFS again on the next if its NOT visited
    // we repeat this until we get the number of clusters and the answer is # clusters - 1

    if (connectionsSize < n - 1) {
        return -1;
    }
    if (connections == NULL) {
        return -1;
    }

    Node **nodeArr = (Node**) calloc (n, sizeof(Node*));

    // fill nodeArr
    for (int i = 0; i < n; i++) {
        Node *newNode = (Node*) malloc (sizeof(Node));
        newNode->visited = false;
        newNode->val = i;
        newNode->maxChildrenSize = 1;
        newNode->childrenSize = 0;
        newNode->children = (uint16_t*) calloc (1, sizeof(uint16_t)); // we know that the max children of any node is n - 1 - DONT DO THIS OR YOU WILL HIT MLE

        nodeArr[i] = newNode;
    }

    // Now we need to assign children to each node
    for (int i = 0; i < connectionsSize; i++) {
        addChildren(nodeArr, connections[i][0], connections[i][1]);
    }

    // printAllChildren(nodeArr, n); // Sanity check that the graph is constructed properly
 
    // Now do DFS to find all clusters
    int ans = countClusters(nodeArr, n);

    return ans - 1;
}