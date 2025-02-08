#include <stdio.h>

typedef long long ll;

// Recursive function to calculate nth Fibonacci number
ll nthFibonacci(ll n) {
    if (n <= 1) return n;
    return nthFibonacci(n - 1) + nthFibonacci(n - 2);
}

int main() {
    ll n;
    printf("Enter n to see nth fibonacci number (0 indexing): ");
    scanf("%lld", &n);

    ll ans = nthFibonacci(n);
    printf("The %lldth fibonacci number is: %lld\n", n, ans);

    return 0;
}
