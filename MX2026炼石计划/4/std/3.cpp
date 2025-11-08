#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int kN = 1e5 + 5;
const LL Mod = LL(1e18) + 3;

int n, m, k; 
int u[kN], v[kN], ans[kN];
vector<pair<int, int>> e[kN];
vector<pair<int, int>> qry[kN];
int col[kN], siz[kN], cnt[kN]; 
LL f[kN];

void dfs (int u, int r, int c) {
  col[u] = c;
  ++siz[c];
  cnt[u] = 1;
  for (auto i : e[u]) {
    int v = i.first;
    if (v == r) continue;
    dfs(v, u, c);
    cnt[u] += cnt[v];
  }
} 

void add (int x) {
  for (int i = (n >> 1); i >= x; --i) {
    f[i] = (f[i] + f[i - x]) % Mod;
  }
}

void del (int x) {
  for (int i = x; i <= (n >> 1); ++i) {
    f[i] = (f[i] - f[i - x] + Mod) % Mod; 
  }
}

void fakemain () {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    cin >> u[i] >> v[i];
    e[u[i]].emplace_back(v[i], i);
    e[v[i]].emplace_back(u[i], i);
  }
  for (int i = 1; i <= n; ++i) {
    if (!col[i]) dfs(i, 0, ++k);
  }
  for (int i = 1; i <= m; ++i) {
    qry[col[u[i]]].emplace_back(min(cnt[u[i]], cnt[v[i]]), i);
  }
  f[0] = 1;
  for (int i = 1; i <= k; ++i) {
    add(siz[i]);
  }
  for (int i = 1; i <= k; ++i) {
    del(siz[i]);
    for (auto j : qry[i]) {
      ans[j.second] = j.first<=(n>>1)&&(f[(n >> 1) - j.first] != 0);
    }
    add(siz[i]);
  }
  for (int i = 1; i <= m; ++i) {
    cout << (ans[i] ? "Yes" : "No") << '\n';
  }
}

int main () {
  cin.tie(0)->sync_with_stdio(0);
  fakemain();
  return 0; 
}
