#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100;

int n, m;
int del[N];
int ans[N];
bool exist[N];

vector<int> e[N];

int fa[N], sum[N];
int find(int x) {
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
void merge(int a, int b, int & ma) {
    a = find(a), b = find(b);
    if(a == b) return;
    fa[a] = b, sum[b] += sum[a];
    ma = max(ma, sum[b]);
}

signed main() {
    for(int i = 0; i < N; i++) fa[i] = i;

    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%lld", &sum[i]);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    for(int i = 1; i <= n; i++) scanf("%lld", &del[i]);
    int ma = 0;
    for(int i = n; i; i--) {
        ans[i] = ma;
        ma = max(ma, sum[del[i]]);
        for(int j : e[del[i]]) {
            if(!exist[j]) continue;
            merge(del[i], j, ma);
        }
        exist[del[i]] = 1;
    }
    for(int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
    return 0;
}