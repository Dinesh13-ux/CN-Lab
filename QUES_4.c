#include <stdio.h>
#define INF 9999
#define V 5  // number of vertices

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

void dijkstra(int graph[V][V], int source, int dest) {
    int dist[V], visited[V], parent[V];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[source] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, u = -1;

        // Find vertex with smallest distance not yet visited
        for (int v = 0; v < V; v++)
            if (!visited[v] && dist[v] < min)
                min = dist[v], u = v;

        if (u == -1) break;
        visited[u] = 1;

        // Stop early if destination is reached
        if (u == dest)
            break;

        // Update neighbors
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INF)
        printf("No path exists from %d to %d\n", source, dest);
    else {
        printf("Shortest distance from %d to %d = %d\n", source, dest, dist[dest]);
        printf("Path: %d", source);
        printPath(parent, dest);
        printf("\n");
    }
}

int main() {
    int graph[V][V] = {
        {0, 6, 0, 1, 0},
        {6, 0, 5, 2, 2},
        {0, 5, 0, 0, 5},
        {1, 2, 0, 0, 1},
        {0, 2, 5, 1, 0}
    };

    int source = 0, dest = 4;
    dijkstra(graph, source, dest);
    return 0;
}
