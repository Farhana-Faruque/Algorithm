#include <stdio.h>

typedef long long ll;

ll F[1000]; // Adjust size based on the maximum 'n' you expect

ll fibonacci(ll n) {
    if (F[n] != -1) return F[n];  // If the value is already computed, return it
    if (n <= 1) {
        F[n] = n;
        return F[n];
    }
    F[n] = fibonacci(n - 1) + fibonacci(n - 2);  // Recursive call
    return F[n];
}

int main() {
    ll n;
    printf("Enter n to see nth fibonacci number (0 indexing): ");
    scanf("%lld", &n);

    // Initialize all Fibonacci numbers to -1 (indicating uncomputed values)
    for (ll i = 0; i <= n; i++) {
        F[i] = -1;
    }

    printf("The %lldth Fibonacci number is: %lld\n", n, fibonacci(n));
    
    return 0;
}
