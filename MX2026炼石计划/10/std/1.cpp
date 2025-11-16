#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 2100;

int n, m, ans;
char mp[N][N];
bool vis[N][N], aces[N][N];

bool dfs_aces(int x, int y) {
    if(x > n || y > m || mp[x][y] == '#') return false;
    if(vis[x][y]) return aces[x][y];
    vis[x][y] = 1;
    aces[x][y] = dfs_aces(x, y + 1) | dfs_aces(x + 1, y);
    return aces[x][y];
}

bool dfs_ans(int x, int y) {
    if(!x || !y || x > n || y > m) return true;
    if(vis[x][y] || aces[x][y]) return true;
    vis[x][y] = 1;
    bool edge = (x != 1 && y != 1 && x != n && y != m);
    edge &= dfs_ans(x + 1, y - 1) & dfs_ans(x + 1, y) & dfs_ans(x + 1, y + 1) & dfs_ans(x, y - 1)
        & dfs_ans(x - 1, y - 1) & dfs_ans(x - 1, y) & dfs_ans(x - 1, y + 1) & dfs_ans(x, y + 1);
    return edge;
}

int main() {
    FILE("grid");
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
    aces[n][m] = vis[n][m] = 1;
    dfs_aces(1, 1);
    memset(vis, 0, sizeof vis);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        if(!aces[i][j] && !vis[i][j]) ans += dfs_ans(i, j);
    printf("%d", aces[1][1] ? ans + 1 : 0);
    return 0;
}