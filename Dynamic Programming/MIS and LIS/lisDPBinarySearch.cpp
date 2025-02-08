#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void LIS_Binary_DP(const vector<int>& nums) {
    int n = nums.size();
    vector<int> dp;          
    vector<int> indices(n);  
    vector<int> previous(n, -1); 

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), nums[i]);
        int pos = it - dp.begin();

        if (it == dp.end()) {
            dp.push_back(nums[i]);
        } else {
            *it = nums[i];
        }

        indices[pos] = i; 
        if (pos > 0) {
            previous[i] = indices[pos - 1]; 
        }
    }

    vector<int> lis;
    for (int i = indices[dp.size() - 1]; i != -1; i = previous[i]) {
        lis.push_back(nums[i]);
    }
    reverse(lis.begin(), lis.end());

    cout << "Length of LIS: " << dp.size() << endl;
    cout << "LIS: ";
    for (int num : lis) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {9, 2, 5, 3, 7, 11, 8, 10, 13, 6};
    LIS_Binary_DP(nums);
    return 0;
}
