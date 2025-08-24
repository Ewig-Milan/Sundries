#include <bits/stdc++.h>
using namespace std;

const int N = 3100, mod = 1e9 + 7;

int n, m, k, ans;

char c[N][N];
int f[N][N], g[N][N];
int sum1[N][N], sum2[N][N];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++) scanf("%s", c[i] + 1);

    for(int i = 1; i <= m; i++) {
        f[1][i] = 1;
        g[1][i] = (i != 1 && c[1][i] == c[1][i - 1]);
        sum1[1][i] = sum1[1][i - 1] + f[1][i];
        sum2[1][i] = sum2[1][i - 1] + g[1][i];
    }

    for(int i = 2; i <= n; i++) for(int j = 1; j <= m; j++) {
        if (j == 1 || c[i][j] != c[i][j - 1]) g[i][j] = 0;
        else g[i][j] = ((sum1[i - 1][min(m, j + k - 1)] - sum1[i - 1][max(0, j - k - 1)]) % mod + mod) % mod
            - ((sum2[i - 1][min(m, j + k - 1)] - sum2[i - 1][max(0, j - k)]) % mod + mod) % mod;
            
        f[i][j] = ((sum1[i - 1][min(m, j + k)] - sum1[i - 1][max(0, j - k - 1)]) % mod + mod) % mod
            - ((sum2[i - 1][min(m, j + k)] - sum2[i - 1][max(0, j - k)]) % mod + mod) % mod;
        if (g[i][j] < 0) g[i][j] += mod;
        if (f[i][j] < 0) f[i][j] += mod;
        sum1[i][j] = (sum1[i][j - 1] + f[i][j]) % mod;
        sum2[i][j] = (sum2[i][j - 1] + g[i][j]) % mod;
    }
    ans = 0;
    for(int i = 1; i <= m; i++) ans = ((ans + (f[n][i] - g[n][i]) % mod) % mod + mod) % mod;
    printf("%d\n", ans);
    return 0;
}