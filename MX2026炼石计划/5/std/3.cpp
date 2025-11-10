#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const int N=202020,inf=2e9;
struct Flametail{
    signed c[N][5],nxt[N],f[N][33][5];int g[N][33][5],w[N],n,z;
    queue<int>Q;vector<int>q;
    inline int add(){
        int now=0,x=getchar()-48;
        for(;0>x||x>9;x=getchar()-48);
        for(;0<=x&&x<=9;x=getchar()-48){
            if(!c[now][x])c[now][x]=++n;
            now=c[now][x];
        }
        return now;
    }
    inline void work(){
        int x,y;
        for(Q.push(0);Q.size();Q.pop()){
            q.push_back(x=Q.front());
            f(i,0,4){
                if(y=c[x][i]){
                    if(x)nxt[y]=c[nxt[x]][i];
                    Q.push(y);
                }else{
                    c[x][i]=c[nxt[x]][i];
                }
            }
        }
        reverse(q.begin(),q.end());
    }
    inline void F(int k,int r){
        f(x,0,n)f(i,0,k-1)f[x][0][i]=c[x][i];
        f(t,1,r)f(x,0,n)f(i,0,k-1){
            z=x;
            f(j,0,k-1)z=f[z][t-1][(i+j)%k];
            f[x][t][i]=z;
        }
    }
    inline void G(int k,int r){
        g(t,r,1)f(x,0,n)f(i,0,k-1){
            z=x;
            f(j,0,k-1){
                g[z][t-1][(i+j)%k]+=g[x][t][i];
                z=f[z][t-1][(i+j)%k];
            }
        }
        f(x,0,n)f(i,0,k-1)w[f[x][0][i]]+=g[x][0][i];
    }
    inline void krow(){for(int x:q)w[nxt[x]]+=w[x];}
}AC;
int a[N],L[N],R[N],k,t,r;
void add(int l,int r,int L,int R,int c,int t){
    if(r<L||R<l)return;
    if(l<=L&&R<=r){
        ++AC.g[s][t][c];s=AC.f[s][t][c];
        return;
    }
    int p=(R-L+1)/k,x=L;
    f(i,0,k-1)add(l,r,x,x+p-1,(c+i)%k,t-1),x+=p;
}
signed main(){
    freopen("yuzhen.in","r",stdin);
    freopen("yuzhen.out","w",stdout); 
    cin>>n>>m>>k;
    for(t=1;t<inf;t*=k)++r;
    f(i,1,n)scanf("%lld %lld",&L[i],&R[i]);
    f(i,1,m)a[i]=AC.add();
    AC.work();AC.F(k,r);
    f(i,1,n)add(L[i],R[i],0,t-1,0,r);
    AC.G(k,r);AC.krow();
    f(i,1,m)printf("%lld\n",AC.w[a[i]]);
    return 0;
}