#include <iostream>

using namespace std;

// there are four nodes in example graph (graph is 1-based)
const int n = 4;
// give appropriate maximum to avoid overflow
const int MAX = 1000000;

// dist[i][j] represents shortest distance to go from i to j
// this matrix can be calculated for any given graph using
// all-pair shortest path algorithms
int dist[n + 1][n + 1] = {
    { 0, 0, 0, 0, 0 },    { 0, 0, 10, 15, 20 },
    { 0, 10, 0, 25, 25 }, { 0, 15, 25, 0, 30 },
    { 0, 20, 25, 30, 0 },
};

// memoization for top down recursion
int memo[n + 1][1 << (n + 1)];

int fun(int i, int mask)
{
    // base case
    // if only ith bit and 1st bit is set in our mask,
    // it implies we have visited all other nodes already
    if (mask == ((1 << i) | 3))
        return dist[1][i];
    // memoization
    if (memo[i][mask] != 0)
        return memo[i][mask];

    int res = MAX; // result of this sub-problem

    // we have to travel all nodes j in mask and end the
    // path at ith node so for every node j in mask,
    // recursively calculate cost of travelling all nodes in
    // mask except i and then travel back from node j to
    // node i taking the shortest path take the minimum of
    // all possible j nodes

    for (int j = 1; j <= n; j++)
        if ((mask & (1 << j)) && j != i && j != 1)
            res = std::min(res, fun(j, mask & (~(1 << i)))
                                    + dist[j][i]);
    return memo[i][mask] = res;
}
// Driver program to test above logic
int main()
{
    int ans = MAX;
    for (int i = 1; i <= n; i++)
        // try to go from node 1 visiting all nodes in
        // between to i then return from i taking the
        // shortest route to 1
        ans = std::min(ans, fun(i, (1 << (n + 1)) - 1)
                                + dist[i][1]);

    printf("The cost of most efficient tour = %d", ans);

    return 0;
}

// Simpler CODE:
// #include <iostream>
// #include <climits> // For INT_MAX

// using namespace std;

// const int n = 4; // Number of cities
// const int INF = INT_MAX; // Large value to represent infinity

// // Distance matrix (1-based indexing)
// int dist[n + 1][n + 1] = {
//     { 0,  0,  0,  0,  0 }, 
//     { 0,  0, 10, 15, 20 }, 
//     { 0, 10,  0, 25, 25 }, 
//     { 0, 15, 25,  0, 30 }, 
//     { 0, 20, 25, 30,  0 }
// };

// // Memoization table
// int dp[16][5]; // dp[mask][currentCity]

// // Solve TSP for `currentCity` with visited cities represented by `mask`
// int tsp(int mask, int currentCity) {
//     // Base case: If all cities are visited, return distance to the starting city
//     if (mask == (1 << n) - 1)
//         return dist[currentCity][1];

//     // If already computed, return the stored value
//     if (dp[mask][currentCity] != -1)
//         return dp[mask][currentCity];

//     int minCost = INF;

//     // Try visiting all unvisited cities
//     for (int nextCity = 1; nextCity <= n; nextCity++) {
//         if (!(mask & (1 << (nextCity - 1)))) { // Check if `nextCity` is not visited
//             int newCost = dist[currentCity][nextCity] + tsp(mask | (1 << (nextCity - 1)), nextCity);
//             minCost = min(minCost, newCost);
//         }
//     }

//     // Store the result in dp table and return it
//     return dp[mask][currentCity] = minCost;
// }

// int main() {
//     // Initialize memoization table with -1
//     memset(dp, -1, sizeof(dp));

//     // Start from city 1, with only city 1 visited (mask = 1)
//     int minCost = tsp(1, 1);

//     cout << "Minimum cost of the tour = " << minCost << endl;

//     return 0;
// }
