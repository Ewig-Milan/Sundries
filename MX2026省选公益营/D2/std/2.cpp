#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()
const int N = 50, K = 10, mod = 1e9 + 7;
ll qpow(ll x ,ll y = mod - 2, ll ans = 1){
	for (; y; (x *= x) %= mod, y >>= 1)
		if (y & 1)
			(ans *= x) %= mod;
	return ans;
}
int T, n, m, k, a[N][N];
struct Pair{
	int k, b;
	Pair() = default;
	Pair(int x, int y) : k(x), b(y) {}
};
Pair operator - (const Pair &a, const Pair &b) {
	return Pair((a.k - b.k + mod) % mod, (a.b - b.b + mod) % mod);
}
Pair operator * (const Pair &a, const Pair &b) {
	return Pair((1ll * a.k * b.b + 1ll * a.b * b.k) % mod, 1ll* a.b * b.b % mod);
}
bool cmp(const Pair &a, const Pair &b) {
	if(a.b != b.b)
		return a.b > b.b;
	else
		return a.k > b.k;
}
Pair det(Pair a[][N]) {
	Pair ans(0, 1);
	for (int i = 0; i < n; i ++) {
		int x = i;
		for (int j = i + 1; j < n; j ++) {
			if (cmp(a[j][i], a[x][i]))
				x = j;
		}
		if (x != i){
			swap(a[x], a[i]);
			ans.b = mod - ans.b;
		}
		if (a[i][i].b) {
			ll iv = qpow(a[i][i].b);
			for (int j = i + 1; j < n; j ++) {
				ll x = (mod - a[j][i].b) * iv % mod;
				ll y = (mod - a[j][i].k + a[j][i].b * iv % mod * a[i][i].k) % mod * iv % mod;
				for (int k = i; k < n; k ++) {
					a[j][k].b = (a[j][k].b + x * a[i][k].b) % mod;
					a[j][k].k = (a[j][k].k + x * a[i][k].k + y * a[i][k].b) % mod;
				}
			}
		} else if (a[i][i].k) {
			ll iv = qpow(a[i][i].k);
			for (int j = i + 1; j < n; j ++) {
				ll x = (mod - a[j][i].k) * iv % mod;
				for (int k = i; k < n; k ++) {
					a[j][k].b = (a[j][k].b + x * a[i][k].b) % mod;
					a[j][k].k = (a[j][k].k + x * a[i][k].k) % mod;
				}
			}
		} else return Pair(0, 0);
	}
	for (int i = 0; i < n; i ++)
		ans = ans * a[i][i];
	return ans;
}
int sample_int(int l, int r) {
	static mt19937 rnd(20260205);
	return uniform_int_distribution<int>(l, r)(rnd);
}
int w[N][N];
Pair f[1 << K];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			a[i][j] = -1;
			w[i][j] = sample_int(0, mod - 1);
		}
	}
	for (int u, v, c; m--; ) {
		scanf("%d%d%d", &u, &v, &c);
		a[--u][--v] = --c;
	}
	for (int S = 0; S < (1 << k); S ++) {
		static Pair s[N][N];
		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < n; j ++) {
				s[i][j] = Pair(0, 0);
				if (a[i][j] == -1)
					continue;
				if (S >> a[i][j] & 1)
					(s[i][j].b += w[i][j]) %= mod;
				if (S >> (a[i][j] + 1) % k & 1)
					(s[i][j].k += w[i][j]) %= mod;
				if (S >> (a[i][j] + k - 1) % k & 1)
					(s[i][j].k += w[i][j]) %= mod;
			}
		}
		f[S] = det(s);
	}
	for (int len = 1; len < (1 << k); len <<= 1) {
		for (int i = 0; i < (1 << k); i += len << 1) {
			for (int j = i; j < i + len; j ++) {
				f[j | len] = f[j | len] - f[j];
			}
		}
	}
	for (int S = 0; S < (1 << k); S ++) {
		putchar('0' + (f[S].k || f[S].b));
	}
	puts("");
}