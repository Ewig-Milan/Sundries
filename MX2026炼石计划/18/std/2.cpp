#include<bits/stdc++.h>
using namespace std;
const int BS=1<<20;
char buf[BS],*P1,*P2;
inline char gc(){
    if(P1==P2)P2=(P1=buf)+fread(buf,1,BS,stdin);
    return P1==P2?EOF:*(P1++);
}
inline int in(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}
    while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=gc();
    return x*f;
}
const int N=2e5+5;
int n,a[N];
int f[N],g[N];
int dp(int x,int val){
    int ls=x<<1,rs=x<<1|1;
    if(ls>n)ls=0;if(rs>n)rs=0;
    if(val<a[ls]&&val<a[rs])return x;
    if(a[ls]<val&&a[ls]<a[rs])return dp(ls,val);
    if(val<a[ls])return min(dp(ls,val),dp(rs,val));
    if(f[ls]<g[ls])return dp(rs,val);
    return dp(ls,val);
}
int main(){
    freopen("swap.in","r",stdin);
    freopen("swap.out","w",stdout);
    n=in();
    a[0]=n+1;
    for(int i=1;i<=n;i++)a[i]=in();
    for(int i=n;i>=1;i--){
        f[i]=dp(i,a[i]);
        if(i%2==0)g[i]=dp(i+1,a[i]);
    }
    for(int i=1;i<=n;i++){
        int ls=i<<1,rs=i<<1|1;
        if(ls>n)ls=0;if(rs>n)rs=0;
        if(a[i]<a[ls]&&a[i]<a[rs])continue;
        if(a[ls]<a[rs]&&a[ls]<a[i]){
            swap(a[i],a[ls]);
            continue;
        }
        swap(a[rs],a[i]);
        if(a[ls]>a[rs])swap(a[ls],a[rs]);
        if(dp(ls,a[ls])>dp(rs,a[ls]))swap(a[ls],a[rs]);
    }
    for(int i=1;i<=n;i++)printf("%d ",a[i]);
    return 0;
}