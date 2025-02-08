#include <stdio.h>

void maxSumInterval(const int nums[], int n) {
    int dp[n];           // Array to store the maximum sum up to index i
    int previous[n];     // Array to store the index of the previous element in the optimal subarray

    // Initialize the first element
    dp[0] = nums[0];
    previous[0] = -1;  // No previous element for the first element

    int maxSum = dp[0];  // The maximum sum found so far
    int maxIndex = 0;    // Index where the maximum sum ends

    // Loop through the array to compute the maximum sum and track the subarray
    for (int i = 1; i < n; i++) {
        if (dp[i - 1] + nums[i] > nums[i]) {
            dp[i] = dp[i - 1] + nums[i];  // Extend the previous subarray
            previous[i] = i - 1;  // Link to the previous element
        } else {
            dp[i] = nums[i];  // Start a new subarray from the current element
            previous[i] = -1;  // No previous element for the new subarray
        }

        // Update the maximum sum and its index
        if (dp[i] > maxSum) {
            maxSum = dp[i];
            maxIndex = i;
        }
    }

    // Reconstruct the subarray by following the previous indices
    int result[100];  // Temporary array to store the subarray
    int length = 0;
    int currentIndex = maxIndex;
    while (currentIndex != -1) {
        result[length++] = nums[currentIndex];  // Store the element in the result array
        currentIndex = previous[currentIndex];  // Move to the previous index
    }

    // Print the maximum sum
    printf("Maximum sum: %d\n", maxSum);
    printf("Maximum sum interval: ");
    
    // Print the subarray in reverse order
    for (int i = length - 1; i >= 0; i--) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int nums[] = {2, -5, 9, -3, 1, 7, -15, 2, 3};  // Example input
    int n = sizeof(nums) / sizeof(nums[0]);  // Calculate the size of the array
    
    maxSumInterval(nums, n);  // Call the function to calculate and print the results
    
    return 0;
}
