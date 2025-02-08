#include <bits/stdc++.h>
using namespace std;

vector<string> editDistance(const string& X, const string& Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
            }
        }
    }

    vector<string> operations;
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && X[i - 1] == Y[j - 1]) {
            i--;
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            operations.push_back("Replace '" + string(1, X[i - 1]) + "' with '" + string(1, Y[j - 1]) + "'");
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            operations.push_back("Delete '" + string(1, X[i - 1]) + "'");
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            operations.push_back("Insert '" + string(1, Y[j - 1]) + "'");
            j--;
        }
    }

    cout << "Edit distance: " << dp[m][n] << "\n";
    cout << "Steps to convert:\n";

    return operations;
}

int main() {
    string X, Y;
    cout << "Enter first string: ";
    cin >> X;
    cout << "Enter second string: ";
    cin >> Y;

    vector<string> operations = editDistance(X, Y);
    for (int k = operations.size() - 1; k >= 0; k--) {
        cout << operations[k] << "\n";
    }
    return 0;
}
