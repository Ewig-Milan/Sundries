#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 10000000000;
int n;
int x[100005],y[100005];
int d[100005],dis[100005];
set<pair<int,int> >s[4][100005];
vector<int>S[4];
int mp[4][100005],mn[100005][4];
int ans =0 ;

priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
void chkmx(int id,int val,int d){
    if(val>=inf)return;
    mn[id][d] = min(mn[id][d],val);
    if(dis[id]>val){
        dis[id] = val;
        q.push({dis[id],id});
    }
}
void work(){
    for(int i = 1;i<=n;i++)dis[i] = inf;dis[1] = 0;
    for(int i = 0;i<4;i++){
        S[i].clear();
        for(int j = 1;j<=n;j++)s[i][j].clear(),mn[j][i] = inf;
    }
    d[1] = 0;
    for(int i = 2;i<=n;i++){
        if(abs(x[i]) == abs(y[i])){
            if(x[i]>0)d[i] = 2|(y[i]>0);
            else d[i] = 0;
        }else if(abs(x[i])<abs(y[i])){
            d[i] = 2|(y[i]>0);
        }else{
            d[i] = (x[i]>0);
        }
        if(d[i]/2){
            S[3].push_back(x[i]);
        }else{
            S[2].push_back(y[i]);
        }
        S[1].push_back(x[i]-y[i]);
        S[0].push_back(x[i]+y[i]);
    }
    S[0].push_back(0),S[1].push_back(0),S[2].push_back(0),S[3].push_back(0);
    for(int i = 0;i<4;i++){
        sort(S[i].begin(),S[i].end());
        S[i].erase(unique(S[i].begin(),S[i].end()),S[i].end());
    }
    for(int i = 1;i<=n;i++){
        mp[0][i] = lower_bound(S[0].begin(),S[0].end(),x[i]+y[i])-S[0].begin()+1;
        mp[1][i] = lower_bound(S[1].begin(),S[1].end(),x[i]-y[i])-S[1].begin()+1;
        mp[2][i] = lower_bound(S[2].begin(),S[2].end(),y[i])-S[2].begin()+1;
        mp[3][i] = lower_bound(S[3].begin(),S[3].end(),x[i])-S[3].begin()+1;
        if(d[i]/2)s[3][mp[3][i]].insert({y[i],i});
        else s[2][mp[2][i]].insert({x[i],i});
        s[1][mp[1][i]].insert({x[i],i});
        s[0][mp[0][i]].insert({x[i],i});
    }

    q.push({0,1});
    while(!q.empty()){
        auto e = q.top();q.pop();
        int dd = e.first,i = e.second;
        if(dd!=dis[i])continue;
        s[0][mp[0][i]].erase({x[i],i});
        s[1][mp[1][i]].erase({x[i],i});
        if(d[i]/2)s[3][mp[3][i]].erase({y[i],i});
        else s[2][mp[2][i]].erase({x[i],i});
        if(d[i]/2){
            int p = mp[3][i];
            if(d[i]%2){
                auto it = s[3][p].upper_bound({y[i]-2*dd,0});
                if(it!=s[3][p].begin()){
                    --it;
                    int id = it->second;
                    chkmx(id,abs(y[i]-y[id])/2,3);

                }
                it = s[3][p].upper_bound({y[i],i});
                if(it!=s[3][p].end()){
                    int id = it->second;
                    chkmx(id,mn[i][3]+abs(y[i]-y[id])/2,3);
                }
            }else{
                auto it = s[3][p].upper_bound({y[i]+2*dd,0});
                if(it!=s[3][p].end()){
                    int id = it->second;
                    chkmx(id,abs(y[i]-y[id])/2,3);

                }
                it = s[3][p].upper_bound({y[i],i});
                if(it!=s[3][p].begin()){
                    --it;
                    int id = it->second;
                    chkmx(id,mn[i][3]+abs(y[i]-y[id])/2,3);
                }
            }
        }else{
            int p = mp[2][i];
            if(d[i]%2){
                auto it = s[2][p].upper_bound({x[i]-2*dd,0});
                if(it!=s[2][p].begin()){
                    --it;
                    int id = it->second;
                    chkmx(id,abs(x[i]-x[id])/2,2);
                }
                it = s[2][p].upper_bound({x[i],i});
                if(it!=s[2][p].end()){
                    int id = it->second;
                    chkmx(id,mn[i][2]+abs(x[i]-x[id])/2,2);
                }
            }else{
                auto it=  s[2][p].upper_bound({x[i]+2*dd,0});
                if(it!=s[2][p].end()){
                    int id = it->second;
                    chkmx(id,abs(x[i]-x[id])/2,2);
                }
                it = s[2][p].upper_bound({x[i],i});
                if(it!=s[2][p].begin()){
                    --it;
                    int id = it->second;
                    chkmx(id,mn[i][2]+abs(x[i]-x[id])/2,2);
                }
            }
        }
        for(int k = 0;k<2;k++){
            int p = mp[k][i];
            if((k == 1 and d[i]%2) or (k==0 and (d[i] == 1 or d[i] == 2))){
                auto it = s[k][p].upper_bound({x[i]-dd,i});
                if(it!=s[k][p].begin()){
                    --it;
                    int id = it->second;
                    chkmx(id,abs(x[i]-x[id]),k);
                }
                it = s[k][p].upper_bound({x[i],i});
                if(it!=s[k][p].end()){
                    int id = it->second;
                    chkmx(id,mn[i][k]+abs(x[i]-x[id]),k);
                }
            }else{
                auto it = s[k][p].upper_bound({x[i]+dd,i});
                if(it!=s[k][p].end()){
                    int id = it->second;
                    chkmx(id,abs(x[i]-x[id]),k);
                }
                it = s[k][p].upper_bound({x[i],i});
                if(it!=s[k][p].begin()){
                    --it;
                    int id = it->second;
                    chkmx(id,mn[i][k]+abs(x[i]-x[id]),k);
                }
            }
        }
    }
    int tot =0 ;
    for(int i = 1;i<=n;i++)if(dis[i]<inf)++tot;
    ans = max(ans,tot);
}
signed main(){
    freopen("bot.in","r",stdin);
    freopen("bot.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i = 1;i<=n;i++)cin >> x[i] >> y[i];
    for(int i = 1;i<=n;i++)x[i]*=2,y[i]*=2;
    for(int i = n;i>=1;i--)x[i]-=x[1],y[i]-=y[1];
    for(int d = 0;d<4;d++){
        work();
        for(int i = 1;i<=n;i++)swap(x[i],y[i]),x[i] = -x[i];
    }
    cout << ans << endl;
    return 0;
}