#include <bits/stdc++.h>
using namespace std;
#define inf 10000000

int findIndex(vector<int> value) {
    int max = -inf, maxIndex;
    for (int i = 0; i < 5; i++) {
        if(value[i] > max) {
            max = value[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

int main() { 
    vector<int> weight = {4, 8, 2, 6, 1};
    vector<int> benefit = {12, 32, 40, 30, 50};
    vector<int> value;
    int maxweight = 10;
    for (int i = 0; i < 5; i++) {
        value.push_back(benefit[i] / weight[i]);
    }
    int profit = 0;
    int w = 0;
    while (w < maxweight) {
        int index = findIndex(value);
        if (weight[index] > (maxweight - w)) {
            weight[index] = maxweight - w;
            profit += value[index]*(maxweight - w);
            w = maxweight;
        }
        else {
            w += weight[index];
            profit += weight[index] * value[index];
            value[index] = -1;
        }
    }
    cout << profit << endl;
} 