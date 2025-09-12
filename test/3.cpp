#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 500100, M = N << 1;
const int mod = 1e9 + 7;

int quick_p(int x, int a) {
    int res = 1;
    while(a > 0) {
        if(a & 1) res *= x, res %= mod;
        a >>= 1;
        x *= x, x %= mod;
    }
    return res;
}

int n, m, ans;

vector<int> bl[N];
int bl_cnt, bl_id[N];

int esiz[N], psiz[N]; // 下标为 bl_id
int res[N][2], f[N][2]; // 下表为 bl_id
int ecnt[N];

struct CFS {
    int h[N], e[M << 1], ne[M << 1], idx;
    void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

    int dfn[N], low[N], cnt;
    stack<int> S;
    void tarjan(int x, int l) {
        S.push(x);
        dfn[x] = low[x] = ++cnt;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if((i ^ 1) == l) continue;
            if(!dfn[j]) tarjan(j, i), low[x] = min(low[x], low[j]);
            else low[x] = min(low[x], dfn[j]);
        }
        if(dfn[x] == low[x]) {
            bl_id[x] = ++bl_cnt;
            bl[bl_cnt].push_back(x);
            while(S.top() != x) {
                bl_id[S.top()] = bl_cnt;
                bl[bl_cnt].push_back(S.top());
                S.pop();
            }
            S.pop();
        }
    }

    void get_ecnt(int x, int l) {
        ecnt[x] = esiz[x];
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == l) continue;
            get_ecnt(j, x);
            ecnt[x] += ecnt[j] + 1;
        }
    }

    void DP(int x, int l) {
        f[x][0] = res[x][0], f[x][1] = (res[x][1] + res[x][0]) % mod;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == l) continue;
            DP(j, x);
            f[x][0] *= (f[j][0] << 1) % mod, f[x][0] %= mod;
            f[x][1] *= ((f[j][0] << 1) % mod + f[j][1]) % mod, f[x][1] %= mod;
        }
        f[x][1] = (f[x][1] - f[x][0] + mod) % mod;
        ans += f[x][1] * quick_p(2, ecnt[1] - ecnt[x] - 1) % mod, ans %= mod;
    }
}mp, bl_mp;

signed main() {
    memset(mp.h, -1, sizeof mp.h);
    memset(bl_mp.h, -1, sizeof bl_mp.h);    
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        mp.add(a, b), mp.add(b, a);
    }
    mp.tarjan(1, -1);
    for(int i = 1; i <= bl_cnt; i++) {
        psiz[i] = (int)bl[i].size();
        for(int x : bl[i])
        for(int k = mp.h[x]; ~k; k = mp.ne[k]) {
            int j = mp.e[k];
            if(bl_id[j] != i) bl_mp.add(i, bl_id[j]);
            else esiz[i]++;
        }
        esiz[i] >>= 1;
        res[i][0] = quick_p(2, esiz[i]);
        res[i][1] = (quick_p(2, psiz[i]) - 1) * quick_p(2, esiz[i]) % mod;
    }
    bl_mp.get_ecnt(1, 0);
    bl_mp.DP(1, 0);
    printf("%lld", ans);
    return 0;
}