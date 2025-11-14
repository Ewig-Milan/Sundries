#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e5+5;
int n,m,x,y,lf,d[N],sz[N];
ll sum[N],f[N],k,ans[N];
pair<ll,int>q[N];
multiset<int>s[N];
vector<int>v[N];
void dfs(int x,int fa){
    if(v[x].size()==1) lf++,sz[x]=1,s[x].insert(-1);
    for(int y:v[x]) if(y!=fa)
        dfs(y,x),sum[x]+=sum[y]+sz[y],sz[x]+=sz[y],s[x].insert(d[y]);
    d[x]=*s[x].rbegin()+1;
}
void upd(int x,int y){
    sum[x]-=sum[y]+sz[y],sz[x]-=sz[y],s[x].erase(s[x].find(d[y])),d[x]=*s[x].rbegin()+1;
    sum[y]+=sum[x]+sz[x],sz[y]+=sz[x],s[y].insert(d[x]),d[y]=*s[y].rbegin()+1;
}
void dfs2(int x,int fa){
    f[d[x]]=max(f[d[x]],(1ll*d[x]*lf-sum[x])/2);
    for(int y:v[x])
        if(y!=fa) upd(x,y),dfs2(y,x),upd(y,x);
}
signed main(){
    FILE("magic");
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        v[x].push_back(i+n),v[i+n].push_back(x);
        v[y].push_back(i+n),v[i+n].push_back(y);
    }
    fill(f,f+1+(n+=n-1),-1e18),dfs(1,0),dfs2(1,0);
    for(int i=2;i<=n;i++) f[i]=max(f[i],f[i-2]+lf);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%lld",&k),q[i]={k,i};
    sort(q+1,q+1+m);
    for(int i=1,j=1;i<=m;i++){
        k=q[i].first;
        while(j<n&&f[j]<k) j++;
        ans[q[i].second]=j<n?j:min(n-1+(k-f[n-1]+lf-1)/lf*2,n-2+(k-f[n-2]+lf-1)/lf*2);
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}