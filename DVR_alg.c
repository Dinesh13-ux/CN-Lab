#include <stdio.h>
#include <stdbool.h>

#define INF 9999
#define N 4


void printRoutingTables(int dist[N][N], int nextHop[N][N]) {
    for (int i = 0; i < N; i++) {
        printf("Routing table for node %d:\n", i);
        printf("Destination\tDistance\tNext Hop\n");
        for (int j = 0; j < N; j++) {
            if (dist[i][j] == INF) {
                printf("%d\t\t%s\t\t%s\n", j, "INF", "-");
            } else if (i == j) {
                printf("%d\t\t%d\t\t-\n", j, dist[i][j]);
            } else {
                printf("%d\t\t%d\t\t%d\n", j, dist[i][j], nextHop[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int graph[N][N] = {
        {0, 1, INF, INF},
        {1, 0, 2, INF},
        {INF, 2, 0, 3},
        {4, INF, 3, 0}
    };

    int dist[N][N];
    int nextHop[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j)
                nextHop[i][j] = j;  
            else
                nextHop[i][j] = -1; 
        }
    }

    bool updated;
    do {
        updated = false;
        for (int i = 0; i < N; i++) { 
            for (int j = 0; j < N; j++) {  
                for (int k = 0; k < N; k++) {  
                    if (dist[i][k] != INF && dist[k][j] != INF &&
                        dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nextHop[i][j] = nextHop[i][k];
                        updated = true;
                    }
                }
            }
        }
    } while (updated);

    printRoutingTables(dist, nextHop);

    return 0;
}
