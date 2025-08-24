#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 5100, INF = 1e9;

int n, k;
ll res, f[N], g[N];

struct Node {int l, r;} d[N];

bool cmp1(Node a, Node b) {return a.r - a.l > b.r - b.l;}

void solve1() {
    sort(d + 1, d + 1 + n, cmp1);
    ll ans = 0;
    for (int i = 1; i < k; i++) ans += d[i].r - d[i].l;
    int ma = -INF, mi = INF;
    for (int i = k; i <= n; i++) ma = max(ma, d[i].l), mi = min(mi, d[i].r);
    ans += max(0, mi - ma);
    res = max(res, ans);
}

bool cmp2(Node a, Node b) {return (a.l == b.l) ? (a.r > b.r) : (a.l < b.l);}

void solve2() {
    int m = 0;
    sort(d + 1, d + 1 + n, cmp2);
    vector<ll> le;
    le.push_back(0);
    for (int i = 1; i <= n; d[++m] = d[i], i++)
    while (m && d[m].r >= d[i].r) {
        le.push_back(d[m].r - d[m].l);
        m--;
    }
    
    sort(le.begin(), le.end());
    reverse(le.begin() + 1, le.end());
    while (le.size() <= k) le.push_back(0);

    for (int i = 1; i < le.size(); i++) le[i] += le[i - 1];
    for (int i = 1; i <= m; i++) f[i] = -INF;
    f[0] = 0;
    for (int T = 1; T <= min(m, k); T++) {
        for (int i = 0; i <= m; i++) g[i] = -INF;
        for (int i = 1; i <= m; i++) f[i - 1] += d[i].r;
        deque<int> q;
        for (int i = 1; i <= m; i++) {
            while (!q.empty() && d[q.front() + 1].r <= d[i].l) q.pop_front();
            while (!q.empty() && f[q.back()] < f[i - 1]) q.pop_back();
            q.push_back(i - 1);
            g[i] = f[q.front()] - d[i].l;
        }
        res = max(res, g[m] + le[k - T]);
        for (int i = 0; i <= m; i++) f[i] = g[i];
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d%d", &d[i].l, &d[i].r);

    solve1(), solve2();
    printf("%lld\n", res);
    return 0;
}