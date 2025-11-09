#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e7 + 9;
int n, hd[1 << 24], nxt[N];
bool del[N];
int lst, mn, ans;
unsigned seed;
unsigned rnd() {
  seed ^= seed << 13, seed ^= seed >> 17, seed ^= seed << 5;
  return (seed ^ ans) & 0xffffff;
}
bool isem(int x) {
  while (hd[x] && del[hd[x]]) hd[x] = nxt[hd[x]];
  return !hd[x];
}
void updatelst() {
  while (isem(lst)) ++lst;
}
void erase(int x) {
  if (del[x]) return;
  del[x] = true;
  if (updatelst(); isem(mn)) mn = lst;
}
void updatemn(int x) {
  int p = hd[mn];
  hd[mn] = nxt[hd[mn]];
  if (updatelst(); x < lst)
    mn = x;
  else
    nxt[p] = hd[x], mn = lst;
  hd[x] = p;
}
signed main() {
  freopen("heap.in", "r", stdin);
  freopen("heap.out", "w", stdout);
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> seed;
  for (int i = 1; i <= n; ++i) {
    int x = rnd();
    nxt[i] = hd[x], hd[x] = i;
  }
  updatelst(), mn = lst;
  for (int i = 1; i < n; ++i) switch (rnd() % 3) {
      case 0:
        ans ^= mn;
        break;
      case 1:
        updatemn(rnd());
        break;
      case 2:
        erase(rnd() % n + 1);
        break;
    }
  return cout << ans << endl, 0;
}