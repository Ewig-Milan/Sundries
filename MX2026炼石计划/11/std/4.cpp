#include <bits/stdc++.h>
using namespace std;

const int N=1e6+5;

int n,m;
int head[N], nex[N*4], to[N*4], indx=0;
int bel[N], L[N], R[N], point[N], c[N];
int trans2[N], trans1[N], pre[N];
pair <int,int> links[N][22];

int getid(int x,int y)
{
    return (x-1)*m+y;
}

void add_edge(int x,int y)
{
    indx++;
    nex[indx]=head[x];
    to[indx]=y;
    head[x]=indx;
}

void add(int x,int y)
{
    add_edge(x,y);
    add_edge(y,x);
}

void dfs(int x,int val)
{
    if(bel[x])
        return;

    bel[x]=val, L[val]=min(L[val],(x+m-1)/m), R[val]=max(R[val],(x+m-1)/m);
    for(int i=head[x];i;i=nex[i])
        dfs(to[i],val);
}

bool cmp(int x,int y)
{
    if(R[x]!=R[y])
        return R[x]<R[y];
    return L[x]>L[y];
}

pair <int,int> merge(pair <int,int> x, int k)
{
    pair <int,int> ans;
    ans.first=max(links[x.first][k].first,links[trans2[x.second]][k].second);
    ans.second=max(links[x.second][k].first,links[x.first][k].second);
    return ans;
}

pair <int,int> getnex(pair <int,int> x,int l,int r)
{
    pair <int,int> ans;
    ans.second=x.first;
    ans.first=max(pre[min(trans2[x.first],r)],min(trans2[x.second],r));
    return ans;
}

int calc(pair <int,int>& now,int l,int r)
{
    if(now.second>=l)
        return 0;

    now.first=max(now.first,pre[min(trans2[now.second],r)]);
    if(now.first>=l)
    {
        now=getnex(now,l,r);
        return 1;
    }

    int ans=0;
    for(int k=21;k>=0;k--)
        if(merge(now,k).first<l)
            now=merge(now,k), ans += 1<<k;

    if(ans>=3000000)
        return ans;

    while(now.second<l)
        now=getnex(now,l,r), ans++;
    return ans;
}

signed main()
{
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
    int q;
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++)
        {
            int x;
            scanf("%1d",&x);
            if(x)
                add(getid(i,j),getid(i,j+1));
        }

    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++)
        {
            int x;
            scanf("%1d",&x);
            if(x)
                add(getid(i,j),getid(i+1,j));
        }

    int cnt=0;
    memset(L,0x3f,sizeof(L));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!bel[getid(i,j)])
                dfs(getid(i,j),++cnt);

    for(int i=1;i<=n;i++)
        scanf("%d",&c[i]);

    for(int i=1;i<=n;i++)
        pre[i]=max(pre[i-1],(c[i]==1?i:0));

    for(int i=1;i<=cnt;i++)
        trans2[L[i]]=max(trans2[L[i]],R[i]);

    for(int i=1;i<=n;i++)
    {
        trans2[i]=max(trans2[i],trans2[i-1]);
        trans1[i]=max(pre[trans2[i]],i);
        links[i][0]=make_pair(max(i,pre[trans2[i]]),i);
    }

    for(int j=1;j<22;j++)
        for(int i=1;i<=n;i++)
            links[i][j]=merge(links[i][j-1],j-1);

    for(int i=1;i<=q;i++)
    {
        int k;
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            point[i]=bel[getid(x,y)];
        }

        bool allsame=true;
        for(int i=2;i<=k;i++)
            if(point[i]!=point[1])
                allsame=false;

        if(allsame)
        {
            printf("0\n");
            continue;
        }

        sort(point+1,point+k+1,cmp);

        int Maxl=0xcfcfcfcf, newk=0;
        for(int i=1;i<=k;i++)
            if(L[point[i]]>Maxl)
                Maxl=L[point[i]], point[++newk]=point[i];
        k=newk;

        int ans;
        pair <int,int> now;
        if(L[point[1]]<=pre[R[point[1]]])
            ans=2, now.first=R[point[1]], now.second=pre[R[point[1]]];
        else
            ans=3, now.first=now.second=R[point[1]];

        for(int i=2;i<=k;i++)
        {
            ans += calc(now,L[point[i]],R[point[i]]);
            if(ans>3000000)
                break;
        }

        if(ans>3000000)
            printf("-1\n");
        else
            printf("%d\n",ans-1);
    }
    return 0;
}