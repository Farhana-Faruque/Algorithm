#include <stdio.h>
#include <stdlib.h>

void findLCS(int A[], int B[], int m, int n) {
    // DP table to store lengths of longest common subsequence
    int dp[m + 1][n + 1];

    // Fill the DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;  // Base case: LCS with an empty array is 0
            } else if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    // Reconstruct the LCS from the dp table
    int lcs_length = dp[m][n];
    int *lcs = (int *)malloc(lcs_length * sizeof(int));  // Array to store LCS
    int index = lcs_length - 1;  // Index for storing LCS

    // Trace back to find the LCS
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            lcs[index] = A[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Output the result
    printf("The Longest Common Subsequence is: ");
    for (int i = 0; i < lcs_length; i++) {
        printf("%d ", lcs[i]);
    }
    printf("\n");

    free(lcs);  // Free the dynamically allocated memory for lcs
}

int main() {
    int n, m;

    // Input for the first array
    printf("Enter the size of the first array: ");
    scanf("%d", &n);
    int A[n];
    printf("Enter the elements of the first array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    // Input for the second array
    printf("Enter the size of the second array: ");
    scanf("%d", &m);
    int B[m];
    printf("Enter the elements of the second array: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &B[i]);
    }

    // Find the Longest Common Subsequence
    findLCS(A, B, n, m);

    return 0;
}
