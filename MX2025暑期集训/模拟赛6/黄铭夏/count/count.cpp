#include <bits/stdc++.h>
#define int long long
using namespace std;

int x, p;
int ans[20], idx;

signed main() {
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    scanf("%lld%lld", &x, &p);
    int tmp = x;
    for(int i = 2; i * i <= tmp; i++) {
        if(tmp % i == 0) {
            idx++;
            int cnt = 0;
            while(tmp % i == 0) tmp /= i, cnt++;
            for(int j = 1; j <= p * cnt; j++)
                if((p + 1) * min(cnt, j) == j + cnt) ans[idx]++;
        }
    }
    int ANS = 1;
    for(int i = 1; i <= idx; i++) ANS *= ans[i], ANS %= 998244353;
    printf("%lld", ANS);
    return 0;
}