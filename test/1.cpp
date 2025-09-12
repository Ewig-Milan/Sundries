#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1100, mod = 998244353;

int T, nothing;

int n, m, C, F;
bool mp[N][N]; // 1 种不了
int righ[N][N], down[N][N];
int f[N][N], Vc, Vf;

signed main() {
    scanf("%lld%lld", &T, &nothing);
    while(T--) {
        memset(mp, 0, sizeof mp);
        memset(righ, 0, sizeof righ);
        memset(down, 0, sizeof down);
        memset(f, 0, sizeof f);
        Vc = Vf = 0;
        
        scanf("%lld%lld%lld%lld", &n, &m, &C, &F);
        for(int i = 1; i <= n; i++) {
            char s[N]; scanf("%s", s + 1);
            for(int j = 1; j <= m; j++) mp[i][j] = s[j] - '0';
            for(int j = m, cont = 0; j; j--) {
                if(mp[i][j]) cont = 0;
                else cont++;
                righ[i][j] = max(cont - 1, 0ll);
            }
        }
        for(int j = 1; j <= m; j++)
        for(int i = n, cont = 0; i; i--) {
            if(mp[i][j]) cont = 0;
            else cont++;
            down[i][j] = max(cont - 1, 0ll);
        }
        for(int i = 3; i <= n; i++) {
            for(int j = 1; j < m; j++) {
                if(mp[i][j] || mp[i - 1][j] || mp[i - 2][j]) {f[i][j] = 0; continue;}
                f[i][j] = f[i - 1][j] + righ[i - 2][j];
                Vc += f[i][j] * righ[i][j] % mod, Vc %= mod;
                Vf += f[i][j] * righ[i][j] % mod * down[i][j] % mod, Vf %= mod;
            }
        }
        printf("%lld %lld\n", Vc * C % mod, Vf * F % mod);
    }
    return 0;
}