#include <bits/stdc++.h>
#define int long long
using namespace std;

int pw[10];
int mask, n, m, ans;

char s[10];

unordered_map<unsigned int, int> mp[1 << 6];

void dfs(int pos, int x) {
    if(pos >= m) {
        unsigned int key = 0;
        for(int i = 0; i < m; i++) {
            if(!(mask & pw[i])) continue;
            if(x & pw[i]) key = key * 31 + s[i];
            else key = key * 31 + '?';
        }
        ans += mp[mask][key];
        return;
    }
    if(!(mask & pw[pos])) dfs(pos + 1, x);
    else dfs(pos + 1, x), dfs(pos + 1, x | pw[pos]);
}

signed main() {
    pw[0] = 1;
    for(int i = 1; i <= 6; i++) pw[i] = pw[i - 1] * 2;

    scanf("%lld%lld", &n, &m);
    int ma_s = 1 << m;
    for(int t = 1; t <= n; t++) {
        scanf("%s", s);
        mask = 0;
        for(int i = 0; i < m; i++) if(s[i] != '?') mask |= pw[i];
        dfs(0, 0);
        for(int i = 0; i < ma_s; i++) {
            unsigned int key = 0;
            for(int j = 0; j < m; j++)
                if(i & pw[j]) key = key * 31 + s[j];
            mp[i][key]++;
        }
    }
    printf("%lld\n", ans);
    return 0;
}