#include <bits/stdc++.h>
using namespace std;

typedef long long ll; 

vector<ll> F;

ll fibonacci(ll n) {
    if (F[n] != -1) return F[n];
    if (n <= 1) {
        F[n] = n;
        return F[n];
    }
    F[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return F[n];
}

int main() {
    ll n;
    cout << "Enter n to see nth fibonacci number(0 indexing) : ";
    cin >> n;

    F.resize(n + 1, -1);
    cout << "The " << n << "th fibonacci number is: " << fibonacci(n) << endl;
    
    return 0;
}
