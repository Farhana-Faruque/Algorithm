#include <iostream>
#include <string>
#define d 256  // Number of characters in the input alphabet
#define q 101  // A prime number for modulo operation (to avoid overflow)

using namespace std;

void rabinKarp(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();
    int i, j;
    int p = 0;  // Hash value for pattern
    int t = 0;  // Hash value for text window
    int h = 1;

    // The value of h would be "pow(d, m-1) % q"
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Compute the hash values for pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // If the hash values match, then check character by character
        if (p == t) {
            bool match = true;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                cout << "Pattern found at index " << i << endl;
        }

        // Compute hash value for next window of text: Remove leading digit, add trailing digit
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            // If t is negative, make it positive
            if (t < 0)
                t += q;
        }
    }
}

int main() {
    string text = "ABCCDDAEFG";
    string pattern = "CDD";
    
    rabinKarp(text, pattern);

    return 0;
}
