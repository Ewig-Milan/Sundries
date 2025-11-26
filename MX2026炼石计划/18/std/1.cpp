#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N=5e5+5;
int n,m,a[N],fir[N],las[N];
int stk[N],tp;
void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]),las[a[i]]=i;
    for(int i=n; i; i--) fir[a[i]]=i;
    vector <tuple <int,int,int> > ans;
    tp=0;
    for(int i=1; i<=n; i++){
        if(fir[a[i]]==i) 
            ans.emplace_back(a[i],i,las[a[i]]),stk[++tp]=a[i];
        if(a[i]!=stk[tp]){
            puts("-1");
            return;
        }
        if(las[a[i]]==i) tp--;
    }
    printf("%d\n",(int)ans.size());
    for(auto [c,x,y]: ans) printf("%d %d %d\n",c,x,y);
}
int main(){
    freopen("paint.in","r",stdin);
    freopen("paint.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}