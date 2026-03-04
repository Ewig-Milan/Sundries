#include<bits/stdc++.h>
#define int long long
using namespace std;
int sum[2005],a[200005],n,m,mod,tp,bl[200005],tmp[2005],val[2005][2005],id[2005][2005],tmp2[2005],mp[2005];
int op,l,r,w,L[2005],R[2005],tag1[2005],tag2[2005],vis[2005],sum2[2005],b[200005],c[2005],d[2005];
struct FastMod
{
    using ull=unsigned long long;
    using L=__int128;
    ull b,m;
    void init(ull x){b=x;m=ull((L(1)<<64)/b);}
    ull reduce(ull a)
    {
    	if(b==1)return 0;
        ull q=(ull)((L(m)*a)>>64),r=a-q*b;
        return r>=b?r-b:r;
    }
}F;
void Add(int &x,int y){x=F.reduce(x+y);}
void rebuild(int x,int l,int r)
{
	sum[x]=0;sum2[x]=0;
	for(int i=L[x];i<=R[x];i++)sum[x]+=a[i],b[i]=F.reduce(a[i]),sum2[x]+=b[i];
	int tot1=0,tot2=0;
	for(int i=1;i<=R[x]-L[x]+1;i++)
	{
		if(l<=id[x][i]&&id[x][i]<=r)c[++tot1]=id[x][i];
		else d[++tot2]=id[x][i];
	}
	int pos=0;b[0]=0x3f3f3f3f3f3f3f3f;
	for(int i=1;i<=tot1;i++)if(b[c[i]]<b[c[pos]])pos=i;
	int tot=0;
	for(int i=pos;i<=tot1;i++)tmp[++tot]=c[i];
	for(int i=1;i<pos;i++)tmp[++tot]=c[i];
	for(int i=1;i<=tot1;i++)c[i]=tmp[i];
	pos=0;b[0]=0x3f3f3f3f3f3f3f3f;
	for(int i=1;i<=tot2;i++)if(b[d[i]]<b[d[pos]])pos=i;
	tot=0;
	for(int i=pos;i<=tot2;i++)tmp[++tot]=d[i];
	for(int i=1;i<pos;i++)tmp[++tot]=d[i];
	for(int i=1;i<=tot2;i++)d[i]=tmp[i];
	tot=0;
	int p=1,q=1;
	while(p<=tot1||q<=tot2)
	{
		if(p>tot1)id[x][++tot]=d[q++];
		else if(q>tot2)id[x][++tot]=c[p++];
		else 
		{
			if(b[c[p]]<b[d[q]])id[x][++tot]=c[p++];
			else id[x][++tot]=d[q++];
		}
	}
	for(int i=1;i<=R[x]-L[x]+1;i++)val[x][i]=b[id[x][i]];
	tag1[x]=tag2[x]=vis[x]=0;mp[x]=-1;
}
void rebuild2(int x)
{
	int tot=0;sum[x]=0;sum2[x]=0;
	for(int i=L[x];i<=R[x];i++)sum[x]+=a[i],sum2[x]+=F.reduce(a[i]);
	int pos=0;tmp[0]=0x3f3f3f3f3f3f3f3f;
	for(int i=1;i<=R[x]-L[x]+1;i++)
	{
		tmp[i]=F.reduce(val[x][i]+tag1[x]+tag2[x]);tmp2[i]=id[x][i];
		if(tmp[i]<tmp[pos])pos=i;
	}
	for(int i=pos;i<=R[x]-L[x]+1;i++)val[x][++tot]=tmp[i],id[x][tot]=tmp2[i];
	for(int i=1;i<pos;i++)val[x][++tot]=tmp[i],id[x][tot]=tmp2[i];
	tag1[x]=tag2[x]=vis[x]=0;mp[x]=-1;
}
bool cmp(int x,int y){return F.reduce(a[x])<F.reduce(a[y]);}
signed main()
{
	freopen("ex_sgt2.in","r",stdin);
	freopen("ex_sgt2.out","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>mod;F.init(mod);
	for(int i=1;i<=n;i++)cin>>a[i];
	int B=512;
	for(int i=1;i<=n;i++)
	{
		bl[i]=(i-1)/B+1;
		if(bl[i]!=bl[i-1])L[bl[i]]=i,R[bl[i-1]]=i-1;
	}
	R[bl[n]]=n;
	for(int i=1;i<=bl[n];i++)
	{
		int tot=0,x=i;mp[i]=-1;
		for(int j=L[x];j<=R[x];j++)id[x][++tot]=j,sum[x]+=a[j],sum2[x]+=F.reduce(a[j]);
		sort(id[x]+1,id[x]+tot+1,cmp);
		for(int j=1;j<=R[x]-L[x]+1;j++)val[x][j]=F.reduce(a[id[x][j]]);
	}
	while(m--)
	{
		cin>>op;
		if(op==1)
		{
			cin>>l>>r>>w;
			if(bl[l]==bl[r])
			{
				for(int i=L[bl[l]];i<=R[bl[l]];i++)
				{
					if(vis[bl[l]])Add(a[i],tag1[bl[l]]);
					a[i]+=tag2[bl[l]];
					if(l<=i&&i<=r)a[i]+=w;
				}
				rebuild(bl[l],l,r);
				continue;
			}
			for(int i=L[bl[l]];i<=R[bl[l]];i++)
			{
				if(vis[bl[l]])Add(a[i],tag1[bl[l]]);
				a[i]+=tag2[bl[l]];
				if(l<=i)a[i]+=w;
			}
			for(int i=L[bl[r]];i<=R[bl[r]];i++)
			{
				if(vis[bl[r]])Add(a[i],tag1[bl[r]]);
				a[i]+=tag2[bl[r]];
				if(i<=r)a[i]+=w;
			}
			rebuild(bl[l],l,R[bl[l]]);rebuild(bl[r],L[bl[r]],r);
			for(int i=bl[l]+1;i<=bl[r]-1;i++)tag2[i]+=w;
		}
		else if(op==2)
		{
			cin>>l>>r;
			if(bl[l]==bl[r])
			{
				for(int i=L[bl[l]];i<=R[bl[l]];i++)
				{
					if(vis[bl[l]])Add(a[i],tag1[bl[l]]);
					if(l<=i&&i<=r)Add(a[i],tag2[bl[l]]);
					else a[i]+=tag2[bl[l]];
				}
				rebuild2(bl[l]);
				continue;
			}
			for(int i=L[bl[l]];i<=R[bl[l]];i++)
			{
				if(vis[bl[l]])Add(a[i],tag1[bl[l]]);
				if(l<=i)Add(a[i],tag2[bl[l]]);
				else a[i]+=tag2[bl[l]];
			}
			for(int i=L[bl[r]];i<=R[bl[r]];i++)
			{
				if(vis[bl[r]])Add(a[i],tag1[bl[r]]);
				if(i<=r)Add(a[i],tag2[bl[r]]);
				else a[i]+=tag2[bl[r]];
			}
			rebuild2(bl[l]);rebuild2(bl[r]);
			for(int i=bl[l]+1;i<=bl[r]-1;i++)Add(tag1[i],tag2[i]),tag2[i]=0,vis[i]=1,mp[i]=-1;
		}
		else 
		{
			cin>>l>>r;
			if(bl[l]==bl[r])
			{
				int ans=0;
				for(int i=l;i<=r;i++)
				{
					int now=a[i];
					if(vis[bl[l]])Add(now,tag1[bl[l]]);
					now+=tag2[bl[l]];
					ans+=now;
				}
				cout<<ans<<'\n';continue;
			}
			int ans=0;
			for(int i=l;i<=R[bl[l]];i++)
			{
				int now=a[i];
				if(vis[bl[l]])Add(now,tag1[bl[l]]);
				now+=tag2[bl[l]];
				ans+=now;
			}
			for(int i=L[bl[r]];i<=r;i++)
			{
				int now=a[i];
				if(vis[bl[r]])Add(now,tag1[bl[r]]);
				now+=tag2[bl[r]];
				ans+=now;
			}
			for(int i=bl[l]+1;i<=bl[r]-1;i++)
			{
				ans+=tag2[i]*(R[i]-L[i]+1)+(vis[i]?sum2[i]:sum[i]);
				if(vis[i])
				{
					if(mp[i]!=-1)ans+=mp[i];
					else ans+=(mp[i]=tag1[i]*(R[i]-L[i]+1)-mod*(R[i]-L[i]+2-(lower_bound(val[i]+1,val[i]+(R[i]-L[i]+1)+1,mod-tag1[i])-val[i])));
				}
			}
			cout<<ans<<'\n';
		}
	}
	return 0;
}

