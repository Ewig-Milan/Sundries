#include <bits/stdc++.h>
using namespace std;

const int N=200005;
const int Mod=1000000007;

int du[N], n;
long long jc[N], c[N];

long long ksm(int x,int y)
{
    if(!y)
        return 1;

    long long t=ksm(x,y/2);
    if(y%2==0)
        return t*t%Mod;
    return t*t%Mod*x%Mod;
}

int inv(int x)
{
    return ksm(x,Mod-2);
}

int dist(int x,int y)
{
    if(x<y)
        return y-x;
    return y-x+n;
}

void update(int x,int y)
{
    for(int i=x;i<=n;i+=i&-i)
        (c[i] *= y) %= Mod;
}

long long query(int x)
{
    long long ans=1;
    for(int i=x;i;i-=i&-i)
        (ans *= c[i]) %= Mod;
    return ans;
}

void MUL(int l,int r,int v)
{
    if(l>r)
        return;

    update(l,v), update(r+1,inv(v));
}

void mul(int a,int b,int c)
{
    if(a<b)
        MUL(a+1,b-1,c);
    else
    {
        MUL(a+1,n,c);
        MUL(1,b-1,c);
    }
}

int main()
{
    freopen("polygon.in","r",stdin);
    freopen("polygon.out","w",stdout);
    int q;
    cin >> n >> q;
    jc[0]=1;
    for(int i=1;i<=n;i++)
        c[i]=1, jc[i]=jc[i-1]*i%Mod;

    for(int i=1;i<=n-3;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        du[a]++, du[b]++;
        mul(a,b,dist(b,a)-1);
        mul(b,a,dist(a,b)-1);
    }

    for(int i=1;i<=q;i++)
    {
        int op;
        scanf("%d",&op);
        if(op==1)
        {
            int a,b,c,d;
            scanf("%d %d %d %d",&a,&b,&c,&d);
            du[a]--, du[b]--, du[c]++, du[d]++;
            mul(a,b,inv(dist(b,a)-1));
            mul(b,a,inv(dist(a,b)-1));
            mul(c,d,dist(d,c)-1);
            mul(d,c,dist(c,d)-1);
        }
        else
        {
            int p;
            scanf("%d",&p);
            printf("%d %lld\n",n-3-du[p],jc[n-3-du[p]]*inv(query(p))%Mod);
        }
    }
    return 0;
}