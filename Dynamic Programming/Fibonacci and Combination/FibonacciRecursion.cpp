#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll nthFibonacci(ll n) {
    if(n <= 1) return n;
    return nthFibonacci(n-1) + nthFibonacci(n-2);
}

int main() {
    cout << "Enter n to see nth fibonacci number(0 indexing) : ";
    ll n;
    cin >> n;
    ll ans = nthFibonacci(n);
    cout << "The " << n << "th fibonacci number is: " << ans << endl;

    return 0;

}