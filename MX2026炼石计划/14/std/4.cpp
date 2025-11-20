#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;
struct FastMod{typedef unsigned long long ull;typedef __uint128_t lll;
ull b,m;void init(ull b){this->b=b,m=ull((lll(1)<<64)/b);}ull operator()
(ull a){ull q=(ull)((lll(m)*a)>>64),r=a-q*b;return r>=b?r-b:r;}}M;
inline int read()
{
    char ch=getchar(); int nega=1; while(!isdigit(ch)) {if(ch=='-') nega=-1; ch=getchar();}
    int ans=0; while(isdigit(ch)) {ans=ans*10+ch-48;ch=getchar();}
    if(nega==-1) return -ans;
    return ans;
}
void print(vector<int> x){for(int i=0;i<(int)x.size();i++) printf("%d%c",x[i]," \n"[i==(int)x.size()-1]);}
inline int mul(int x,int y) {return M((unsigned long long)x*y);}
inline int mul(int x,int y,int z) {return mul(mul(x,y),z);}
#define inc(x,y) x=add(x,y)
#define dec(x,y) x=sub(x,y)
#define N 100005
int n,m,mod;
inline int add(int x,int y) {return x+y>=mod?x+y-mod:x+y;}
inline int add(int x,int y,int z) {return add(add(x,y),z);}
inline int sub(int x,int y) {return x-y<0?x-y+mod:x-y;}
map<int,int> f[105][105];
int fac[N],inv[N],ifac[N],pw2[N];
void init()
{
    pw2[0]=1; for(int i=1;i<N;i++) pw2[i]=mul(pw2[i-1],2);
    fac[0]=1; for(int i=1;i<N;i++) fac[i]=mul(fac[i-1],i);
    inv[0]=inv[1]=1; for(int i=2;i<N;i++) inv[i]=mul(mod-mod/i,inv[mod%i]);
    ifac[0]=1; for(int i=1;i<N;i++) ifac[i]=mul(ifac[i-1],inv[i]);
}
int C(int x,int y)
{
    int ans=ifac[y];
    for(int i=0;i<y;i++) ans=mul(ans,x-i);
    return ans;
}
int solve(int i,int j,int k)
{
    if(i<=0) return 0;
    if(k==0)
    {
        if(j) return 0;
        return __builtin_popcount(i)==1;
    }
    if(f[j][k].find(i)!=f[j][k].end()) return f[j][k][i];
    int ans=0;
    for(int tj=0;tj<=k-j;tj++)
    {
        if((i+j-tj)&1) continue;
        int ti=(i+j-tj)/2;
        int tmp=solve(ti,tj,k-j);
        int coef=mul(C(ti,j),pw2[j]);
        ans=add(ans,mul(tmp,coef));
    }
    return f[j][k][i]=ans;
}
signed main()
{
    FILE("num");
    n = read(), m = read(), mod = read();
    M.init(mod);
    init();
    int ans=0;
    for(int j=0;j<=m;j++)
    {
        if((n-j+1)&1) continue;
        int i=(n-j+1)/2;
        ans=add(ans,solve(i,j,m));
    }
    cout<<ans<<endl;
    return 0;
}