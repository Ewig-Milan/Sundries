#include <bits/stdc++.h>
using namespace std;

const int N = 12100, M = 70100;

int n, m, q;
int p_idx;
vector<int> P[2100];

int dis[2100][2100];

int h[N], e[M], v[M], ne[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int t_dis[N];
bool vis[N];
void bfs(int s) {
    memset(t_dis, 63, sizeof t_dis);
    memset(vis, 0, sizeof vis);
    deque<int> q;
    t_dis[s] = 0;
    q.push_back(s);
    while(!q.empty()) {
        int x = q.front();
        q.pop_front();
        if(vis[x] || (x <= n && x != s)) continue;
        vis[x] = 1;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(vis[j]) continue;
            if(t_dis[j] > t_dis[x] + v[i]) {
                t_dis[j] = t_dis[x] + v[i];
                if(v[i]) q.push_back(j);
                else q.push_front(j);
            }
        }
    }
}

int main() {
    freopen("orz.in", "r", stdin);
    freopen("orz.out", "w", stdout);
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    p_idx = n + 1;
    for(int j = 1; j <= m; j++) {
        int a, b = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a);
            add(a, p_idx, 0), add(p_idx, a, 0);
            for(int x : P[a]) add(x, p_idx, 1), add(p_idx, x, 1);
            P[a].push_back(p_idx);
            if(b) add(b, p_idx, 0);
            b = p_idx++;
        }
    }
    for(int i = 1; i <= n; i++) {
        bfs(i);
        for(int j = 1; j <= n; j++) if(i != j) dis[i][j] = t_dis[j];
    }
    scanf("%d", &q);
    while(q--) {
        int a, b; scanf("%d%d", &a, &b);
        printf("%d\n", dis[a][b] > 1e9 ? -1 : dis[a][b] + 1);
    }
    return 0;
}