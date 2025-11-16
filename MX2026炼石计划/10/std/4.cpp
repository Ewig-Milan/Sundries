#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;
typedef unsigned long long ull;
const int N=2001;
const short dt[6][2]={{5,2},{3,4},{4,0},{1,5},{2,1},{0,3}};
int n,m,k,a0[N][N],a1[N][N],a2[N][N],g[N][N];
mt19937 rnd(random_device{}());
char buf[1<<22],*p1=buf,*p2=buf;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1==p2)?EOF:*p1++)
int read(){
    char ch=gc;int res=0;
    while(!isdigit(ch)) ch=gc;
    while(isdigit(ch)) res=res*10+ch-'0',ch=gc;
    return res;
}
struct str
{
    ull b[N],c[N],h[N][N];
    set<int> w;
    void solve(int a1[N][N],int a2[N][N])
    {
        for(int i=1;i<=n;++i) b[i]=rnd();
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j) h[a2[i][j]][g[i][j]]+=b[a1[i][j]];
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j) c[a1[i][j]]+=h[a2[i][j]][g[i][j]];
        }
        ull p=0;
        for(int i=1;i<=n;++i) p+=b[i]*k;
        for(int i=1;i<=n;++i)
        {
            if(c[i]==p+(n-k)*b[i]) w.insert(i);
        }
    }
    int sum(int x)
    {
        set<int>::iterator p=w.lower_bound(x+1);
        if(p!=w.end()) return *p;
        p=w.lower_bound(1);
        if(p!=w.end()) return *p;
        return -1;
    }
}S[6];
int main()
{
    FILE("matrix");
    n=read();k=read();m=read();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            a0[i][j]=read();
            a1[i][j]=i;
            a2[i][j]=j;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            g[i][j]=read();
        }
    }
    S[0].solve(a1,a2);
    S[1].solve(a2,a1);
    S[2].solve(a0,a2);
    S[3].solve(a2,a0);
    S[4].solve(a0,a1);
    S[5].solve(a1,a0);
    int t=0,t0=0,t1=0,t2=0;
    for(int i=1;i<=m;++i)
    {
        char z=gc;
        while(!isalpha(z)) z=gc;
        if(z=='I')
        {
            t=dt[t][0];
            swap(t0,t2);
        }
        else if(z=='C')
        {
            t=dt[t][1];
            swap(t0,t1);
        }
        else if(z=='Q')
        {
            int x=S[t].sum((t1%n+n)%n);
            if(x==-1) puts("-1");
            else printf("%d\n",((x-t1-1)%n+n)%n+1);
        }
        else
        {
            int x=read();
            if(z=='Y') t1-=x;
            else if(z=='X') t2-=x;
        }
    }
    return 0;
}