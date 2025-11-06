#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 510, mod = 1e9 + 7;

int quick_p(ll x, int a) {
    ll res = 1;
    while(a) {
        if(a & 1) res *= x, res %= mod;
        a >>= 1, x *= x, x %= mod;
    }
    return (int)res;
}

int n;

int d[N];
int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
    d[a]++, d[b]++;
}

ll f[N][2][2], g[N];

void get_g(int x, int l, int k) {
    memset(g, 0, sizeof g);
    g[0] = 1;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        for(int u = k; u; u--) {
            g[u] *= f[j][0][1], g[u] %= mod;
            g[u] += g[u - 1] * f[j][1][1] % mod, g[u] %= mod;
        }
        g[0] *= f[j][0][1], g[0] %= mod;
    }
}

void DP(int x, int l, int k) {
    f[x][0][1] = f[x][1][0] = 1, f[x][1][1] = 0;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        DP(j, x, k);
        f[x][0][1] *= (f[j][0][1] + f[j][1][0] + f[j][1][1]) % mod;
        f[x][0][1] %= mod;
    }
    get_g(x, l, k);
    f[x][1][0] = g[k];
    if(k > 0) for(int i = 0; i < k; i++) f[x][1][1] += g[i];
    f[x][1][1] %= mod;
}

int work(int k) {
    DP(1, 0, k);
    return (f[1][0][1] + f[1][1][0] + f[1][1][1]) % mod;
}

int main() {

    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);

    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b);
    }
    int ma_d = 0;
    for(int i = 1; i <= n; i++) ma_d = max(ma_d, d[i]);
    for(int k = 0; k <= ma_d; k++) printf("%d ", work(k));
    for(int k = ma_d + 1; k < n; k++) printf("%d ", quick_p(2, n));
    return 0;
}