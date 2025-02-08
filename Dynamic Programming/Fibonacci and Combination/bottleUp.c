#include <stdio.h>

typedef long long ll;

// Function to compute the nth Fibonacci number iteratively
ll fibonacci(ll n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    ll a = 0, b = 1;  // Initialize the first two Fibonacci numbers
    ll result;

    // Compute Fibonacci numbers iteratively
    for (ll i = 2; i <= n; i++) {
        result = a + b;  // F(i) = F(i-1) + F(i-2)
        a = b;  // Update the previous Fibonacci number
        b = result;  // Update the current Fibonacci number
    }

    return result;  // Return the nth Fibonacci number
}

int main() {
    ll n;
    printf("Enter n to see nth Fibonacci number (0 indexing): ");
    scanf("%lld", &n);

    printf("The %lldth Fibonacci number is: %lld\n", n, fibonacci(n));

    return 0;
}
