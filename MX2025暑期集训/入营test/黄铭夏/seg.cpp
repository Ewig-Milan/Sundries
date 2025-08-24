#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100, M = 101, mod = 1e9 + 7;

struct Ques {
    int id, l, r, x, bl;
    friend bool operator < (const Ques &a, const Ques &b) {
        return a.bl == b.bl ? a.r < b.r : a.bl < b.bl;
    }
};
vector<Ques> Q;

int n, m, q;
int w[N], f[M], tmp[M];
int ans[N];
int ga;

int work(int l, int r, int x) {
    memcpy(tmp, f, sizeof f);
    for(int i = l; i <= r; i++)
    for(int j = m; j >= w[i]; j--) tmp[j] += tmp[j - w[i]], tmp[j] %= mod;
    return tmp[x];
}

signed main() {
    freopen("seg.in", "r", stdin);
    freopen("seg.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &q);
    memset(f, 0, sizeof f), f[0] = 1;
    ga = sqrt(n);
    for(int i = 1; i <= n; i++) scanf("%lld", &w[i]);

    for(int i = 1; i <= q; i++) {
        int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        if(b - a + 1 <= ga) ans[i] = work(a, b, c);
        else Q.push_back({i, a, b, c, a / ga});
    }

    sort(Q.begin(), Q.end());
    for(int i = 0, r; i < Q.size(); i++) {
        if(!i || Q[i].bl != Q[i - 1].bl)
            memset(f, 0, sizeof f), f[0] = 1, r = ga * (Q[i].bl + 1);
        while(r <= Q[i].r) {
            for(int j = m; j >= w[r]; j--) f[j] += f[j - w[r]], f[j] %= mod;
            r++;
        }
        ans[Q[i].id] = work(Q[i].l, ga * (Q[i].bl + 1) - 1, Q[i].x);
    }
    for(int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
    return 0;
}