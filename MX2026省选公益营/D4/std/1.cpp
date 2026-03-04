#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,tr[40],B,pw[40],val[100005],a[40],c[40],lim[40],w[100005],popc[100005];
int pre[40],pre2[100005];pair<int,ll>dp[1000005],ans[40];
void change(int x,int v){for(int i=x;i<=n;i+=i&(-i))tr[i]+=v;}
int query(int x){int res=0;for(int i=x;i;i-=i&(-i))res+=tr[i];return res;}
void work(int w)
{
	int now=0;
	for(int i=0;i<=B;i++)now+=pw[i]*val[i];
	if(w<dp[now].first)dp[now]={w,1};
	else if(w==dp[now].first)dp[now].second++;
}
void dfs(int x,int s,int w)
{
	if(x==n+1){work(w);return;}
	dfs(x+1,s,w);
	change(a[x],1);
	for(int i=1;i<=B;i++)if(a[x]<c[i]){val[i-1]++;break;}
	if(a[x]>c[B])val[B]++;
	dfs(x+1,s+1,w+s+1-query(a[x]));
	change(a[x],-1);
	for(int i=1;i<=B;i++)if(a[x]<c[i]){val[i-1]--;break;}
	if(a[x]>c[B])val[B]--;
}
namespace BF
{
	void main()
	{
		for(int s=1;s<(1<<n);s++)
		{
			for(int i=1;i<=n;i++)tr[i]=0;
			int now=0;
			for(int i=1;i<=n;i++)
			{
				if((s>>(i-1))&1)
				{
					now+=query(n)-query(a[i]);
					change(a[i],1);
				}
			}
			int num=__builtin_popcount(s);
			if(ans[num].first>now)ans[num]={now,1};
			else if(ans[num].first==now)ans[num].second++;
		}
		for(int i=1;i<=n;i++)cout<<ans[i].first<<' '<<ans[i].second<<'\n';
	}
}
signed main()
{
	freopen("ex_search3.in","r",stdin);
	freopen("ex_search3.out","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;B=10;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)ans[i]={0x3f3f3f3f,0};
	if(n<=B){BF::main();return 0;}
	for(int i=1;i<=B;i++)c[i]=a[i];
	sort(c+1,c+B+1);
	lim[0]=c[1];
	for(int i=1;i<B;i++)lim[i]=c[i+1]-c[i];
	lim[B]=n-c[B]+1;
	pw[0]=1;
	for(int i=1;i<=B+1;i++)pw[i]=pw[i-1]*lim[i-1];
	for(int s=0;s<pw[B+1];s++)dp[s]={0x3f3f3f3f,0};
	dfs(B+1,0,0);
	for(int s=0;s<(1<<B);s++)
	{
		for(int i=1;i<=n;i++)tr[i]=0;
		for(int i=0;i<B;i++)
		{
			if((s>>i)&1)
			{
				w[s]+=query(n)-query(a[i+1]);
				change(a[i+1],1);
			}
		}
	}
	for(int i=0;i<(1<<B);i++)popc[i]=__builtin_popcount(i);
	for(int s=0;s<pw[B+1];s++)
	{
		int x=s;
		for(int i=0;i<=B;i++)pre[i]=x%lim[i],x/=lim[i];
		for(int i=1;i<=B;i++)pre[i]+=pre[i-1];
		for(int i=0;i<B;i++)
		{
			for(int j=1;j<=B;j++)if(a[i+1]==c[j])pre2[1<<i]=pre[j-1];
		}
		val[0]=0;
		for(int t=1;t<(1<<B);t++)
		{
			int x=t&(-t);
			val[t]=val[t^x]+pre2[x];
		}
		for(int t=0;t<(1<<B);t++)
		{
			int num=popc[t]+pre[B],res=w[t]+val[t]+dp[s].first,cur=dp[s].second;
			if(ans[num].first>res)ans[num]={res,cur};
			else if(ans[num].first==res)ans[num].second+=cur;
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i].first<<' '<<ans[i].second<<'\n';
	return 0;
}

