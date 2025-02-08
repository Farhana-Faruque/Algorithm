#include <bits/stdc++.h>    
using namespace std;

int combination(int n, int r) {
    if(r == 1) return n;
    if(r == n or r == 0) return 1;
    return combination(n-1, r-1) + combination(n-1, r);
}

int main() {
    int n, r;
    cout << "Enter n and r: ";
    cin >> n >> r;
    int ans = combination(n,r);
    cout << n << "C" << r << " = " << ans;
}