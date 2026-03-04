#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "debug.h"
#else
#define debug(...) void ()
#endif
#define all(x) (x).begin (), (x).end ()
template <class T> auto ary (T *a, int l, int r) {
    return vector<T>{a + l, a + 1 + r};
}
using ll = long long;
using ull = unsigned long long;
const int N=2e3+10,mod=1e9+7;
ll qpow(ll x,ll y=mod-2,ll ans=1){
    for(;y;(x*=x)%=mod,y>>=1)if(y&1)(ans*=x)%=mod;
    return ans;
}
const int i10=qpow(10);
int n,m,k,vis[N],mn[N],s[N*3];
vector<int>tr[N],to[N];
void dfs(int u){
    if(vis[u])return;
    vis[u]=1;
    for(int v:tr[u])dfs(v);
}
int is[N];
void run(){
    static int ne[N];
    int val=10;
    for(int i=1;i<=n;i++){
        if(is[i])val=min(val,mn[i]);
    }
    s[++k]=val;
    for(int i=1;i<=n;i++){
        if(is[i]&&val==mn[i]){
            for(int j:to[i])ne[j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        swap(is[i]=0,ne[i]);
    }
}
int calc(int *s){
    static int nex[N*2];
    for(int i=2,j=0;i<=n+n;i++){
        for(;j&&s[j+1]!=s[i];j=nex[j]);
        nex[i]=j+=s[j+1]==s[i];
    }
    return n+n-nex[n+n];
}
int main () {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    scanf("%d%d",&n,&m);
    vector<tuple<int,int,int>>E(m);
    for(auto &[u,v,w]:E){
        scanf("%d%d%d",&u,&v,&w);
        tr[++v].push_back(++u);
    }
    fill(vis+1,vis+1+n,0);
    dfs(2);
    if(!vis[1])puts("-1"),exit(0);
    // debug(ary(vis,1,n));
    fill(mn+1,mn+1+n,10);
    for(auto &[u,v,w]:E){
        if(!vis[u]||!vis[v])continue;
        mn[u]=min(mn[u],w);
    }
    for(auto &[u,v,w]:E){
        if(!vis[u]||!vis[v])continue;
        if(mn[u]==w)to[u].push_back(v);
    }
    k=0;
    fill(is+1,is+1+n,0);
    is[1]=1;
    // debug(ary(mn,1,n));
    // debug(ary(to,1,n));
    for(;k<3*n;){
        run();
        // debug(ary(is,1,n));
        if(is[2]){
            // debug(ary(s,1,k));
            int ans=0;
            for(int i=k;i>=1;i--){
                ans=1ll*(ans+s[i])*i10%mod;
            }
            printf("%d\n",ans);
            return 0;
        }
    }
    int len=calc(s+n),val=0;
    // debug(ary(s,1,k),len);
    for(int i=n+len;i>n;i--){
        val=1ll*(val+s[i])*i10%mod;
    }
    val=val*qpow((1-qpow(i10,len)+mod)%mod)%mod;
    for(int i=n;i>=1;i--){
        val=1ll*(val+s[i])*i10%mod;
    }
    printf("%d\n",val);
    return 0;
}
#ifdef DEBUG
#include "debug.hpp"
#endif