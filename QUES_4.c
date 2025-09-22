#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6  
int Distance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}


void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }

    printPath(parent, parent[j]);
    printf("%d ", j);
}


void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];      
    bool sptSet[V];   
    int parent[V];   

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = Distance(dist, sptSet);  
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {

            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        printf("No path from %d to %d\n", src, dest);
    } else {
        printf("Shortest path distance from %d to %d is %d\n", src, dest, dist[dest]);
        printf("Path: ");
        printPath(parent, dest);
        printf("\n");
    }
}

int main() {
    int graph[V][V] = {
        {0, 5, 1, 0, 0, 0},
        {5, 0, 2, 1, 0, 0},
        {1, 2, 0, 4, 8, 0},
        {0, 1, 4, 0, 3, 6},
        {0, 0, 8, 3, 0, 0},
        {0, 0, 0, 6, 0, 0}
    };

    int source = 0;      // Node 'A' if you map 0 -> A, 1 -> B, etc.
    int destination = 5; 

    dijkstra(graph, source, destination);

    return 0;
}
