#include<stdio.h>
#include<stdbool.h>
#define INF 9999
#define V 4

void Printpath(int parent[], int j){
    if (parent[j] == -1){
        return;
    }
    Printpath(parent,parent[j]);
    printf(" -> %d",j);
    
}


void PrintRoutingTables(int dist[V][V], int NextHop[V][V]){
    for (int i = 0; i < V; i++){
        printf("Routing Table for node %d: \n",i);
        printf("Destination\tDistance\tNext Hop\n");
        for (int j = 0; j < V; j++){
            if (dist[i][j] == INF){
                printf("%d\t\tINF\t\t-\n",j);
            }
            else if (i == j)
            {
                printf("%d\t\t%d\t\t-\n",j,dist[i][j]);
            }
            else{
                printf("%d\t\t%d\t\t%d\n",j,dist[i][j],NextHop[i][j]);   
            }  
        }
    }
        

}

void dijkstra(int graph[V][V], int source, int dest){
    int dist[V], visited[V], parent[V];

    for (int i = 0; i < V; i++){
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[source] = 0;

    for (int count = 0; count < V-1; count++){
        int min = INF , u = -1;

        for (int v = 0; v < V; v++){
            if (!visited[v] && dist[v] < min){
                min = dist[v], u = v;
            }
        }
        if(u == -1) break;
        visited[u] =  1;

        if(u == dest) break;
        
        for (int v = 0; v < V; v++){
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v] ){
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }   
        } 
    }
    if (dist[dest]==INF){
        printf("No path found\n");
    }
    else{
        printf("Shortest path from %d to %d is: %d\n",source,dest,dist[dest]);
        printf("Path %d ",source);
        Printpath(parent,dest);
        printf("\n");
    }
}

int main(){
    int graph[V][V] = {
        {0, 1, INF, INF},
        {1, 0, 2, INF},
        {INF, 2, 0, 3},
        {4, INF, 3, 0}
    };

    int dist[V][V];
    int nextHop[V][V];
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++)
        {
            dist[i][j] = graph[i][j];
            if(graph[i][j] != INF &&  i!=j){
                nextHop[i][j] = j;
            }
            else{
                nextHop[i][j] = -1;
            }
        }
    }

    bool updated;
    do{
        updated = false;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                for (int k = 0; k < V; k++)
                {
                    if (dist[i][k]!=INF && dist[k][j]!= INF &&
                        dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nextHop[i][j] = nextHop[i][k];
                        updated = true;
                    }
                    
                }
                
            }
            
        }
        


    } while (updated);
    
    
    PrintRoutingTables(dist,nextHop);
    // dijkstra(graph,0,4);
}