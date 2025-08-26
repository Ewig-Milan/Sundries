// 这是干掉std的乱搞做法
#include <bits/stdc++.h>
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;

const int N = 2100;

int p, id2, id0, id1;
int ans[N];
PII d[N][N];
bool flag2[N];

int Map[N];

int h[N], e[N << 1], v[N << 1], ne[N << 1], dir[N << 1], idx;
void add(int a, int b, int c) {
	dir[idx] = 1, e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
	dir[idx] = 0, e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

bool vis[N];

void dfs(int x) {
	if(vis[x]) return;
	vis[x] = 1;
	for(int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if(vis[j]) continue;
		if(dir[i]) ans[j] = (ans[x] + v[i]) / 2;
		else ans[j] = 2 * ans[x] - v[i];
		dfs(j);
	}
}

namespace Guass {
	const int N = 2100;
	
	int n;
	int maap[N];
	double a[N][N];
	double ANS[N];
	
	double abss(double x) {
		if(x<0) return -x;
		return x;
	}
	void work() {
		for(int i=1;i<=n;i++){
			int r=i;
			for(int j=i+1;j<=n;j++){
				if(abss(a[r][i])<abss(a[j][i]))r=j;
			}
			if(i!=r)swap(a[i],a[r]);
			double div=a[i][i];
			for(int j=i;j<=n+1;j++)a[i][j]/=div;
			for(int j=i+1;j<=n;j++){
				div=a[j][i];
				for(int k=i;k<=n+1;k++){
					a[j][k]-=a[i][k]*div;
				}
			}
		}
		ANS[n]=a[n][n+1];
		for(int i=n-1;i>=1;i--){
			ANS[i]=a[i][n+1];
			for(int j=i+1;j<=n;j++){
				ANS[i]-=(a[i][j]*ANS[j]);
			}
		}
		for(int i=1;i<=n;i++) ans[maap[i]] = round(ANS[i]);
		return;
	}
}

int main() {
	memset(h, -1, sizeof h);
	memset(ans, -1, sizeof ans);
	scanf("%d", &p);
	for(int i = 1; i <= p; i++) {
		memset(flag2, 0, sizeof flag2);
		bool flag0 = true, flag1 = true;
		int cnt_flag2 = 0;
		
		for(int j = 1; j <= p; j++) {
			int a, b; scanf("%d%d", &a, &b);
			d[i][j] = {++a, ++b};
			flag0 &= (a == b && a == i);
			if(j > 1) flag1 &= (a == d[i][j - 1].fi);
			if(!flag2[a]) cnt_flag2++;
			flag2[a] = true;
		}
		if(flag0) ans[i] = 0, id0 = i;
		else if(flag1) ans[i] = 1, id1 = i;
		else if(cnt_flag2 == 2) ans[i] = 2, id2 = i;
	}
	
	for(int i = 1; i <= p; i++) {
		if(ans[i] != -1) continue;
		add(d[id2][i].se, i, ans[d[id2][i].fi] ? p : 0);
	}
	dfs(id0), dfs(id1), dfs(id2);
	
	int idx2 = 0;
	for(int i = 1; i <= p; i++) if(ans[i] == -1) {
		Guass::maap[++idx2] = i, Map[i] = idx2;
	}
	Guass::n = idx2;
	
	int idx3 = 0;
	for(int i = 1; i <= p; i++) {
		if(ans[i] != -1) continue;
		idx3++;
		Guass::a[idx3][Map[i]] = 2, Guass::a[idx3][Map[d[id2][i].se]] = -1;
		Guass::a[idx3][idx2 + 1] = ans[d[id2][i].fi] ? p : 0;
	}
	Guass::work();
	for(int i = 1; i <= p; i++) printf("%d ", ans[i]);
	return 0;
}