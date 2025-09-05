#include <bits/stdc++.h>
#define ll long long
#define PIL pair<int, ll>
using namespace std;

const int N = 200100, mod = 998244353;

int T, n, P_cnt, ans[N];
int P[N << 1];
vector<int> B, cir;
stack<int> S;
int dfn[N], low[N], cnt;
bool in_cir[N];

int h[N << 1], e[N << 2], ne[N << 2], v[N << 2], idx;
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

int fa[N << 1], p_siz[N << 1], e_siz[N << 1], self_cir[N << 1];
int find(int x) {
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
void merge(int a, int b) {
    a = find(a), b = find(b);
    e_siz[a]++;
    if(a == b) return;
    if(p_siz[a] < p_siz[b]) swap(a, b);
    fa[b] = a;
    p_siz[a] += p_siz[b];
    e_siz[a] += e_siz[b];
    self_cir[a] = max(self_cir[a], self_cir[b]);
}

int dfs(int x, int l) {
    int res = 0;
    B.push_back(x);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || in_cir[j]) continue;
        res += dfs(j, x);
        if(v[i]) res++;
    }
    return res;
}

void DP(int x, int l) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        if(v[i]) ans[j] = ans[x] - 1;
        else ans[j] = ans[x] + 1;
        DP(j, x);
    }
}

PIL work_tree(int rt) {
    int mi = 1e9; ll mi_ans = 1;
    B.resize(0);
    ans[rt] = dfs(rt, 0);
    DP(rt, 0);
    for(int i : B) {
        if(ans[i] < mi) mi = ans[i], mi_ans = 0;
        if(ans[i] == mi) mi_ans++;
    }
    return {mi, mi_ans};
}

void find_cir(int x, int l) {
    S.push(x);
    dfn[x] = low[x] = ++cnt;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if((i ^ 1) == l) continue;
        if(!dfn[j]) {
            find_cir(j, i);
            low[x] = min(low[x], low[j]);
        } else low[x] = min(low[x], dfn[j]);
    }
    if(low[x] == dfn[x]) {
        if(S.top() != x) cir.push_back(x), in_cir[x] = 1;
        while(S.top() != x) {
            cir.push_back(S.top());
            in_cir[S.top()] = 1;
            S.pop();
        }
        S.pop();
    }
}

PIL work_cir(int rt) {
    int mi = 0, V1 = 0, V0 = 0; ll mi_ans;
    cir.resize(0);
    find_cir(rt, -1);
    for(int i : cir) mi += dfs(i, 0);
    for(int i = h[cir[0]], j = cir[0], l = -1; l == -1 || j != cir[0]; l = i, j = e[i], i = h[j]) {
        while(!in_cir[e[i]] || (i ^ 1) == l) i = ne[i];
        if(v[i]) V1++;
        else V0++;
    }
    if(V1 == V0) mi_ans = 2, mi += V1;
    else mi_ans = 1, mi += min(V1, V0);
    return {mi, mi_ans};
}

int main() {
    memset(h, -1, sizeof h);
    for(int i = 0; i < N << 1; i++) fa[i] = i, p_siz[i] = 1;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        if(!P[a]) P[a] = ++P_cnt;
        if(!P[b]) P[b] = ++P_cnt;
        if(P[a] == P[b]) self_cir[find(P[a])] = P[a];
        merge(P[a], P[b]);
        add(P[a], P[b], 1); add(P[b], P[a], 0);
    }
    int mi = 0; ll mi_ans = 1;
    for(int i = 1; i <= P_cnt; i++) {
        if(fa[i] != i) continue;
        if(e_siz[i] > p_siz[i]) {
            mi = -1, mi_ans = -1;
            break;
        } else if(self_cir[i]) mi += dfs(self_cir[i], self_cir[i]);
        else if(e_siz[i] == p_siz[i]) {
            PIL res = work_cir(i);
            mi += res.first;
            mi_ans = (mi_ans * res.second) % mod;
        } else {
            PIL res = work_tree(i);
            mi += res.first;
            mi_ans = (mi_ans * res.second) % mod;
        }
    }
    printf("%d %lld\n", mi, mi_ans);
    return 0;
}