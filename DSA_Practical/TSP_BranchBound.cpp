#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to find the minimum cost edge from a given city
int findMinEdge(const vector<vector<int>> &cost, int city, vector<bool> &visited) {
    int minCost = INT_MAX;
    for (int i = 0; i < cost.size(); i++) {
        if (!visited[i] && cost[city][i] != 0) {
            minCost = min(minCost, cost[city][i]);
        }
    }
    return (minCost == INT_MAX) ? 0 : minCost;
}

// Calculate the lower bound for the given path
int calculateBound(const vector<vector<int>> &cost, vector<bool> &visited, int currentCost) {
    int bound = currentCost;
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i]) {
            bound += findMinEdge(cost, i, visited);
        }
    }
    return bound;
}

// Recursive function to solve TSP using Branch and Bound
void tspBranchAndBound(const vector<vector<int>> &cost, vector<bool> &visited, vector<int> &path, vector<int> &bestPath,
                       int currentCost, int &minCost, int level, int currentCity) {
    int n = cost.size();

    // If all cities are visited, check the total cost
    if (level == n) {
        if (cost[currentCity][path[0]] != 0) { // Add cost of returning to the starting city
            int totalCost = currentCost + cost[currentCity][path[0]];
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = path;
            }
        }
        return;
    }

    // Explore all possible paths
    for (int nextCity = 0; nextCity < n; nextCity++) {
        if (!visited[nextCity] && cost[currentCity][nextCity] != 0) {
            int tempCost = currentCost + cost[currentCity][nextCity];
            visited[nextCity] = true;
            path[level] = nextCity;

            // Calculate bound for the next level
            int bound = calculateBound(cost, visited, tempCost);
            if (bound < minCost) { // Only proceed if bound is promising
                tspBranchAndBound(cost, visited, path, bestPath, tempCost, minCost, level + 1, nextCity);
            }

            // Backtrack
            visited[nextCity] = false;
        }
    }
}

int main() {
    // Cost matrix representing the graph
    vector<vector<int>> cost = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int n = cost.size();
    vector<int> path(n);    // Stores the current path
    vector<int> bestPath;   // Stores the best path
    vector<bool> visited(n, false);
    int minCost = INT_MAX;

    // Start with the first city
    path[0] = 0;
    visited[0] = true;

    tspBranchAndBound(cost, visited, path, bestPath, 0, minCost, 1, 0);

    // Output the result
    cout << "Minimum cost: " << minCost << endl;
    cout << "Optimal path: ";
    for (int city : bestPath) {
        cout << city << " -> ";
    }
    cout << bestPath[0] << endl; // Return to the starting city

    return 0;
}
