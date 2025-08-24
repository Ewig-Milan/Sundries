#include <bits/stdc++.h>
#define Lb(x) ((x) & -(x))
using namespace std;

const int N = 1000100;

int n, m, q;
int ans[N];
struct Magic {int a, b;} mgc[N];
struct Ques {int r, id;};
vector<Ques> Q[N];

int pidx, w[N], fa[N][21], dep[N];

struct Bit_T {
    int sum[N];
    void modify(int l, int r, int delta) {
        while(l <= m) sum[l] += delta, l += Lb(l);
        r++;
        while(r <= m) sum[r] -= delta, r += Lb(r);
    }
    int query(int x) {
        int res = 0;
        while(x) res += sum[x], x -= Lb(x);
        return res;
    }
}t;

int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 20; i >= 0; i--)
        if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if(x == y) return y;
    for(int i = 20; i >= 0; i--) if(fa[x][i] != fa[y][i])
        x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= m; i++) scanf("%d%d", &mgc[i].a, &mgc[i].b);
    for(int i = 1; i <= q; i++) {
        int a, b; scanf("%d%d", &a, &b);
        Q[a].push_back({b, i});
    }
    w[0] = m + 1, pidx = n;
    for(int i = 1; i < n; i++) t.modify(1, w[LCA(i, i + 1)] - 1, 1);
    for(int i = m; i; i--) {
        int a = mgc[i].a, b = mgc[i].b;
        if(a != b) {
            if(a < n) t.modify(1, w[LCA(a, a + 1)] - 1, -1);
            if(a > 1) t.modify(1, w[LCA(a, a - 1)] - 1, -1);
            w[++pidx] = i, dep[pidx] = dep[b];
            memcpy(fa[pidx], fa[b], sizeof fa[b]);
            fa[a][0] = pidx, dep[a] = dep[b] = dep[pidx] + 1;
            for(int i = 1; i < 21; i++) fa[a][i] = fa[fa[a][i - 1]][i - 1];
            memcpy(fa[b], fa[a], sizeof fa[a]);
            if(a < n) t.modify(1, w[LCA(a, a + 1)] - 1, 1);
            if(a > 1) t.modify(1, w[LCA(a, a - 1)] - 1, 1);
        }
        for(auto x : Q[i]) ans[x.id] = t.query(x.r);
    }
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i] + 1);
    return 0;
}