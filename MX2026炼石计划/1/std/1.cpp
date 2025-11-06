#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1000100;

int n, v[N], sum[N];

signed main() {

	freopen("universe.in", "r", stdin);
	freopen("universe.out", "w", stdout);
	
	int nothing; scanf("%lld", &nothing);
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &v[i]);
	sort(v + 1, v + n + 1);
	v[n + 1] = 1e18;
	for(int i = 1; i <= n + 1; i++) sum[i] = sum[i - 1] + v[i];
	for(int k = 1, le = 1; k < n; k++) {
		while(le < n && sum[le] + k * (v[le + 1] - 1) >= le * v[le + 1]) le++;
		printf("%lld ", (sum[le] - le) / (le - k));
	}
	return 0;
}