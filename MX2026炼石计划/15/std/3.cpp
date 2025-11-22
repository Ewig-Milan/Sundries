#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
using namespace std;
typedef long long ll;
typedef pair<int,int> Pair;
const int N=1e5+5;
const ll T=3e7;
#define F first
#define S second
Pair seq[N];
ll a[N],b[N],p[N],cnt[30000005];
int n;
ll ans,tot,A,B,D;
int cmp(Pair a, Pair b){ return a.S-a.F>b.S-b.F; }
int main(){
    FILE("monitor");
    scanf("%d",&n);
    for (int i=1; i<=n; i++){
        scanf("%d%d",&seq[i].F,&seq[i].S);
        p[0]+=seq[i].F; tot+=seq[i].S;
    }
    sort(seq+1,seq+1+n,cmp);
    for (int i=1; i<=n; i++){
        a[i]=seq[i].F,b[i]=seq[i].S;
        p[i]=p[i-1]-a[i]+b[i];
        A+=a[i],B+=b[i];
    }
    D=min(T,tot);
    for (int i=1; i<=D; i++) cnt[((A+i-1)/i)*i-A]++;
    for (int i=1; i<=n; i++){
        if (p[i-1]>A+T) break;
        for (int j=p[i-1]-A+1; j<=p[i]-A && j<=T; j++) ans+=1ll*i*cnt[j];
    }
    for (ll l=D+1,r; l<=tot; l=r+1){
        ll L=l,R=tot;
        while (L<=R){
            ll mid=(L+R)>>1;
            if ((A+l-1)/l==(A+mid-1)/mid) r=mid,L=mid+1;
            else R=mid-1;
        }
        ll k=(A+l-1)/l;
        ll l0=max(l,(A+k-1)/k),r0=min(r,B/k);
        if (l0<=r0){
            for (int i=1; i<=n; i++){
                if (p[i]/k>=l0) ans+=1ll*i*(min(p[i]/k,r0)-l0+1);
                if (p[i-1]/k>=l0) ans-=1ll*i*(min(p[i-1]/k,r0)-l0+1);
            }
        }
    }
    printf("%lld\n",ans);
}