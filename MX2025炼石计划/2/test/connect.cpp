#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100;

int n, m;
int ans;
char mp[N][55];
int id[N][55], idx, cnt;
int fa[N * 55];
int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    fa[b] = a;
    return true;
}

signed main() {
    
    freopen("connect.in", "r", stdin);
    freopen("connect.out", "w", stdout);

    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%s", mp[i] + 1);
        for(int j = 1; j <= m; j++) id[i][j] = ++idx;
    }
    for(int start = 1; start <= n; start++) {
        cnt = 0;
        for(int i = 1; i <= n * m; i++) fa[i] = i;
        for(int i = 1; i <= m; i++) {
            if(mp[start][i - 1] == '1' && mp[start][i] == '1') merge(id[start][i - 1], id[start][i]);
            if(mp[start][i - 1] != '1' && mp[start][i] == '1') cnt++;
        }
        ans += cnt;
        for(int i = start + 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(mp[i][j - 1] == '1' && mp[i][j] == '1') merge(id[i][j - 1], id[i][j]);
                if(mp[i][j - 1] != '1' && mp[i][j] == '1') cnt++;
            }
            for(int j = 1; j <= m; j++) {
                if(mp[i][j] == '1' && mp[i - 1][j] == '1') cnt -= merge(id[i - 1][j], id[i][j]);
            }
            ans += cnt;
        }
    }
    printf("%lld", ans);
    return 0;
}