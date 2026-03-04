#include<bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#ifdef DEBUG
template<class T>
ostream& operator << (ostream &out,vector<T>a){
	out<<'[';
	for(auto x:a)out<<x<<',';
	return out<<']';
}
template<class T>
auto ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
template<class T>
void debug(T x){
	cerr<<x<<endl;
}
template<class T,class...S>
void debug(T x,S...y){
	cerr<<x<<' ',debug(y...);
}
#else
#define debug(...) void()
#endif
const int N=2e5+10,INF=1e9;
int n,cnt,q;
int a[N],b[N];
namespace SGT1{
	int t[N<<2];
	void pushup(int rt){
		t[rt]=min(t[rt<<1],t[rt<<1|1]);
	}
	void build(int l=1,int r=n,int rt=1){
		if(l==r)return t[rt]=a[l]?a[l]:INF,void();
		int mid=(l+r)>>1;
		build(l,mid,rt<<1);
		build(mid+1,r,rt<<1|1);
		pushup(rt);
	}
	int query(int L,int R,int l=1,int r=n,int rt=1){
		if(r<L||R<l)return INF;
		if(L<=l&&r<=R)return t[rt];
		int mid=(l+r)>>1;
		return min(query(L,R,l,mid,rt<<1),query(L,R,mid+1,r,rt<<1|1));
	}
}
namespace SGT2{
	int t[N<<2];
	void pushup(int rt){
		t[rt]=max(t[rt<<1],t[rt<<1|1]);
	}
	void build(int l=1,int r=n,int rt=1){
		if(l==r)return t[rt]=a[l]?a[l]:0,void();
		int mid=(l+r)>>1;
		build(l,mid,rt<<1);
		build(mid+1,r,rt<<1|1);
		pushup(rt);
	}
	int query(int L,int R,int l=1,int r=n,int rt=1){
		if(r<L||R<l)return 0;
		if(L<=l&&r<=R)return t[rt];
		int mid=(l+r)>>1;
		return max(query(L,R,l,mid,rt<<1),query(L,R,mid+1,r,rt<<1|1));
	}
}
struct opts{
	int op,l,r,w;
};
ostream& operator << (ostream &out,opts a){
	return out<<'('<<"lr"[a.op]<<','<<a.l<<','<<a.r<<','<<a.w<<')';
}
using ll=long long;
ll ans;
ll f[N][2];
int m,g[N][2];
struct SGT{
	pair<int,int>mn[N<<2];
	int laz[N<<2];
	void pushup(int rt){
		mn[rt]=min(mn[rt<<1],mn[rt<<1|1]);
		mn[rt].first+=laz[rt];
	}
	void pushlaz(int rt,int x){
		mn[rt].first+=x;
		laz[rt]+=x;
	}
	void build(int l=1,int r=m,int rt=1){
		laz[rt]=0;
		if(l==r)return mn[rt]={INF,l},void();
		int mid=(l+r)>>1;
		build(l,mid,rt<<1);
		build(mid+1,r,rt<<1|1);
		pushup(rt);
	}
	void update(int L,int R,int x,int l=1,int r=m,int rt=1){
		// if(rt==1)debug("update",L,R,x);
		if(r<L||R<l)return;
		if(L<=l&&r<=R)return pushlaz(rt,x);
		int mid=(l+r)>>1;
		update(L,R,x,l,mid,rt<<1);
		update(L,R,x,mid+1,r,rt<<1|1);
		pushup(rt);
	}
	pair<int,int> query(int L,int R,int l=1,int r=m,int rt=1){
		if(r<L||R<l)return {INF,0};
		if(L<=l&&r<=R)return mn[rt];
		int mid=(l+r)>>1;
		auto res=min(query(L,R,l,mid,rt<<1),query(L,R,mid+1,r,rt<<1|1));
		res.first+=laz[rt];
		return res;
	}
	void modify(int x,int y,int l=1,int r=m,int rt=1){
		// if(rt==1)debug("modify",x,y);
		if(l==r)return mn[rt]={y,l},void();
		int mid=(l+r)>>1;
		y-=laz[rt];
		if(x<=mid)modify(x,y,l,mid,rt<<1);
		else modify(x,y,mid+1,r,rt<<1|1);
		pushup(rt);
	}
}T[2];
int sum[N];
void solve(vector<int>p,int L,int R,vector<opts>o){
	// debug("bg",ans,p,L,R,o);
	vector<opts>ot;
	for(auto x:o){
		x.r=upper_bound(all(p),x.r)-p.begin()-1;
		x.l=lower_bound(all(p),x.l)-p.begin();
		if(x.l>x.r){
			ans+=x.op?b[x.w]:-b[x.w];
		}else{
			if(x.op&&x.w>=R)ans+=b[x.w];
			else if(!x.op&&x.w<=L)ans-=b[x.w];
			else ot.push_back(x);
		}
	}
	swap(o,ot);
	// debug("ed",ans,p,L,R,o);
	if(o.empty()||L==R){
		for(auto x:o){
			ans+=x.op?b[max(L,x.w)]:-b[min(L,x.w)];
		}
		for(int x:p)a[x]=L;
		return;
	}
	int mid=(L+R)>>1;
	// debug(mid,p,L,R,o);
	m=p.size();
	T[0].build();
	T[1].build();
	sort(all(o),[&](opts x,opts y){
		return x.r<y.r;
	});
	for(int i=1,j=0;i<=m;i++){
		T[0].modify(i,f[i-1][1]);
		T[1].modify(i,f[i-1][0]);
		// debug(i);
		for(;j<o.size()&&o[j].r<=i-1;j++){
			// debug(j,o[j]);
			if(o[j].op){
				if(o[j].w<=mid)T[0].update(1,o[j].l+1,-1);
			}else{
				if(o[j].w>mid)T[1].update(1,o[j].l+1,-1);
			}
		}
		tie(f[i][0],g[i][0])=T[0].query(1,i);
		tie(f[i][1],g[i][1])=T[1].query(1,i);
	}
	int cur=m,op=f[m][1]<f[m][0];
	vector<int>pt[2];
	sum[m]=0;
	// debug("OK1");
	// debug(f[1][0],f[1][1],g[1][0],g[1][1]);
	for(;cur>0;cur=g[cur][op]-1,op^=1){
		// debug(cur,g[cur][op]);
		for(int i=cur;i>=g[cur][op];i--){
			sum[i-1]=sum[i]+op;
			pt[op].push_back(p[i-1]);
		}
	}
	for(int c:{0,1})reverse(all(pt[c]));
	// debug("OK2");
	vector<opts>oo[2];
	for(auto x:o){
		int cnt1=sum[x.l]-sum[x.r+1],cnt0=(x.r-x.l+1)-cnt1;
		x.l=p[x.l];
		x.r=p[x.r];
		if(x.op){
			oo[!!cnt1].push_back(x);
		}else{
			oo[!cnt0].push_back(x);
		}
	}
	// debug(oo[0],oo[1]);
	solve(pt[0],L,mid,oo[0]);
	solve(pt[1],mid+1,R,oo[1]);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i])b[++cnt]=a[i];
	}
	if(!cnt)b[++cnt]=1;
	sort(b+1,b+1+cnt);
	cnt=unique(b+1,b+1+cnt)-b-1;
	for(int i=1;i<=n;i++){
		if(a[i])a[i]=lower_bound(b+1,b+1+cnt,a[i])-b;
	}
	SGT1::build();
	SGT2::build();
	vector<opts>o;
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
		o.push_back({0,l,r,SGT1::query(l,r)});
		o.push_back({1,l,r,SGT2::query(l,r)});
	}
	vector<int>p;
	for(int i=1;i<=n;i++){
		if(!a[i])p.push_back(i);
	}
	solve(p,1,cnt,o);
	// ll ans2=0;
	// SGT1::build();
	// SGT2::build();
	// for(auto [op,l,r,x]:o){
	// 	if(op)ans2+=SGT2::query(l,r);
	// 	else ans2-=SGT1::query(l,r);
	// }
	// assert(ans==ans2);
	printf("%lld\n",ans);
    for(int i=1;i<=n;i++){
        printf("%d%c",b[a[i]],"\n "[i<n]);
    }
	// debug(ans,ary(a,1,n));
	// cerr<<1.0*clock()/CLOCKS_PER_SEC<<"s\n";
	return 0;
}
/*
g++ I.cpp -o I -O2 -Wno-unused-result -DDEBUG && .\I < .in
*/