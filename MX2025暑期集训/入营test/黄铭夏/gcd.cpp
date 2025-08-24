#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int gcd(int a, int b) {
    if(!b) return a;
    return gcd(b, a % b);
}

int n, q;
int g[N][18];

int get_gcd(int l, int r) {
    int res = 0;
    for(int i = 17; i >= 0; i--)
        if(l + (1 << i) - 1 <= r) res = gcd(g[l][i], res), l += (1 << i);
    return res;
}

int main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &g[i][0]);
    for(int i = 1; i < 18; i++) 
    for(int j = 1; j <= n; j++)
        g[j][i] = gcd(g[j][i - 1], g[j + (1 << (i - 1))][i - 1]);
    while(q--) {
        int l, r; scanf("%d%d", &l, &r);
        int ans = 0, all_g = get_gcd(l, r);
        for(int x = l; x <= r; x++) {
            int tmp = 0;
            for(int i = 17; i >= 0; i--)
                if(gcd(g[x][i], tmp) > all_g && x + (1 << i) - 1 <= r)
                    tmp = gcd(g[x][i], tmp), x += (1 << i);
            if(x <= r) ans++;
        }
        printf("%d\n", r - l + 1 - ans);
    }
    return 0;
}