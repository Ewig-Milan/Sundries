#include <bits/stdc++.h>

using namespace std;

#define pb push_back

typedef long long ll;
typedef vector<int> vi;

const int N = 3e5 + 5;

int n, k;
ll a[N];
vi g[N];
ll ans;
struct Z {
    int o, p1, p2, lim;
    ll v;
    inline friend bool operator < (Z x, Z y) {
        return x.v < y.v;
    }
};
priority_queue<Z> q[N];

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        g[x].pb(y), g[y].pb(x);
    }
    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end(), [&](int x, int y) {
            return a[x] > a[y];
        });
        int len = g[i].size();
        if (len < 3) continue;
        ll sum = a[i] + a[g[i][0]] + a[g[i][1]];
        for (int j = 2; j < len; j++) {
            sum += a[g[i][j]];
            q[i].push(Z{i, j - 1, j, len, sum});
        }
        if (!q[i].empty()) q[0].push(q[i].top());
    }
    while (k--) {
        assert(!q[0].empty());
        auto now = q[0].top();
        q[0].pop();
        ans ^= abs(now.v);
        int i = now.o;
        now = q[i].top();
        q[i].pop();
        if (now.p2 + 1 < now.lim) {
            q[i].push(Z{i, now.p1, now.p2 + 1, now.lim, now.v + a[g[i][now.p2+1]] - a[g[i][now.p2]]});
        }
        if (now.p1 >= 0 && now.p1 + 1 < now.p2) {
            q[i].push(Z{i, now.p1 - 1, now.p1 + 1, now.p2, now.v + a[g[i][now.p1+1]] - a[g[i][now.p1]]});
        }
        if (!q[i].empty()) q[0].push(q[i].top());
    }
    printf("%lld\n", ans);
    return 0;
}