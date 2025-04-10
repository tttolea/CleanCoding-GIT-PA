#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

typedef struct Graph {
    int vertices;
    int* visited;
    struct Node** adjacency_lists;
} GPH;

// ---------- Utils ----------
NODE* create_node(int v) {
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH* create_graph(int vertices) {
    GPH* graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE*));
    graph->visited = calloc(vertices, sizeof(int));
    for (int i = 0; i < vertices; i++)
        graph->adjacency_lists[i] = NULL;
    return graph;
}

void add_edge(GPH* graph, int src, int dest) {
    NODE* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void wipe_visited_list(GPH* graph) {
    for (int i = 0; i < graph->vertices; i++)
        graph->visited[i] = 0;
}

// ---------- DFS ----------
void DFS(GPH* graph, int vertex) {
    NODE* temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (!graph->visited[connected_vertex]) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// ---------- BFS ----------
typedef struct Queue {
    int items[100];
    int front;
    int rear;
} Queue;

Queue* create_queue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int is_empty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == 99) return; // full
    if (is_empty(q)) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (is_empty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) q->front = q->rear = -1;
    return item;
}

void BFS(GPH* graph, int start_vertex) {
    Queue* q = create_queue();
    graph->visited[start_vertex] = 1;
    enqueue(q, start_vertex);

    while (!is_empty(q)) {
        int current = dequeue(q);
        printf("%d ", current);

        NODE* temp = graph->adjacency_lists[current];
        while (temp != NULL) {
            int adj = temp->data;
            if (!graph->visited[adj]) {
                graph->visited[adj] = 1;
                enqueue(q, adj);
            }
            temp = temp->next;
        }
    }

    free(q);
}

// ---------- Main ----------
int main() {
    int n, m;
    printf("Cate noduri are graful? ");
    scanf("%d", &n);
    printf("Cate muchii are graful? ");
    scanf("%d", &m);

    GPH* graph = create_graph(n);

    printf("Introdu muchiile (nodurile de la 0 la %d):\n", n - 1);
    for (int i = 0; i < m; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }

    int start;
    printf("De unde plecam in DFS? ");
    scanf("%d", &start);
    printf("Parcurgere cu DFS: ");
    DFS(graph, start);

    wipe_visited_list(graph);
    printf("\nDe unde plecam in BFS? ");
    scanf("%d", &start);
    printf("Parcurgere cu BFS: ");
    BFS(graph, start);
    printf("\n");

    return 0;
}
