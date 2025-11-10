#include<bits/stdc++.h>
#define FILE(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout);
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
const int N=5e5,B=500;
int a[N],b[N],c[N],f[N],g[N],sk[N],rk[N],x,y,z;
signed main(){
    FILE("tuyuan");
    n=read();s=read();
    f(i,1,n)rk[sk[i]=i/B+1]=i;
    f(_,1,n){
        x=read();y=read()+s*l;
        if(x<2){
            c[++m]=y%26;
            while(z&&c[z+1]!=c[m])z=f[z];
            f[m]=z+=(c[z+1]==c[m]&&m>1);
            int L=rk[sk[m]-1]+1;
            g[m]=f[m]<L?f[m]:g[f[m]];
            for(x=m;x;x=g[x])++b[x];
        }else{
            y=y%m+1;
            int L=rk[sk[y]-1]+1,R=rk[sk[y]];
            g(i,R,L){
                a[i]+=b[i];
                if(L<=f[i])b[f[i]]+=b[i];
                b[i]=0;
            }
            write(l=a[y]);putchar('\n');
        }
    }
    return 0;
}