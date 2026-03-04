#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#define gc (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000001, stdin), p1 == p2) ? EOF : *p1 ++)

using std::min; using std::max;
typedef long long ll;
const ll INF = 1e18;
const int mod = 998244353;
char buf[1000001], *p1, *p2;
inline int read() {
	char ch; int x = 0; while ((ch = gc) < 48); do x = x * 10 + ch - 48; while ((ch = gc) >= 48); return x;
}
inline ll readll() {
	char ch; ll x = 0; while ((ch = gc) < 48); do x = x * 10 + ch - 48; while ((ch = gc) >= 48); return x;
}
std::vector<int> G[300005];
int ls[10000005], rs[10000005], sze[300005], top[300005], fa[300005], son[300005], dep[300005], tot, res, n, q;
int ans[300005], rt[300005],idq[300005];
ll mx[10000005], mn[10000005], tag[10000005], resval;
bool isquery[300005];
void init1(int u) {
	sze[u] = 1;
	for (int v : G[u]) if (v != fa[u]) {
		fa[v] = u, dep[v] = dep[u] + 1, init1(v), sze[u] += sze[v];
		if (sze[son[u]] < sze[v]) son[u] = v;
	}
}
void init2(int u) {
	if (son[u]) top[son[u]] = top[u], init2(son[u]);
	for (int v : G[u]) if (v != fa[u] && v != son[u]) top[v] = v, init2(v);
}
int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}
void update(int &p, int l, int r, int x, ll y) {
	if (r < x) return;
	if (!p) p = ++ tot;
	if (x <= l) {tag[p] += y, mn[p] += y, mx[p] += y; return;}
	int mid = l + r >> 1;
	update(ls[p], l, mid, x, y), update(rs[p], mid + 1, r, x, y);
	mn[p] = min(mn[ls[p]], mn[rs[p]]) + tag[p];
	mx[p] = max(mx[ls[p]], mx[rs[p]]) + tag[p];
}
void find(int p, int l, int r, int x, ll y, ll stag) {
	if (x < l || mn[p] + stag > y) return;
	if (l == r) {res = l, resval = mn[p] + stag; return;}
	int mid = l + r >> 1;
	find(rs[p], mid + 1, r, x, y, stag + tag[p]);
	if (res == -1) find(ls[p], l, mid, x, y, stag + tag[p]);
}
ll query(int &p, int l, int r, int x, int y, ll stag) {
	if (x > y) return -INF;
	if (x <= l && r <= y) return mx[p] + stag;
	int mid = l + r >> 1; ll ans = -INF;
	if (x <= mid) ans = query(ls[p], l, mid, x, y, stag + tag[p]);
	if (mid < y) ans = max(ans, query(rs[p], mid + 1, r, x, y, stag + tag[p]));
	return ans;
}
ll getval(int p, int x) {
	int l = 0, r = q; ll sum = 0;
	while (p) {
		sum += tag[p]; int mid = l + r >> 1;
		if (x <= mid) p = ls[p], r = mid;
		else l = mid + 1, p = rs[p];
	}
	return sum;
}
void merge(int &u, int v) {
	if (!u || !v) {u |= v; return;}
	merge(ls[u], ls[v]), merge(rs[u], rs[v]);
	tag[u] += tag[v];
	mn[u] = min(mn[ls[u]], mn[rs[u]]) + tag[u];
	mx[u] = max(mx[ls[u]], mx[rs[u]]) + tag[u];
}
std::vector<std::pair<ll, int> > oper[300005], qry[300005];
inline ll calc(ll n) {n = (n % mod + mod) % mod; return (n * (n + 1) >> 1) % mod;}
void dfs(int u) {
	for (int v : G[u]) if (v != fa[u]) dfs(v), merge(rt[u], rt[v]);
	for (auto i : oper[u]) update(rt[u], 0, q, i.second, i.first);
	for (auto i : qry[u]) {
		int tme = i.second;
		ll base = getval(rt[u], tme) - i.first;
		res = -1, find(rt[u], 0, q, tme, base, 0ll); int A = res;
		if (A == -1) {ans[tme] = -1; continue;}
		if (resval < base) {
			if (res < tme) ans[tme] = (query(rt[u], 0, q, res + 1, tme, 0ll) - base + mod) % mod;
			else ans[tme] = -1;
			continue;
		}
		ll rmax = query(rt[u], 0, q, res, tme, 0ll);
		res = -1, find(rt[u], 0, q, A - 1, base - 1, 0ll); int B = res;
		if (B == -1) {
			ll down = max(0ll, rmax - base);
			ans[tme] = (calc(INF) - calc(down - 1) + mod) % mod;
		} else {
			ll lmax = query(rt[u], 0, q, B, A, 0ll);
			if (lmax <= rmax) ans[tme] = (rmax - base) % mod;
			else ans[tme] = (calc(lmax - base) - calc(rmax - base - 1) + mod) % mod;
		}
	}
}

int main() {
	freopen("candy.in","r",stdin);
	freopen("candy.out","w",stdout); 
	n = read(), q = read();
	for (int i = 1, u, v; i < n; ++ i) u = read(), v = read(), G[u].emplace_back(v), G[v].emplace_back(u);
	init1(1), top[1] = 1, init2(1);
	for (int i = 1,j=0; i <= q; ++ i) {
		int op = read(), a = read();
		if (op != 3) {
			int b = read(), lca = LCA(a, b), x = read();
			if (op == 2) x = -x;
			oper[a].emplace_back(std::make_pair(x, i));
			oper[b].emplace_back(std::make_pair(x, i));
			oper[lca].emplace_back(std::make_pair(-x, i));
			oper[fa[lca]].emplace_back(std::make_pair(-x, i));
		} else {isquery[i] = true; ll y = readll(); qry[a].emplace_back(std::make_pair(y, i));idq[i]=++j;}
	}
	dfs(1);
	for (int i = 1; i <= q; ++ i) if (isquery[i]) printf("%d\n", ans[i]);
	return 0;
}
