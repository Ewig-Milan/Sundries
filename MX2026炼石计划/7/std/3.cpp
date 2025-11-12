#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#define int long long
#define N 1000005
using namespace std;
const int mod=998244353,mod1=998244352,inv2=(mod+1)/2;
int n,f[N],sum[N],g[N],sumg[N],pw[N],pw1[N];
inline int qpow(int a,int b,int p)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=1ll*res*a%p;
        b>>=1;
        a=1ll*a*a%p; 
    }
    return res;
}
inline int inv(int x)
{
    return qpow(x,mod-2,mod);
}
inline int calc(int j)
{
    return 1ll*inv(1-qpow(inv2,pw1[j+1],mod))*qpow(inv2,pw1[j],mod)%mod*(2+mod-qpow(inv2,pw1[j]-1,mod))%mod;
}
main()
{
    FILE("forest");
    pw[0]=1;
    pw1[0]=1;
    for(int i=1;i<N;i++)
    {
        pw[i]=pw[i-1]<<1;
        pw[i]-=pw[i]>=mod?mod:0;
        pw1[i]=pw1[i-1]<<1;
        pw1[i]-=pw1[i]>=mod1?mod1:0;
    }
    ios::sync_with_stdio(false);
    cin>>n;
    f[0]=1;
    sum[0]=1;
    g[0]=1ll*f[0]*calc(0)%mod;
    sumg[0]=g[0];
    g[0]+=mod,g[0]%=mod;
    for(int i=1;i<=n;i++)
    {
        f[i]=1ll*(qpow(2,pw1[i],mod)-1)*(sum[i-1]+1)%mod;
        f[i]-=1ll*qpow(2,pw1[i]-1,mod)*(1-qpow(inv2,pw1[i],mod))%mod*sumg[i-1]%mod;
        f[i]%=mod;
        f[i]+=mod;
        f[i]%=mod;
        g[i]=f[i]*calc(i)%mod;
        g[i]+=mod,g[i]%=mod;
        sum[i]=(sum[i-1]+f[i])%mod;
        sumg[i]=(sumg[i-1]+g[i])%mod;
    }
    cout<<sum[n-1]<<endl;
}