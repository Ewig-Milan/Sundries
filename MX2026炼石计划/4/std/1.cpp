#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e6 + 9, M = 1 << 20;
int n, m, a[N], s[N], v[M], lb[N], rb[N];
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = n; i; --i) s[i] = s[i + 1] ^ a[i];
  for (int i = 1; i <= n; ++i) {
    int& j = lb[i] = i - 1;
    while (j && a[j] <= a[i]) j = lb[j];
  }
  for (int i = n; i; --i) {
    int& j = rb[i] = i + 1;
    while (j <= n && a[j] < a[i]) j = rb[j];
  }
  for (int i = 1; i <= n; ++i) {
    int l = lb[i], r = rb[i];
    if (i - l <= r - i)
      for (int j = max(l, i - a[i]) + 1; j <= min(i, r - a[i]); ++j)
        ++v[s[j] ^ s[j + a[i]]];
    else
      for (int j = min(r, i + a[i]); j > max(i, l + a[i]); --j)
        ++v[s[j] ^ s[j - a[i]]];
  }
  partial_sum(v, v + M, v);
  for (int x; m; --m) cin >> x, cout << v[x] << '\n';
  return cout << flush, 0;
}
