#include <bits/stdc++.h>
using namespace std;

const int N = 1100, M = 2250000, mod = 500009;

int prim[M >> 2], d[M], sum[M], len;
bool flag[M];

void eular(int n) {
    d[1] = 1;
    for(int i = 2; i <= n; i++)  {
        if(!flag[i]) prim[len++] = i, sum[i] = 1, d[i] = 2;

        for(int j = 0; j < len && i * prim[j] <= n; j++)  {
            flag[i * prim[j]] = 1;
            if(i % prim[j] == 0) {
                sum[i * prim[j]] = sum[i] + 1;
                d[i * prim[j]] = d[i] / (sum[i] + 1) * (sum[i] + 2);
                break;
            }
            sum[i * prim[j]] = 1, d[i * prim[j]] = d[i] * 2;
        }
    }
}

int ans[M], cnt[N];

int T, n;

int main() {
    eular(M - 1);
    ans[0] = 1;
    for(int i = 1; i < M; i++) ans[i] = (long long)(++cnt[d[i]]) * ans[i - 1] % mod;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        printf("%d\n", n >= M ? 0 : ans[n]);
    }
    return 0;
}