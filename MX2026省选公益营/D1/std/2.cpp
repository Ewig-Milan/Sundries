#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "debug.h"
#else
#define debug(...) void ()
#endif
#define all(x) (x).begin (), (x).end ()
template <class T> auto ary (T *a, int l, int r) {
    return vector<T>{a + l, a + 1 + r};
}
using ll = long long;
using ull = unsigned long long;
using vec=complex<ll>;
using LL=__int128;
const int N=1e5+10;
LL dot(const vec &a,const vec &b){
    return (LL)real(a)*real(b)+(LL)imag(a)*imag(b);
}
LL cross(const vec &a,const vec &b){
    return (LL)real(a)*imag(b)-(LL)imag(a)*real(b);
}
int cmp(const vec &a,const vec &b){
    LL t=cross(a,b);
    if(t)return t>0?-1:1;
    LL x=dot(a,a)-dot(b,b);
    if(x)return x>0?-1:1;
    return 0;
}
struct Cmp{
    bool operator () (const vec &a,const vec &b)const{
        return real(a)^real(b)?real(a)<real(b):imag(a)<imag(b);
    }
};
namespace FHQ{
    struct node{
        int ls,rs,rnd;
        vec val,sum;
    }t[N];
    int root,k,top,stk[N];
    void clear(){
        root=k=top=0;
    }
    int newnode(vec val){
        int id=top?stk[top--]:++k;
        static mt19937 rnd(20260219);
        t[id]={0,0,(int)rnd(),val,val};
        return id;
    }
    void pushup(int rt){
        t[rt].sum=t[t[rt].ls].sum+t[t[rt].rs].sum+t[rt].val;
    }
    void split1(int rt,vec val,int &x,int &y){
        if(!rt)return x=y=0,void();
        if(cmp(val,t[rt].val)<0)y=rt,split1(t[rt].ls,val,x,t[rt].ls);
        else x=rt,split1(t[rt].rs,val,t[rt].rs,y);
        pushup(rt);
    }
    void split2(int rt,vec val,int &x,int &y){
        if(!rt)return x=y=0,void();
        if(cmp(val,t[rt].val)<=0)y=rt,split2(t[rt].ls,val,x,t[rt].ls);
        else x=rt,split2(t[rt].rs,val,t[rt].rs,y);
        pushup(rt);
    }
    int merge(int x,int y){
        if(!x||!y)return x|y;
        if(t[x].rnd<t[y].rnd){
            t[x].rs=merge(t[x].rs,y);
            return pushup(x),x;
        }else{
            t[y].ls=merge(x,t[y].ls);
            return pushup(y),y;
        }
    }
    void insert(vec val){
        // debug("insert",val);
        int x=newnode(val),r1,r2;
        split1(root,val,r1,r2);
        root=merge(merge(r1,x),r2);
    }
    void erase(vec val){
        // debug("erase",val);
        int r1,r2,r3;
        split1(root,val,r2,r3);
        split2(r2,val,r1,r2);
        stk[++top]=r2;
        r2=merge(t[r2].ls,t[r2].rs);
        root=merge(merge(r1,r2),r3);
    }
    void query(vec &cur,int rt=root){
        if(!rt)return;
        if(cmp(t[rt].val,cur-t[t[rt].ls].sum)<0){
            // debug(cur,t[t[rt].ls].sum+t[rt].val,t[rt].sum);
            cur-=t[t[rt].ls].sum+t[rt].val;
            query(cur,t[rt].rs);
        }else query(cur,t[rt].ls);
    }
    void print(){
        vector<vec>s;
        function<void(int)>dfs=[&](int u){
            if(!u)return;
            dfs(t[u].ls);
            s.push_back(t[u].val);
            dfs(t[u].rs);
        };
        dfs(root);
        debug(s);
    }
}
bool check(vec a,vec b,vec c){
    return cross(c-b,a-b)>0;
}
template<class T,class S>
ostream& operator << (ostream &out,set<T,S>a){
    out<<'[';
    for(auto x:a)out<<x<<',';
    return out<<']';
}
struct Set{
    set<vec,Cmp>s;
    void insert(vec a){
        auto it=s.lower_bound(a),x=prev(it);
        if(it!=s.end()){
            if(!check(*x,a,*it))return;
            FHQ::erase(*it-*x);
        }
        for(;x!=s.begin();){
            auto y=prev(x);
            if(!check(*y,*x,a)){
                FHQ::erase(*x-*y);
                s.erase(x);
                x=y;
            }else break;
        }
        FHQ::insert(a-*x);
        if(it!=s.end()){
            for(;x=next(it),x!=s.end();){
                if(!check(a,*it,*x)){
                    FHQ::erase(*x-*it);
                    s.erase(it);
                    it=x;
                }else break;
            }
            FHQ::insert(*it-a);
        }
        s.insert(a);
    }
}s[N];
int T,n,m;
void write(vec a){
    ll p=imag(a),q=real(a),g=__gcd(p,q);
    printf("%lld/%lld\n",p/g,q/g);
}
void work(){
    FHQ::clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        s[i].s.clear();
        s[i].s.insert(vec(0,0));
    }
    vec sum(0,0);
    for(int i=1,z;i<=n;i++){
        static ll x,y;
        scanf("%lld%lld%d",&x,&y,&z);
        sum+=vec(x,y);
        s[z].insert(vec(x,y));
        vec ans=sum;
        // for(int j=0;j<m;j++)ans-=*next(s[j].s.begin());
        // debug(ans);
        FHQ::query(ans);
        write(ans);
        // for(int j=0;j<m;j++)debug(s[j].s);
        // FHQ::print();
    }
}
int main () {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    for(scanf("%d",&T);T--;)work();
    return 0;
}
#ifdef DEBUG
#include "debug.hpp"
#endif