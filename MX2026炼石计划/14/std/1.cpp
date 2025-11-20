#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#define ll long long
using namespace std;

const int N = 200100;

int n, T;

int h[N], e[N << 1], w[N << 1], v[N << 1], ne[N << 1], idx;
void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, w[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

ll sum[N];
int g[N], f[N], siz[N];

void prepare(int x, int l) {
    siz[x] = 1, g[x] = 0;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        prepare(j, x);
        siz[x] += siz[j];
        g[x] += (v[i] ? siz[j] : g[j]);
    }
}

void DP(int x, int l) {
    if(!l) f[x] = g[x];
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        int siz_ = siz[1] - siz[j], sum_ = f[x] - (v[i] ? siz[j] - g[j] : g[j]);
        f[j] = g[j] + (v[i] ? siz_ : sum_);
        DP(j, x);
    }
}

void work() {
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    for(int bit = 0; bit < 30; bit++) {
        for(int i = 0; i < idx; i++) v[i] = ((w[i] >> bit) & 1);
        prepare(1, 0), DP(1, 0);
        for(int i = 1; i <= n; i++) sum[i] += (1ll << bit) * f[i];
    }
    ll mi = 1e18;
    for(int i = 1; i <= n; i++) mi = min(mi, sum[i]);
    printf("%lld\n", mi);
}

void cl() {
    idx = 0;
    for(int i = 0; i <= n; i++) h[i] = -1, sum[i] = 0;
}

int main() {
    FILE("tree");
    memset(h, -1, sizeof h);
    scanf("%d", &T);
    while(T--) work(), cl();
    return 0;
}