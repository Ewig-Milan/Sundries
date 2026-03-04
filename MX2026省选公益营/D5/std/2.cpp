#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;

const int MAXN=4e5+10,MOD=998244353,MOD1=9982244353,MOD2=1e9+7,B=600;
vector<int> key,suf,G[MAXN];
int n,m,fail[MAXN],dep[MAXN],ex[MAXN],ed[MAXN],Tr[MAXN][2],tr[MAXN][2],ori[MAXN],pw1[MAXN*5],pw2[MAXN*5];
ll dp[MAXN];
string T[MAXN];

namespace DS {
	int bel[MAXN],L[MAXN],R[MAXN];
	ll s1[MAXN],s2[MAXN];
	void init(int n) {
		int k=sqrt(n);
		ffor(i,1,k) L[i]=R[i-1]+1,R[i]=i*k;
		if(R[k]<n) ++k,L[k]=R[k-1]+1,R[k]=n;
		ffor(i,1,k) ffor(j,L[i],R[i]) bel[j]=i;
		return ;
	}
	inline void update(const int p,const int v) {return s1[p]+=v,s2[bel[p]]+=v,void();}
	inline int query(const int l,const int r) {
		__int128 res=0;
		if(bel[l]==bel[r]) ffor(i,l,r) res+=s1[i];
		else {
			ffor(i,l,R[bel[l]]) res+=s1[i];
			ffor(i,L[bel[r]],r) res+=s1[i];
			ffor(i,bel[l]+1,bel[r]-1) res+=s2[i];	
		}
		return res%MOD;
	}
};
int pre1[MAXN],pre2[MAXN],fa[MAXN][20],sze[MAXN],dfn[MAXN],tt;
void dfs(int u) {
	ffor(i,1,19) fa[u][i]=fa[fa[u][i-1]][i-1];
	dfn[u]=++tt,sze[u]=1;
	ffor(j,0,1) if(tr[u][j]) {
		int v=tr[u][j];fa[v][0]=u,dep[v]=dep[u]+1;
		pre1[v]=(1ll*pre1[u]*3+j+1)%MOD1;
		pre2[v]=(1ll*pre2[u]*3+j+1)%MOD2;
		dfs(v),sze[u]+=sze[v];
	}
	return ;
}
namespace SA {
	int Fa[MAXN],tmp[MAXN],rnk[MAXN];
	int height[MAXN],sa[MAXN],st[20][MAXN];
	pair<int,int> s[MAXN];
	void renew(void) {
		ffor(i,1,m)	tmp[i]=Fa[Fa[i]];
		vector<pair<int,int>> v;
		ffor(i,1,m) s[i]=make_pair(rnk[i],rnk[Fa[i]]),v.push_back(s[i]);
		sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());
		ffor(i,1,m) rnk[i]=lower_bound(v.begin(),v.end(),s[i])-v.begin()+1,Fa[i]=tmp[i];
		return ;
	}
	int lcp(int u,int v) {
		int len=0;
		roff(i,19,0) if(fa[u][i]&&fa[v][i]) {
			int x=(pre1[u]-1ll*pre1[fa[u][i]]*pw1[(1<<i)])%MOD1;
			int y=(pre1[v]-1ll*pre1[fa[v][i]]*pw1[(1<<i)])%MOD1;
			if((x-y)%MOD1) continue ;
			x=(pre2[u]-1ll*pre2[fa[u][i]]*pw2[(1<<i)])%MOD2;
			y=(pre2[v]-1ll*pre2[fa[v][i]]*pw2[(1<<i)])%MOD2;
			if((x-y)%MOD2) continue ;
			len+=(1<<i),u=fa[u][i],v=fa[v][i];
		}
		return len;
	}
	inline int LCP(int u,int v) {
		if(u==v) return dep[u]-1;
		u=rnk[u],v=rnk[v];
		if(u>v) swap(u,v); v--;
		int k=log2(v-u+1);
		return min(st[k][u],st[k][v-(1<<k)+1]);
	}
	void SA(void) {
		ffor(i,1,m) ffor(j,0,1) if(tr[i][j]) rnk[tr[i][j]]=j+2,Fa[tr[i][j]]=i;
		rnk[1]=1;ffor(i,1,20) renew();
		ffor(i,1,m) sa[rnk[i]]=i; ffor(i,1,m-1) height[i]=lcp(sa[i],sa[i+1]),st[0][i]=height[i];
		ffor(s,1,19) ffor(i,1,m-(1<<s)+1) st[s][i]=min(st[s-1][i],st[s-1][i+(1<<s-1)]);
		return ;
	}
};
namespace TRTR {
	int idx=1,Tr[MAXN][2],ex[MAXN];
	void insert(string S)	{
		reverse(S.begin(),S.end());
		int u=1;
		for(auto ch:S) {
			if(ch=='2') break ;
			int o=ch-'0';
			if(!Tr[u][o]) Tr[u][o]=++idx;
			u=Tr[u][o],ex[u]++;
		}
		return ;
	}
	inline int qr(int u) {
		int p=1;__int128 res=0;
		ffor(i,1,B) {
			int v=fa[u][0];
			if(!v) continue ;
			int o=0;
			if(u==tr[v][1]) o=1;
			p=Tr[p][o];
			if(!ex[p]) break ;
			res+=1ll*dp[v]*ex[p];
			u=v;
		}
		return res%MOD;
	}
};
vector<int> upd[MAXN];
int insert(string S) {
	int u=1;
	for(auto ch:S) if(ch!='2') {
		if(!tr[u][ch-'0']) tr[u][ch-'0']=++m;
		u=tr[u][ch-'0'];	
	}
	return u;
}
int pre[MAXN];
void dfs3(int u,int t,int b,int ad) {
	dp[u]=(dp[u]+1ll*ex[t]*ad)%MOD;
	if(b) {
		if(tr[u][0]&&ex[tr[t][0]]) dfs3(tr[u][0],tr[t][0],b-1,ad);
		if(tr[u][1]&&ex[tr[t][1]]) dfs3(tr[u][1],tr[t][1],b-1,ad);
	}
	return ;
}
void solve(int u) {
	int s1=0,s2=0,v=u;
	if(u!=1&&ori[u]) {
		dp[u]+=TRTR::qr(u);
		dp[u]+=DS::query(dfn[u],dfn[u]+sze[u]-1);
		for(auto v:suf) {
			int len=SA::LCP(u,v);
			if(len) dp[u]+=pre[dep[u]-1]-pre[dep[u]-len-1];
		}
	}
	dp[u]%=MOD;
	dfs3(u,1,B,dp[u]);
	pre[dep[u]]=(pre[dep[u]-1]+dp[u])%MOD;
	for(auto v:upd[u]) DS::update(dfn[v],dp[u]);
	if(tr[u][0]) solve(tr[u][0]);
	if(tr[u][1]) solve(tr[u][1]);
	return ;
}
void build(void) {
	queue<int> q;
	if(tr[1][0]) q.push(tr[1][0]),fail[tr[1][0]]=1; else tr[1][0]=1;
	if(tr[1][1]) q.push(tr[1][1]),fail[tr[1][1]]=1; else tr[1][1]=1;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		if(tr[u][0]) fail[tr[u][0]]=tr[fail[u]][0],q.push(tr[u][0]); else tr[u][0]=tr[fail[u]][0];
		if(tr[u][1]) fail[tr[u][1]]=tr[fail[u]][1],q.push(tr[u][1]); else tr[u][1]=tr[fail[u]][1];
		G[fail[u]].push_back(u);
	}
	return ;
}

