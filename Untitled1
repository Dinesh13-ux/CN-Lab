#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

// Structure to represent a graph edge
struct Edge {
    int vertex;
    int weight;
};

// Function to perform Dijkstra's algorithm
void dijkstra(int start, int numVertices, vector<vector<Edge>>& graph) {
    // Distance array, initialized to infinity
    vector<int> dist(numVertices, INT_MAX);
    dist[start] = 0;

    // Min-heap priority queue to select the vertex with the minimum distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    // Dijkstra's algorithm loop
    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // If the current distance is greater than the already found shortest distance, skip
        if (currentDist > dist[u]) continue;

        // Explore all neighbors of the current vertex
        for (const auto& edge : graph[u]) {
            int v = edge.vertex;
            int weight = edge.weight;

            // Relax the edge if a shorter path is found
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Output the shortest distances from the start vertex
    cout << "Shortest distances from vertex " << start << ":\n";
    for (int i = 0; i < numVertices; ++i) {
        if (dist[i] == INT_MAX) {
            cout << "Vertex " << i << ": INF\n";
        } else {
            cout << "Vertex " << i << ": " << dist[i] << "\n";
        }
    }
}

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    // Initialize graph as an adjacency list
    vector<vector<Edge>> graph(numVertices);

    cout << "Enter the edges (vertex1, vertex2, weight):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        // Add the edge to the adjacency list (undirected graph, so add both directions)
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    int startVertex;
    cout << "Enter the start vertex: ";
    cin >> startVertex;

    // Run Dijkstra's algorithm from the start vertex
    dijkstra(startVertex, numVertices, graph);

    return 0;
}
