#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
using namespace std;
const int N=200020;
typedef pair<int,int> pii;
int n;
int vis[N];
pii tmp[N];
struct deck{
    int x,y,z;
}a[N];
inline bool battle(int i,int j){
    return (a[i].x>a[j].x)+(a[i].y>a[j].y)+(a[i].z>a[j].z)>=2;
}
struct Segment_Tree{
    struct node{
        pii mx;
    }t[N<<2];
    #define ls u<<1
    #define rs u<<1|1
    inline void update(int u){
        t[u].mx=max(t[ls].mx,t[rs].mx);
    }

    void build(int u,int L,int R){
        if(L==R){
            t[u].mx=tmp[L];
            return;
        }
        int mid=(L+R)>>1;
        build(ls,L,mid);
        build(rs,mid+1,R);
        update(u);
    }
    pii _query(int u,int L,int R,int l,int r){
        if(l>r)return {-1,-1};
        if(L>=l&&R<=r){
            return t[u].mx;
        }
        pii ans={-1,-1};
        int mid=(L+R)>>1;
        if(l<=mid)ans=max(ans,_query(ls,L,mid,l,r));
        if(r>mid)ans=max(ans,_query(rs,mid+1,R,l,r));
        return ans;
    }
    void _ch(int u,int L,int R,int p,pii w){
        if(L==R){
            t[u].mx=w;
            return;
        }
        int mid=(L+R)>>1;
        p<=mid?_ch(ls,L,mid,p,w):_ch(rs,mid+1,R,p,w);
        update(u);
    }
    void Del(int p){
        _ch(1,0,n,p,{-1,-1});
    }
    pii Query(int l,int r){
        return _query(1,0,n,l,r);
    }
    #undef ls
    #undef rs
}Tab,Tca,Tbc;
mt19937 rnd(233);
struct Treap{
    int rt;
    struct node{
        int ch[2];
        node(){ch[0]=ch[1]=-1;}
        unsigned int key;
    }t[N];
    #define ls(u) t[u].ch[0]
    #define rs(u) t[u].ch[1]
    inline void zig(int &u){
        int v=ls(u);
        ls(u)=rs(v);
        rs(v)=u;
        u=v;
    }
    inline void zag(int &u){
        int v=rs(u);
        rs(u)=ls(v);
        ls(v)=u;
        u=v;
    }
    int Del(int &u){
        if(ls(u)==-1){
            int tmp=u;
            u=rs(u);
            return tmp;
        }
        return Del(ls(u));
    }
    int First(){
        if(rt==-1)return -1;
        return Del(rt);
    }
    void Insert(int &u,int x){
        if(u==-1){
            u=x;
            t[u].key=rand();
            return;
        }
        if(battle(x,u)){
            Insert(rs(u),x);
        }
        else{
            Insert(ls(u),x);
        }
        if(~ls(u)&&t[ls(u)].key>t[u].key){
            zig(u);
        }
        if(~rs(u)&&t[rs(u)].key>t[u].key){
            zag(u);
        }
    }
    #undef ls
    #undef rs
}T;
void Erase(int u){
    Tab.Del(a[u].x);
    Tbc.Del(a[u].y);
    Tca.Del(a[u].z);
}
void Ins(int u){
    Erase(u);
    T.Insert(T.rt,u);
}
int MAIN() {
    cin>>n;
    for(int i=0;i<=n;++i) cin>>a[i].x>>a[i].y>>a[i].z;
    for(int i=0;i<=n;++i) tmp[a[i].x]={a[i].y,i};
    Tab.build(1,0,n);
    for(int i=0;i<=n;++i) tmp[a[i].y]={a[i].z,i};
    Tbc.build(1,0,n);
    for(int i=0;i<=n;++i) tmp[a[i].z]={a[i].x,i};
    Tca.build(1,0,n);
    Erase(0);
    vector<int> ans;
    while(1){
        int v=T.First();
        if(v==-1)break;
        if(v) ans.push_back(v), vis[v]=1;
        while(1){
            auto [y,id]=Tab.Query(a[v].x+1,n);
            if(y>a[v].y) Ins(id);
            else break;
        }
        while(1) {
            auto [z,id]=Tbc.Query(a[v].y+1,n);
            if(z>a[v].z) Ins(id);
            else break;
        }
        while(1) {
            auto [x,id]=Tca.Query(a[v].z+1,n);
            if(x>a[v].x) Ins(id);
            else break;
        }
    }
    cout<<ans.size()<<'\n';
    return 0;
}

void cl() {
    memset(vis, 0, sizeof vis);
    T.rt = 0;
    for(int i = 0; i <= n; i++) T.t[i].ch[0] = T.t[i].ch[1] = -1, T.t[i].key = 0;
}

int main() {
    FILE("triple");
    ios::sync_with_stdio(false);
    cin.tie(0);
    int nothing; cin >> nothing;
    int T_T; cin >> T_T;
    while(T_T--) MAIN(), cl();
    return 0;
}