#include <stdio.h>

// Function to find the position to insert using binary search
int lower_bound(int arr[], int size, int target) {
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

void LIS_Binary_DP(const int nums[], int n) {
    int dp[n];            // Array to store the current LIS values
    int indices[n];       // To store the indices of elements in the LIS
    int previous[n];      // To store the previous element in the LIS
    
    // Initialize arrays
    for (int i = 0; i < n; i++) {
        dp[i] = 0;
        previous[i] = -1;
    }

    int length = 0;  // Length of the longest increasing subsequence found so far

    // Compute the LIS using binary search and dynamic programming
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(dp, length, nums[i]);  // Find the position of nums[i] in dp

        dp[pos] = nums[i];
        indices[pos] = i;  // Store the index of the element in nums

        if (pos > 0) {
            previous[i] = indices[pos - 1];  // Link to the previous element in LIS
        }

        if (pos == length) {
            length++;  // If we extended the LIS, increase the length
        }
    }

    // Reconstruct the LIS from the previous[] array
    int lis[length];
    int idx = indices[length - 1];
    for (int i = length - 1; i >= 0; i--) {
        lis[i] = nums[idx];
        idx = previous[idx];
    }

    // Print the result
    printf("Length of LIS: %d\n", length);
    printf("LIS: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", lis[i]);
    }
    printf("\n");
}

int main() {
    int nums[] = {9, 2, 5, 3, 7, 11, 8, 10, 13, 6};  // Example input
    int n = sizeof(nums) / sizeof(nums[0]);  // Size of the array
    
    LIS_Binary_DP(nums, n);  // Call the LIS function
    
    return 0;
}
