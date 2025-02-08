#include <stdio.h>

int cutRod(int price[], int n) {
    // Base case
    if (n == 0) return 0;

    int maxRevenue = -1;

    // Try all possible lengths for the first cut
    for (int i = 1; i <= n; i++) {
        int revenue = price[i] + cutRod(price, n - i);
        if (revenue > maxRevenue) {
            maxRevenue = revenue;
        }
    }

    return maxRevenue;
}

int main() {
    int price[] = {0, 1, 5, 8, 9, 10, 12, 17}; // Prices for lengths 0 to 7
    int n = 7;  // Length of the rod
    printf("Maximum revenue for rod of size %d is: %d\n", n, cutRod(price, n));
    return 0;
}
