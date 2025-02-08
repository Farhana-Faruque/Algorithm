#include <stdio.h>

#define MAX 1000  // Define a maximum size for n

// 2D array to store previously computed combinations
int dp[MAX][MAX];

// Initialize the dp array with -1, indicating the value has not been computed yet
void initialize_dp(int n) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
}

// Function to compute the combination C(n, r) using memoization
int combination(int n, int r) {
    // Base cases
    if (r == 0 || r == n) return 1;

    // Return the stored result if already computed
    if (dp[n][r] != -1) return dp[n][r];

    // Compute the combination recursively and store the result
    dp[n][r] = combination(n - 1, r - 1) + combination(n - 1, r);
    return dp[n][r];
}

int main() {
    int n, r;

    // Prompt user for input
    printf("Enter n and r: ");
    scanf("%d %d", &n, &r);

    // Initialize the dp array
    initialize_dp(n);

    // Calculate the combination using the memoized function
    int ans = combination(n, r);

    // Display the result
    printf("%dC%d = %d\n", n, r, ans);

    return 0;
}
