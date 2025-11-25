#include <bits/stdc++.h>
using namespace std;
#define rep(i, j, k) for(int i = (j); i <= (k); i++)
#define per(i, j, k) for(int i = (j); i >= (k); i--)
#define pb emplace_back
#define fi first
#define se second
using vi = vector<int>;
using pi = pair<int, int>;

template<typename T0, typename T1> bool chmin(T0 &x, const T1 &y){
    if(y < x){x = y; return true;} return false;
}
template<typename T0, typename T1> bool chmax(T0 &x, const T1 &y){
    if(x < y){x = y; return true;} return false;
}

template<typename T> void debug(char *s, T x){
    cerr << s <<" = "<< x <<endl;
}
template<typename T, typename ...Ar> void debug(char *s, T x, Ar... y){
    int dep = 0;
    while(!(*s == ',' && dep == 0)){
        if(*s == '(') dep++;
        if(*s == ')') dep--;
        cerr << *s++;
    }
    cerr <<" = "<< x <<",";
    debug(s + 1, y...);
}
#define gdb(...) debug((char*)#__VA_ARGS__, __VA_ARGS__)

const int N = 1e6 + 5;
vi flow(int n, int m, const vector<vi> &G){
    static vi vis(N), match(N), pre(N), dis(N);

    fill(vis.begin(), vis.begin() + n, 0);
    fill(match.begin(), match.begin() + n, -1);
    fill(pre.begin(), pre.begin() + m, -1);
    
    auto bfs = [&]()->bool {
        fill(dis.begin(), dis.begin() + n, -1);
        static queue<int> Q;
        rep(i, 0, n - 1){
            if(match[i] == -1){
                dis[i] = 0;
                Q.emplace(i);
            }
        }
        bool o = 0;
        while(Q.size()){
            int u = Q.front();
            Q.pop();
            for(int v:G[u]){
                int r = pre[v];
                if(r == -1){
                    o = 1;
                } else if(dis[r] == -1){
                    dis[r] = dis[u] + 1;
                    Q.emplace(r);
                }
            }
        }
        return o;
    };

    auto dfs = [&](auto &self, int u)->bool {
        if(vis[u]){
            return false;
        }
        vis[u] = 1;
        for(int v:G[u]){
            int r = pre[v];
            if(r == -1 || (dis[r] == dis[u] + 1 && self(self, r))){
                match[u] = v, pre[v] = u;
                return true;
            }
        }
        return false;
    };

    int cnt = 0;
    while(bfs()){
        fill(vis.begin(), vis.begin() + n, 0);
        rep(i, 0, n - 1){
            if(match[i] == -1){
                cnt += dfs(dfs, i);
            }
        }
    }

    if(cnt == n){
        return {-1};
    } else if(cnt < n - 1){
        return {};
    } else{
        vi V;
        fill(vis.begin(), vis.begin() + n, 0);
        bfs();
        dfs(dfs, find(match.begin(), match.end(), -1) - match.begin());
        rep(i, 0, n - 1){
            if(vis[i]){
                V.pb(i);
            }
        }
        return V;
    }
}

void solve(){
    int n;
    cin >> n;
    vector<vi> G0(n);
    rep(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        u --, v --;
        G0[u].pb(v);
        G0[v].pb(u);
    }
    int m;
    cin >> m;
    vector<vi> G1(m);
    rep(i, 1, m - 1){
        int u, v;
        cin >> u >> v;
        u --, v --;
        G1[u].pb(v);
        G1[v].pb(u);
    }
    vector<vi> S(m), fS(m);
    {
        auto dfs = [&](auto &self, int u)->void {
            for(int v:G1[u]){
                S[u].pb(v);
                fS[u].pb(v + m);
                S[v].pb(v + m);
                fS[v].pb(v);
                G1[v].erase(find(G1[v].begin(), G1[v].end(), u));
                self(self, v);
            }
        };
        dfs(dfs, 0);
    }

    bool ans = 0;
    vector< vector<bool> > f(n, vector<bool>(m * 2));
    auto dfs = [&](auto &self, int u)->void {
        for(int v:G0[u]){
            G0[v].erase(find(G0[v].begin(), G0[v].end(), u));
            self(self, v);
        }
        rep(i, 0, m - 1){
            static vector<vi> E(N);
            rep(j, 0, (int)G0[u].size() - 1){
                int v = G0[u][j];
                rep(k, 0, (int)S[i].size() - 1){
                    if(f[v][ S[i][k] ]){
                        E[k].pb(j);
                    }
                }
            }
            vi match = flow(S[i].size(), G0[u].size(), E);
            if(match == (vi){-1}){
                ans = 1;
            } else{
                for(int x:match){
                    f[u][ fS[i][x] ] = 1;
                }
            }
            rep(j, 0, (int)S[i].size() - 1){
                E[j].clear();
            }
        }
    };
    dfs(dfs, 0);
    cout << (ans? "Yes": "No") <<'\n';
}
signed main(){
    freopen("winter.in", "r", stdin);
    freopen("winter.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int tid;
    cin >> tid;
    int t;
    cin >> t;
    rep(_, 1, t){
        solve();
    }
}