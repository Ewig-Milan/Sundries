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
const int N=5e5+10;
const ll INF=1e18;
int n,m,fa[N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
struct ques{
	int t,i,id;
}o[N];
ll w[N],a[N];
int cur[N],oth[N];
int pre[N],nex[N];
ll pw[N],sw[N];
int d[N];
int tlas[N];
void getd(int i){
	if(pw[i]>sw[i])d[i]=-1;
	else if(pw[i]<sw[i])d[i]=1;
	else d[i]=0;
}
void swp(int y){
	int x=pre[y];
	int p=pre[x],q=nex[y];
	nex[p]=y,pre[y]=p;
	nex[y]=x,pre[x]=y;
	nex[x]=q,pre[q]=x;
	pw[y]=pw[pre[y]]+w[pre[y]];
	pw[x]=pw[pre[x]]+w[pre[x]];
	sw[x]=sw[nex[x]]+w[nex[x]];
	sw[y]=sw[nex[y]]+w[nex[y]];
}
int refind(int x,int t){
	if(oth[x]){
		int y=oth[x];
		if((t-tlas[x])&1){
			swp(a[x]<a[y]?y:x);
			swap(a[x],a[y]);
			tlas[x]=tlas[y]=t;
			return y;
		}else{
			tlas[x]=tlas[y]=t;
			return x;
		}
	}else{
		a[x]+=(t-tlas[x])*d[x],tlas[x]=t;
		return x;
	}
}
ll geta(int x,int t){
	if(oth[x]){
		int y=oth[x];
		if((t-tlas[x])&1)return a[y];
		else return a[x];
	}else{
		return a[x]+(t-tlas[x])*d[x];
	}
}
void remove(int y){
	int x=pre[y];
	fa[y]=x;
	w[x]+=w[y];
	nex[x]=nex[y];
	pre[nex[y]]=x;
	sw[x]=sw[nex[x]]+w[nex[x]];
}
int vcnt,val[N];
void update(int x){
	if(oth[x]){
		int y=oth[x];
		oth[x]=oth[y]=0;
		val[y]=++vcnt;
		getd(y);
	}
	val[x]=++vcnt;
}
priority_queue<tuple<ll,int,int,int>>q;
void push(int y,int t0){
	int x=pre[y];
	if(geta(y,t0)-geta(x,t0)==0){
		q.push({-t0,y,val[x],val[y]});
		return;
	}
	if(d[y]-d[x]>=0)return;
	int v=d[x]-d[y];
	ll t=t0+(geta(y,t0)-geta(x,t0)+v-1)/v;
	q.push({-t,y,val[x],val[y]});
}
ll ans[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i],&w[i]);
	a[0]=-INF,a[n+1]=INF;
	iota(cur,cur+1+n+1,0);
	sort(cur+1,cur+1+n,[&](int x,int y){
		return a[x]<a[y];
	});
	iota(fa,fa+1+n,0);
	for(int l=1,r,las=0;l<=n+1;l=r){
		for(r=l+1;r<=n&&a[cur[l]]==a[cur[r]];r++);
		for(int i=l+1;i<r;i++)fa[cur[i]]=cur[l],w[cur[l]]+=w[cur[i]];
		nex[las]=cur[l],pre[cur[l]]=las;
		las=cur[l];
	}
	for(int i=0;i!=n+1;i=nex[i])pw[nex[i]]=pw[i]+w[i];
	for(int i=n+1;i!=0;i=pre[i])sw[pre[i]]=sw[i]+w[i];
	for(int i=1;i<=m;i++){
		scanf("%d%d",&o[i].t,&o[i].i);
		o[i].id=i;
	}
	sort(o+1,o+1+m,[&](ques x,ques y){
		return x.t<y.t;
	});
	for(int i=0;;i=nex[i]){
		getd(i);
		if(i==n+1)break;
	}
	for(int i=0;i!=n+1;i=nex[i])push(nex[i],0);
	for(int ot=1;ot<=m;ot++){
		int t0=o[ot].t,x=o[ot].i;
		for(;!q.empty()&&get<0>(q.top())>-t0;){
			auto [t,y,w1,w2]=q.top();
			t=-t;
			q.pop();
			int x=pre[y];
			if(fa[x]!=x||fa[y]!=y)continue;
			if(val[x]!=w1||val[y]!=w2)continue;
			x=refind(x,t),y=refind(y,t);
			int v=d[x]-d[y];
			if(a[x]==a[y]){
				update(y);
				remove(y);
				getd(x);
				update(x);
				if(pre[x]>0)push(pre[x],t);
				push(x,t);
				push(nex[x],t);
				if(nex[x]<=n)push(nex[nex[x]],t);
			}else{
				swp(y);
				update(x);
				update(y);
				getd(x),getd(y);
				if(d[y]==1&&d[x]==-1){
					oth[y]=x,oth[x]=y;
					d[x]=d[y]=0;
				}
				push(y,t);
				push(x,t);
				push(nex[x],t);
			}
		}
		x=find(x);
		ans[o[ot].id]=geta(x,t0);
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif