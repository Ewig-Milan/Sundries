#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
mt19937 rnd(0x66ccff);
struct FHQ{
int rt[N],ls[N],rs[N],sz[N],va[N],p[N],sum[N],ct[N];
inline void pushup(int x){
    sz[x]=sz[ls[x]]+sz[rs[x]]+1;
    sum[x]=sum[ls[x]]+sum[rs[x]]+va[x];
}
int merge(int x,int y){
    if(!x||!y)return x|y;
    if(p[x]<p[y]){
        rs[x]=merge(rs[x],y);
        return pushup(x),x;
    }else{
        ls[y]=merge(x,ls[y]);
        return pushup(y),y;
    }
}
void split(int u,int k,int &x,int &y){
    if(!u)return x=y=0,void();
    if(sz[ls[u]]<k){
        x=u,split(rs[u],k-sz[ls[u]]-1,rs[x],y);
        pushup(x);
    }else{
        y=u,split(ls[u],k,x,ls[y]);
        pushup(y);
    }
}
int qry(int x,int r){
    int u,w;
    split(rt[x],r,u,rt[x]);
    w=sum[u];
    rt[x]=merge(u,rt[x]);
    return w;
}
void pushback(int x,int y){
    sz[y]=1,sum[y]=va[y];
    ++ct[x],va[x]+=va[y];
    rt[x]=merge(rt[x],y);
}
void pushfront(int x,int y){
    sum[y]=va[y];
    ++ct[x],va[x]+=va[y];
    rt[x]=merge(y,rt[x]);
}
int popback(int x){
    int y;
    --ct[x];
    split(rt[x],ct[x],rt[x],y);
    va[x]-=va[y];
    return y;
}
int popfront(int x){
    int y;
    --ct[x];
    split(rt[x],1,y,rt[x]);
    va[x]-=va[y];
    return y;
}
}T;
int ls[N],rs[N],va[N],tg[N],rt[N],sz[N],fa[N],p[N];
#define cs(x) T.ct[x]
#define tsz(x) T.va[x]
int tid,n,m;
void pushtg(int x,int v){
    tg[x]+=v,va[x]+=v;
}
void pushup(int x){
    sz[x]=sz[ls[x]]+sz[rs[x]]+1;
    if(ls[x])fa[ls[x]]=x;
    if(rs[x])fa[rs[x]]=x;
}
void pushdown(int x){
    if(tg[x]){
        if(ls[x])pushtg(ls[x],tg[x]);
        if(rs[x])pushtg(rs[x],tg[x]);
        tg[x]=0;
    }
}
int merge(int x,int y){
    if(!x||!y)return x|y;
    pushdown(x),pushdown(y);
    if(p[x]<p[y]){
        rs[x]=merge(rs[x],y);
        return pushup(x),x;
    }else{
        ls[y]=merge(x,ls[y]);
        return pushup(y),y;
    }
}
void split(int u,int k,int &x,int &y){
    if(!u)return x=y=0,void();
    fa[u]=0,pushdown(u);
    if(sz[ls[u]]<k){
        x=u,split(rs[u],k-sz[ls[u]]-1,rs[x],y);
        pushup(x);
    }else{
        y=u,split(ls[u],k,x,ls[y]);
        pushup(y);
    }
}
void pushback(int x,int y){
    rt[y]=merge(y,rt[y]);
    T.pushback(x,y);
    rt[x]=merge(rt[x],rt[y]);
    int o=T.qry(x,cs(x)>>1);
    split(rt[x],o,rt[x],y);
    pushtg(y,1);
    rt[x]=merge(rt[x],y);
}
void pushfront(int x,int y){
    rt[y]=merge(y,rt[y]);
    T.pushfront(x,y);
    rt[x]=merge(rt[y],rt[x]);
    int o=T.qry(x,cs(x)+1>>1);
    split(rt[x],o,y,rt[x]);
    pushtg(y,1);
    rt[x]=merge(y,rt[x]);
}
void popback(int x){
    int y,o=T.qry(x,cs(x)>>1);
    y=T.popback(x);
    split(rt[x],o,rt[x],rt[y]);
    pushtg(rt[y],-1);
    rt[x]=merge(rt[x],rt[y]);
    split(rt[x],tsz(x)-1,rt[x],rt[y]);
    split(rt[y],1,y,rt[y]);
}
void popfront(int x){
    int y,o=T.qry(x,cs(x)+1>>1);
    y=T.popfront(x);
    split(rt[x],o,rt[y],rt[x]);
    pushtg(rt[y],-1);
    rt[x]=merge(rt[y],rt[x]);
    split(rt[x],tsz(y),rt[y],rt[x]);
    split(rt[y],1,y,rt[y]);
}
int qry(int x){
    int res=va[x];
    while(fa[x])x=fa[x],res+=tg[x];
    return res;
}
int main(){
    freopen("deque.in","r",stdin);
    freopen("deque.out","w",stdout);
    scanf("%d%d%d",&tid,&n,&m);
    for(int i=1;i<=n;++i)T.sz[i]=sz[i]=T.va[i]=1,T.p[i]=rnd(),p[i]=rnd();
    for(int i=1,x,y;i<=m;++i){
        string S;
        cin>>S;
        if(S=="push_back"){
            scanf("%d%d",&y,&x);
            pushback(x,y);
        }
        if(S=="push_front"){
            scanf("%d%d",&y,&x);
            pushfront(x,y);
        }
        if(S=="pop_back"){
            scanf("%d",&x);
            popback(x);
        }
        if(S=="pop_front"){
            scanf("%d",&x);
            popfront(x);
        }
        if(S=="pop_complexity"){
            scanf("%d",&x);
            printf("%d\n",qry(x));
        }
    }
    return 0;
}