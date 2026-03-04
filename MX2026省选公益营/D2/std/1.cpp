#include<bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include"debug.h"
#else
#define debug(...) void()
#endif
#define all(x) (x).begin(),(x).end()
template<class T>
auto ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
using ll=long long;
using ull=unsigned long long;
const int N=5e2+10,M=1e6+10;
int n,q;
char a[N][N];
int s[N][N];
void solve(int k){
	if(k<0){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]^=1;
			}
		}
		solve(-k);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]^=1;
			}
		}
		return;
	}
	for(int i=0;i<=n+1;i++){
		fill(s[i],s[i]+1+n+1,0);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]!='0')continue;
			int lx=max(1,i-k),rx=min(n,i+k);
			int ly=max(1,j-k),ry=min(n,j+k);
			s[lx][ly]++,s[lx][ry+1]--,s[rx+1][ly]--,s[rx+1][ry+1]++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]="01"[!s[i][j]];
		}
	}
}
int h[M],is[M];
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
	}
	vector<int>t;
	int mx=0,mn=0,las=0,cur=0;
	for(int i=1,op,k;i<=q;i++){
		scanf("%d%d",&op,&k);
		h[i]=op?-k:k;
		// solve(k*(op?-1:1));
	}
	for(int i=1;i<=q;i++)h[i]+=h[i-1];
	fill(is,is+1+q,0);
	is[0]=is[q]=1;
	for(int i=1,mx=0,mn=0;i<q;i++){
		if(h[i]>mx)mx=h[i],is[i]=1;
		if(h[i]<mn)mn=h[i],is[i]=1;
	}
	for(int i=q-1,mx=h[q],mn=h[q];i>0;i--){
		if(h[i]>mx)mx=h[i],is[i]=1;
		if(h[i]<mn)mn=h[i],is[i]=1;
	}
	for(int i=0,las=0;i<=q;i++){
		if(is[i]){
			t.push_back(h[i]-h[las]);
			las=i;
		}
	}
	for(int x:t){
		solve(x);
		if([&](){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					if(a[i][j]!=a[1][1])return 0;
				}
			}
			return 1;
		}())break;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			putchar(a[i][j]);
		}
		puts("");
	}
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif