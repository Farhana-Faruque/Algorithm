#include <iostream>

using namespace std;

int climbs(int n){
    if(n == 1){
        return 1;
    }
    else if(n == 2){
        return 2;
    }
    else{
        int dp[n+1];
        dp[1] = 1;
        dp[2] = 2;

        for(int i = 3; i <= n; i++){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
}

int main() {
    int n;
    cout << "The number of stairs : ";
    cin >>n;
    if(n < 1 || n > 45){
        return 1;
    }
    else{
        cout << "The distinct ways to reach is " << climbs(n) << endl;
    }

    return 0;
}
