#include <bits/stdc++.h>
using namespace std;

const int N = 500100;

int n, k, ans;
int A[N], pre[N], suf[N];

int main() {
    freopen("music.in", "r", stdin);
    freopen("music.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    sort(A + 1, A + n + 1);
    for(int i = 1, l = 1; i <= n; i++) {
        while(l < i && A[i] - A[l] > k) l++;
        pre[i] = max(pre[i - 1], i - l + 1);
    }
    for(int i = n, r = n; i; i--) {
        while(r > i && A[r] - A[i] > k) r--;
        suf[i] = max(suf[i + 1], r - i + 1);
    }
    for(int l = 1, r = 1; r <= n; r++) {
        while(l < r && A[r] - A[l] > k) l++;
        ans = max(ans, r - l + 1 + max(pre[l - 1], suf[r + 1]));
    }
    printf("%d", ans);
    return 0;
}