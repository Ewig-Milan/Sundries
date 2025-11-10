#include<bits/stdc++.h>
#define FILE(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout);
#define int long long
using namespace std;

const int N = 2000100, mod = 998244353;

int get_inv(int x) {
    int a = mod - 2, res = 1;
    while(a) {
        if(a & 1) res *= x, res %= mod;
        x *= x, x %= mod, a >>= 1;
    }
    return res;
}

int n, m, T;
int f[N], g[N];

int fac[N], inv[N];
void prepare() {
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % mod;
    inv[N - 1] = get_inv(fac[N - 1]);
    for(int i = N - 1; i; i--) inv[i - 1] = inv[i] * i % mod;
}
int C(int n, int m) {
    if(n < m || m < 0) return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

signed main() {
    FILE("aman");
    prepare();
    scanf("%lld", &T);
    while(T--) {
        scanf("%lld%lld", &n, &m);
        if(n == 1) {printf("%lld\n", m * (m + 3) / 2 % mod); continue;}
        int ans = 0;
        for(int i = 1; i <= m + n; i++) {
            f[i] = (f[i - 1] + C(i - 1, n - 2)) % mod;
            g[i] = (g[i - 1] + C(i - 1, n - 2) * i * 2) % mod;
        }
        for(int i = n + 1; i <= n + m; i++)
            ans = (ans + (f[i / 2] * i - g[i / 2] + mod) % mod * get_inv(C(i - 1, n - 1))) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}