#include <bits/stdc++.h>
using namespace std;

vector<int> price = {0, 1, 5, 8, 9, 10, 12, 17};

int cutRod(vector<int> price, int n) {
    if(n == 0) return 0;
    int maxRevenue = -1;
    for(int i = 1; i<=n; i++) {
        maxRevenue = max(maxRevenue, price[i] + cutRod(price, n-i));
    }
    return maxRevenue;
}

int main() {
    int n;
    n = 7;
    cout << "Maximum revenue for rod of size 7 is: " << cutRod(price, n) << endl;
}