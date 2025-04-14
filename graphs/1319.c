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
    int vertex;
    struct Node* next;
} Node;

// Structure for adjacency list
typedef struct Graph {
    int numVertices;
    Node** adjLists;  // Array of linked lists
    int* visited;     // Visited array
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)calloc(vertices, sizeof(int));

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, add reverse edge
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    // printf("Visiting %d\n", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        if (!graph->visited[temp->vertex]) {
            DFS(graph, temp->vertex);
        }
        temp = temp->next;
    }
}

int countConnectedComponents(Graph* graph) {
    int components = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            DFS(graph, i);
            components++; // Each DFS call = a new connected component
        }
    }

    return components;
}

int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize) {

    // as long as connectionsSize >= n - 1, there will an answer
    // let's figure out how many computers are NOT connected at all, that should be the answer
    // the previous is not necessarily true, if thers a group of computers who are connected but are not connected to the rest of the network. They will count as connected but
    // will require 1 connection be connected to the 0 computer

    // we can conclude the every connected computer has at least 2 connections except the last and first computer (these have 1) if you arrange them linearly

    // we will need to use DFS to identify computer clusters. Each cluster can be treated as one computer. The answer is number of clusters - 1.

    if (connectionsSize < n - 1) {
        return -1;
    }
    if (connections == NULL) {
        return -1;
    }

    Graph* graph = createGraph(n);

    for (int i = 0; i < connectionsSize; i++) {

        addEdge(graph, connections[i][0], connections[i][1]);

    }

    int clusters = countConnectedComponents(graph); // returns the number of computer clusters
    // printf("Number of clusters: %d\r\n", clusters);

    return clusters - 1;
}