#include <bits/stdc++.h>
using namespace std;

const int N = 200100, M = 400100;

int dsu[N];
int find(int x) {return x == dsu[x] ? x : dsu[x] = find(dsu[x]);}
bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    dsu[a] = b;
    return true;
}

int n, m, H[N];
int ans[N];

struct Edge {
    int a, b, val;
    friend bool operator < (const Edge &a, const Edge &b) {return a.val < b.val;}
};
vector<Edge> E, rem;

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

// 链赋值 树剖
int L[N], dfn[N], cnt, dep[N], fa[N]; // L: 点 id -> dfn  dfn: dfn 序-get_ans 需要
int siz[N], ma_s[N], top[N];
void dfs_pre(int x, int l) {
    siz[x] = 1, dep[x] = dep[l] + 1, fa[x] = l;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs_pre(j, x);
        siz[x] += siz[j];
        if(siz[j] > siz[ma_s[x]]) ma_s[x] = j;
    }
}

void get_top(int x, int l, int tp) {
    L[x] = ++cnt, dfn[cnt] = x, top[x] = tp;
    if(ma_s[x]) get_top(ma_s[x], x, tp);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || j == ma_s[x]) continue;
        get_top(j, x, j);
    }
}

struct TR {
    vector<int> num, ly;
    void cl(int Nn) {
        num.resize(Nn << 2), ly.resize(Nn << 2);
        for(int i = 0; i < (Nn << 2); i++) num[i] = ly[i] = -1;
    }
    void push_down(int rt) {
        if(ly[rt] == -1) return;
        ly[rt << 1] = ly[rt << 1 | 1] = ly[rt];
        num[rt << 1] = num[rt << 1 | 1] = ly[rt];
        ly[rt] = -1;
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        if(ql <= l && qr >= r) {
            ly[rt] = num[rt] = x;
            return;
        }
        push_down(rt);
        int mid = (l + r) >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
    }
    void get_ans(int rt, int l, int r) {
        if(l == r) {
            ans[dfn[l]] = num[rt];
            return;
        }
        push_down(rt);
        int mid = (l + r) >> 1;
        get_ans(rt << 1, l, mid), get_ans(rt << 1 | 1, mid + 1, r);
    }
}t;

void modify(int x, int y, int a) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        t.modify(1, 1, n, L[top[x]], L[x], a);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    t.modify(1, 1, n, L[y], L[x], a);
}

int main() {

    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);

    memset(h, -1, sizeof h);
    for(int i = 1; i < N; i++) dsu[i] = i;

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &H[i]);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        E.push_back({a, b, abs(H[a] - H[b])});
    }
    sort(E.begin(), E.end());
    for(auto x : E)
        if(merge(x.a, x.b)) add(x.a, x.b);
        else rem.push_back(x);

    dep[0] = -1;
    dfs_pre(1, 0), get_top(1, 0, 1);
    t.cl(n);
    
    reverse(rem.begin(), rem.end()); // 大 -> 小
    for(auto x : rem) modify(x.a, x.b, x.val);
    t.get_ans(1, 1, n);
    for(int i = 1; i <= n; i++) {
        printf("%d", ans[i]);
        if(i < n) putchar(' ');
    }
    putchar('\n');
    return 0;
}