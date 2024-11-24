#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if nums can be reduced to a zero array with the given queries
bool canConvertToZeroArray(const vector<int>& nums, const vector<vector<int>>& queries, vector<bool>& removed) {
    int n = nums.size();
    vector<int> delta(n + 1, 0); // Difference array to simulate decrements
    
    // Apply all non-removed queries
    for (int i = 0; i < queries.size(); ++i) {
        if (!removed[i]) {
            int l = queries[i][0], r = queries[i][1];
            delta[l] -= 1;          // Decrement starts at index l
            if (r + 1 < n) delta[r + 1] += 1; // Stop decrement at index r + 1
        }
    }
    
    // Simulate the effect of decrements on nums
    vector<int> temp(nums);
    int current = 0; // Tracks the cumulative effect
    for (int i = 0; i < n; ++i) {
        current += delta[i];
        temp[i] += current;
        if (temp[i] < 0) return false; // Negative values are invalid
    }
    
    return all_of(temp.begin(), temp.end(), [](int x) { return x == 0; }); // Check for zero array
}

// Function to find the maximum number of removable queries
int maxRemovableQueries(vector<int>& nums, vector<vector<int>>& queries) {
    int m = queries.size();
    vector<bool> removed(m, false); // Track which queries are removed
    int removable = 0; // Number of removable queries
    
    // Try removing queries one by one
    for (int i = 0; i < m; ++i) {
        removed[i] = true; // Tentatively remove the query
        if (!canConvertToZeroArray(nums, queries, removed)) {
            removed[i] = false; // Revert if nums can't be reduced to zero
        } else {
            removable++;
        }
    }
    
    // Check if it's possible to convert nums to a zero array
    if (!canConvertToZeroArray(nums, queries, removed)) return -1;
    return removable;
}

int main() {
    vector<int> nums1 = {2, 0, 2};
    vector<vector<int>> queries1 = {{0, 2}, {0, 2}, {1, 1}};
    cout << maxRemovableQueries(nums1, queries1) << endl; // Expected Output: 1
    
    vector<int> nums2 = {1, 1, 1, 1};
    vector<vector<int>> queries2 = {{1, 3}, {0, 2}, {1, 3}, {1, 2}};
    cout << maxRemovableQueries(nums2, queries2) << endl; // Expected Output: 2
    
    vector<int> nums3 = {1, 2, 3, 4};
    vector<vector<int>> queries3 = {{0, 3}};
    cout << maxRemovableQueries(nums3, queries3) << endl; // Expected Output: -1
    
    return 0;
}
