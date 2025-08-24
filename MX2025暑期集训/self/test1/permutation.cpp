#include <bits/stdc++.h>
using namespace std;

const int N = 310;

int n, m, ans;
int P[N];

int delta(int p[]) {
    int res = 0, ma = 0;
    for(int i = 1; i < n; i++) {
        if(P[i] > ma && P[i] > P[i + 1]) res++;
        ma = max(ma, P[i]);
    }
    return res;
}

int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        P[a] = b;
    }
    bool sortable = true;
    while(sortable) {
        ans += delta(P), ans %= 998244353;
        sortable = false;
        for(int i = 1; i < n; i++) if(P[i] > P[i + 1]) swap(P[i], P[i + 1]), sortable = true;
    }
    printf("%d", ans);
    return 0;
}