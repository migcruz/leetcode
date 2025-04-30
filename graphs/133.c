/*
 * LeetCode Problem 133: Clone Graph
 * Difficulty: Medium
 *
 * Problem Description:
 * Given a reference to a node in a connected undirected graph, return a deep copy (clone) of the graph.
 * Each node contains an integer value and a list of its neighbors.
 *
 * class Node {
 *     public int val;
 *     public List<Node> neighbors;
 * }
 *
 * The graph is connected, has no self-loops or repeated edges, and each node has a unique value.
 *
 * Example 1:
 * Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
 * Output: [[2,4],[1,3],[2,4],[1,3]]
 * Explanation:
 * Node 1 is connected to Nodes 2 and 4.
 * Node 2 is connected to Nodes 1 and 3.
 * Node 3 is connected to Nodes 2 and 4.
 * Node 4 is connected to Nodes 1 and 3.
 *
 * Example 2:
 * Input: adjList = [[]]
 * Output: [[]]
 * Explanation: One node (val = 1) with no neighbors.
 *
 * Example 3:
 * Input: adjList = []
 * Output: []
 * Explanation: Empty graph (no nodes).
 *
 * Constraints:
 *   - Number of nodes: 0 to 100
 *   - 1 <= Node.val <= 100
 *   - Node.val is unique
 *   - No repeated edges or self-loops
 *   - The graph is connected and all nodes can be visited from the given node
 */

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */

 struct Node *dfs(struct Node *root, bool visited[], struct Node **nodeArr) {

    if (root == NULL) {
        return NULL;
    }

    if (visited[root->val]) {// we've been here so just return the copy 
        return nodeArr[root->val];
    }

    visited[root->val] = true;

    // copy current node
    struct Node *newNode = (struct Node*) malloc (sizeof(struct Node));
    newNode->val = root->val;
    newNode->numNeighbors = root->numNeighbors;
    newNode->neighbors = (struct Node**) calloc (newNode->numNeighbors, sizeof(struct Node*));

    // add it to the nodeArr so it can be referenced during recursion
    nodeArr[root->val] = newNode;

    //go through all the children and do dfs
    for (int i = 0; i < root->numNeighbors; i++) {
        struct Node* temp = dfs(root->neighbors[i], visited, nodeArr);
        if (temp != NULL) {
            newNode->neighbors[i] = temp;
        }
    }

    return newNode;
}

struct Node *cloneGraph(struct Node *s) {

    // we can use dfs to keep cloning the current node and then iteratively clone the children
    // and assign the cloned children to the current cloned node before recursing back
    // dfs will return a copy of the current node

    // we will need an array to mark if the node is visited since the values are unique and there are maximum of 100 nodes

    if (s == NULL) {
        return NULL;
    }

    bool visited[101] = {false};
    struct Node **nodeArr = (struct Node**) calloc (101, sizeof(struct Node*));

    struct Node *ans = dfs(s, visited, nodeArr);

    return ans;
	
}