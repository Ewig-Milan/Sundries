#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,q,tot,sze[MAXN],dfn[MAXN],fa[MAXN][21],dep[MAXN];
vector<int> G[MAXN],T[MAXN]; 
void dfs(int u,int f) {
	fa[u][0]=f,dep[u]=dep[f]+1,dfn[u]=++tot,sze[u]=1;
	ffor(i,1,19) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(auto v:G[u]) if(v!=f) dfs(v,u),sze[u]+=sze[v];
	return ;
}
int lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	roff(i,19,0) if((dep[u]-dep[v])&(1<<i)) u=fa[u][i];
	if(u==v) return u;
	roff(i,19,0) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];	
}
struct INFO {int mn,samp,t0,t1;}dp1[MAXN],dp2[MAXN];
INFO operator +(INFO A,INFO B) {
	if(A.mn<B.mn) {if(B.mn==A.mn+1) A.t1=min(A.t1,B.t0);return A;}
	if(A.mn>B.mn) {if(A.mn==B.mn+1) B.t1=min(B.t1,A.t0);return B;}
	return {A.mn,(A.samp==B.samp)?A.samp:-1,min(A.t0,B.t0),min(A.t1,B.t1)};
}
INFO operator +(INFO A,int B) {return A.mn+=B,A;}
int lst[MAXN],rnk[MAXN],res[MAXN]; 
int build(vector<int> v) {
	vector<int> lst=v;
	sort(v.begin(),v.end(),[&](int x,int y) {return dfn[x]<dfn[y];});
	ffor(i,1,(int)v.size()-1) lst.push_back(lca(v[i-1],v[i]));
	sort(lst.begin(),lst.end(),[&](int x,int y) {return dfn[x]<dfn[y];});
	lst.erase(unique(lst.begin(),lst.end()),lst.end());
	for(auto u:lst) T[u].clear();
	ffor(i,1,(int)lst.size()-1) T[lca(lst[i],lst[i-1])].push_back(lst[i]);
	return lst[0];
}
int TC;
void dfs1(int u) {
	if(lst[u]==TC) dp1[u]={0,u,rnk[u],n+1};
	else dp1[u]={n+1,-1,n+1,n+1};
	for(auto v:T[u]) {dfs1(v);if(dp1[v].samp!=-1&&dp1[v].t1>dp1[v].t0) dp1[u]=dp1[u]+(dp1[v]+(dep[v]-dep[u]));}
	return ;
}
int jumping(int u,int dt) {roff(i,19,0) if(dt&(1<<i)) u=fa[u][i];return u;}
int div(int v) {if(v%2==0) return v/2;return (v-1)/2;}
void dfs2(int u,int fa) {
	if(fa) {
		int id1=dp1[u].samp,id2=dp2[u].samp;
		if(dp1[u].t0>dp1[u].t1) id1=-1;
		if(id2!=-1) assert(dp2[u].t0<dp2[u].t1);
		if(id1!=-1||id2!=-1) {
			if(id1==-1) res[id2]+=sze[jumping(u,dep[u]-dep[fa]-1)]-sze[u];
			else if(id2==-1) res[id1]+=sze[jumping(u,dep[u]-dep[fa]-1)]-sze[u];
			else {
				int t1=dep[u]+dp1[u].mn,t2=dep[u]-dp2[u].mn,mp=-1;
				if((t1-t2)%2==0) mp=div(t1+t2);
				else if(rnk[id1]<rnk[id2]) mp=div(t1+t2);
				else mp=div(t1+t2)+1;
				if(dep[u]>mp&&mp>dep[fa]) res[id1]++,res[id2]++;
				if(mp+1<dep[u]) res[id1]+=sze[jumping(u,min(dep[u]-dep[fa]-1,dep[u]-mp-1))]-sze[u];
				if(mp-1>dep[fa]) res[id2]+=sze[jumping(u,dep[u]-dep[fa]-1)]-sze[jumping(u,max(0,dep[u]-mp))];
			}
		}
	}
	else {
		if(dp1[u].samp!=-1&&dp1[u].t0<dp1[u].t1) res[dp1[u].samp]+=sze[1]-sze[u];
		dp2[u]={n+1,-1,n+1,n+1};
	}
	if(lst[u]==TC) {
		for(auto v:T[u]) dp2[v]={dep[v]-dep[u],u,rnk[u],n+1},dfs2(v,u);
		int ex=sze[u];
		for(auto v:T[u]) ex-=sze[jumping(v,dep[v]-dep[u]-1)];
		res[u]+=ex;
		return ;
	}
	INFO pre=dp2[u];
	for(auto v:T[u]) {
		dp2[v]=pre+(dep[v]-dep[u]);
		if(dp1[v].samp!=-1&&dp1[v].t1>dp1[v].t0) pre=pre+(dp1[v]+(dep[v]-dep[u]));
	}
	pre={n+1,-1,n+1,n+1};
	reverse(T[u].begin(),T[u].end());
	for(auto v:T[u]) {
		dp2[v]=dp2[v]+(pre+(dep[v]-dep[u]));
		if(dp1[v].samp!=-1&&dp1[v].t1>dp1[v].t0) pre=pre+(dp1[v]+(dep[v]-dep[u]));
		if(dp2[v].samp==-1||dp2[v].t1<dp2[v].t0) dp2[v]={n+1,-1,n+1,n+1};	
		dfs2(v,u);
	}
	auto info=dp2[u]+dp1[u];
	if(info.samp!=-1&&info.t0<info.t1) {
		int ex=sze[u];
		for(auto v:T[u]) ex-=sze[jumping(v,dep[v]-dep[u]-1)];
		res[info.samp]+=ex;
	}
	else {
		for(auto v:T[u]) if(dp1[v].samp!=-1&&dp1[v].t1>dp1[v].t0) res[dp1[v].samp]++;
		if(dp2[u].samp!=-1&&dp2[u].t1>dp2[u].t0) res[dp2[u].samp]++;
	}
	return ;
	
}
int main() {
	freopen("civilization.in","r",stdin);
	freopen("civilization.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	dfs(1,0);
	cin>>q;
	ffor(i,1,q) {
		int k,id,ts=0; cin>>k,TC=i;
		vector<int> A,del;
		ffor(j,1,k) cin>>id,A.push_back(id),del.push_back(0);
		for(auto u:A) lst[u]=i,rnk[u]=++ts,res[u]=0;
		for(auto u:A) {
			int v=fa[u][0];
			if(lst[v]==i) if(rnk[v]<rnk[u]&&!del[rnk[v]-1]) del[rnk[u]-1]=1;
			else if(rnk[v]>rnk[u]&&!del[rnk[u]-1]) del[rnk[v]-1]=1;
		}
		vector<int> node;
		for(auto u:A) if(!del[rnk[u]-1]) node.push_back(u);
		else lst[u]=0;
		int r=build(node);
		dfs1(r),dfs2(r,0);
		for(auto u:A) cout<<(del[rnk[u]-1]?1:res[u])<<' ';
		cout<<'\n';
	}
	return 0;
}

