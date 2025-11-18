#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod=1e9+7;
ll fac[100005],ifac[100005];
int n,k,q;
ll ksm(ll a,ll m,ll p){
    ll ans=1;
    while(m){
        if(m&1)ans=ans*a%p;
        a=a*a%p;
        m>>=1;
    }
    return ans;
}
ll C(int n,int m){
    if(n<0||m<0||n<m)return 0;
    return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
ll f[100005][335],tmp[335];
int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout); 
    scanf("%d%d%d",&n,&k,&q);
    fac[0]=1;
    for(int i=1;i<=n+1;i++)fac[i]=fac[i-1]*i%mod;
    ifac[n+1]=ksm(fac[n+1],mod-2,mod);
    for(int i=n+1;i;i--)ifac[i-1]=ifac[i]*i%mod;
    if((ll)k*k>n){
        while(q--){
            int x,r;scanf("%d%d",&x,&r);
            ll ans=0;
            for(int i=r;i<=n;i+=k)ans=(ans+C(i,x))%mod;
            printf("%lld\n",ans);
        }
        return 0;
    }
    for(int i=0;i<k;i++)f[0][i]=n/k;
    ll ivk=ksm(k,mod-2,mod);
    for(int i=1;i<=n;i++){
        ll s1=0;
        for(int j=1;j<k;j++)tmp[j]=f[i-1][j-1],tmp[j]=(tmp[j]+tmp[j-1])%mod,s1=(s1+tmp[j])%mod;
        f[i][0]=(C(n,i+1)-s1+mod)*ivk%mod;
        for(int j=1;j<k;j++)f[i][j]=(f[i][0]+tmp[j])%mod;
    }
    while(q--){
        int x,r;scanf("%d%d",&x,&r);
        printf("%lld\n",(f[x][r]+(r==0?C(n,x):0))%mod);
    }
    return 0;
}