#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 45, mod = 1e9 + 7;

int n, m, ans;
int X[N], Y[N], choice_0[N], choice_1[N];
int min_case[N], new_case[N];

// 以下记的是基于前缀和的约束
int method[N];
vector<int> CC[N];
int dis[N], id[N];
int h[N], e[N << 1], v[N << 1], ne[N << 1], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

bool vis[N];
int cnt;
void map_dfs(int x, int l) {
    vis[x] = 1, id[x] = cnt;
    CC[cnt].push_back(x);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(vis[j]) {
            if(dis[j] != dis[x] ^ v[i]) {
                puts("0\n-1");
                exit(0);
            }
            continue;
        }
        dis[j] = dis[x] ^ v[i];
        map_dfs(j, x);
    }
}

int f[N][2];
bool reach[2];
vector<int> back[N][2], nxt[N][2];

void work() {
    f[0][0] = 1, f[0][1] = 0;
    for(int i = 1; i <= n; i++) {
        back[i][0].resize(0), back[i][1].resize(0);
        nxt[i][0].resize(0), nxt[i][1].resize(0);
        if(method[i] != 0) {
            f[i][1] = ((ll)f[i - 1][1] * choice_0[i] % mod + (ll)f[i - 1][0] * choice_1[i] % mod) % mod;
            if(f[i - 1][1] && choice_0[i]) back[i][1].push_back(1);
            if(f[i - 1][0] && choice_1[i]) back[i][1].push_back(0);
        } else f[i][1] = 0;
        if(method[i] != 1) {
            f[i][0] = ((ll)f[i - 1][1] * choice_1[i] % mod + (ll)f[i - 1][0] * choice_0[i] % mod) % mod;
            if(f[i - 1][1] && choice_1[i]) back[i][0].push_back(1);
            if(f[i - 1][0] && choice_0[i]) back[i][0].push_back(0);
        } else f[i][0] = 0;
    }
    for(int i = n; i > 1; i--) {
        if(!nxt[i][0].empty() || i == n) for(int x : back[i][0]) nxt[i - 1][x].push_back(0);
        if(!nxt[i][1].empty() || i == n) for(int x : back[i][1]) nxt[i - 1][x].push_back(1);
    }
    reach[0] = !nxt[1][0].empty();
    reach[1] = !nxt[1][1].empty();
    bool now = 0;
    for(int i = 1; i <= n; i++) {
        if(reach[X[i] & 1]) {
            new_case[i] = X[i], now ^= (X[i] & 1);
            reach[0] = reach[1] = 0;
            for(int x : nxt[i][now]) reach[x ^ now] = 1;
        } else {
            new_case[i] = X[i] + 1, now ^= !(X[i] & 1);
            reach[0] = reach[1] = 0;
            for(int x : nxt[i][now]) reach[x ^ now] = 1;
        }
    }
    if(f[n][0] || f[n][1]) for(int i = 1; i <= n; i++) {
        if(new_case[i] < min_case[i]) {
            swap(new_case, min_case);
            break;
        }
        if(new_case[i] > min_case[i]) break;
    }
    ans += (f[n][1] + f[n][0]) % mod, ans %= mod;
}

void dfs(int dep) {
    if(dep > cnt) {
        work();
        return;
    }
    for(int i : CC[dep]) method[i] = 0 ^ dis[i];
    dfs(dep + 1);
    if(CC[dep][0]) {
        for(int i : CC[dep]) method[i] = 1 ^ dis[i];
        dfs(dep + 1);
    }
}

int main() {
    memset(h, -1, sizeof h);
    memset(method, -1, sizeof method);
    memset(min_case, 63, sizeof min_case);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &X[i], &Y[i]);
        if((X[i] & 1) ^ (Y[i] & 1)) choice_0[i] = choice_1[i] = Y[i] - X[i] + 1 >> 1;
        else if(X[i] & 1) choice_0[i] = Y[i] - X[i] >> 1, choice_1[i] = choice_0[i] + 1;
        else choice_1[i] = Y[i] - X[i] >> 1, choice_0[i] = choice_1[i] + 1;
    }
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a - 1, b, c);
    }
    for(int i = 0; i <= n; i++) if(!vis[i] && h[i] != -1) cnt++, map_dfs(i, -1);
    dfs(1);
    printf("%d\n", ans);
    if(ans) for(int i = 1; i <= n; i++) printf("%d ", min_case[i]);
    else puts("-1");
    return 0;
}