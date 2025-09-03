#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2100, mod = 998244353;

int n;
int f[N][N << 1];
int ans;

int inv[N << 1];
void get_inv() {
    inv[1] = inv[0] = 1;
    for(int i = 2; i <= 4100; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

signed main() {
    get_inv();
    scanf("%lld", &n);
    f[0][0] = 1;
    for(int i = 0; i <= n; i++)
    for(int j = 0; j <= (i << 1); j++) {
        if(i < n) f[i + 1][j] += (n - i) * inv[n + i - j] % mod * f[i][j] % mod, f[i + 1][j] %= mod;
        if(j < (i << 1) && i < n) f[i][j + 1] += ((i << 1) - j) * inv[n + i - j] % mod * f[i][j] % mod, f[i][j + 1] %= mod;
    }
    for(int i = 0; i <= (n << 1); i++) ans += f[n][i] * (n + i) % mod, ans %= mod;
    printf("%lld", ans);
    return 0;
}