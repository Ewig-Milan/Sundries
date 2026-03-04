#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=0x3f3f3f3f;
struct Segment1
{
	pair<int,int>tr[800005];int tag[800005];
	void pushup(int k){tr[k]=min(tr[k<<1],tr[k<<1|1]);}
	void build(int k,int l,int r)
	{
		tag[k]=0;
		if(l==r){tr[k]={l,l};return;}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);build(k<<1|1,mid+1,r);
		pushup(k);
	}
	void update(int k,int v){tr[k].first+=v;tag[k]+=v;}
	void pushdown(int k)
	{
		if(!tag[k])return;
		update(k<<1,tag[k]);update(k<<1|1,tag[k]);
		tag[k]=0;
	}
	void change(int k,int l,int r,int x,int y,int v)
	{
		if(x<=l&&r<=y){update(k,v);return;}
		int mid=(l+r)>>1;pushdown(k);
		if(x<=mid)change(k<<1,l,mid,x,y,v);
		if(y>mid)change(k<<1|1,mid+1,r,x,y,v);
		pushup(k);
	}
}seg1;
struct Segment2
{
	pair<int,int>tr[800005];queue<int>q[200005];
	void pushup(int k){tr[k]=min(tr[k<<1],tr[k<<1|1]);}
	void build(int k,int l,int r)
	{
		if(l==r){while(!q[l].empty())q[l].pop();tr[k]={inf,l};return;}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);build(k<<1|1,mid+1,r);
		pushup(k);
	}
	void ins(int k,int l,int r,int x,int v)
	{
		if(l==r){q[l].push(v);tr[k]={q[l].front(),l};return;}
		int mid=(l+r)>>1;
		if(x<=mid)ins(k<<1,l,mid,x,v);
		else ins(k<<1|1,mid+1,r,x,v);
		pushup(k);
	}
	void del(int k,int l,int r,int x)
	{
		if(l==r){q[l].pop();tr[k]={q[l].size()?q[l].front():inf,l};return;}
		int mid=(l+r)>>1;
		if(x<=mid)del(k<<1,l,mid,x);
		else del(k<<1|1,mid+1,r,x);
		pushup(k);
	}
	pair<int,int>query(int k,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)return tr[k];
		int mid=(l+r)>>1;pair<int,int>res={inf,inf};
		if(x<=mid)res=min(res,query(k<<1,l,mid,x,y));
		if(y>mid)res=min(res,query(k<<1|1,mid+1,r,x,y));
		return res;
	}
}seg2;
struct node{int l,r,w;}tr[12000005];
int tot,n,q,t,Log[200005],st[20][200005],a[200005],l,r,lst;
void pushup(int k){tr[k].w=tr[tr[k].l].w+tr[tr[k].r].w;}
void change(int &k,int pre,int l,int r,int x)
{
	tr[k=++tot]=tr[pre];
	if(l==r){tr[k].w++;return;}
	int mid=(l+r)>>1;
	if(x<=mid)change(tr[k].l,tr[pre].l,l,mid,x);
	else change(tr[k].r,tr[pre].r,mid+1,r,x);
	pushup(k);
}
int query(int k,int l,int r,int x,int y)
{
	if(!k)return 0;
	if(x<=l&&r<=y)return tr[k].w;
	int mid=(l+r)>>1,res=0;
	if(x<=mid)res+=query(tr[k].l,l,mid,x,y);
	if(y>mid)res+=query(tr[k].r,mid+1,r,x,y);
	return res;
}
struct DS
{
	vector<pair<int,int> >v;int n;vector<int>rt;
	void build()
	{
		n=v.size();rt.resize(n+1);
		seg1.build(1,0,n);seg2.build(1,0,n);
		for(int i=1;i<=n;i++)
		{
			pair<int,int> now=v[i-1];rt[i]=rt[i-1];
			now.second=min(now.second,n);
			seg1.change(1,0,n,now.second,n,-1);
			seg2.ins(1,0,n,now.second,i);
			if(seg1.tr[1].first<0)
			{
				int pos=seg1.tr[1].second;
				pair<int,int> now2=seg2.query(1,0,n,0,pos);
				seg1.change(1,0,n,now2.second,n,1);
				seg2.del(1,0,n,now2.second);
				if(now2.first)change(rt[i],rt[i],1,n,now2.first);
			}
		}
	}
	int calc(int l,int r){return query(rt[r],1,n,l,r);}
}ds[60];
int calc(int l,int r)
{
	int k=Log[r-l+1];
	return max(st[k][l],st[k][r-(1ll<<k)+1]);
}
signed main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>q>>t;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];int p=0;
		for(int j=0;j<60;j++)if((a[i]>>j)&1)p=j;
		st[0][i]=p;
		ds[p].v.emplace_back(make_pair(i,a[i]^(1ll<<p))); 
	}
	for(int i=1;(1<<i)<=n;i++)
	{
		for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
	}
	for(int i=2;i<=n;i++)Log[i]=Log[i>>1]+1;
	for(int i=0;i<60;i++)ds[i].build();
	while(q--)
	{
		cin>>l>>r;
		l^=(t-1)*lst;r^=(t-1)*lst;
		int mx=calc(l,r);
		int ans=(1ll<<mx)+r-l+1;
		int pl=lower_bound(ds[mx].v.begin(),ds[mx].v.end(),make_pair(l,0ll))-ds[mx].v.begin()+1;
		int pr=lower_bound(ds[mx].v.begin(),ds[mx].v.end(),make_pair(r+1,0ll))-ds[mx].v.begin();
		ans+=pr-pl+1-ds[mx].calc(pl,pr);
		cout<<ans<<'\n';lst=ans;
	}
	return 0;
}
