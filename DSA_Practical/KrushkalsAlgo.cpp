#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to find the root of an element using path compression
int findParent(int node, vector<int>& parent) {
    if (parent[node] == node) {
        return node;
    }
    return parent[node] = findParent(parent[node], parent);
}

// Function to union two sets
void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Kruskal's algorithm
void kruskalAlgorithm(vector<Edge>& edges, int V) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    vector<int> parent(V);
    vector<int> rank(V, 0);

    // Initialize parent of each node to itself
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    vector<Edge> mst;  // To store edges of the MST
    int mstWeight = 0;

    for (auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;

        // Check if the current edge forms a cycle
        if (findParent(u, parent) != findParent(v, parent)) {
            mst.push_back(edge);
            mstWeight += edge.weight;
            unionSets(u, v, parent, rank);
        }
    }

    // Print the MST
    cout << "Edge \tWeight" << endl;
    for (auto& edge : mst) {
        cout << edge.src << " - " << edge.dest << "\t" << edge.weight << endl;
    }
    cout << "Total Weight of MST: " << mstWeight << endl;
}

int main() {
    int V = 5;  // Number of vertices
    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 3, 8}, {1, 4, 5},
        {1, 2, 3}, {2, 4, 7}, {3, 4, 9}
    };

    kruskalAlgorithm(edges, V);

    return 0;
}

