#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int n, k, A[N];
int ans = 1;

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    sort(A + 1, A + n + 1);
    for(int i = n - 1; i; i--) {
        if(A[i + 1] - A[i] <= k) ans++;
        else break;
    }
    printf("%d", ans);
    return 0;
}