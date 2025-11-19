#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;'0'>ch||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(;'0'<=ch&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
void write(int x){if(x>9)write(x/10);putchar(x%10+48);}
const int N=2e6,mo=998244353;
struct Kazemaru{
    int c[N];
    inline void add(int x,int y){for(;x<=n;x+=-x&x)c[x]+=y;}
    inline int sum(int x,int y=0){for(;x;x-=-x&x)y+=c[x];return y;}
}A,B;
struct op{int k,f,g;};
int a[N],b[N],p[N],q[N],f[N],g[N],h[N],L[N],R[N],O[N];
vector<int>e[N];vector<op>o[N];__int128 C;
inline int mg(int x,int y){if(!x||!y)return x|y;if(a[x]<a[y])swap(x,y);q[y]=p[x];p[x]=y;return x;}
inline int mh(int x){return q[x]?mg(mg(x,q[x]),mh(q[q[x]])):x;}
void dfs(int x,int v){
    O[L[x]=++l]=x;a[x]+=v;
    int&F=f[x]=x,&G=g[x]=1,&H=h[x]=a[x];
    for(int y:e[x])dfs(y,a[x]),F=mg(F,f[y]),G+=g[y],H+=h[y];
    for(;(C+H-a[F])*G<(C+H)*(G-1);F=mh(p[F]))--G,H-=a[F];
    v=(C+H)%mo*b[G]%mo;
    o[L[x]].push_back({F,1,v});
    o[l+1].push_back({F,-1,v});
    R[x]=l;m+=v-a[x];
}
signed main(){
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    n=read();C=n*read();
    f(i,1,n)e[read()].push_back(i);
    f(i,1,n)a[i]=read();
    f(i,1,n)b[i]=i<2?1:(mo-mo/i)*b[mo%i]%mo;
    dfs(e[0][0],0);
    f(i,1,n)b[i]=a[i];
    sort(b+1,b+n+1);
    f(i,1,n)p[i]=b-lower_bound(b+1,b+n+1,a[i])+n+1;
    f(i,1,n){
        for(op e:o[i])A.add(p[e.k],e.f),B.add(p[e.k],-e.f*e.g);
        s=O[i];f[s]=m+a[s]*A.sum(p[s])+B.sum(p[s]);
    }
    f(i,1,n)write((f[i]%mo+mo)%mo),putchar(10);
    return 0;
}