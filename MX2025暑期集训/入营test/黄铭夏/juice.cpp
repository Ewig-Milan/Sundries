#include <bits/stdc++.h>
using namespace std;

const int N = 1100;

int A, B, C, a, b, c;
int ans[N], cnt;
int vis[110][110][110];

void dfs(int a_, int b_, int c_, int x, int y, int dep) {
    if(dep >= vis[a_][b_][c_]) return;
    vis[a_][b_][c_] = dep;
    ans[a_] = min(ans[a_], dep);
    ans[b_] = min(ans[b_], dep);
    ans[c_] = min(ans[c_], dep);
    if((x != 2 || y != 1) && b_ != B && a_) dfs(max(0, a_ + b_ - B), min(B, a_ + b_), c_, 1, 2, dep + 1);
    if((x != 3 || y != 1) && c_ != C && a_) dfs(max(0, a_ + c_ - C), b_, min(C, a_ + c_), 1, 3, dep + 1);
    if((x != 1 || y != 2) && a_ != A && b_) dfs(min(A, a_ + b_), max(0, a_ + b_ - A), c_, 2, 1, dep + 1);
    if((x != 3 || y != 2) && c_ != C && b_) dfs(a_, max(0, b_ + c_ - C), min(C, b_ + c_), 2, 3, dep + 1);
    if((x != 1 || y != 3) && a_ != A && c_) dfs(min(A, a_ + c_), b_, max(0, a_ + c_ - A), 3, 1, dep + 1);
    if((x != 2 || y != 3) && b_ != B && c_) dfs(a_, min(B, b_ + c_), max(0, b_ + c_ - B), 3, 2, dep + 1);
}

int main() {
    freopen("juice.in", "r", stdin);
    freopen("juice.out", "w", stdout);
    memset(ans, 63, sizeof ans);
    memset(vis, 63, sizeof vis);
    scanf("%d%d%d", &A, &B, &C);
    scanf("%d%d%d", &a, &b, &c);
    dfs(a, b, c, 0, 0, 0);
    for(int i = 0; i <= C; i++) printf("%d ", ans[i] >= 20 ? -1 : ans[i]);
    return 0;
}