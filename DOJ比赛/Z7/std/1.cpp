#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5100, M = 1100000;

int n, ans;
int A[N], cnt[M];

signed main() {
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &A[i]);
	for(int i = 2; i <= n; i++) for(int j = 2; j < i; j++) cnt[A[i] ^ A[j]]++;
	
	for(int i = 2; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) cnt[A[i] ^ A[j]]--;
		for(int j = 1; j < i; j++) ans += cnt[A[i] ^ A[j]];
	}
	printf("%lld", ans);
	return 0;
}