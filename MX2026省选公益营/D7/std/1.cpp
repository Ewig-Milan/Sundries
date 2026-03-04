#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int BS=1<<20|5;
char buf[BS],*P1,*P2;
inline char gc(){
    if(P1==P2)P2=(P1=buf)+fread(buf,1,BS,stdin);
    return P1==P2?EOF:*(P1++);
}
inline ll in(){
    ll x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=gc();
    return x*f;
}
const int N=1e5+5;
int n,q;
ll pk[N],pb[N],pl[N],pr[N],qx[N];
vector<int> e[N];
int fa[N],son[N],sz[N],dep[N],top[N],dfn[N],dfp[N],dfn_tot,dfn1[N];
void dfs1(int x){
	dep[x]=dep[fa[x]]+1,sz[x]=1;
	for(int y:e[x]){
		if(y==fa[x])continue;
		fa[y]=x,dfs1(y);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
void dfs2(int x){
	dfn[x]=dfn1[x]=++dfn_tot;
	dfp[dfn_tot]=x;
	if(son[x]){
		top[son[x]]=top[x];
		dfs2(son[x]);
		dfn1[x]=dfn1[son[x]];
	}
	for(int y:e[x]){
		if(y==fa[x]||y==son[x])continue;
		top[y]=y,dfs2(y);
	}
}
int rt0,rt[N<<2],tot;
struct node{
	int ls,rs,id;
}T[N*350];
#define ls(x) T[(x)].ls
#define rs(x) T[(x)].rs
#define id(x) T[(x)].id
inline int newnode(){
	tot++,ls(tot)=rs(tot)=id(tot)=0;
	return tot;
}
inline ll Y(int p,int x){return 1ll*pk[p]*x+pb[p];}
void insert1(int &p,int l,int r,int cur){
	if(!p)p=newnode();
	if(!id(p)){id(p)=cur;return;}
	int mid=l+r>>1;
	if(Y(id(p),mid)<Y(cur,mid))swap(id(p),cur);
	if(l<mid&&pk[cur]<pk[id(p)])insert1(ls(p),l,mid,cur);
	if(mid<r&&pk[cur]>pk[id(p)])insert1(rs(p),mid+1,r,cur);
}
void insert(int &p,int l,int r,int ql,int qr,int cur){
	if(!p)p=newnode();
	if(ql<=l&&r<=qr){
		insert1(p,l,r,cur);
		return;
	}
	int mid=l+r>>1;
	if(ql<=mid)insert(ls(p),l,mid,ql,qr,cur);
	if(mid<qr)insert(rs(p),mid+1,r,ql,qr,cur);
}
int merge(int p,int q,int l,int r){
	if(!p||!q)return p|q;
	if(l==r){
		if(Y(id(p),l)<Y(id(q),l))id(p)=id(q);
		return p;
	}
	int mid=l+r>>1;
	ls(p)=merge(ls(p),ls(q),l,mid);
	rs(p)=merge(rs(p),rs(q),mid+1,r);
	insert1(p,l,r,id(q));
	return p;
}
ll query(int p,int l,int r,int d){
	if(!p)return 0;
	if(l==r)return Y(id(p),d);
	int mid=l+r>>1;
	ll res;
	if(d<=mid)res=query(ls(p),l,mid,d);
	else res=query(rs(p),mid+1,r,d);
	res=max(res,Y(id(p),d));
	return res;
}
vector<int> qe[N];
ll ans[N];
void dfs3(int x){
	insert(rt0,0,1e6,pl[x],pr[x],x);
	for(int i:qe[x])ans[i]=max(ans[i],query(rt0,0,1e6,qx[i]));
	if(son[x])dfs3(son[x]);
	for(int y:e[x]){
		if(y==fa[x]||y==son[x])continue;
		rt0=tot=0;
		dfs3(y);
	}
}
int rt1[N],ls[N<<2],rs[N<<2],tot1;
vector<int> qe1[N<<2];
void addqe(int &p,int l,int r,int ql,int qr,int cur){
	if(!p)p=++tot1;
	if(ql<=l&&r<=qr){
		qe1[p].push_back(cur);
		return;
	}
	int mid=l+r>>1;
	if(ql<=mid)addqe(ls[p],l,mid,ql,qr,cur);
	if(mid<qr)addqe(rs[p],mid+1,r,ql,qr,cur);
}
void solve(int &p,int l,int r,int op){
	if(!p)p=++tot1;
	if(l==r){
		int x=dfp[l];
		insert(rt[p],0,1e6,pl[x],pr[x],x);
		for(int i:qe1[p]){
			if(qx[i]>=pl[x]&&qx[i]<=pr[x]){
				ans[i]=max(ans[i],1ll*pk[x]*qx[i]+pb[x]);
			}
		}
		return;
	}
	int mid=l+r>>1;
	op|=qe1[p].size()>0;
	solve(ls[p],l,mid,op),solve(rs[p],mid+1,r,op);
	rt[p]=merge(rt[ls[p]],rt[rs[p]],0,1e6);
	if(!op)return;
	for(int i:qe1[p])ans[i]=max(ans[i],query(rt[p],0,1e6,qx[i]));
}
int main(){
	freopen("unknow.in","r",stdin);
	freopen("unknow.out","w",stdout); 
	n=in(),q=in();
	for(int i=1;i<=n;i++)
		pk[i]=in(),pb[i]=in(),pl[i]=in(),pr[i]=in();
	for(int i=1;i<n;i++){
		int x=in(),y=in();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs1(1),top[1]=1,dfs2(1);
	for(int i=1;i<=q;i++){
		int u=in(),v=in();qx[i]=in();
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]])swap(u,v);
			qe[u].push_back(i);
			u=fa[top[u]];
		}
		if(dfn[u]>dfn[v])swap(u,v);
		addqe(rt1[top[u]],dfn[top[u]],dfn1[top[u]],dfn[u],dfn[v],i);
	}
	dfs3(1);tot=0;
	for(int i=1;i<=n;i++)if(top[i]==i)solve(rt1[i],dfn[i],dfn1[i],0);
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
	return 0;
}
