#include <bits/stdc++.h>
#define db double
using namespace std;

const int N = 10100, M = 80100;
const db eps = 1e-5;

int n, m, s, t;
db S;
int pidx, id[110][110];

int h[N], e[M], v[M], ne[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

struct Node {
    int id; db dis;
    friend bool operator < (const Node & a, const Node & b) {return a.dis > b.dis;}
};
db dis[N];
bool vis[N];
void dji(db k) {
    memset(vis, 0, sizeof vis);
    for(int i = 0; i < N; i++) dis[i] = 1e9;
    priority_queue<Node> q;
    dis[s] = 0, q.push({s, 0});
    while(!q.empty()) {
        int x = q.top().id;
        q.pop();
        if(x == t) return;
        if(vis[x]) continue;
        vis[x] = 1;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            db V = v[i] == -1 ? k : (db)v[i];
            if(dis[x] + V < dis[j]) {
                dis[j] = dis[x] + V;
                q.push({j, dis[j]});
            }
        }
    }
}

bool check(db k) {
    dji(k);
    return S - dis[t] <= eps;
}

int main() {
    freopen("msg.in", "r", stdin);
    freopen("msg.out", "w", stdout);
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    int sx, sy, tx, ty; scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int a; scanf("%d", &a);
            if(a) continue; 
            id[i][j] = ++pidx;
            if(i == sx && j == sy) s = pidx;
            if(i == tx && j == ty) t = pidx;
            if(id[i - 1][j]) add(id[i - 1][j], pidx, -1);
            if(id[i][j - 1]) add(id[i][j - 1], pidx, 1);
        }
    }
    scanf("%lf", &S);
    db l = 0, r = 1e5;
    while(r - l > eps) {
        db mid = (l + r) / 2;
        if(check(mid)) r = mid; // 大于等于 S
        else l = mid;
    }
    printf("%.3lf", l);
    return 0;
}