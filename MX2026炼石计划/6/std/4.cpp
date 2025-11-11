#include <bits/stdc++.h>

using namespace std;

#define pb push_back

typedef long long ll;
typedef vector<int> vi;

const int N = 1e5 + 5, M = 3e5 + 5, K = 6e6 + 5, inf = 2e9;

int n, m, k;
int a[N], w[N], pos[N];
vi g[M];
int v[M];
int fa[M], dep[M], sz[M], son[M];
int ch[K][2], tot, s[K], tp, c[K];
int ans[N];
int grt;

void dfs1(int x, int fat, int dpt) {
    fa[x] = fat, dep[x] = dpt, sz[x] = 1;
    for (auto y : g[x]) if (y != fa[x]) {
        dfs1(y, x, dep[x] + 1);
        sz[x] += sz[y];
        if (!son[x] || sz[son[x]] < sz[y]) son[x] = y;
    }
}

inline int nwnd() {
    if (tp) return s[tp--];
    else return ++tot;
}

inline void clr(int p) {
    s[++tp] = p, ch[p][0] = ch[p][1] = c[p] = 0;
}

inline void ins(int &rt, int x, int v) {
    if (!rt) rt = nwnd();
    int p = rt;
    c[rt] += v;
    for (int i = 29; i >= 0; i--) {
        int o = (x >> i & 1);
        if (!ch[p][o]) ch[p][o] = nwnd();
        int q = ch[p][o];
        c[q] += v;
        if (!c[q]) ch[p][o] = 0;
        if (!c[p]) clr(p);
        p = q;
    }
    if (!c[p]) clr(p);
    if (!c[rt]) rt = 0;
}

inline int qry(int p, int x) {
    if (!p) return inf;
    int res = 0;
    for (int i = 29; i >= 0; i--) {
        int o = (x >> i & 1);
        if (ch[p][o]) p = ch[p][o];
        else p = ch[p][o^1], res ^= (1 << i); 
        assert(p);
    }
    return res;
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    c[x] += c[y];
    ch[x][0] = merge(ch[x][0], ch[y][0]);
    ch[x][1] = merge(ch[x][1], ch[y][1]);
    clr(y);
    return x;
}

int dfs2(int x) {
    static int col[N];
    vi p;
    function<void(int, int)> dfs3 = [&](int x, int o) {
        if (v[x]) p.pb(v[x]), col[v[x]] = o;
        for (auto y : g[x]) if (y != fa[x]) dfs3(y, o);    
    };
    if (v[x]) {
        ans[v[x]] = min(ans[v[x]], qry(grt, a[v[x]]));
        p.pb(v[x]), col[v[x]] = x;
    }
    for (auto y : g[x]) if (y != fa[x] && y != son[x]) {
        dfs3(y, y);
    }
    int qwq = 0;
    for (int i = 0, j = 0; i < (int)p.size(); i++) {
        while (j < i && col[p[j]] != col[p[i]]) {
            ins(qwq, a[p[j]], 1);
            j++;
        }
        ans[p[i]] = min(ans[p[i]], qry(qwq, a[p[i]] ^ w[dep[x]]));
    }
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        if (col[p[i]] != col[p.back()]) break;
        ins(qwq, a[p[i]], 1);
    }
    for (int i = 0, j = 0; i < (int)p.size(); i++) {
        while (j < (int)p.size() && col[p[j]] == col[p[i]]) {
            ins(qwq, a[p[j]], -1);
            j++;
        }
        ans[p[i]] = min(ans[p[i]], qry(qwq, a[p[i]] ^ w[dep[x]]));
    }
    assert(qwq == 0);
    
    for (auto i : p) {
        ins(grt, a[i] ^ w[dep[x]], 1);
    }
    int rt = 0;
    if (son[x]) {
        rt = dfs2(son[x]);
    }
    for (auto i : p) {
        ins(grt, a[i] ^ w[dep[x]], -1);
        ans[i] = min(ans[i], qry(rt, a[i] ^ w[dep[x]]));
    }
    for (auto y : g[x]) if (y != fa[x] && y != son[x]) {
        int k = dfs2(y);
        rt = merge(rt, k);
    }
    if (v[x]) {
        ins(rt, a[v[x]], 1);
    }
    return rt;
}

int main()
{
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i <= m; i++) scanf("%d", &w[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ans[i] = inf;
    for (int i = 1; i < k; i++) {
        int x, y;
        static char str[10];
        scanf("%d%d%s", &x, &y, str);
        g[x].pb(y), g[y].pb(x);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &pos[i]);
        v[pos[i]] = i;
    }
    dfs1(1, 0, 0);
    dfs2(1);
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
//        printf("ans[%d] = %d\n", i, ans[i]);
        sum += ans[i];
    }
    printf("%lld\n", sum);
    return 0;
}