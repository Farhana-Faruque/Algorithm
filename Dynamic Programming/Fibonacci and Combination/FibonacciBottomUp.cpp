#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll fibonacci(ll n) {
    if(n == 0) return 0;
    if(n == 1) return 1;
    ll array[n+1];
    array[0] = 0;
    array[1] = 1;
    for(ll i = 2; i <= n; i++) {
        array[i] = array[i-1] + array[i-2];
    }
    return array[n];
}

int main() {
    cout << "Enter n to see nth fibonacci number(0 indexing) : ";
    ll n;
    cin >> n;
    cout << "The " << n << "th fibonacci number is: " << fibonacci(n) << endl;
    return 0;
}

// 100th fibonacci number is 3736710778780434371