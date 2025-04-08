#include <bits/stdc++.h>
using namespace std;

void minCoins(const vector<int>& coins, int target) {
    vector<int> dp(target + 1, INT_MAX);
    vector<int> lastCoin(target + 1, -1);

    dp[0] = 0;

    for (int i = 1; i <= target; ++i) {
        for (int coin : coins) {
            if (i - coin >= 0 && dp[i - coin] != INT_MAX) {
                if (dp[i] > dp[i - coin] + 1) {
                    dp[i] = dp[i - coin] + 1;
                    lastCoin[i] = coin; 
                }
            }
        }
    }

    if (dp[target] == INT_MAX) {
        cout << "It is not possible to make the target sum with the given coins." << endl;
        return;
    }

    cout << "The minimum number of coins required to make the sum " << target << " is " << dp[target] << "." << endl;

    vector<int> result;
    int current = target;
    while (current > 0) {
        result.push_back(lastCoin[current]);
        current -= lastCoin[current];
    }

    cout << "Coins used: ";
    for (int coin : result) {
        cout << coin << " ";
    }
    cout << endl;
}

int main() {
    vector<int> coins = {1, 3, 5};
    int target = 11;

    minCoins(coins, target);

    return 0;
}
