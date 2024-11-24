#include <iostream>
#include <algorithm> // For max function
using namespace std;

void knapsack(int P[], int wt[], int m, int n) {
    int k[n + 1][m + 1];

    // Building the knapsack table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= m; w++) {
            if (i == 0 || w == 0) {
                k[i][w] = 0;
            } else if (wt[i] <= w) {
                k[i][w] = max(P[i] + k[i - 1][w - wt[i]], k[i - 1][w]);
            } else {
                k[i][w] = k[i - 1][w];
            }
        }
    }

    // Output the maximum profit
    cout << "Maximum profit is " << k[n][m] << endl;

    // Finding the items included in the knapsack
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (k[i][j] == k[i - 1][j]) {
            cout << "Item " << i << " = 0" << endl; // Item not included
            i--;
        } else {
            cout << "Item " << i << " = 1" << endl; // Item included
            j = j - wt[i];
            i--;
        }
    }
}

int main() {
    // Arrays for profits and weights
    int P[5] = {0, 1, 2, 5, 6}; // Profit values (0-index not used)
    int wt[5] = {0, 2, 3, 4, 5}; // Weight values (0-index not used)
    int maxp = 8; // Maximum weight of the knapsack
    int n = 4;    // Number of items

    // Call the knapsack function
    knapsack(P, wt, maxp, n);

    return 0;
}
