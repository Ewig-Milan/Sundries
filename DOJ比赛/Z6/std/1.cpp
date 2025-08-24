#include <bits/stdc++.h>
using namespace std;

const int N = 10000100;
const long long mod = 1e9 + 7;

int n;
long long ans;
char s[N];

int h[N], f[N];
int sum[N];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);

    memset(h, -1, sizeof h);
    for(int i = 2; i <= n; i++) {
        if(s[i] == '(') continue;
        int tmp = i - 1;
        while(tmp > 0 && s[tmp] == ')') tmp = h[tmp];
        h[i] = max(tmp - 1, -1);
    }
    for(int i = 1; i <= n; i++) if(h[i] != -1) f[i] = f[h[i]] + 1;
    for(int i = 1; i <= n; i++) sum[i + 1] -= f[i];

    for(int i = 1; i <= n; i++) h[i] = n + 2;
    memset(f, 0, sizeof f);
    for(int i = n - 1; i; i--) {
        if(s[i] == ')') continue;
        int tmp = i + 1;
        while(tmp <= n && s[tmp] == '(') tmp = h[tmp];
        h[i] = min(tmp + 1, n + 2);
    }
    for(int i = n; i; i--) if(h[i] != n + 2) f[i] = f[h[i]] + 1;
    for(int i = 1; i <= n; i++) sum[i] += f[i];

    for(int i = 2; i <= n; i++) sum[i] += sum[i - 1];
    for(int i = 1; i <= n; i++) ans += (long long)i * sum[i] % mod;
    printf("%lld\n", ans);
    return 0;
}