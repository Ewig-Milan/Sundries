#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10,MAXM=(1<<16)+10,MOD=998244353;
int n,m,k,dp[2][MAXM][8][2],ok[2][MAXM],f[MAXM],g[MAXM];
string S;
void solve(int n,int m,string S) {
	k=S.size(),S="&"+S;
	memset(ok,0,sizeof(ok)),memset(dp,0,sizeof(dp)),memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
	int s0=0;
	ffor(i,1,k) s0=s0*2+S[i]-'0';
	ok[0][0]=1,dp[0][0][0][0]=1;
	int t=(1<<k+1);
	ffor(i,1,max(n,m)) {
		int st=(i&1),ls=st^1;
		memset(dp[st],0,sizeof(dp[st]));
		memset(ok[st],0,sizeof(ok[st]));
		ffor(s,0,(1<<t)-1) if(ok[ls][s]) ffor(lst,0,(1<<k)-1) ffor(o,0,1) if(dp[ls][s][lst][o]) {
			ffor(nw,0,1) {
				int ns=s,nlst=lst,no=o;
				if(i>=k+1) ns|=(1<<((lst<<1)|nw));
				nlst=((lst<<1)|nw)&((1<<k)-1);
				if(i>=k&&nlst==s0) no=1;
				ok[st][ns]=1,dp[st][ns][nlst][no]=(dp[st][ns][nlst][no]+dp[ls][s][lst][o])%MOD;
			}
		}
		if(i==n) ffor(s,0,(1<<t)-1) ffor(lst,0,(1<<k)-1) f[s]=(f[s]+dp[st][s][lst][1])%MOD;	
		if(i==m) ffor(s,0,(1<<t)-1) ffor(lst,0,(1<<k)-1) g[s]=(g[s]+dp[st][s][lst][1])%MOD;
	}
	ffor(i,0,t-1) ffor(j,0,(1<<t)-1) if(!(j&(1<<i))) f[j]=(f[j]+f[j+(1<<i)])%MOD;
	ffor(i,0,t-1) ffor(j,0,(1<<t)-1) if(!(j&(1<<i))) g[j]=(g[j]+g[j+(1<<i)])%MOD;
	ffor(j,0,(1<<t)-1) f[j]=1ll*f[j]*g[j]%MOD;
	ffor(i,0,t-1) ffor(j,0,(1<<t)-1) if(!(j&(1<<i))) f[j]=(f[j]-f[j+(1<<i)])%MOD;
	cout<<(f[0]%MOD+MOD)%MOD<<'\n';
	return ;
}
signed main() {
	freopen("substring.in","r",stdin);
	freopen("substring.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) {
		int N,M; string S;
		cin>>N>>M>>S;
		solve(N,M,S);	
	}
	return 0;
}


