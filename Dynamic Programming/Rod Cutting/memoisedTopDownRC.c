#include <stdio.h>

#define INF 1505

// Define the price array (prices for rod lengths 0 to 7)
int price[] = {0, 1, 5, 8, 9, 10, 12, 17};
int revenue[1505];  // Array to store the maximum revenue for each rod length

// Memoized cutRod function
int memoizedCutRod(int price[], int n) {
    // If the value has been computed, return it
    if (revenue[n] >= 0) return revenue[n];  
    
    // Base case: If rod length is 0, no revenue
    if (n == 0) return 0;  

    int maxRevenue = -INF;  // Initialize the max revenue to a very low number
    
    // Try all possible cuts and calculate the max revenue
    for (int i = 1; i <= n; i++) {
        int currentRevenue = price[i] + memoizedCutRod(price, n - i);
        if (currentRevenue > maxRevenue) {
            maxRevenue = currentRevenue;
        }
    }
    
    revenue[n] = maxRevenue;  // Store the result in the revenue array
    return maxRevenue;
}

int main() {
    int n = 7;  // The length of the rod
    
    // Initialize the revenue array with a default value (-INF) for all rod lengths
    for (int i = 0; i <= n; i++) {
        revenue[i] = -INF;  
    }
    
    // The base case: no rod, no revenue
    revenue[0] = 0;

    // Call the memoized cutRod function and print the result
    printf("Maximum revenue for rod of size %d is: %d\n", n, memoizedCutRod(price, n));
    
    return 0;
}
