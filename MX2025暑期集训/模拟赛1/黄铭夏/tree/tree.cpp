#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100;

int q, w[N], p_idx = 1, w_[N];
struct Ques {int mode, id;} Q[N];

int h[N], e[N], ne[N], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

int L[N], R[N], id[N], dep[N], cnt;
int ma_s[N], siz[N];
int tp[N], fa[N];

void dfs_pre(int x, int l) {
    fa[x] = l, dep[x] = dep[l] + 1, siz[x] = 1;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        dfs_pre(j, x);
        siz[x] += siz[j];
        if(siz[j] > siz[ma_s[x]]) ma_s[x] = j;
    }
}

void dfs_top(int x, int top) {
    tp[x] = top, L[x] = ++cnt, id[cnt] = x;
    if(ma_s[x]) dfs_top(ma_s[x], top);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == ma_s[x]) continue;
        dfs_top(j, j);
    }
    R[x] = cnt;
}

struct TR {
    vector<int> a, b, c, ly;
    void cl(int n) {
        a.resize(0), a.resize(n << 2);
        b.resize(0), b.resize(n << 2);
        c.resize(0), c.resize(n << 2);
        ly.resize(0), ly.resize(n << 2);
    }
    void push_up(int rt) {
        a[rt] = a[rt << 1] + a[rt << 1 | 1];
        b[rt] = b[rt << 1] + b[rt << 1 | 1];
        c[rt] = c[rt << 1] + c[rt << 1 | 1];
    }
    void build(int rt, int l, int r) {
        if(l == r) {
            b[rt] = c[rt] = w_[id[l]];
            return;
        }
        int mid = l + r >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void op(int rt, int k) {
        a[rt] += k * b[rt] + k * (k - 1) / 2 * c[rt];
        b[rt] += c[rt] * k;
    }
    void push_down(int rt) {
        if(!ly[rt]) return;
        op(rt << 1, ly[rt]);
        op(rt << 1 | 1, ly[rt]);
        ly[rt << 1] += ly[rt];
        ly[rt << 1 | 1] += ly[rt];
        ly[rt] = 0;
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        if(ql <= l && qr >= r) {
            op(rt, x), ly[rt] += x;
            return;
        }
        push_down(rt);
        int mid = l + r >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
        push_up(rt);
    }
}t;

void modify(int x, int y, int delta) {
    while(tp[x] != tp[y]) {
        if(dep[tp[x]] < dep[tp[y]]) swap(x, y);
        t.modify(1, 1, p_idx, L[tp[x]], L[x], delta);
        x = fa[tp[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    t.modify(1, 1, p_idx, L[y], L[x], delta);
}

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld%lld", &q, &w[1]);
    w_[1] = w[1], Q[0] = {1, 1}, dep[0] = -1;
    for(int i = 1; i <= q; i++) {
        scanf("%lld", &Q[i].mode);
        if(Q[i].mode == 1) {
            Q[i].id = ++p_idx;
            int b; scanf("%lld%lld", &w[p_idx], &b);
            w_[p_idx] = w[p_idx] - w[b];
            add(b, p_idx);
        }
    }
    dfs_pre(1, 0), dfs_top(1, 1);
    t.cl(p_idx), t.build(1, 1, p_idx);
    for(int i = 0; i <= q; i++) {
        if(Q[i].mode == 2) printf("%lld\n", t.a[1]);
        else modify(1, Q[i].id, 1);
    }
    return 0;
}