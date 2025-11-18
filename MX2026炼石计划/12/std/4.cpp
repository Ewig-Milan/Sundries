#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int BS=1<<20|5;
char buf[BS],*P1,*P2;
inline char gc(){
    if(P1==P2)P2=(P1=buf)+fread(buf,1,BS,stdin);
    return P1==P2?EOF:*(P1++);
}
inline int in(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=gc();
    return x*f;
}
const int N=1e5+5,M=5005;
const ll inf=1e18;
int n,l,r,a[N];
int mark[N],mark1[N];
int b[M],m;
int p[M][M];
ll f[M][M],ans;
void solve(int L,int R){
    b[m=0]=L;
    for(int i=L+1;i<R;i++){
        if(mark[i])b[++m]=i;
    }
    b[m+1]=R;
    for(int i=1;i<=m;i++)f[i][i]=b[i+1]-b[i-1]-1,p[i][i]=i;
    for(int d=2;d<=m;d++){
        for(int l=1,r=d;r<=m;l++,r++){
            f[l][r]=inf;
            for(int k=p[l][r-1];k<=p[l+1][r];k++){
                int val=f[l][k-1]+f[k+1][r];
                if(val<f[l][r]){
                    f[l][r]=val;
                    p[l][r]=k;
                }
            }
            f[l][r]+=b[r+1]-b[l-1]-1;
        }
    }
    ans+=f[1][m];
}
int lp[N],rp[N];
int main(){
    freopen("bst.in","r",stdin);
    freopen("bst.out","w",stdout);
    n=in();
    for(int i=1;i<=n;i++)a[i]=in();
    l=in(),r=in();
    for(int i=1;i<=n;i++)lp[i]=i-1,rp[i]=i+1;
    for(int i=n;i>=1;i--){
        if(i<l||i>r)ans+=rp[a[i]]-lp[a[i]]-1;
        rp[lp[a[i]]]=rp[a[i]],lp[rp[a[i]]]=lp[a[i]];
    }
    for(int i=1;i<l;i++)mark1[a[i]]=1;
    mark1[n+1]=1;
    for(int i=l;i<=r;i++)mark[a[i]]=1;
    for(int i=0,j;i<=n;i=j){
        for(j=i+1;!mark1[j];j++);
        solve(i,j);
    }
    cout<<ans<<endl;
    return 0;
}