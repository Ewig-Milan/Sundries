#include<bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxn = 5e5 + 5;
struct Node{
    LL ans;
    vector<pair<LL, int> > v;

}dp[maxn];

Node merge(const Node &a, const Node &b){
    Node ret;
    ret.ans = max(a.ans, b.ans);
    for(auto va : a.v){
        for(auto vb : b.v){
            LL x=va.first, y=vb.first;
            int id1=va.second, id2=vb.second;
            if (id1 != id2){
                ret.ans = max(ret.ans, x & y);
            }
        }
    }
    ret.v.resize(a.v.size() + b.v.size());
    merge(a.v.begin(), a.v.end(), b.v.begin(), b.v.end(), ret.v.begin());
    auto &v = ret.v;
    v.erase(unique(v.begin(), v.end()), v.end());
    auto it = upper_bound(v.begin(), v.end(), make_pair(ret.ans, 1000'000));
    v.erase(v.begin(), it);
    return ret;
}

int main(){

    freopen("stone.in", "r", stdin);
    freopen("stone.out", "w", stdout);

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        LL x;
        cin >> x;
        dp[i].ans = 0;
        dp[i].v = {{x, i}};
    }
    vector<vector<int> > g(n + 1);
    vector<int> din(n + 1);
    vector<bool> leaf(n + 1);
    while(m--){
        int a, b;
        cin >> a >> b;
        g[b].push_back(a);
        din[a] += 1;
    }
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if (din[i] == 0){
            leaf[i] = true;
            q.push(i);
        }
    }
    while(!q.empty()){
        int t = q.front();
        q.pop();
        for(auto j : g[t]){
            dp[j] = merge(dp[j], dp[t]);
            if (--din[j] == 0){
                q.push(j);
            }
        }
    }
    for(int i = 1; i <= n; i++){
        if (leaf[i]) dp[i].ans = -1;
        cout << dp[i].ans << " \n"[i == n];
    }

}