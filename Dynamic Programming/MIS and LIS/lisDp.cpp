#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void LIS_Optimized_DP(const vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);        
    vector<int> previous(n, -1); 

    int maxLength = 1, maxIndex = 0;

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

    vector<int> lis;
    for (int i = maxIndex; i != -1; i = previous[i]) {
        lis.push_back(nums[i]);
    }
    reverse(lis.begin(), lis.end());

    cout << "Length of LIS: " << maxLength << endl;
    cout << "LIS: ";
    for (int num : lis) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {9, 2, 5, 3, 7, 11, 8, 10, 13, 6};
    LIS_Optimized_DP(nums);
    return 0;
}
