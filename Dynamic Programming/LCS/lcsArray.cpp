#include <bits/stdc++.h>
using namespace std;

vector<int> findLCS(const vector<int>& A, const vector<int>& B) {
    int m = A.size(), n = B.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    vector<int> lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            lcs.push_back(A[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int main() {
    int n, m;
    cout << "Enter the size of the first array: ";
    cin >> n;
    vector<int> A(n);
    cout << "Enter the elements of the first array: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    cout << "Enter the size of the second array: ";
    cin >> m;
    vector<int> B(m);
    cout << "Enter the elements of the second array: ";
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }

    vector<int> lcs = findLCS(A, B);

    cout << "The Longest Common Subsequence is: ";
    for (int num : lcs) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
