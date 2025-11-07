#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100, mod = 1e9 + 7;

struct Node {int len, cnt;};
Node max(Node a, Node b) {
    if(a.len != b.len) return a.len > b.len ? a : b;
    return {a.len, (a.cnt + b.cnt) % mod};
}

int n, a[N], A[N];

struct Bit_T {
    Node bit[N];
    void cl() {for(int i = 1; i <= n; i++) bit[i] = {0,0};}

    void update(int x, const Node &p) {while(x <= n) bit[x] = max(bit[x], p), x += (x & -x);}
    Node ask(int x) {
        Node ret = {0,0};
        while(x) ret = max(ret, bit[x]), x -= (x & -x);
        return ret;
    }
}t;

Node f[N], f1[N], f2[N], f3[N], f4[N];
void solve() {
    t.cl();
    for(int i = 1; i <= n; i++) {
        f[i] = t.ask(A[i] - 1);
        f[i].len++, f[i].cnt = max(f[i].cnt, 1ll);
        t.update(A[i], f[i]);
    }
}

signed main() {

    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);

    int T; scanf("%lld", &T);
    while(T--) {
        scanf("%lld", &n);
        for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), A[i] = a[i];
        solve(); copy(f + 1, f + n + 1, f1 + 1);

        for(int i = 1; i <= n; i++) A[i] = n - A[i] + 1;
        solve(); copy(f + 1, f + n + 1, f2 + 1);

        reverse(A + 1, A + n + 1);
        solve(); copy(f + 1, f + n + 1, f3 + 1); reverse(f3 + 1, f3 + n + 1);

        for(int i = 1; i <= n; i++) A[i] = n - A[i] + 1;
        solve(); copy(f + 1, f + n + 1, f4 + 1); reverse(f4 + 1, f4 + n + 1);
        
        Node lis = f1[1], lds = f2[1];
        for(int i = 2; i <= n; i++) lis = max(lis, f1[i]), lds = max(lds, f2[i]);
        
        int tot = lis.cnt * lds.cnt % mod, sum = 0;
        for(int i = 1; i <= n; i++) {
            if(f1[i].len + f3[i].len - 1 == lis.len && f2[i].len + f4[i].len - 1 == lds.len)
                sum = (sum + f1[i].cnt * f2[i].cnt % mod * f3[i].cnt % mod * f4[i].cnt) % mod;
        }
        printf("%lld\n", lis.len + lds.len - (sum == tot));
    }
    return 0;
}