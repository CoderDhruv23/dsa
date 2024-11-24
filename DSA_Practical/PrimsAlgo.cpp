#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void primsAlgorithm(vector<vector<int>>& graph, int V) {
    vector<int> key(V, INT_MAX);  // Stores the minimum weight edge for each vertex
    vector<int> parent(V, -1);   // Stores the parent node of each vertex in the MST
    vector<bool> mstSet(V, false);  // True if the vertex is included in the MST

    // Start with the first vertex
    key[0] = 0;

    for (int count = 0; count < V - 1; ++count) {
        // Find the vertex with the minimum key value that is not yet included in the MST
        int u = -1;
        int minKey = INT_MAX;

        for (int v = 0; v < V; ++v) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        // Include the chosen vertex in the MST
        mstSet[u] = true;

        // Update the key and parent arrays for adjacent vertices of the chosen vertex
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the MST
    cout << "Edge \tWeight" << endl;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
    }
}

int main() {
    // Example graph represented as an adjacency matrix
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    int V = graph.size();
    primsAlgorithm(graph, V);

    return 0;
}
