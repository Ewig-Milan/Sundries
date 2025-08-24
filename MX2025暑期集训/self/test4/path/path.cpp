#include <bits/stdc++.h>
#define int long long
using namespace std;

int k, m, s;

namespace M_0 {
    int f[2000];
    void work() {
        int n = 1 << k;
        memset(f, 63, sizeof f);
        for(int i = 1; i <= k; i++) scanf("%lld", &f[i]);
        f[0] = 0;
        for(int times = 1; times <= 300; times++) // 30
        for(int i = 0; i <= k; i++) { // 20
            for(int j = 0; j <= k; j++) // 20
            for(int K = i + j; K >= max(i - j, j - i); K -= 2) // 20
                if((i + j + K >> 1) <= k) f[K] = min(f[K], f[i] + f[j]);
        }
        for(int i = 0; i < n; i++) { // 1e5
            int dif = s ^ i, cnt = 0;
            for(int j = 0; j <= k; j++) if(dif & (1 << j)) cnt++; // 20
            printf("%lld ", f[cnt]);
        }
    }
};

namespace Mnot0 {
    const int N = 1000100;
    int n;

    int h[N], e[N << 1], ne[N << 1], v[N << 1], idx;
    void add(int a, int b, int c) {
        e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
        e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++; 
    }

    int A[20];

    struct Node {
        int id, dis;
        friend bool operator < (const Node & a, const Node & b) {return a.dis > b.dis;}
    };
    int dis[N];
    bool vis[N];
    void dji(int s) {
        memset(vis, 0, sizeof vis);
        memset(dis, 63, sizeof dis);
        priority_queue<Node> q;
        dis[s] = 0, q.push({s, 0});
        while(!q.empty()) {
            int x = q.top().id;
            q.pop();
            if(vis[x]) continue;
            vis[x] = 1;
            for(int i = h[x]; ~i; i = ne[i]) {
                int j = e[i];
                if(dis[x] + v[i] < dis[j]) {
                    dis[j] = dis[x] + v[i];
                    q.push({j, dis[j]});
                }
            }
        }
    }

    void work() {
        n = 1 << k;
        memset(h, -1, sizeof h);
        for(int i = 1; i <= k; i++) scanf("%lld", &A[i]);
        for(int i = 1; i <= m; i++) {
            int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
            add(a, b, c);
        }
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            int dif = i ^ j, cnt = 0;
            for(int j = 0; j <= k; j++) if(dif & (1 << j)) cnt++;
            add(i, j, A[cnt]);
        }
        dji(s);
        for(int i = 0; i < n; i++) printf("%lld ", dis[i]);
    }
};

signed main() {
    scanf("%lld%lld%lld", &k, &m, &s);
    if(!m) M_0::work();
    else Mnot0::work();
    return 0;
}