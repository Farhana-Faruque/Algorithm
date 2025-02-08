#include <stdio.h>
#include <limits.h>

#define INF 1505

// Define the price array (prices for rod lengths 0 to 7)
int price[] = {0, 1, 5, 8, 9, 10, 12, 17};
int revenue[1505];  // Array to store the maximum revenue for each rod length
int cut[1505];      // Array to store the first cut for each rod length

// Bottom-up dynamic programming function to calculate max revenue
int bottomUpCutRod(int price[], int n, int revenue[], int cut[]) {
    int maxRevenue;
    // Loop through all rod lengths from 1 to n
    for (int j = 1; j <= n; j++) {
        maxRevenue = -INF;
        // Try all possible first cuts
        for (int i = 1; i <= j; i++) {
            if (maxRevenue < price[i] + revenue[j - i]) {
                maxRevenue = price[i] + revenue[j - i];
                cut[j] = i;  // Store the first cut for this rod length
            }
        }
        revenue[j] = maxRevenue;  // Store the maximum revenue for rod length j
    }
    return revenue[n];  // Return the maximum revenue for the full rod
}

// Function to print the cutting lengths
void printCuts(int n, int cut[]) {
    printf("Cutting lengths: ");
    while (n > 0) {
        printf("%d ", cut[n]);  // Print the first cut
        n -= cut[n];  // Reduce the remaining rod length
    }
    printf("\n");
}

int main() {
    int n = 7;  // Length of the rod
    
    // Initialize revenue and cut arrays
    for (int i = 0; i <= n; i++) {
        revenue[i] = -INF;  // Set initial revenue to a very low number
        cut[i] = 0;  // No cuts yet
    }
    revenue[0] = 0;  // Base case: No rod, no revenue

    // Get the maximum revenue and the cutting strategy
    int maxRevenue = bottomUpCutRod(price, n, revenue, cut);

    // Print the maximum revenue
    printf("Maximum revenue for rod of size %d is: %d\n", n, maxRevenue);

    // Print the revenue array
    printf("Revenue array: ");
    for (int i = 0; i <= n; i++) {
        printf("%d ", revenue[i]);
    }
    printf("\n");

    // Print the optimal cuts
    printCuts(n, cut);

    return 0;
}
