#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void printOptimalParenthesis(const vector<vector<int>> &s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int lookupChain(const vector<int> &p, int i, int j, vector<vector<int>> &m, vector<vector<int>> &s) {
    if (m[i][j] < INT_MAX) 
        return m[i][j]; 

    if (i == j) 
        return m[i][j] = 0; 

    for (int k = i; k < j; ++k) {
        int cost = lookupChain(p, i, k, m, s) +
                   lookupChain(p, k + 1, j, m, s) +
                   p[i - 1] * p[k] * p[j];

        if (cost < m[i][j]) {
            m[i][j] = cost;
            s[i][j] = k; 
        }
    }

    return m[i][j];
}

int memoizedMatrixChain(const vector<int> &p, vector<vector<int>> &s) {
    int n = p.size();
    vector<vector<int>> m(n, vector<int>(n, INT_MAX));

    lookupChain(p, 1, n - 1, m, s); 
    return m[1][n - 1]; 
}

int main() {
    vector<int> dimensions = {10, 5, 1, 10, 2, 10}; 

    int n = dimensions.size();
    vector<vector<int>> s(n, vector<int>(n, 0)); 

    int minCost = memoizedMatrixChain(dimensions, s);

    cout << "Minimum number of scalar multiplications: " << minCost << endl;
    cout << "Optimal parenthesization: ";
    printOptimalParenthesis(s, 1, n - 1); 
    cout << endl;

    return 0;
}
