#include <bits/stdc++.h>
using namespace std;

#define inf 1505

vector<int> price = {0, 1, 5, 8, 9, 10, 12, 17};
vector<int> revenue; 

int memoizedCutRod(vector<int> price, int n, vector<int>& revenue) {
    if (revenue[n] >= 0) return revenue[n];
    if (n == 0) return 0; 

    int maxRevenue = -inf;
    for (int i = 1; i <= n; i++) {
        maxRevenue = max(maxRevenue, price[i] + memoizedCutRod(price, n - i, revenue));
    }
    revenue[n] = maxRevenue;
    return maxRevenue;
}

int main() {
    int n = 7;
    revenue = vector<int>(n + 1, -inf); 
    revenue[0] = 0; 

    cout << "Maximum revenue for rod of size 7 is: " << memoizedCutRod(price, n, revenue) << endl;
}
