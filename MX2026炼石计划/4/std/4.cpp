#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 9, L = 20;
int n, m, dfn[N], t, sz[N], st[L][N], d[N], dx[N], sx[N];
vector<pair<int, int>> es[N];
void dfs1(int x, int fa) {
  st[0][dfn[x] = ++t] = d[fa], sz[x] = 1, dx[x] = d[x];
  es[x].erase(remove_if(es[x].begin(), es[x].end(),
                        [fa](auto p) { return p.first == fa; }),
              es[x].end());
  for (auto [y, w] : es[x]) {
    if (y == fa) continue;
    d[y] = d[x] + w, dfs1(y, x);
    sz[x] += sz[y], dx[x] ^= dx[y];
  }
}
void dfs2(int x, int fa) {
  sx[x] = sx[fa];
  if (sz[x] & 1) sx[x] ^= d[x] ^ d[fa];
  for (auto [y, w] : es[x])
    if (y != fa) dfs2(y, x);
}
inline void init() {
  dfs1(1, 0), dfs2(1, 0);
  for (int i = 1; i < L; ++i)
    for (int j = 2; j + (1 << i) <= n + 1; ++j)
      st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
inline int dlca(int x, int y) {
  if (x == y) return d[x];
  if ((x = dfn[x]) > (y = dfn[y])) swap(x, y);
  int h = __lg((++y) - (++x));
  return min(st[h][x], st[h][y - (1 << h)]);
}
inline bool isanc(int x, int y) {
  return dfn[y] >= dfn[x] && dfn[y] < dfn[x] + sz[x];
}
inline vector<pair<int, bool>> cv(int x, int y, bool typ) {
  if (typ) return {{y, false}};
  if (x == y) return {{1, true}};
  if (!isanc(y, x)) return {{y, true}};
  int z = prev(upper_bound(es[y].begin(), es[y].end(), make_pair(x, 0),
                           [](pair<int, int> x, pair<int, int> y) {
                             return dfn[x.first] < dfn[y.first];
                           }))
              ->first;
  return {{1, true}, {z, true}};
}
inline int solve(int y, int z, bool ty, bool tz) {
  if (!ty && !tz) return dlca(y, z);
  if (!ty) swap(y, z), swap(ty, tz);
  if (!tz) {
    if (!isanc(y, z) || y == z) return (sz[y] & 1) ? dlca(y, z) : 0;
    int ans = sx[z] ^ sx[y];
    if (sz[y] & 1) ans ^= d[y];
    return ans;
  }
  if (!isanc(y, z)) swap(y, z);
  if (!isanc(y, z)) return ((sz[y] & 1) && (sz[z] & 1)) ? dlca(y, z) : 0;
  int ans = dx[z];
  if (sz[z] & 1) {
    ans ^= d[z] ^ sx[z] ^ sx[y];
    if (sz[y] & 1) ans ^= d[y];
  }
  return ans;
}
inline int solve(int x, int y, int z, bool ty, bool tz) {
  int ans = solve(y, z, ty, tz);
  if (!ty || (sz[y] & 1)) ans ^= solve(x, z, false, tz);
  if (!tz || (sz[z] & 1)) ans ^= solve(x, y, false, ty);
  return ans;
}
signed main() {
  freopen("lca.in", "r", stdin);
  freopen("lca.out", "w", stdout);
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1, u, v, w; i < n; ++i) {
    cin >> u >> v >> w;
    es[u].emplace_back(v, w);
    es[v].emplace_back(u, w);
  }
  init();
  for (int x, y, z, typ; m; --m) {
    cin >> x >> y >> z >> typ;
    vector<pair<int, bool>> a = cv(x, y, typ > 2), b = cv(x, z, ~typ & 1);
    int ans = 0;
    for (auto [y, ty] : a)
      for (auto [z, tz] : b) ans ^= solve(x, y, z, ty, tz);
    cout << ans << '\n';
  }
  return cout << flush, 0;
}