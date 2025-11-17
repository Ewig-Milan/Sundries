#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#define ll long long
using namespace std;

const int N = 5100, mod = 1e9 + 7;

int n, k;
int f[N][2][N];
int ans;

int main() {
    FILE("sequence");
    scanf("%d%d", &n, &k);
    f[2][0][2] = f[2][1][2] = 1;
    for(int len = 2; len <= n; len++) {
        for(int i = len; i <= n; i++) {
            f[len + 1][0][i + 1] += f[len][0][i], f[len + 1][0][i + 1] %= mod;
            f[len + 1][1][i + len] += f[len][0][i], f[len + 1][1][i + len] %= mod;
            f[len + 1][1][i + 1] += f[len][1][i], f[len + 1][1][i + 1] %= mod;
            f[len + 1][0][i + len] += f[len][1][i], f[len + 1][0][i + len] %= mod;
        }
        for(int i = len + 1; i <= n; i++) {
            f[len + 1][0][i] += f[len + 1][0][i - 2], f[len + 1][0][i] %= mod;
            f[len + 1][1][i] += f[len + 1][1][i - 2], f[len + 1][1][i] %= mod;
        }
    }
    for(int len = 2; len <= k; len++) for(int i = len; i <= n; i++) {
        ans += ((ll)f[len][0][i] + f[len][1][i]) % mod * (k - len + 1) % mod;
        ans %= mod;
    }
    printf("%d", ans);
    return 0;
}