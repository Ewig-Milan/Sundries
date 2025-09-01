#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 8500, mod = 998244353;

int k, q;
int cnt[N], cnt_[N], ans[N];

signed main() {
    freopen("xortree.in", "r", stdin);
    freopen("xortree.out", "w", stdout);
    scanf("%lld%lld", &k, &q);
    ans[k] = cnt[k] = cnt_[k] = 1;
    while(q--) {
        int mode; scanf("%lld", &mode);
        if(mode == 1) {
            int x; scanf("%lld", &x);
            for(int i = 0; i < (1 << 13); i++)
                ans[i ^ x] += 2 * cnt[i], cnt_[i ^ x] += cnt[i];
            for(int i = 0; i < (1 << 13); i++) cnt[i] = cnt_[i];
            for(int i = 0; i < (1 << 13); i++) ans[i] %= mod, cnt[i] %= mod, cnt_[i] %= mod;
        } else {
            int x; scanf("%lld", &x);
            printf("%lld\n", ans[x]);
        }
    }
    return 0;
}