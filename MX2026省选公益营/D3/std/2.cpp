#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,w[2005],f[2005][2005][2][2],g[2005][2005],ans,val[2005];
bitset<2005>a[2][2005],b[2][2005],c[2][2005];char s[2005];
void cmax(int &x,int y){x=(x>y?x:y);}
signed main()
{
	freopen("dp6_3.in","r",stdin);
	freopen("dp6_3.out","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	int sum=0;
	for(int i=1;i<=n;i++)cin>>w[i],sum+=w[i];
	for(int i=1;i<=n;i++)
	{
		cin>>(s+1);
		for(int j=1;j<=n;j++)
		{
			a[1][i][j]=s[j]-'0';b[1][j][i]=a[1][i][j];
		}
	}
	int N=n+2;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			a[0][i][j]=a[1][i][j]^1;b[0][i][j]=b[1][i][j]^1;
		}
	}
	for(int i=1;i<=N;i++)
	{
		c[0][i]=(b[1][i]<<1)&(a[0][i]>>1);
		c[1][i]=(b[1][i]<<1)&(a[1][i]>>1);
	}
	memset(f,-0x3f,sizeof(f));memset(g,-0x3f,sizeof(g));
	f[2][3][a[1][1][2]][a[1][1][4]]=w[1];g[1][2]=w[3];
	for(int i=1;i<=N;i++)
	{
		vector<pair<int,int> >vec;
		for(int j=1;j<i;j++)
		{
			if(g[j][i]<0)continue;
			vec.emplace_back(make_pair(g[j][i]+w[j],j));
		}
		sort(vec.begin(),vec.end());reverse(vec.begin(),vec.end());
		bitset<2005>bs[2][2];val[i+2]=0;
		int mx=0;
		for(int j=i+2;j<=n+1;j++)
		{
			bs[0][0][j]=bs[0][1][j]=bs[1][0][j]=bs[1][1][j]=1;
			val[j+1]=val[j]+w[j];mx=max(mx,val[j]);
			if(!a[1][j-1][j])break;
		}
		for(int j=0;j<vec.size();j++)
		{
			int x=vec[j].second;
			cmax(ans,g[x][i]+mx); 
			for(int p=0;p<2;p++)
			{
				bitset<2005>now=bs[a[1][x][i]][p]&c[p][x];
				for(int k=now._Find_first();k<=n+1;k=now._Find_next(k))
				{
					cmax(f[i][k][a[1][x][i]][a[1][x][k+1]],g[x][i]+w[x]+val[k]);
					bs[a[1][x][i]][p][k]=0;
				}
			}
		}
		for(int j=i+1;j<=N;j++)
		{
			for(int p=0;p<2;p++)
			{
				for(int q=0;q<2;q++)
				{
					if(f[i][j][p][q]<0)continue;
					cmax(ans,f[i][j][p][q]);
					if(p)cmax(f[j][j+1][a[1][i][j]][a[1][i][j+2]],f[i][j][p][q]+w[i]);
					if(q&&j+1<=n)cmax(g[i][j],f[i][j][p][q]+w[j+1]);
				}
			}
		}
	}
	cerr<<sum<<' '<<ans<<'\n';
	cout<<ans;
	return 0;
}
