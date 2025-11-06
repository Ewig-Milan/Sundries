#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool Mbe;
constexpr int N = 1e5 + 10, M = 52;
int n, m;
char mp[N][M];

struct node
{
    int sz; ll ans;
    array<int, M> arr;
};
struct dsu
{
    int n;
    vector<int> fa;
    dsu(int _n) : n(_n) { fa.resize(n + 1), iota(fa.begin(), fa.end(), 0); }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    bool unite(int x, int y)
    {
        if ((x = find(x)) == (y = find(y))) return false;
        if (x > y) swap(x, y);
        return fa[y] = x, true;
    }
    bool unite(int x, int y, bool &res)
    {
        if ((x = find(x)) == (y = find(y))) return false;
        if (x > y) swap(x, y);
        if (x <= m && y <= m)
            return fa[y] = x, res = true, false;
        
        return fa[y] = x, true;
    }
};
array<int, M> getdsu(dsu &d)
{
    array<int, M> res;
    for (int i = 1; i <= m; ++i) res[i] = d.find(i);
    return res;
}
ll solve(int l, int r)
{
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    dsu dl(m * (mid - l + 1)), dr(m * (r - mid + 1));
    for (int i = 2; i <= m; ++i)
        if (mp[mid][i] == '1' && mp[mid][i - 1] == '1')
            dl.unite(i - 1, i), dr.unite(i - 1, i);

    vector<node> vl, vr;
    vl.push_back({1, 0, getdsu(dl)});
    vr.push_back({1, 0, getdsu(dr)});
    for (int i = mid - 1, cnt = 0; i >= l; --i)
    {
        bool chg = false;
        for (int j = 1; j <= m; ++j)
        {
            if (mp[i][j] == '0') continue;
            int cur = m * (mid - i) + j;
            ++cnt;
            if (mp[i + 1][j] == '1')
                cnt -= dl.unite(cur - m, cur, chg);
            if (mp[i][j - 1] == '1')
                cnt -= dl.unite(cur - 1, cur, chg);
        }
        if (chg) vl.push_back({1, cnt, getdsu(dl)});
        else ++vl.back().sz, vl.back().ans += cnt;
    }
    for (int i = mid + 1, cnt = 0; i <= r; ++i)
    {
        bool chg = false;
        for (int j = 1; j <= m; ++j)
        {
            if (mp[i][j] == '0') continue;
            int cur = m * (i - mid) + j;
            ++cnt;
            if (mp[i - 1][j] == '1')
                cnt -= dr.unite(cur - m, cur, chg);
            if (mp[i][j - 1] == '1')
                cnt -= dr.unite(cur - 1, cur, chg);
        }
        if (chg) vr.push_back({1, cnt, getdsu(dr)});
        else ++vr.back().sz, vr.back().ans += cnt;
    }
    ll ans = 0;
    for (auto &nl : vl) for (auto &nr : vr)
    {
        int cnt = 0;
        dsu dm(m);
        for (int i = 1; i <= m; ++i)
            dm.unite(i, nl.arr[i]), dm.unite(i, nr.arr[i]);

        for (int i = 1; i <= m; ++i)
            if (mp[mid][i] == '1' && dm.find(i) == i) ++cnt;

        ans += nl.sz * nr.ans + nl.ans * nr.sz + 1ll * cnt * nl.sz * nr.sz;
    }
    return ans + solve(l, mid - 1) + solve(mid + 1, r);
}
bool Med;
int main()
{

    freopen("connect.in", "r", stdin);
    freopen("connect.out", "w", stdout);
    
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> (mp[i] + 1);
    cout << solve(1, n) << '\n';
    return 0;
}