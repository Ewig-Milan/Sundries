#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 200100;

int n;
int col[N];
int ans;

int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

int siz[N], cut[N]/*下标是颜色*/;
void DP(int x, int l) {
    siz[x] = 1;
    int tmp = cut[col[x]];
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        int pre = cut[col[x]];
        DP(j, x);
        siz[x] += siz[j];
        int connect = siz[j] - cut[col[x]] + pre;
        ans -= connect * (connect - 1) / 2;
    }
    cut[col[x]] = tmp + siz[x];
}

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &col[i]);
    ans = n * (n - 1) / 2 * n;
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        add(a, b);
    }
    DP(1, 0);
    for(int i = 1; i <= n; i++) {
        int connect = siz[1] - cut[i];
        ans -= connect * (connect - 1) / 2;
    }
    printf("%lld", ans);
    return 0;
}