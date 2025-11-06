#include<bits/stdc++.h>
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
typedef long long ll;
const int N=50,MAXN=100005,mod=998244353;
struct node {
    int a,b,d,e;
    inline void print() {
        printf("%d %d %d %d",a,b,d,e);
    }
} ;
vector<node>vec,tmp;
vector<int>e[N*N];
bool vis[N*N],chk[N*N],h[MAXN][N][2][2],vvis[MAXN];
int k,a[MAXN],n,ans,f[MAXN][N],g[MAXN][N][2][2];
char s[MAXN];
void dfs(int u) {
    if(vis[u])return;
    vis[u]=true;
    for(int v:e[u]) dfs(v);
}
bool Dfs(int u) {
    if(chk[u]) return true;
    if(vvis[u])return false;
    vvis[u]=true;
    for(int v:e[u]) if(Dfs(v))return true;
    return false;
}
inline void Getmod(int&a,int b) {
    if((a+=b)>=mod) a-=mod;
}
int solve(int l,int id,int lim1,int lim2) {
    if(h[l][id][lim1][lim2]) return g[l][id][lim1][lim2];
    h[l][id][lim1][lim2]=true;
    int r=n-l+1,&res=g[l][id][lim1][lim2]=0;
    if(!lim1&&!lim2) {
        for(int v:e[id]) Getmod(res,f[r-l+1][v]);
    } else if(l==r) {
        for(int v:e[id])
            if(chk[v]&&(!lim1||tmp[v].a<a[l]||(tmp[v].a==a[l]&&!lim2)))++res;
    } else if(l+1==r) {
        for(int v:e[id])
            if(vis[v]&&(!lim1||tmp[v].a<a[l]||(tmp[v].a==a[l]&&(tmp[v].b<a[r]||(tmp[v].b==a[r]&&!lim2)))))++res;
    } else {
        for(int v:e[id])
            if(!lim1||tmp[v].a<=a[l])
                Getmod(res,solve(l+1,v,lim1&&tmp[v].a==a[l],(lim2&&tmp[v].b==a[r])||tmp[v].b>a[r]));
    }
    return res;
}
inline int calc(int c) {
    for(int a=0; a<k; ++a)
        for(int b=0; b<k; ++b)
            for(int d=0; d<c; ++d) {
                int e=(a+k-b*c%k)%k;
                if(e<c&&d*k+b-c<a*c&&a*c<=d*k+b)
                    vec.push_back(node {a,b,d,e});
            }
    for(unsigned i=0; i<vec.size(); ++i)
        for(unsigned j=0; j<vec.size(); ++j)
            if((vec[i].b*c+vec[i].e)/k==vec[j].e&&(vec[j].d+vec[i].a*c)%k==vec[i].b) {
                e[i].push_back(j);
                if(i==j) chk[i]=true;
            }
    for(unsigned i=0; i<vec.size(); ++i)
        if(!vec[i].d&&!vec[i].e&&vec[i].a)
            dfs(i);
    for(unsigned i=0; i<vec.size(); ++i)
        if(vis[i]&&!chk[i]) {
            for(unsigned j=0; j<vec.size(); ++j)vvis[j]=false;
            chk[i]=Dfs(i);
        }
    for(unsigned i=0; i<vec.size(); ++i)
        if(chk[i]&&vis[i])
            tmp.push_back(vec[i]);
    for(unsigned i=0; i<vec.size(); ++i)e[i].clear(),chk[i]=vis[i]=false;
    for(unsigned i=0; i<tmp.size(); ++i)
        for(unsigned j=0; j<tmp.size(); ++j)
            if((tmp[i].b*c+tmp[i].e)/k==tmp[j].e&&(tmp[j].d+tmp[i].a*c)%k==tmp[i].b)
                e[i].push_back(j);
    for(unsigned i=0; i<tmp.size(); ++i) 
        if(((tmp[i].b*c+tmp[i].e)/k+tmp[i].a*c)%k==tmp[i].b)
            f[2][i]=1,vis[i]=true;
    for(unsigned i=0; i<tmp.size(); ++i)
        if(tmp[i].a==tmp[i].b)
            f[1][i]=1,chk[i]=true;
    for(int i=1; i+2<=n; ++i)
        for(unsigned u=0; u<tmp.size(); ++u)
            for(int v:e[u])
                Getmod(f[i+2][u],f[i][v]);
    int res=0;
    for(int i=1; i<n; ++i)
        for(unsigned u=0; u<tmp.size(); ++u)
            if(!tmp[u].d&&!tmp[u].e&&tmp[u].a)
                Getmod(res,f[i][u]);
    for(unsigned u=0; u<tmp.size(); ++u)
        if(!tmp[u].d&&!tmp[u].e&&tmp[u].a&&tmp[u].a<=a[1])
            Getmod(res,solve(2,u,tmp[u].a==a[1],tmp[u].b>a[n]));
    for(int i=1; i<=n; ++i)
        for(unsigned u=0; u<tmp.size(); ++u)
            f[i][u]=0,h[i][u][0][0]=h[i][u][0][1]=h[i][u][1][0]=h[i][u][1][1]=0;
    for(unsigned i=0; i<tmp.size(); ++i)e[i].clear(),vis[i]=chk[i]=false;
    vec.clear(),tmp.clear();
    return res;
}
int main() {
    File("reverse");
    scanf("%d%s",&k,s+1),n=strlen(s+1);
    for(int i=1; i<=n; ++i) a[i]=isdigit(s[i])?s[i]-'0':s[i]-'A'+10;
    if(n==1) {
        printf("%d\n",a[1]);
        return 0;
    } else if(n==2) {
        ans=k-1;
        for(int i=k; i<=a[1]*k+a[2]; ++i)
            if((i/k+i%k*k)%i==0)
                ++ans;
        printf("%d\n",ans);
        return 0;
    }
    if(k==4) {
        ans=(calc(1)+calc(3))%mod;
    } else if(k==5) {
        ans=((calc(1)+calc(2))%mod+calc(4))%mod;
    } else for(int c=1; c<k; ++c) Getmod(ans,calc(c));
    printf("%d\n",ans);
    return 0;
}