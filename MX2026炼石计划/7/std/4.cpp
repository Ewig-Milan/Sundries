#include<bits/stdc++.h> 
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;
typedef long long ll;
typedef long double db;
const ll inf=1e18,N=201001,MAX=2001;
const db PI=acosl(-1);
inline void read(ll &ret)
{
    ret=0;char c=getchar();bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,a[N],x,y,dep[N<<1],f[N<<1][21],deep[N<<1];
vector<pair<ll,ll> >v[N<<1];
inline void dfs(ll ver,ll fa)
{
    deep[ver]=deep[fa]+1;
    f[ver][0]=fa;
    for(int i=1;i<=20;i++)
        f[ver][i]=f[f[ver][i-1]][i-1];
    for(int i=0;i<v[ver].size();i++)
    {
        ll to=v[ver][i].first,dis=v[ver][i].second;
        if(to==fa)
            continue;
        dep[to]=dep[ver]+dis;
        dfs(to,ver);
    }
    return;
}
struct node
{
    ll x,y,dis;
}seg[N<<3];
inline ll lca(ll p,ll q)
{
    if(deep[p]<deep[q])
        swap(p,q);
    ll d=deep[p]-deep[q];
    for(int i=0;i<=20;i++)
        if((1<<i)&d)
            p=f[p][i];
    if(p==q)
        return p;
    for(int i=20;i+1;i--)
    {
        if(f[p][i]!=f[q][i])
        {
            p=f[p][i];
            q=f[q][i];
        }
    }
    return f[p][0];
}
inline ll dis(ll x,ll y)
{
    return dep[x]+dep[y]-(dep[lca(x,y)]<<1);
}
inline bool operator <(node a,node b)
{
    return a.dis<b.dis;
}
inline node operator +(node a,node b)
{
    return max({a,b,node{a.x,b.x,dis(a.x,b.x)},node{a.x,b.y,dis(a.x,b.y)},node{a.y,b.x,dis(a.y,b.x)},node{a.y,b.y,dis(a.y,b.y)}});
}
inline void build(ll pos,ll l,ll r)
{
    if(l==r)
    {
        seg[pos].x=seg[pos].y=l;
        seg[pos].dis=dis(l,l);
        return;
    }
    else
    {
        ll mid=l+r>>1;
        build(pos<<1,l,mid);
        build(pos<<1|1,mid+1,r);
        seg[pos]=seg[pos<<1]+seg[pos<<1|1];
    }
    return;
}
inline void update(ll pos,ll l,ll r,ll p)
{
    if(l>p||r<p)
        return;
    else if(l==r)
    {
        seg[pos].x=seg[pos].y=l;
        return;	
    }
    ll mid=l+r>>1;
    update(pos<<1,l,mid,p);
    update(pos<<1|1,mid+1,r,p);
    seg[pos]=seg[pos<<1]+seg[pos<<1|1];
    return;
}
signed main()
{
    FILE("immortality");
    read(n);
    for(int i=1;i<=n;i++)
        read(a[i]),v[i].push_back(make_pair(i+n,a[i])),v[i+n].push_back(make_pair(i,a[i]));
    for(int i=1;i<n;i++)
    {
        read(x);
        read(y);
        v[x].push_back(make_pair(y,1));
        v[y].push_back(make_pair(x,1));
    }
    dfs(1,0);
    build(1,1,n<<1);
    ll m;
    read(m);
    for(int i=1;i<=m;i++)
    {
        ll v,val;
        read(v);
        read(val);
        a[v]=val;
        dep[v+n]=dep[v]+val;
        update(1,1,n<<1,v+n);
        ll x=seg[1].x,y=seg[1].y;
        ll d=dis(x,y);
        if(x>n&&a[x-n]*2>=d)
            printf("%lld\n",a[x-n]);
        else if(y>n&&a[y-n]*2>=d)
            printf("%lld\n",a[y-n]);
        else
            printf("%lld\n",(d+1)>>1);
    }
    exit(0);
}