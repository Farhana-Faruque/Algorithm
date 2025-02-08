#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void editDistance(const char* X, const char* Y) {
    int m = strlen(X), n = strlen(Y);
    
    // Create a 2D array to store the dynamic programming table
    int dp[m + 1][n + 1];
    
    // Initialize the base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    // Fill the dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j - 1] < dp[i - 1][j] ? (dp[i - 1][j - 1] < dp[i][j - 1] ? dp[i - 1][j - 1] : dp[i][j - 1]) : (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]));
            }
        }
    }

    // Print the edit distance
    printf("Edit distance: %d\n", dp[m][n]);

    // Trace back to find the operations
    printf("Steps to convert:\n");
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && X[i - 1] == Y[j - 1]) {
            i--;
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            printf("Replace '%c' with '%c'\n", X[i - 1], Y[j - 1]);
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            printf("Delete '%c'\n", X[i - 1]);
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            printf("Insert '%c'\n", Y[j - 1]);
            j--;
        }
    }
}

int main() {
    char X[100], Y[100];
    
    // Input strings
    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);

    // Call the function to calculate and display edit distance and operations
    editDistance(X, Y);

    return 0;
}
