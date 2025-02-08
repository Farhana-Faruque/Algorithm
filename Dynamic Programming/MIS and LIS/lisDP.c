#include <stdio.h>

void LIS_Optimized_DP(const int nums[], int n) {
    int dp[n];            // Array to store the length of LIS ending at each index
    int previous[n];      // Array to store the previous element index in LIS

    // Initialize the dp array to 1 (every element is an LIS of length 1 at least)
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        previous[i] = -1;  // No previous element initially
    }

    int maxLength = 1, maxIndex = 0;

    // Compute the LIS using dynamic programming
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                previous[i] = j;
            }
        }
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            maxIndex = i; 
        }
    }

    // Reconstruct the LIS from the previous array
    int lis[maxLength];  // Array to store the LIS
    int idx = maxIndex;
    int lisLength = maxLength - 1;
    
    while (idx != -1) {
        lis[lisLength--] = nums[idx];
        idx = previous[idx];
    }

    // Print the result
    printf("Length of LIS: %d\n", maxLength);
    printf("LIS: ");
    for (int i = 0; i < maxLength; i++) {
        printf("%d ", lis[i]);
    }
    printf("\n");
}

int main() {
    int nums[] = {9, 2, 5, 3, 7, 11, 8, 10, 13, 6};  // Example input
    int n = sizeof(nums) / sizeof(nums[0]);  // Size of the array
    
    LIS_Optimized_DP(nums, n);  // Call the LIS function
    
    return 0;
}
