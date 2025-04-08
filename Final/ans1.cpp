#include <bits/stdc++.h>
using namespace std;

void findPath(vector<vector<int>>& table) {
    int m = table.size();
    int n = table[0].size();
    vector<vector<int>> dp(m, vector<int>(n));

    dp[0][0] = table[0][0];

    for(int j = 1; j < n; j++) 
        dp[0][j] = dp[0][j-1] + table[0][j];

    for(int i = 1; i < m; i++) 
        dp[i][0] = dp[i-1][0] + table[i][0];
    
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + table[i][j];
        }
    }
    
    cout << "Minimum cost: " << dp[m-1][n-1] << endl;
    cout << "Path: ";
    int i = m-1, j = n-1;
    vector<pair<int,int>> path;
    
    while(i >= 0 && j >= 0) {
        path.push_back({i, j});
        if(i == 0 && j == 0) break;
        if(i == 0) j--;
        else if(j == 0) i--;
        else {
            if(dp[i-1][j] < dp[i][j-1]) i--;
            else j--;
        }
    }
    
    for(int k = path.size()-1; k >= 0; k--)
        cout << "(" << path[k].first << "," << path[k].second << ") ";
    cout << endl;
}

int main() {
    vector<vector<int>> table = {
        {5, 7, 9},
        {8, 12, 20}
    };
    
    int m = table.size();
    int n = table[0].size();
    
    findPath(table);
    return 0;
} 
