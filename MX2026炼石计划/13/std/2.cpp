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
const int N=3e5;
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
set<int>a;int x,y,z,o;
inline int ask(int x,int y){return a.find(x*N+y)!=a.end();}
signed main(){
    freopen("well.in","r",stdin);
    freopen("well.out","w",stdout);
    n=read();m=read();
    f(_,1,m){
        s-=z=read();x=read();y=read();o=x*N+y;
        if(z<0)a.erase(o);else a.insert(o);
        f(t,0,3)l+=z*ask(x+dx[t],y+dy[t]);
        if(ask(x+1,y)&&ask(x,y+1)&&ask(x+1,y+1))l-=z;
        if(ask(x-1,y)&&ask(x,y+1)&&ask(x-1,y+1))l-=z;
        if(ask(x+1,y)&&ask(x,y-1)&&ask(x+1,y-1))l-=z;
        if(ask(x-1,y)&&ask(x,y-1)&&ask(x-1,y-1))l-=z;
        write(s+l+!!s);putchar('\n');
    }
    return 0;
}