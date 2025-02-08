#include <bits/stdc++.h>
using namespace std;

// this works like a two d array
vector<vector<int>> dp;

int combination(int n, int r) {
    if (r == 0 || r == n) return 1;
    if (dp[n][r] != -1) return dp[n][r]; // Returns the stored result if already computed
    return dp[n][r] = combination(n - 1, r - 1) + combination(n - 1, r);
}

int main() {
    int n, r;
    cout << "Enter n and r: ";
    cin >> n >> r;
    dp.assign(n + 1, vector<int>(r + 1, -1));
    int ans = combination(n, r);
    cout << n << "C" << r << " = " << ans;
    return 0;
}
