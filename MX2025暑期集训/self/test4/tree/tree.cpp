#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100;

int n, w[N];

int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

int f[N];
void DP(int x, int l) {
    f[x] = w[x];
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        DP(j, x);
        if(f[j] > 0) f[x] += f[j];
    }
}

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &w[i]);
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        add(a, b);
    }
    DP(1, 0);
    int ans = 0;
    for(int i = 1; i <= n; i++) ans = max(ans, f[i]);
    printf("%lld", ans);
}