#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 400100, mod = 998244353;

int n, m, H;

struct Edge {
    int a, b, c;
    friend bool operator < (const Edge &a, const Edge &b) {return a.c < b.c;}
}E[N];

int pidx, w[N];

int h[N], e[N], ne[N], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

int fa[N], rep[N];
int find(int x) {
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
void merge(int a, int b, int c) {
    a = find(a), b = find(b);
    if(a == b) return;
    fa[a] = b, w[++pidx] = c;
    add(pidx, rep[a]), add(pidx, rep[b]);
    rep[b] = pidx;
}

int f[N];
void DP(int x, int l) {
    for(int i = h[x]; ~i; i = ne[i]) {
        if(!f[x]) f[x] = 1;
        int j = e[i];
        DP(j, x);
        f[x] *= f[j], f[x] %= mod;
    }
    f[x] += w[l] - w[x], f[x] %= mod;
}

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld%lld%lld", &n, &m, &H);
    for(int i = 1; i <= m; i++) scanf("%lld%lld%lld", &E[i].a, &E[i].b, &E[i].c);
    sort(E + 1, E + m + 1);
    for(int i = 1; i <= n; i++) fa[i] = i, rep[i] = ++pidx, w[pidx] = -1;
    for(int i = 1; i <= m; i++) merge(E[i].a, E[i].b, E[i].c);
    w[0] = H;
    DP(pidx, 0);
    printf("%lld", f[pidx]);
    return 0;
}