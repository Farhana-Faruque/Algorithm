#include <bits/stdc++.h>
using namespace std;

void maxSumInterval(const vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n);           
    vector<int> previous(n, -1); 

    dp[0] = nums[0];
    int maxSum = dp[0];
    int maxIndex = 0; 

    for (int i = 1; i < n; i++) {
        if (dp[i - 1] + nums[i] > nums[i]) {
            dp[i] = dp[i - 1] + nums[i];
            previous[i] = i - 1; 
        } else {
            dp[i] = nums[i];
            previous[i] = -1;
        }

        if (dp[i] > maxSum) {
            maxSum = dp[i];
            maxIndex = i; 
        }
    }

    vector<int> result;
    int currentIndex = maxIndex;
    while (currentIndex != -1) {
        result.push_back(nums[currentIndex]);
        currentIndex = previous[currentIndex];
    }

    reverse(result.begin(), result.end()); 

    cout << "Maximum sum: " << maxSum << endl;
    cout << "Maximum sum interval: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {2, -5, 9, -3, 1, 7, -15, 2, 3};
    maxSumInterval(nums);
    return 0;
}
