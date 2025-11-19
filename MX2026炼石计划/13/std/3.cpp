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
const int N=5050,mo=998244353;
inline void Add(int&x,int y){x=(x+y)%mo;}
int c[N],f[N][N][2],F[N][3],H[N][9];
vector<int>q[N];
void dfs(int x,int fa){
    for(int y:q[x])if(y!=fa)dfs(y,x);
    int&X=c[x]=F[0][0]=1;
    for(int y:q[x])if(y!=fa){
        auto&G=f[y];int&Y=c[y];
        f(i,0,X)f(j,0,Y)f(p,0,2)f(q,0,1)Add(H[i+j][p+q],F[i][p]*G[j][q]);
        X+=Y;
        f(i,0,X)f(p,0,2)F[i][p]=H[i][p],H[i][p]=0;
    }
    g(i,X,0){
        Add(f[x][i+1][0],F[i][0]+F[i][1]*2+F[i][2]*2);
        Add(f[x][i][1],F[i][0]+F[i][1]);
        F[i][0]=F[i][1]=F[i][2]=0;
    }
}
signed main(){
    freopen("fox.in","r",stdin);
    freopen("fox.out","w",stdout);
    n=read();
    f(i,2,n){
        s=read();l=read();
        q[s].push_back(l);
        q[l].push_back(s);
    }
    dfs(1,0);s=n%2?mo-1:1;
    f(i,1,n)s=s*(mo-i)%mo,m=(m+f[1][i][0]*s)%mo;
    write(m);
    return 0;
}