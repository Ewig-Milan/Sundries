#include<bits/stdc++.h>
#define ll long long
using namespace std;
int Log[400005],h[400005],mn[20][400005],tot,mx[400005],num;char s[400005];
int n,sa[400005],rk[400005],rt[400005],c[400005],x[400005],y[400005];ll ans;
struct tree{int l,r,val,tag;}tr[20000005];
int getmn(int l,int r)
{
	int k=Log[r-l+1];
	if(h[mn[k][l]]<h[mn[k][r-(1<<k)+1]])return mn[k][l];
	else return mn[k][r-(1<<k)+1];
}
void pushup(int k){tr[k].val=tr[tr[k].l].val+tr[tr[k].r].val;}
void update(int &k,int l,int r,int v){if(!k)k=++tot;tr[k].val+=v*(r-l+1);tr[k].tag+=v;}
void pushdown(int k,int l,int r)
{
	if(!tr[k].tag)return;
	int mid=(l+r)>>1;
	update(tr[k].l,l,mid,tr[k].tag);update(tr[k].r,mid+1,r,tr[k].tag);
	tr[k].tag=0;
}
void change(int &k,int l,int r,int x,int y,int v)
{
	if(!k)k=++tot;
	if(x<=l&&r<=y){update(k,l,r,v);return;}
	int mid=(l+r)>>1;pushdown(k,l,r);
	if(x<=mid)change(tr[k].l,l,mid,x,y,v);
	if(y>mid)change(tr[k].r,mid+1,r,x,y,v);
	pushup(k);
}
void change2(int &k,int l,int r,int x,int y)
{
	if(!k)return;
	if(x<=l&&r<=y){k=0;return;}
	int mid=(l+r)>>1;pushdown(k,l,r);
	if(x<=mid)change2(tr[k].l,l,mid,x,y);
	if(y>mid)change2(tr[k].r,mid+1,r,x,y);
	pushup(k);
}
int query(int k,int l,int r,int x,int y)
{
	if(!k)return 0;
	if(x<=l&&r<=y)return tr[k].val;
	int mid=(l+r)>>1,res=0;pushdown(k,l,r);
	if(x<=mid)res+=query(tr[k].l,l,mid,x,y);
	if(y>mid)res+=query(tr[k].r,mid+1,r,x,y);
	return res;
}
int solve(int l,int r)
{
	if(l==r){mx[++num]=n-sa[l]+1;change(rt[num],1,n,1,n-sa[l]+1,1);return num;}
	int pos=getmn(l+1,r);
	int ls=solve(l,pos-1);int rs=solve(pos,r);
	int low=max(h[l],h[r+1]),x=++num;
	if(mx[ls]<mx[rs])
	{
		rt[x]=rt[rs];
		if(h[pos]<mx[ls])change2(rt[x],1,n,h[pos]+1,mx[ls]);
	}
	else 
	{
		rt[x]=rt[ls];
		if(h[pos]<mx[rs])change2(rt[x],1,n,h[pos]+1,mx[rs]);
	}
	mx[x]=max(mx[ls],mx[rs]);
	ans+=1ll*(h[pos]-low)*(h[pos]-low-1)/2;
	ans+=1ll*(h[pos]-low)*query(rt[x],1,n,h[pos]+1,n);
	return x;
}
signed main()
{
	freopen("string2_4.in","r",stdin);
	freopen("string2_4.out","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>(s+1);
	int m=122;
	for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
	for(int j=1;j<=n;j<<=1)
	{
		int tot=0;
		for(int i=n-j+1;i<=n;i++)y[++tot]=i;
		for(int i=1;i<=n;i++)if(sa[i]>j)y[++tot]=sa[i]-j;
		for(int i=1;i<=m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
		swap(x,y);x[sa[1]]=1;tot=1;
		for(int i=2;i<=n;i++)x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+j]==y[sa[i-1]+j]?tot:++tot);
		if(m==n)break;m=tot;
	}
	for(int i=1;i<=n;i++)rk[sa[i]]=i;
	for(int i=1,k=0;i<=n;i++)
	{
		if(rk[i]==1)continue;
		if(k)k--;
		while(i+k<=n&&sa[rk[i]-1]+k<=n&&s[i+k]==s[sa[rk[i]-1]+k])k++;
		h[rk[i]]=k;
	}
	for(int i=1;i<=n;i++)mn[0][i]=i;
	for(int i=2;i<=n;i++)Log[i]=Log[i>>1]+1;
	for(int i=1;(1<<i)<=n;i++)
	{
		for(int j=1;j+(1<<i)-1<=n;j++)
		{
			if(h[mn[i-1][j]]<h[mn[i-1][j+(1<<(i-1))]])mn[i][j]=mn[i-1][j];
			else mn[i][j]=mn[i-1][j+(1<<(i-1))];
		}
	}
	for(int i=1;i<=n;i++)
	{
		int low=max(h[i],h[i+1]);
		ans+=1ll*(n-sa[i]-low+1)*(n-sa[i]-low)/2;
	}
	solve(1,n);cout<<ans;
	return 0;
}
