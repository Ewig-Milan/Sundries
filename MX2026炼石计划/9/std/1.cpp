#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#define ll long long
using namespace std;
const int N=1e5+5,mod=998244353; 
ll n,c[N];
int cnt,a[]={2,3,5,7,11,13,17,19,23,29},ans;
ll qpow(ll x,ll n,ll mod){
    ll ans=1;
    for(;n;n>>=1,x=(__int128)x*x%mod)
        if(n&1) ans=(__int128)ans*x%mod;
    return ans; 
}
bool MR(ll p){
    if(p==1) return 0;
    for(int i=0;i<10;i++){
        if(a[i]==p) return 1;
        if(qpow(a[i],p-1,p)!=1) return 0;
        for(ll j=p-1,v;j%2==0;){
            if((v=qpow(a[i],j/=2,p))==p-1) break;
            if(v!=1) return 0;
        }
    }
    return 1;
}
void dfs(int x,int num,int v){
    if(x>cnt){
        ans=(ans+1ll*(qpow(2,num,mod)-1)*v%mod)%mod;
        return ;
    }
    for(int i=0;i<3;i++)
        dfs(x+1,1ll*num*(c[x]+1-i)%mod,i==1?-2ll*v%mod:v);
}
signed main(){
    FILE("set");
    scanf("%lld",&n);
    for(int i=2;1ll*i*i*i<=n;i++) if(n%i==0){
        int e=0;
        while(n%i==0) n/=i,e++;
        c[++cnt]=e;
    }
    if(n>1){
        if(MR(n)) c[++cnt]=1;
        else if((int)sqrt(n)*(int)sqrt(n)==n) c[++cnt]=2;
        else c[++cnt]=1,c[++cnt]=1;
    }
    dfs(1,1,1),printf("%d\n",(ans+mod)%mod);
    return 0;
}