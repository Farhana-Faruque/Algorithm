#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            }
        }
    }

    int w = W;
    cout << "Items selected: ";
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << i << " ";
            w -= weights[i - 1];
        }
    }
    cout << endl;

    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> values(n), weights(n);
    cout << "Enter the values and weights of the items:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> values[i] >> weights[i];
    }

    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    int maxProfit = knapsack(W, weights, values, n);
    cout << "Maximum profit: " << maxProfit << endl;

    return 0;
}
