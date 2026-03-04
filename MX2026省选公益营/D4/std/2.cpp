#include<bits/stdc++.h>
using namespace std;
int n,m,mod,inv[300005],fac[300005],val[205][300005],f[300005][205],s[205][205];
void Add(int &x,int y){x=(x+y>=mod?x+y-mod:x+y);}
int main()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>mod;
	inv[1]=fac[1]=s[0][0]=1;
	for(int i=2;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=i;j++)
		{
			s[i][j]=s[i-1][j-1];
			Add(s[i][j],1ll*j*s[i-1][j]%mod);
		}
	}
	for(int j=0;j<=m;j++)val[j][n+1]=1;
	for(int i=n;i>=2;i--)
	{
		for(int j=0;j<=m;j++)val[j][i]=1ll*val[j][i+1]*(mod+1-inv[n-i+2+j])%mod;
	}
	f[0][0]=1;
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			Add(f[i+1][j],f[i][j]);
			Add(f[i+1][j+1],1ll*f[i][j]*val[j][i+2]%mod);
		}
	}
	for(int i=1;i<=m;i++)
	{
		int ans=0;
		for(int j=1;j<=i;j++)Add(ans,1ll*f[n][j]*s[i][j]%mod*fac[j]%mod);
		cout<<ans<<'\n';
	}
	return 0;
}

