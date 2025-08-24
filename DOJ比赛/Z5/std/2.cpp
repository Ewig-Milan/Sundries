#include <bits/stdc++.h>
#define int long long
#define Lb(x) (x & (-x))
using namespace std;

const int N = 200100, mod = 1e9 + 7;

int quick_p(int x, int a) {
    int res = 1;
    while(a) {
        if(a & 1) res *= x, res %= mod;
        x *= x, x %= mod;
        a >>= 1;
    }
    return res;
}

int n, ans;

int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

struct Bit_T {
    int sum[N];
    void modify(int x, int delta) {while(x <= n) sum[x] += delta, x += Lb(x);}
    int query(int x) {
        int res = 0;
        while(x) res += sum[x], x -= Lb(x);
        return res;
    }
}t;

void DP(int x, int l) {
    t.modify(x, 1);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        ans += t.query(j) - 1;
        DP(j, x);
    }
    t.modify(x, -1);
}

signed main() {
    freopen("dfs.in", "r", stdin);
    freopen("dfs.out", "w", stdout);
    memset(h, -1, sizeof h);
    scanf("%lld", &n);
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        add(a, b);
    }
    DP(1, 0);
    printf("%lld", quick_p(2, ans));
    return 0;
}