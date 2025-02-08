#include <bits/stdc++.h>
using namespace std;

#define inf 1505

vector<int> price = {0, 1, 5, 8, 9, 10, 12, 17};
vector<int> revenue;  
vector<int> cut;      

int bottomUpCutRod(vector<int> price, int n, vector<int>& revenue, vector<int>& cut) {
    int maxRevenue;
    for (int j = 1; j <= n; j++) {
        maxRevenue = -inf;
        for (int i = 1; i <= j; i++) {
            if (maxRevenue < price[i] + revenue[j - i]) {
                maxRevenue = price[i] + revenue[j - i];
                cut[j] = i; 
            }
        }
        revenue[j] = maxRevenue;
    }
    return revenue[n];
}

void printCuts(int n, vector<int>& cut) {
    cout << "Cutting lengths: ";
    while (n > 0) {
        cout << cut[n] << " ";
        n -= cut[n]; 
    }
    cout << endl;
}

int main() {
    int n = 7;
    revenue = vector<int>(n + 1, -inf); 
    cut = vector<int>(n + 1, 0);       
    revenue[0] = 0;                    

    int maxRevenue = bottomUpCutRod(price, n, revenue, cut);

    cout << "Maximum revenue for rod of size " << n << " is: " << maxRevenue << endl;

    cout << "Revenue array: ";
    for (auto it : revenue) {
        cout << it << " ";
    }
    cout << endl;

    printCuts(n, cut);

    return 0;
}
