#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 45, M = 1100000;

int n, A_n, B_n;
int A[N >> 1], B[N >> 1], a[M], b[M]; // a b 存具体值
int sa[M], sb[M]; // 存排列 存的遍历顺序 递增 
int rka[M], rkb[M]; // 存排名 下标遍历顺序
int T[10]; // 桶 计数排序用 
int idxa, idxb; // 遍历顺序（下标） 

ll ans;

void dfs_A(int dep, int sum, int k) {
	if(dep > A_n) {
		idxa++;
		T[sum / k % 10]++;
		a[idxa] = sum % (k * 10);
		return;
	}
	dfs_A(dep + 1, sum, k);
	dfs_A(dep + 1, sum + A[dep], k);
}

void dfs_B(int dep, int sum, int k) {
	if(dep > B_n) {
		idxb++;
		T[sum / k % 10]++;
		b[idxb] = sum % (k * 10);
		return;
	}
	dfs_B(dep + 1, sum, k);
	dfs_B(dep + 1, sum + B[dep], k);
}

int main() {
	scanf("%d", &n);
	A_n = (n >> 1), B_n = n - A_n;
	for(int i = 1; i <= A_n; i++) scanf("%d", &A[i]);
	for(int i = 1; i <= B_n; i++) scanf("%d", &B[i]);
	
	for(int i = 0; i < M; i++) sa[i] = sb[i] = i;
	
	for(int k = 1; k <= 100000000; k *= 10) {
		 memset(T, 0, sizeof T);
		 idxa = 0, dfs_A(1, 0, k);
		 for(int i = 1; i <= 9; i++) T[i] += T[i - 1];
		 for(int i = idxa; i; i--) rka[sa[i]] = T[a[sa[i]] / k]--;
		 for(int i = 1; i <= idxa; i++) sa[rka[i]] = i;
		 memset(T, 0, sizeof T);
		 idxb = 0, dfs_B(1, 0, k);
		 for(int i = 1; i <= 9; i++) T[i] += T[i - 1];
		 for(int i = idxb; i; i--) rkb[sb[i]] = T[b[sb[i]] / k]--;
		 for(int i = 1; i <= idxb; i++) sb[rkb[i]] = i;
		 
		 int l = idxb + 1, r = idxb + 1;
		 for(int i = 1; i <= idxa; i++) {
		 	int L = 4 * k - a[sa[i]], R = 5 * k - a[sa[i]];
		 	if(R < 0) break;
		 	while(l > 1 && b[sb[l - 1]] >= L) l--;
		 	while(r > l && b[sb[r - 1]] >= R) r--;
		 	ans += r - l;
		 }
		 l = idxb + 1, r = idxb + 1;
		 for(int i = 1; i <= idxa; i++) {
		 	int L = 14 * k - a[sa[i]], R = 15 * k - a[sa[i]];
		 	if(R < 0) break;
		 	while(l > 1 && b[sb[l - 1]] >= L) l--;
		 	while(r > l && b[sb[r - 1]] >= R) r--;
		 	ans += r - l;
		 }
	}
	printf("%lld", ans);
	return 0;
}