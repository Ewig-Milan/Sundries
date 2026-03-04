#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int maxn=1e5+5;
int N,Q,res[maxn],ql[maxn],qr[maxn],qu[maxn];
int idf[maxn],sz[maxn],hson[maxn],dfn[maxn],fa[maxn],Top[maxn],dep[maxn];
int tot,tot1;
struct DSU{
	int fa[maxn];
	void init(){for(int i=1;i<=Q;++i)fa[i]=i;}
	int find(int r){return r==fa[r]?r:(fa[r]=find(fa[r]));}
}T;
struct node{
	int son[2],fa,key;
	int now,val,tag,tag1;
	pii mn;
}t[maxn];
#define ls(p) t[p].son[0]
#define rs(p) t[p].son[1]
#define fa(p) t[p].fa
#define now(p) t[p].now
#define val(p) t[p].val
#define tag(p) t[p].tag
#define tag1(p) t[p].tag1
#define mn(p) t[p].mn
#define key(p) t[p].key
int A[maxn],M;
vector<int>ins[maxn],road[maxn],que[maxn];
void dfs(int u){
	sz[u]=1;hson[u]=-1;
	for(int v:road[u]){
		dep[v]=dep[u]+1;dfs(v);sz[u]+=sz[v];
		if(hson[u]==-1||sz[v]>sz[hson[u]])hson[u]=v;
	}
}
void dfs1(int u,int g){
	dfn[u]=++tot;idf[tot]=u;Top[u]=g;
	if(hson[u]!=-1)dfs1(hson[u],g);
	for(int v:road[u]){
		if(v==hson[u])continue;
		dfs1(v,v);
	}
}
pii ran[100];int tot2;
void Add(int v,int u){
	tag(v)+=tag(u),now(v)+=tag(u);
	tag1(v)+=tag1(u),val(v)+=tag1(u),mn(v).fi+=tag1(u);
}
void pd(int p){
	if(ls(p))Add(ls(p),p);
 	if(rs(p))Add(rs(p),p);
	tag(p)=tag1(p)=0;
}
void pp(int p){
	mn(p)=make_pair(val(p),p);
	if(ls(p))mn(p)=min(mn(p),mn(ls(p))),fa(ls(p))=p;
	if(rs(p))mn(p)=min(mn(p),mn(rs(p))),fa(rs(p))=p;
}
void split(int u,int &x,int &y,int v){
	if(!u){x=y=0;return;}pd(u);
	if(t[u].now<=v){
		x=u;
		split(rs(u),rs(x),y,v);
	}else{
		y=u;
		split(ls(u),x,ls(y),v);
	} pp(u);
}
int merge(int u,int v){
	if(!u||!v)return (u|v);pd(u),pd(v);
	if(key(u)<key(v)){
		rs(u)=merge(rs(u),v);
		pp(u);return u;
	}else{
		ls(v)=merge(u,ls(v));
		pp(v);return v;
	}
}
int rt;
void Ins(int id){
	if(!rt){rt=id;return;}
	int a,b;split(rt,a,b,t[id].now-1);
	int c=b;if(!b){rt=merge(rt,id);return;}
	while(ls(c))c=ls(c);
    if(now(c)==now(id)){rt=merge(a,b);T.fa[T.find(id)]=T.find(c);return;}
    rt=merge(a,id);rt=merge(rt,b);
}
int aid[100005],tot3;
void up(int l,int r){
    int a,b,c;
    split(rt,a,b,l-1);
    split(b,b,c,r);
    tot3=0;
    if(!b){
    	rt=merge(a,c);
    	return;
	}
    while(b&&!mn(b).fi){
    	int e=b;
    	while(e!=mn(b).se){
    		pd(e);int now;
    		if(ls(e)&&mn(ls(e))==mn(b))now=ls(e);
    		else now=rs(e);e=now;
		}
    	int d=mn(b).se,ls=ls(d),rs=rs(d),fat=fa(d),op;
    	if(ls(fat)==d)op=0;else op=1;
    	pd(d);now(d)=dfn[fa[idf[now(d)]]];
    	val(d)=dep[idf[now(d)]]-dep[Top[idf[now(d)]]];
    	ls(d)=rs(d)=fa(d)=0;mn(d)=make_pair(val(d),d);
    	fa(ls)=fa(rs)=0;tag(d)=tag1(d)=0;
    	ls=merge(ls,rs);
		if(d==b){b=ls;aid[++tot3]=d;continue;}
		fa(ls)=fat;t[fat].son[op]=ls;
    	while(1){
    		pp(fat);
    		if(fat==b)break;
    		fat=fa(fat);
		}
		aid[++tot3]=d;
	}
	if(b){
		--tag(b),--tag1(b);
		--now(b),--mn(b).fi,--val(b);
		int d=b;while(ls(d))pd(d),d=ls(d);
		int ls=ls(d),rs=rs(d),fat=fa(d),op;
    	if(ls(fat)==d)op=0;else op=1;pd(d);
    	ls(d)=rs(d)=fa(d)=0;mn(d)=make_pair(val(d),d);
    	fa(ls)=fa(rs)=0;tag(d)=tag1(d)=0;
    	ls=merge(ls,rs);
		if(d==b)b=ls;
		else{
			fa(ls)=fat;t[fat].son[op]=ls;
    	    while(1){
    		pp(fat);
    		if(fat==b)break;
    		fat=fa(fat);
		    }
		}
		aid[++tot3]=d;
	}
	rt=merge(a,b);rt=merge(rt,c);
	for(int i=1;i<=tot3;++i)Ins(aid[i]);
}
void down(int l,int r,int nxt){
	int a,b,c;
    split(rt,a,b,l-1);
    split(b,b,c,r);
    if(!b){
    	rt=merge(a,c);
    	return;
	}
	int d=b;
    while(rs(d))pd(d),d=rs(d);
    if(now(d)==r){
    	int ls=ls(d),rs=rs(d),fat=fa(d),op;
    	if(ls(fat)==d)op=0;else op=1;
    	pd(d);now(d)=dfn[nxt];
    	val(d)=dep[idf[now(d)]]-dep[Top[idf[now(d)]]];
    	ls(d)=rs(d)=fa(d)=0;mn(d)=make_pair(val(d),d);
    	fa(ls)=fa(rs)=0;tag(d)=tag1(d)=0;
    	ls=merge(ls,rs);
		if(d==b)b=ls;
		else {
			fa(ls)=fat;t[fat].son[op]=ls;
		    while(1){
    		    pp(fat);
    		    if(fat==b)break;
    		    fat=fa(fat);
		    }
		}
		if(b){
			++tag(b),++tag1(b);
			++now(b),++val(b),++mn(b).fi;
		}
		rt=merge(a,b);
		rt=merge(rt,c);
		Ins(d);
	}else{
		++tag(b),++tag1(b);
		++now(b),++val(b),++mn(b).fi;
		rt=merge(a,b);
		rt=merge(rt,c);
	}
}
int Id[100005];
void upd(int x){
	if(!rt)return;
	tot2=0;
	if(x==1){up(2,N);return;}
    int u=fa[x],lst=x;
    while(1){
        down(dfn[Top[u]],dfn[u],lst);
        if(Top[u]==1)break;
		lst=Top[u];u=fa[Top[u]];
	}
	u=x;
	while(1){
		ran[++tot2]=make_pair(dfn[Top[u]],dfn[u]);
		if(Top[u]==1)break;u=fa[Top[u]];
	}
	reverse(ran+1,ran+tot2+1);lst=1;
	for(int i=1;i<=tot2;++i){
		if(ran[i].fi>lst)up(lst,ran[i].fi-1);
		lst=ran[i].se+1;
	}if(lst<=N)up(lst,N);
}
int Par[1003],tot4;
int query(int u){
   tot4=0;Par[++tot4]=u;
   int v=fa(u);
   while(v){
   	    Par[++tot4]=v;
   	    if(v==rt)break;
   	    v=fa(v);
   }
   reverse(Par+1,Par+tot4+1);
   for(int i=1;i<=tot4;++i)pd(Par[i]);
   return now(u);
}
int main(){
	freopen("query.in","r",stdin);
	freopen("query.out","w",stdout); 
	mt19937 rnd(time(0));
    scanf("%d%d%d",&N,&M,&Q);T.init();
    for(int i=2;i<=N;++i)scanf("%d",&fa[i]),road[fa[i]].push_back(i);
    dfs(1);dfs1(1,1);for(int i=1;i<=M;++i)scanf("%d",&A[i]);
    for(int i=1;i<=Q;++i)scanf("%d%d%d",&ql[i],&qr[i],&qu[i]),ins[ql[i]].push_back(i),que[qr[i]].push_back(i);
    for(int i=1;i<=M;++i){
    	for(int v:ins[i]){
    		++tot1;Id[v]=tot1;
			now(tot1)=dfn[qu[v]];val(tot1)=dep[qu[v]]-dep[Top[qu[v]]];
    		mn(tot1)=make_pair(val(tot1),tot1);key(tot1)=rnd()%(int)(1e9);
    		Ins(tot1);
		}
		upd(A[i]);
		for(int v:que[i])res[v]=idf[query(T.find(Id[v]))];
	}
	for(int i=1;i<=Q;++i)printf("%d\n",res[i]);
	return 0;
}
