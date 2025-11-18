#include<bits/stdc++.h>
using namespace std;
#define N 305
#define ll long long
ll f[1025][N][N],w[N][N],dis1[N];
int vis[1025][N],id[N];
int n,q,ps[N],tt,vis1[N];
#define mid (l+r>>1)
#define ls (p<<1)
#define rs (p<<1|1)
const ll inf=1e18;
void Add(int id,int x){
    if(vis[id][x])return;
    tt=0;
    for(int i=1;i<=n;++i)if(vis[id][i])ps[++tt]=i,dis1[i]=w[i][x],vis1[i]=0;
    for(int T=1;T<=tt;++T){
        int p=-1;
        for(int i=1;i<=tt;++i){
            if(vis1[ps[i]])continue;
            if(p==-1||dis1[p]>dis1[ps[i]])p=ps[i];
        }
        if(p==-1)break;
        vis1[p]=1,f[id][p][x]=dis1[p];
        for(int i=1;i<=tt;++i)dis1[ps[i]]=min(dis1[ps[i]],dis1[p]+w[ps[i]][p]);
    }
    for(int i=1;i<=tt;++i)dis1[ps[i]]=w[x][ps[i]],vis1[ps[i]]=0;
    for(int T=1;T<=tt;++T){
        int p=-1;
        for(int i=1;i<=tt;++i){
            if(vis1[ps[i]])continue;
            if(p==-1||dis1[p]>dis1[ps[i]])p=ps[i];
        }
        if(p==-1)break;
        vis1[p]=1,f[id][x][p]=dis1[p];
        for(int i=1;i<=tt;++i)dis1[ps[i]]=min(dis1[ps[i]],dis1[p]+w[p][ps[i]]);
    }
    for(int i=1;i<=tt;++i)
        for(int j=1;j<=tt;++j)
            f[id][ps[i]][ps[j]]=min(f[id][ps[i]][ps[j]],f[id][ps[i]][x]+f[id][x][ps[j]]);
    vis[id][x]=1;
}
void slv(int p,int l,int r){
    if(l==r){id[l]=p;return;}
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)f[ls][i][j]=f[rs][i][j]=f[p][i][j];
        vis[ls][i]=vis[rs][i]=vis[p][i];
    }
    for(int i=l;i<=r;++i)Add((i<=mid?rs:ls),i);
    slv(ls,l,mid),slv(rs,mid+1,r);
}
int main(){
    freopen("distance.in","r",stdin);
    freopen("distance.out","w",stdout);
    ios::sync_with_stdio(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)cin>>w[i][j];
    slv(1,1,n);
    while(q--){
        int s,t,p;
        cin>>s>>t>>p;
        cout<<f[id[p]][s][t]<<endl;
    }
    return 0;
}