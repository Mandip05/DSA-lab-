#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

struct Graph {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int visited[MAX_VERTICES];
};

void initGraph(struct Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->adjMatrix[i][j] = 0;
        }
        graph->visited[i] = 0;
    }
}

void addEdge(struct Graph* graph, int start, int end) {
    graph->adjMatrix[start][end] = 1;
    graph->adjMatrix[end][start] = 1;
}

void BFS(struct Graph* graph, int startVertex) {
    int queue[MAX_VERTICES], front = -1, rear = -1;
    queue[++rear] = startVertex;
    graph->visited[startVertex] = 1;

    while (front != rear) {
        int vertex = queue[++front];
        printf("%d ", vertex);

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph->adjMatrix[vertex][i] == 1 && !graph->visited[i]) {
                queue[++rear] = i;
                graph->visited[i] = 1;
            }
        }
    }
}

int main() {
    struct Graph graph;
    initGraph(&graph);

    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 3);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 0, 4);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 6);
    addEdge(&graph, 4, 8);

    printf("Breadth-First Search starting from vertex 0:\n");
    BFS(&graph, 0);
    
    getchar();
    getchar();

    return 0;
}
