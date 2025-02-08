#include <stdio.h>

int combination(int n, int r) {
    if (r == 1) return n;
    if (r == n || r == 0) return 1;
    return combination(n - 1, r - 1) + combination(n - 1, r);
}

int main() {
    int n, r;
    printf("Enter n and r: ");
    scanf("%d %d", &n, &r);
    int ans = combination(n, r);
    printf("%dC%d = %d\n", n, r, ans);
    return 0;
}
