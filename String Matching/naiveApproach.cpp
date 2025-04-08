#include <iostream>
#include <string>
using namespace std;

// Naïve String Matching Algorithm
void naiveStringMatcher(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    for (int s = 0; s <= n - m; s++) {  // Possible shifts
        int j;
        for (j = 0; j < m; j++) {
            if (text[s + j] != pattern[j])
                break;
        }
        if (j == m)  // If full pattern matched
            cout << "Pattern occurs with shift " << s << endl;
    }
}

int main() {
    string text = "abcaabaabcab";
    string pattern = "aabc";
    
    naiveStringMatcher(text, pattern);
    
    return 0;
}
