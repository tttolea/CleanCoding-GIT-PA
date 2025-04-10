#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int v;
    int *visited;
    Node **adjList;
} Graph;

Node *createNode(int v) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->v = vertices;
    graph->visited = calloc(vertices, sizeof(int));
    graph->adjList = malloc(vertices * sizeof(Node *));
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    Node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

int DFS(Graph *graph, int src, int target) {
    if (src == target) return 1;
    graph->visited[src] = 1;

    Node *adj = graph->adjList[src];
    while (adj != NULL) {
        if (!graph->visited[adj->data]) {
            if (DFS(graph, adj->data, target)) {
                return 1;
            }
        }
        adj = adj->next;
    }
    return 0;
}

void resetVisited(Graph *graph) {
    for (int i = 0; i < graph->v; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int vertices, edges;
    printf("Enter number of restaurants (nodes): ");
    scanf("%d", &vertices);

    Graph *graph = createGraph(vertices);

    printf("Enter number of paths (edges): ");
    scanf("%d", &edges);

    printf("Enter each path (two node indexes, 0-based):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int from, to;
    printf("Check direct path from: ");
    scanf("%d", &from);
    printf("To: ");
    scanf("%d", &to);

    if (DFS(graph, from, to)) {
        printf(" There is a path between %d and %d\n", from, to);
    } else {
        printf(" No path exists between %d and %d\n", from, to);
    }

    return 0;
}
