#include <stdio.h>
#include <string.h>

void findLCS(char X[], char Y[]) {
    int m = strlen(X), n = strlen(Y);

    // Create a 2D array to store lengths of longest common subsequence.
    int dp[m + 1][n + 1];

    // Build the dp array in bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;  // Base case: If either string is empty, LCS length is 0
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;  // Characters match, extend LCS
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];  // Take max of previous LCS lengths
            }
        }
    }

    // Reconstruct the LCS from the dp table
    int lcsLength = dp[m][n];
    char lcs[lcsLength + 1];  // Array to store the LCS
    int index = lcsLength - 1;

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index] = X[i - 1];  // If characters match, it is part of the LCS
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;  // Move up in the table
        } else {
            j--;  // Move left in the table
        }
    }

    // Null-terminate the string
    lcs[lcsLength] = '\0';

    // Print the result
    printf("The Longest Common Subsequence is: %s\n", lcs);
}

int main() {
    char X[100], Y[100];

    // Input strings
    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);

    // Call the function to find the LCS
    findLCS(X, Y);

    return 0;
}
