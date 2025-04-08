#include <iostream>
#include <vector>
using namespace std;

// Compute Prefix Function (Pi Table)
vector<int> computePrefixFunction(string pattern) {
    int m = pattern.length();
    vector<int> pi(m, 0);
    int k = 0;  // Length of previous longest prefix suffix

    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[k] != pattern[q])
            k = pi[k - 1];

        if (pattern[k] == pattern[q])
            k++;

        pi[q] = k;
    }
    return pi;
}

// KMP Pattern Matching Algorithm
void KMPMatcher(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> pi = computePrefixFunction(pattern);

    int q = 0;  // Number of characters matched
    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i])
            q = pi[q - 1];

        if (pattern[q] == text[i])
            q++;

        if (q == m) {
            cout << "Pattern occurs with shift " << i - m + 1 << endl;
            q = pi[q - 1];  // Continue searching
        }
    }
}

int main() {
    string text = "abacaabababaca";
    string pattern = "ababaca";

    KMPMatcher(text, pattern);
    
    return 0;
}
