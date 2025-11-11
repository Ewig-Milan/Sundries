#include <bits/stdc++.h>
#define FILE(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout);
using namespace std;

const int N = 305;

int n, m;
unordered_set<int> mp[N][N], f[N][N];

int main() {
    FILE("a");
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        mp[b][c].insert(a);
    }
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        f[i][i].insert(a);
    }
    for(int len = 2; len <= n; len++) {
        for(int l = 1, r = l + len - 1; r <= n; l++, r++) {
            for(int i = l; i < r; i++) {
                if(f[l][i].empty() || f[i + 1][r].empty()) continue;
                for(int a : f[l][i]) for(int b : f[i + 1][r]) for(int x : mp[a][b]) f[l][r].insert(x);
            }
        }
    }
    if(f[1][n].empty()) puts("-1");
    else {
        vector<int> ans;
        for(int x : f[1][n]) ans.push_back(x);
        sort(ans.begin(), ans.end());
        for(int x : ans) printf("%d ", x);
    }
    return 0;
}