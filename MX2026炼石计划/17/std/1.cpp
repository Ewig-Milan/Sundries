#include <bits/stdc++.h>
#define ll long long
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
using namespace std;

const int N = 2000100;

int n, A[N], Q[N];
ll ans, ANS;
bool exist[N];
int fa[N], ma[N];
int find(int x) {
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
void merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return;
    fa[b] = a, ma[a] = max(ma[a], ma[b]);
}

int main() {
    FILE("spring");
    memset(exist, 1, sizeof exist);
    int nothing; scanf("%d%d", &nothing, &n);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for(int i = n; i > 1; i--) scanf("%d", &Q[i]), exist[Q[i]] = 0;
    for(int i = 1; i <= n; i++) if(exist[i]) Q[1] = i, exist[i] = 0;

    for(int i = 1; i <= n; i++) fa[i] = i, ma[i] = A[i];
    for(int i = 1; i <= n; i++) {
        int x = Q[i];
        exist[x] = 1;
        ll pre = 0, now = A[x], tmp;
        if(x - 1 > 0 && exist[x - 1])
            tmp = ma[find(x - 1)], pre += tmp, now = max(now, tmp), merge(x - 1, x);
        if(x + 1 <= n && exist[x + 1])
            tmp = ma[find(x + 1)], pre += tmp, now = max(now, tmp), merge(x + 1, x);
        if(i < n) ans += now - pre, ANS ^= ans;
    }
    printf("%lld", ANS);
    return 0;
}