int lst[MAXN][2];
void Dfs1(int u) {
	if(u!=1) {
		if(lst[u][0]==-1) lst[u][0]=lst[fail[u]][0];
		if(lst[u][1]==-1) lst[u][1]=lst[fail[u]][1];
	}
	for(auto v:G[u]) Dfs1(v);
	return ;
}
int sp,STACK[MAXN];
int anc(int u,int v) {
	return STACK[dep[u]-v];	
}
void Dfs2(int u) {
	STACK[dep[u]]=u;
	
	int v=lst[u][0];
	if(v==sp&&sp!=1) upd[anc(u,dep[v]-1)].push_back(u);
	
	if(!tr[u][0]) {
		int v=lst[u][0];
		while(v!=-1&&v!=0&&v!=1) {
			if(v!=sp&&ori[anc(u,dep[v]-1)]) upd[anc(u,dep[v]-1)].push_back(u);
			v=lst[fail[v]][0];
		}
	}
	if(!tr[u][1]) {
		int v=lst[u][1];
		while(v!=-1&&v!=0&&v!=1) {
			if(v!=sp&&ori[anc(u,dep[v]-1)]) upd[anc(u,dep[v]-1)].push_back(u);
			v=lst[fail[v]][1];
		}
	}
	if(tr[u][0]) Dfs2(tr[u][0]);
	if(tr[u][1]) Dfs2(tr[u][1]);
	return ;
}
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m; int s=0;
	ffor(i,1,n) cin>>T[i],s+=T[i].size();
	ffor(i,1,m) cin>>tr[i][0]>>tr[i][1],ori[i]=1;
	pw1[0]=pw2[0]=1;
	ffor(i,1,2000000) pw1[i]=1ll*pw1[i-1]*3%MOD1,pw2[i]=1ll*pw2[i-1]*3%MOD2;
	ffor(i,1,n) if(T[i].size()<=B) {
		int u=1;
		ffor(j,0,T[i].size()-1) {
			int o=T[i][j]-'0';
			if(o==2) break ;
			if(!tr[u][o]) tr[u][o]=++m;
			u=tr[u][o],ex[u]++;
		}
		TRTR::insert(T[i]);
	}
	else {
		int id=insert(T[i]);
		if(T[i][0]!='2') key.push_back(id);
		if(T[i][T[i].size()-1]!='2') suf.push_back(id);
	}
	dep[1]=1,dfs(1);
	SA::SA();
	DS::init(m);
	ffor(i,1,m) Tr[i][0]=tr[i][0],Tr[i][1]=tr[i][1];
	build();
	ffor(i,1,m) tr[i][0]=Tr[i][0],tr[i][1]=Tr[i][1];
	for(auto id:key) {
		ffor(i,1,m) lst[i][0]=lst[i][1]=-1;
		lst[id][0]=lst[id][1]=id;
		int u=id;
		while(fa[u][0]) {
			int v=fa[u][0];
			if(u==tr[v][0]) lst[v][0]=v;
			else lst[v][1]=v;
			u=v;
		}
		sp=id,Dfs1(1),Dfs2(1);
	}
	dp[1]=1,solve(1);
	ffor(i,1,m) if(ori[i]) cout<<(dp[i]%MOD+MOD)%MOD<<' ';
	return 0;
}
