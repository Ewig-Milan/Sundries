#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int N=2e5;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;'0'>ch||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(;'0'<=ch&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
struct op{int x,d;};set<int>o,p[N],q[N],r[N];set<op>Q;
bool operator<(op a,op b){return a.d==b.d?a.x<b.x:a.d<b.d;}
#define sz(x)r[x].size()
#define ADD(x,y,z)z[x].insert(y);z[y].insert(x);
#define DEL(x,y,z)z[x].erase(y);z[y].erase(x);
void add(int x,int y){ADD(x,y,q);ADD(x,y,r);}
void del(int x,int y){DEL(x,y,p);DEL(x,y,q);DEL(x,y,r);}
int ck(int x){
    Q.insert({x,sz(x)});if(sz(x)!=1)return 0;
    int y=*r[x].begin();Q.insert({y,sz(y)});
    q[y].erase(x);p[y].insert(x);return y;
}
int get(){
    st:op e=*--Q.end();Q.erase(e);
    if(sz(e.x)==e.d&&p[e.x].size())return e.x;
    goto st;
}
int F(int x,int z=-1){
    int y;ck(x);
    if(z<0)y=*p[x].begin();
    else if(!z)y=*q[x].begin();
    else y=*r[x].begin();
    if(y==z)y=*--r[x].end();return y;
}
int c[N],e[N],x,y,z;
void kil(int x,int y,int z){s=F(x);l=F(y);del(s,x);del(l,y);ck(x);ck(y);c[e[s]]=c[e[l]]=z+1;}
int Go(int x,int z){
    int A=F(x),B=x,C=F(B,0),D=F(C,B);
    if(p[D].size())return kil(B,D,z),0;
    if(sz(B)+sz(D)>z+1)return 1;
    c[e[A]]=c[e[D]]=z+1;del(A,B);
    if(sz(B)<sz(D))swap(B,D),e[B]=e[D];
    del(B,C);o=r[D];
    for(int x:o)del(D,x),add(B,x),ck(x);
    ck(B);ck(C);return 0;
}
inline void doing(){
    n=read()*2;m=s=l=x=y=z=0;
    f(i,0,n)o=p[i]=q[i]=r[i]={};Q.clear();
    f(i,2,n)add(read(),read());
    f(i,1,n)ck(e[i]=i);
    g(i,n/2,1){
        x=z?z:get();y=x==(y=get())?get():y;ck(x);ck(y);
        if(sz(x)==i&&(z=x)||Go(x,i)&&Go(y,i))kil(x,y,i);
    }--c[e[l]];
    f(i,1,n)printf("%lld ",c[i]);
    putchar('\n');
}
signed main(){
    freopen("chengyan.in","r",stdin);
    freopen("chengyan.out","w",stdout);
    int t;
    cin>>t;
    while(t--)doing(); 
    return 0;
}