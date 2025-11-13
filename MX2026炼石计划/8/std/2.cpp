#include<bits/stdc++.h>
#define ll long long
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 310, mod = 1e9 + 7;

void add(int &x, int y) {if((x += y) >= mod) x -= mod;}

int tid, T, n;
int l[N], r[N], f[2][N][N];

void work() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]);
    memset(f[0], 0, sizeof f[0]);
    f[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        memset(f[i&1], 0, sizeof f[i&1]);
        for(int j = 0; j < i; j++) for(int k = 0; k <= n; k++) {
            if(!f[i-1&1][j][k]) continue;
            if(l[i] == 0){
                add(f[i&1][j + 1][k], f[i-1&1][j][k]);
                if(k) add(f[i&1][j][k - 1], (ll)f[i-1&1][j][k] * k % mod);
            }
            if(l[i] <= 1 && r[i] >= 1) {
                add(f[i&1][j + 1][k + 1], 2ll * f[i-1&1][j][k] % mod);
                add(f[i&1][j][k], 2ll * f[i-1&1][j][k] * k % mod);
            }
            if(r[i] == 2) {
                add(f[i&1][j + 1][k + 2], f[i-1&1][j][k]);
                add(f[i&1][j][k + 1], (ll)f[i-1&1][j][k] * k % mod);
                add(f[i&1][j][k + 1], 2ll * f[i-1&1][j][k] * j % mod);
                if(j > 1) add(f[i&1][j - 1][k], 2ll * f[i-1&1][j][k] * k % mod * (j - 1) % mod);
            }
        }
    }
    printf("%d\n", f[n&1][1][0]);
}
int main(){
    FILE("tree");
    scanf("%d%d", &tid, &T);
    while(T--) work();
    return 0;
}