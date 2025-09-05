#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 60, M = 10100;

int n, m, cnt;
int ans[N], f[M];

signed main() {
    scanf("%lld%lld", &n, &m);
    f[0] = 1;
    for(int i = 0; i <= m; i++) {
        int B; scanf("%lld", &B);
        while(B - f[i] > 0ll) {
            ans[++cnt] = i;
            if(cnt == n) break;
            for(int j = m; j - i >= 0; j--) f[j] += f[j - i];
        }
    }
    for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    return 0;
}