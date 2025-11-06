#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100100, mod = 1e9 + 7;

int n;
struct Node {
    int a, b;
    friend bool operator < (const Node &a, const Node &b) {return a.a < b.a;}
}d[N];

int quick_p(ll x, int a) {
    ll res = 1;
    while(a) {
        if(a & 1) res *= x, res %= mod;
        a >>= 1, x *= x, x %= mod;
    }
    return (int)res;
}

int main() {

    freopen("mex.in", "r", stdin);
    freopen("mex.out", "w", stdout);

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &d[i].a);
    for(int i = 1; i <= n; i++) scanf("%d", &d[i].b);
    sort(d + 1, d + n + 1);
    int min_mex = 0, cnt = 0;
    for(int i = 1; i <= n; i++) if(d[i].a == d[i].b && min_mex == d[i].a) min_mex++;
    for(int i = 1; i <= n; i++) if(d[i].a == min_mex || d[i].b == min_mex) cnt++;
    printf("%d %d", min_mex, quick_p(2, n - cnt));
    return 0;
}