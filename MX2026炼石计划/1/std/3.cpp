#include <bits/stdc++.h>
#define int long long
#define mr make_pair
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;

const int mod = 1e9 + 7 ;
void cmin(auto &x, auto y) {
    x = min(x, y) ;
}
void cmax(int &x, int y) {
    x = max(x, y) ;
}
int read() {
    char ch ;int s = 0 ;int w = 1;
    while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
    while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
    return s * w ;
}
void print(int x) {
    if(x < 0) putchar('-'), x = -x ;                  
    if(x > 9)print(x / 10) ;
    putchar(x % 10 + '0') ;
}                                   
void prn(int x) {      
    print(x) ;                                          
    putchar('\n') ;            
} 
int pows(int x, int k) {
    long long bace = x, ans = 1 ;
    while(k) {
        if(k & 1) ans *= bace, ans %= mod ;
        bace *= bace, bace %= mod ;
        k >>= 1 ;
    }
    return ans ;
}
mt19937 rnd(time(0)^clock()) ;
int TT ;
int n,m,k;
int c ;
struct node {
    int x, y ;
} p[1000005] ;
int f[1005005] ;
int cal(int x, int y) {
    if(x>y) swap(x,y) ;
    return min(y-x,x+n-y) ;
}
struct nd {
    int f ;
    int f1,f2 ;
    int lz ;
} t[1000005<<2] ;
void pup(int p) {
    t[p].f1=min(t[p<<1].f1,t[p<<1|1].f1) ;
    t[p].f2=min(t[p<<1].f2,t[p<<1|1].f2) ;
    t[p].f=min(t[p<<1].f,t[p<<1|1].f) ;
}
void gx(int p,int x) {
    t[p].lz+=x ;
    t[p].f1+=x ;
    t[p].f2+=x ;
    t[p].f+=x ;
}
void dw(int p) {
    if(!t[p].lz) return ;
    gx(p<<1,t[p].lz) ;
    gx(p<<1|1,t[p].lz) ;
    t[p].lz=0 ;
}
void build(int l, int r, int p) {
    if(l==r) {
        t[p].f=f[l] ;
        t[p].f1=f[l]+l ;
        t[p].f2=f[l]-l ;
        return ;
    }
    int mid=l+r>>1 ;
    build(l,mid,p<<1) ;
    build(mid+1,r,p<<1|1) ;
    pup(p) ;
}
void change(int l, int r, int x, int k, int p) {
    if(l==r&&l==x) {
        cmin(t[p].f,k) ;
        t[p].f1=t[p].f+l ;
        t[p].f2=t[p].f-l ;
        return ;
    }
    dw(p) ;
    int mid=l+r>>1 ;
    if(x<=mid) change(l,mid,x,k,p<<1) ;
    else change(mid+1,r,x,k,p<<1|1) ;
    pup(p) ;
}
int ask1(int l, int r, int ql, int qr, int p) {
    if(l>=ql&&r<=qr) return t[p].f1 ;
    dw(p) ;
    int mid=l+r>>1,res=1e18 ;
    if(ql<=mid) cmin(res,ask1(l,mid,ql,qr,p<<1)) ;
    if(qr>mid) cmin(res,ask1(mid+1,r,ql,qr,p<<1|1)) ;
    return res ;
}
int ask2(int l, int r, int ql, int qr, int p) {
    if(l>=ql&&r<=qr) return t[p].f2 ;
    dw(p) ;
    int mid=l+r>>1,res=1e18 ;
    if(ql<=mid) cmin(res,ask2(l,mid,ql,qr,p<<1)) ;
    if(qr>mid) cmin(res,ask2(mid+1,r,ql,qr,p<<1|1)) ;
    return res ;
}
int ask3(int l, int r, int x, int p) {
    if(l==r) return t[p].f ;
    dw(p) ;
    int mid=l+r>>1 ;
    if(x<=mid)return ask3(l,mid,x,p<<1) ;
    if(x>mid)return ask3(mid+1,r,x,p<<1|1) ;
}
int ask4(int l, int r, int x, int p) {
    if(l==r) return t[p].f1 ;
    dw(p) ;
    int mid=l+r>>1 ;
    if(x<=mid)return ask4(l,mid,x,p<<1) ;
    if(x>mid)return ask4(mid+1,r,x,p<<1|1) ;
}
void work() {
    cin>>c>>n>>m ;
    for(int i=1;i<=m;i++) {
        p[i].x=read(),p[i].y=read() ;
    }
    sort(p+1,p+m+1,[](node a, node b){
        return mr(a.x,a.y)<mr(b.x,b.y) ;
    }) ;
    memset(f,0x3f,sizeof(f)) ;
    p[0].y=1 ;
    f[n]=0 ;
    build(1,n,1) ;
    for(int i=1;i<=m;i++) {
        int R=1e18 ;
        {
            int res1=ask1(1,n,p[i].y,n,1) ;
            int res2=ask2(1,n,p[i].y,n,1) ;
            res1-=p[i].y ;
            res2+=n+p[i].y ;
            cmin(R,min(res1,res2)) ;
        }
        {
            int res1=ask2(1,n,1,p[i].y,1) ;
            int res2=ask1(1,n,1,p[i].y,1) ;
            res1+=p[i].y ;
            res2+=n-p[i].y ;
            cmin(R,min(res1,res2)) ;
        }
        
        if(p[i].x==p[i-1].x) {
            gx(1,1e9) ;
        }
        else gx(1,cal(p[i].y,p[i-1].y)) ;
        change(1,n,p[i-1].y,R,1) ;
    }
    cout<<t[1].f;
} 
signed main(){
    File("circle");
    work() ;
    return 0;
}