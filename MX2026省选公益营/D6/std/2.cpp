#include <stdio.h>

const int N = 2e5 + 7, M = 1e4, K = 5e3 + 1, mod = 998244353;
int a[N], b[N], inv[M + 7], c[K + 7][K + 7], c_[K + 7][K + 7], power[M + 7], val[M + 7], ans[K + 7][K + 7];

inline void init(){
	inv[0] = inv[1] = 1;
	for (register int i = 2; i <= M; i++){
		inv[i] = mod - 1ll * (mod / i) * inv[mod % i] % mod;
	}
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int quick_pow(int x, int p){
	int ans = 1;
	while (p){
		if (p & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline int sub(int x, int y){
	return x - y < 0 ? x - y + mod : x - y;
}

int main(){
	freopen("nonsense.in","r",stdin);
	freopen("nonsense.out","w",stdout);
	int n, x, y, q;
	init();
	scanf("%d %d %d %d", &n, &q, &x, &y);
	int maxa = 0, maxb = 0, maxab, sum;
	for (register int i = 1; i <= q; i++){
		scanf("%d %d", &a[i], &b[i]);
		maxa = max(maxa, a[i]);
		maxb = max(maxb, b[i]);
	}
	maxab = max(maxa, maxb);
	sum = maxa + maxb;
	for (register int i = 0; i <= maxab; i++){
		c[i][0] = 1;
		for (register int j = 1; j <= maxab; j++){
			c[i][j] = 1ll * c[i][j - 1] * (n - i - j + 1) % mod * inv[j] % mod;
		}
	}
	for (register int i = 0; i <= maxab; i++){
		for (register int j = 0; j <= i; j++){
			c_[i][j] = c[i - j][j];
		}
	}
	if (x == 0){
		power[sum] = quick_pow(y, n - sum);
		for (register int i = sum - 1; i >= 0; i--){
			power[i] = 1ll * power[i + 1] * y % mod;
		}
		for (register int i = 0; i <= maxa; i++){
			for (register int j = 0; j <= maxb; j++){
				ans[i][j] = 1ll * c[i][j] * power[i + j] % mod;
			}
		}
	} else if (y == 0){
		power[sum] = quick_pow(x, n - sum);
		for (register int i = sum - 1; i >= 0; i--){
			power[i] = 1ll * power[i + 1] * x % mod;
		}
		for (register int i = 0; i <= maxa; i++){
			for (register int j = 0; j <= maxb; j++){
				ans[i][j] = 1ll * c[j][i] * power[i + j] % mod;
			}
		}
	} else {
		if (x == y){
			int sum_i = sum + 1;
			val[0] = 1;
			for (register int i = 1; i <= sum_i; i++){
				val[i] = 1ll * val[i - 1] * (n - i + 2) % mod * inv[i] % mod;
			}
			power[sum] = quick_pow(x, n - sum);
			for (register int i = sum - 1; i >= 0; i--){
				power[i] = 1ll * power[i + 1] * x % mod;
			}
			for (register int i = 0; i <= maxa; i++){
				for (register int j = 0; j <= maxb; j++){
					ans[i][j] = 1ll * val[i + j + 1] * power[i + j] % mod;
				}
			}
		} else {
			int p = 1ll * x * quick_pow(y, mod - 2) % mod, invpd = quick_pow(p - 1, mod - 2), r = quick_pow(p, mod - 2), invrd = quick_pow(r - 1, mod - 2), inv_val = quick_pow(sub(y, x), mod - 2);
			if (p == 1){
				int t = 1;
				for (register int i = 0; i <= maxa; i++){
					if (i > 0) t = 1ll * t * (n - i + 1) % mod * inv[i + 1] % mod;
					ans[i][0] = 1ll * t * quick_pow(x, n - i) % mod;
				}
			} else {
				int full = quick_pow(y, n), t = 1ll * p * invpd % mod;
				power[maxa] = quick_pow(p, n - maxa);
				for (register int i = maxa - 1; i >= 0; i--){
					power[i] = 1ll * power[i + 1] * p % mod;
				}
				for (register int i = 0; i <= maxa; i++){
					int val = 1ll * (quick_pow(p, n - i + 1) - 1) * invpd % mod;
					for (register int j = 1; j <= i; j++){
						val = 1ll * (1ll * power[i - j] * c_[i][j] % mod - val + mod) * t % mod;
					}
					ans[i][0] = 1ll * val * full % mod * quick_pow(x, mod - i - 1) % mod;
				}
			}
			if (r == 1){
				int t = 1;
				for (register int i = 0; i <= maxb; i++){
					if (i > 0) t = 1ll * t * (n - i + 1) % mod * inv[i + 1] % mod;
					ans[i][0] = 1ll * t * quick_pow(y, n - i) % mod;
				}
			} else {
				int full = quick_pow(x, n), t = 1ll * r * invrd % mod;
				power[maxb] = quick_pow(r, n - maxb);
				for (register int i = maxb - 1; i >= 0; i--){
					power[i] = 1ll * power[i + 1] * r % mod;
				}
				for (register int i = 1; i <= maxb; i++){
					int val = 1ll * (quick_pow(r, n - i + 1) - 1) * invrd % mod;
					for (register int j = 1; j <= i; j++){
						val = 1ll * (1ll * power[i - j] * c_[i][j] % mod - val + mod) * t % mod;
					}
					ans[0][i] = 1ll * val * full % mod * quick_pow(y, mod - i - 1) % mod;
				}
			}
			for (register int i = 1; i <= maxa; i++){
				for (register int j = 1; j <= maxb; j++){
					ans[i][j] = 1ll * (ans[i - 1][j] - ans[i][j - 1] + mod) * inv_val % mod;
				}
			}
		}
	}
	for (register int i = 1; i <= q; i++){
		printf("%d\n", ans[a[i]][b[i]]);
	}
	return 0;
}
