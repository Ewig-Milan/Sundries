#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define mk make_pair
#define lowbit(x) (x&(-x))
#define pb emplace_back
#define pr pair<int,int>
#define let const auto
const int N=2e5+5,M=1e6+5;
ll read(){
    ll x=0,f=1; char c=getchar();
    while(('0'>c||c>'9')&&c!='-') c=getchar();
    if(c=='-') f=0,c=getchar();
    while('0'<=c&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?x:-x;
}
int n,a[N],pos[N],nxt[N],m,at[N];

int sum[(1<<21)|5];
#define ls (k<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
void build(int k,int l,int r){
    if(l==r) return at[l]=k,void();
    build(ls,l,mid),build(rs,mid+1,r);
}
void modify(int l,int r,int u,int k,int v){
    if(l==r) return sum[k]=v,void();
    u<=mid?modify(l,mid,u,ls,v):modify(mid+1,r,u,rs,v);
    sum[k]=sum[ls]+sum[rs];
}
pr binary(int l,int r,int k,int kth){
    if(l==r) return {pos[l],kth};
    return sum[ls]>=kth?binary(l,mid,ls,kth):binary(mid+1,r,rs,kth-sum[ls]);
}

void add(int l,int r){
    for(int i=l; i<=r; )
        modify(1,n,a[i],1,min(r+1,nxt[i])-i),i=nxt[i];
}
int get(int x){
    pr o=binary(1,n,1,x);
    return a[o.first+o.second-1];
}
vector <pr> qry[N];
int ans[M];
int stk[N],tp;
int main(){
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);
    n=read(),m=read();
    for(int i=1; i<=n; i++) a[i]=read(),pos[a[i]]=i;
    for(int i=n; i; i--){
        while(tp&&a[stk[tp]]<a[i]) tp--;
        if(!tp) nxt[i]=n+1;
        else nxt[i]=stk[tp];
        stk[++tp]=i;
    }
    build(1,1,n);
    add(1,n/2),add(n/2+1,n);
    for(int i=1; i<=m; i++){
        int t=read(),pos=read();
        t=min(t,n);
        if(t==0) ans[i]=a[pos];
        else qry[t].pb(pos,i);
    }
    for(int i=1; i<=n; i++){
        for(auto &[x,id]:qry[i]) ans[id]=get(x);
        pr o=binary(1,n,1,n/2);
        int len=sum[at[a[o.first]]];
        int cur=o.second+o.first;
        modify(1,n,a[o.first],1,o.second);
        while(cur-o.first<len){
            int npos=nxt[cur];
            modify(1,n,a[cur],1,min(npos,o.first+len)-cur);
            cur=npos;
        }
    }
    for(int i=1; i<=m; i++) printf("%d\n",ans[i]);
    return 0;
}