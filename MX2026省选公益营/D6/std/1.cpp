#include<stdio.h>
#include<algorithm>
typedef unsigned int uint;
typedef unsigned long long ull;
constexpr uint mod{998244353};
constexpr uint power(uint x,uint y) {
    uint s{1};
    while(y>0) {
        if(y&1) {
            s=ull(s)*x%mod;
        }
        x=ull(x)*x%mod;
        y>>=1;
    }
    return s;
}
constexpr uint plus(const uint &x,const uint &y) {
    if(x+y>=mod) {
        return x+y-mod;
    }
    return x+y;
}
constexpr uint minus(const uint &x,const uint &y) {
    if(x<y) {
        return x-y+mod;
    }
    return x-y;
}
constexpr int N{500};
uint C[N+5][N+5];
uint a[N+5],prob[N+5][N+5];
uint fl[N+5][N+5],fr[N+5][N+5];
uint gl[N+5][N+5],gr[N+5][N+5];
int main() {
	freopen("competition.in","r",stdin);
	freopen("competition.out","w",stdout);
    int n;
    scanf("%d",&n);
    C[0][0]=1;
    for(int i=1;i<=n;i++) {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++) {
            C[i][j]=plus(C[i-1][j-1],C[i-1][j]);
        }
    }
    for(int i=1;i<=n;i++) {
        scanf("%u",a+i);
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            prob[i][j]=ull(a[i])*power(a[i]+a[j],mod-2)%mod;
        }
    }
    for(int i=n;i>=1;i--) {
        std::fill(fl[i]+i,fl[i]+n+1,0);
        std::fill(fr[i]+i,fr[i]+n+1,0);
        std::fill(gl[i]+i,gl[i]+n+1,0);
        std::fill(gr[i]+i,gr[i]+n+1,0);
        fl[i][i]=fr[i][i]=1;
        for(int j=i+1;j<=n;j++) {
            for(int k=j;k>i;k--) {
                gl[i][j]=(gl[i][j]+ull(fl[i][k-1])*fr[k][j]%mod*C[j-i-1][j-k])%mod;
            }
            for(int k=j;k>i;k--) {
                fl[i][j]=(fl[i][j]+ull(gl[i][k])*fl[k][j]%mod*C[j-i-1][j-k]%mod*prob[i][k])%mod;
            }
            for(int k=i;k<j;k++) {
                gr[i][j]=(gr[i][j]+ull(fr[k+1][j])*fl[i][k]%mod*C[j-i-1][k-i])%mod;
            }
            for(int k=i;k<j;k++) {
                fr[i][j]=(fr[i][j]+ull(gr[k][j])*fr[i][k]%mod*C[j-i-1][k-i]%mod*prob[j][k])%mod;
            }
        }
    }
    uint sum{1};
    for(int i=1;i<=n-1;i++) {
        sum=ull(sum)*i%mod;
    }
    sum=power(sum,mod-2);
    uint sss{0};
    for(int i=1;i<=n;i++) {
        printf("%u\n",ull(fr[1][i])*fl[i][n]%mod*C[n-1][i-1]%mod*sum%mod);
    }
    return 0;
}
