#include<bits/stdc++.h>
#define y1 Clein_qwq
#define pii pair<int,int>
using namespace std;
const int LG=21;
const int N=1005;
const int NN=2000005;
const int fx[5]={-1,1,0,0};
const int fy[5]={0,0,-1,1};
template <typename T> inline void chkmax(T& x, T y){ x=max(x,y); }
template <typename T> inline void chkmin(T& x, T y){ x=min(x,y); }
int tid,n,m,Q,nn,idx,top,cnt,dfn[NN],low[NN],stc[NN],ins[NN],col[NN],sz[NN];
int a[N][N],id[N][N],dep[NN],sum[NN],xmn[NN],xmx[NN],ymn[NN],ymx[NN],ff[NN],fa[NN];
int lg[NN],par[LG][NN],dir[NN],pos[NN],val[NN],le[NN],ri[NN];
int cur[NN],son[NN]; vector<int>o[NN],e[NN]; vector<pii>g[NN],alle; string str;
inline int find(int x){ return ff[x]==x?x:ff[x]=find(ff[x]); }
inline void tarjan(int x,int y){
    dfn[id[x][y]]=low[id[x][y]]=++idx;
    stc[++top]=id[x][y]; ins[id[x][y]]=1;
    for(int i=0;i<4;i++){
        int nx=x+fx[i],ny=y+fy[i];
        if(i==a[x][y]||!nx||!ny||nx>n||ny>m) continue;
        if(!dfn[id[nx][ny]]){
            tarjan(nx,ny);
            chkmin(low[id[x][y]],low[id[nx][ny]]);
        }
        else if(ins[id[nx][ny]]) chkmin(low[id[x][y]],dfn[id[nx][ny]]);
    }
    if(low[id[x][y]]==dfn[id[x][y]]){
        cnt++;
        do{
            col[stc[top]]=cnt;
            ins[stc[top]]=0;
            sz[cnt]++;
        }while(stc[top--]!=id[x][y]);
    }
}
inline void add(int u,int v){
    // 儿子链上的 u->v 单向边，为了维护 fa 的儿子链的形态先连成双向，并将方向存下来后面处理
    o[u].emplace_back(v);
    o[v].emplace_back(u);
    alle.emplace_back(u,v);
}
inline void dfs(int u){
    par[0][u]=fa[u];
    for(int i=1;i<=lg[dep[u]];i++) par[i][u]=par[i-1][par[i-1][u]];
    if(e[u].empty()) return;
    sum[e[u][0]]=sz[e[u][0]];
    for(int i=1;i<e[u].size();i++) sum[e[u][i]]=sum[e[u][i-1]]+sz[e[u][i]];
    le[e[u][0]]=e[u][0]; ri[e[u].back()]=e[u].back();
    // le / ri: 在链上往左/右走儿子链单向边能走到最远的兄弟节点
    for(int i=1;i<e[u].size();i++)
        if(dir[e[u][i-1]]==-1) le[e[u][i]]=le[e[u][i-1]];
        else le[e[u][i]]=e[u][i];
    for(int i=e[u].size()-2;~i;i--)
        if(dir[e[u][i]]==1) ri[e[u][i]]=ri[e[u][i+1]];
        else ri[e[u][i]]=e[u][i];
    for(int v:e[u]){
        dep[v]=dep[u]+1;
        val[v]=val[u]+sum[ri[v]]-sum[le[v]]+sz[le[v]];
        dfs(v);
    }
}
inline int anc(int x,int t){
    for(int i=0;i<=lg[t];i++)
        if(t&(1<<i))
            x=par[i][x];
    return x;
}
inline int query(int x,int y){
    if(dep[x]<dep[y]) return -1;
    int ans=val[x];
    x=anc(x,dep[x]-dep[y]);
    ans-=val[x];
    if(fa[x]!=fa[y]) return -1;
    if(pos[x]<=pos[y]){
        if(pos[ri[x]]<pos[y]) return -1;
        ans+=sum[y]-sum[x]+sz[x];
    }
    else{
        if(pos[le[x]]>pos[y]) return -1;
        ans+=sum[x]-sum[y]+sz[y];
    }
    return ans;
}
int main(){
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>tid>>n>>m>>Q;
    for(int i=1;i<=n;i++){
        cin>>str;
        for(int j=1;j<=m;j++){
            if(str[j-1]=='U') a[i][j]=0;
            else if(str[j-1]=='D') a[i][j]=1;
            else if(str[j-1]=='L') a[i][j]=2;
            else a[i][j]=3;
            id[i][j]=++nn;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!dfn[id[i][j]]) tarjan(i,j);
    for(int i=1;i<=cnt;i++) xmn[i]=n+1,ymn[i]=m+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            chkmin(xmn[col[id[i][j]]],i);
            chkmin(ymn[col[id[i][j]]],j);
            chkmax(xmx[col[id[i][j]]],i);
            chkmax(ymx[col[id[i][j]]],j);
            g[col[id[i][j]]].emplace_back(i,j);
        }
    for(int i=1;i<=cnt;i++) ff[i]=i;
    for(int i=cnt;i;i--){ // 按拓扑序处理
        // step1 : 将包含 i 的矩形内的所有 j 向 i 连边
        for(pii j:g[i]){
            int x=j.first,y=j.second;
            for(int k=0;k<4;k++){
                int nx=x+fx[k],ny=y+fy[k];
                if(nx<xmn[i]||ny<ymn[i]||nx>xmx[i]||ny>ymx[i]) continue;
                int nf=find(col[id[nx][ny]]);
                if(nf!=i) ff[nf]=fa[nf]=i;
            }
        }
        // step2 : 将贴着 i 的相同方向上的矩形合并，并向 i 连边
        for(int x:{xmn[i]-1,xmx[i]+1}){
            if(!x||x>n||col[id[x][ymn[i]]]<i) continue;
            int all=1,flag=1,u=find(col[id[x][ymn[i]]]);
            for(int j=ymn[i];j<=ymx[i];j++){
                if(a[x][j]!=(x==xmn[i]-1)) all=0;
                int v=find(col[id[x][j]]);
                if(u!=v){
                    if(flag){
                        ff[u]=fa[u]=++cnt;
                        u=cnt; ff[u]=u;
                        flag=0;
                    }
                    ff[v]=fa[v]=u;
                }
            }
            if(!all) add(u,i); // 并排的合并起来后，向 i 连边
        }
        for(int y:{ymn[i]-1,ymx[i]+1}){
            if(!y||y>m||col[id[xmn[i]][y]]<i) continue;
            int all=1,flag=1,u=find(col[id[xmn[i]][y]]);
            for(int j=xmn[i];j<=xmx[i];j++){
                if(a[j][y]!=2+(y==ymn[i]-1)) all=0;
                int v=find(col[id[j][y]]);
                if(u!=v){
                    if(flag){
                        ff[u]=fa[u]=++cnt;
                        u=cnt; ff[u]=u;
                        flag=0;
                    }
                    ff[v]=fa[v]=u;
                }
            }
            if(!all) add(u,i);
        }
    }
    for(int i=1;i<=cnt;i++) son[fa[i]]++;
    for(int i=0;i<=cnt;i++) e[i].resize(son[i]),pos[i]=-1;
    for(int i=1;i<=cnt;i++){
        if(~pos[i]||o[i].size()>1) continue;
        if(o[i].empty()) pos[i]=cur[fa[i]]++;
        else{
            int u=i;
            pos[u]=cur[fa[i]]++;
            u=o[u][0];
            while(o[u].size()==2){
                pos[u]=cur[fa[i]]++;
                u=o[u][pos[o[u][0]]!=-1];
            }
            pos[u]=cur[fa[i]]++;
        }
    }
    for(pii i:alle){ // 处理儿子链
        int x=i.first,y=i.second;
        if(pos[x]<pos[y]) dir[x]=1;
        else dir[y]=-1;
    }
    for(int i=1;i<=cnt;i++) e[fa[i]][pos[i]]=i;
    for(int i=2;i<=cnt;i++) lg[i]=lg[i>>1]+1; dfs(0);
    while(Q--){
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        cout<<query(col[id[x1][y1]],col[id[x2][y2]])<<'\n';
    }
    return 0;
}