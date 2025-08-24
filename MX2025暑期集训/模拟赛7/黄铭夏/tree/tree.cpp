#include <bits/stdc++.h>
using namespace std;

int n;

namespace N_1000 {
    #define PII pair<int, int>
    #define fi first
    #define se second
    const int N = 1100;

    int ans;

    int h[N], e[N << 1], ne[N << 1], idx;
    void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx++;
        e[idx] = a, ne[idx] = h[b], h[b] = idx++;
    }

    int fa[N], siz[N], ma_s[N], dep[N], top[N];
    int dfn[N], L[N], R[N], cnt;

    PII F(PII a, PII b) {return {min(a.fi, b.fi), max(a.se, b.se)};}

    struct TR {
        vector<int> mi, ma;
        void cl(int n) {
            mi.resize(n << 2);
            for(int i = 0; i < (n << 2); i++) mi[i] = 1e9;
            ma.resize(0), ma.resize(n << 2);
        }
        void push_up(int rt) {
            mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
            ma[rt] = max(ma[rt << 1], ma[rt << 1 | 1]);
        }
        void build(int rt, int l, int r) {
            if(l == r) {
                mi[rt] = dfn[l], ma[rt] = dfn[l];
                return;
            }
            int mid = l + r >> 1;
            build(rt << 1, l, mid);
            build(rt << 1 | 1, mid + 1, r);
            push_up(rt);
        }
        PII query(int rt, int l, int r, int ql, int qr) {
            if(ql <= l && qr >= r) return {mi[rt], ma[rt]};
            int mid = l + r >> 1;
            PII ans = {1e9, 0}; // min max
            if(ql <= mid) ans = F(ans, query(rt << 1, l, mid, ql, qr));
            if(qr > mid) ans = F(ans, query(rt << 1 | 1, mid + 1, r, ql, qr));
            return ans;
        }
    }t;

    void dfs_pre(int x, int l) {
        fa[x] = l, siz[x] = 1, dep[x] = dep[l] + 1;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == l) continue;
            dfs_pre(j, x);
            siz[x] += siz[j];
            if(siz[j] > siz[ma_s[x]]) ma_s[x] = j;
        }
        return;
    }

    void dfs_top(int x, int tp) {
        dfn[++cnt] = x, L[x] = cnt, top[x] = tp;
        if(ma_s[x]) dfs_top(ma_s[x], tp);
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == fa[x] || j == ma_s[x]) continue;
            dfs_top(j, j);
        }
        R[x] = cnt;
    }

    PII query_path(int x, int y) {
        PII ans = {1e9, 0}; // min max
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) swap(x, y);
            ans = F(ans, t.query(1, 1, n, L[top[x]], L[x]));
            x = fa[top[x]];
        }
        if(dep[x] < dep[y]) swap(x, y);
        ans = F(ans, t.query(1, 1, n, L[y], L[x]));
        return ans;
    }

    void work() {
        memset(h, -1, sizeof h);
        for(int i = 1; i < n; i++) {
            int a, b; scanf("%d%d", &a, &b);
            add(a, b);
        }
        dep[0] = -1;
        dfs_pre(1, 0);
        dfs_top(1, 1);
        t.cl(n);
        t.build(1, 1, n);
        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                PII tmp = query_path(i, j);
                if((i == tmp.fi || i == tmp.se) && (j == tmp.fi || j == tmp.se)) ans++;
            }
        }
        printf("%d\n", ans);
    }
};

namespace Flower {
    const int N = 100100;

    int d[N], leq, deq;

    void work() {
        for(int i = 1; i < n; i++) {
            int a, b; scanf("%d%d", &a, &b);
            d[a]++, d[b]++;
        }
        int rt;
        for(int i = 1; i <= n; i++) if(d[i] == n - 1) {
            rt = i;
            break;
        }
        for(int i = 1; i <= n; i++) if(i != rt) {
            if(i < rt) leq++;
            else deq++;
        }
        printf("%lld", (long long)leq * deq + (long long)(n - 1));
    }
};

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    if(n <= 1000) N_1000::work();
    Flower::work();
    return 0;
}