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
const int N=2e5,M=1e7,mo=1e9+7;
inline int ksm(int x,int p=mo-2,int y=1){for(;p;p/=2,x=x*x%mo)if(p&1)y=x*y%mo;return y;}
int a[N],b[M],c[M],f[M],p,q;
inline int sz(int x){int t=__lg(n)-__lg(x);return x<=n?((1ll)<<t)-1+min(n+1,(x+1)<<t)-min(n+1,x<<t):0;}
signed main(){
    freopen("snake.in","r",stdin);
    freopen("snake.out","w",stdout);
    n=read();m=read();b[1]=s=p=q=1;
    f(i,1,m)for(l=a[i]=read();l/=2;)f(t,0,1)b[++s]=l*2+t;
    sort(b,b+s+1);s=unique(b,b+s+1)-b-1;l=0;
    f(i,1,s){
        for(;b[l]<b[i]/2;)++l;
        c[i]=sz(b[i]);f[i]=l;
    }
    if(n>N)p=698611116;
    else f(i,1,n)p=p*i%mo;
    for(int x=n;x/=2;){
        int t=__lg(x),l=1<<t,r=(2<<t)-1;
        q=q*ksm(sz(l),x-l)%mo*sz(x)%mo*ksm(sz(r),r-x)%mo;
    }
    f(i,0,m){
        int x=lower_bound(b,b+s+1,a[i])-b,y=c[x];
        if(y)p=p*y%mo,q=q*(n--)%mo;
        for(c[x]=0;c[x=f[x]];q=q*(c[x]-=y)%mo)p=p*c[x]%mo;
        write(p*ksm(q)%mo);putchar('\n');
    }
    return 0;
}