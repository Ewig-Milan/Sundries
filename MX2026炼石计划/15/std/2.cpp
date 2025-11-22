#include <bits/stdc++.h>
#define FILE(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);
using namespace std;

int T, n, q;
string s, t;
const int N = 3e5 + 5;
int a[N], b[N];
typedef long long ll;

struct TR {
    int tag[N * 4];
    int mn[N * 4];
    void build(int u, int l, int r) {
        tag[u] = 0;
        mn[u] = 0;
        if(l == r)
            return;
        build(u << 1, l,(l + r >> 1));
        build(u << 1 | 1,(l + r >> 1) + 1, r);
        return;
    }
    void apply(int u, int v) {tag[u] += v, mn[u] += v;}
    void rec(int u) {mn[u] = min(mn[u << 1], mn[u << 1 | 1]);}
    void pd(int u) {
        if(tag[u]) {
            apply(u << 1, tag[u]);
            apply(u << 1 | 1, tag[u]);
            tag[u] = 0;
        }
    }
    void modify(int u, int l, int r, int ql, int qr, int v) {
        if(ql <= l && qr >= r) {
            apply(u, v);
            return;
        }
        pd(u);
        int md = (l + r >> 1);
        if(ql <= md) modify(u << 1, l, md, ql, qr, v);
        if(qr > md) modify(u << 1 | 1, md + 1, r, ql, qr, v);
        rec(u);
    }
    int qmin() {return mn[1];}
}tr;

void solv() {
    cin >> n >> q >> s >> t;
    for(int i = 0; i < s.size(); i++) {
        if((s[i] == 'A') ^ (i & 1)) a[i + 1] = 0;
        else a[i + 1] = 1;
    }
    for(int i = 0; i < t.size(); i++) {
        if((t[i] == 'A') ^ (i & 1)) b[i + 1] = 0;
        else b[i + 1] = 1;
    }
    int ca = 0, cb = 0;
    for(int i = n; i >= 1; i--) {
        a[i] ^= a[i - 1], b[i] ^= b[i - 1];
        ca += a[i], cb += b[i];
    }
    if(ca % 2 == cb % 2 && ca >= cb) {
        int j = 1;
        ca = cb = 0;
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            if(b[i]) {
                cb++, ans -= i;
                bool ok = 0;
                while(j <= n) {
                    ca += a[j];
                    if(j >= i && (ca & 1) == (cb & 1) && a[j]) {
                        ans += j, j++, ok = 1;
                        break;
                    }
                    if(a[j]) {
                        if((ca + cb + 1) & 1) ans -= j;
                        else ans += j;
                    }
                    j++;
                }
                if(!ok) {ans = -1; break;}
            }
        }
        if(ans != -1) {
            while(j <= n) {
                ca += a[j];
                if(a[j]) {
                    if((ca + cb) & 1) ans -= j;
                    else ans += j;
                }
                j++;
            }
        }
    }
    ca = cb = 0;
    for(int i = 1; i <= n; i++) ca ^= a[i], cb ^= b[i];
    tr.build(1, 1, n);
    for(int i = 1; i <= n; i++) {
        if(a[i]) tr.modify(1, 1, n, 1, i, 1);
        if(b[i]) tr.modify(1, 1, n, 1, i, -1);
    }
    while(q--) {
        char c;
        int pos;
        cin >> c >> pos;
        if(c == 'X') {
            tr.modify(1, 1, n, 1, pos, (a[pos] == 1 ? -1 : 1));
            a[pos] ^= 1;
            ca ^= 1;
            if(pos + 1 <= n) {
                tr.modify(1, 1, n, 1, pos + 1, (a[pos + 1] == 1 ? -1 : 1));
                a[pos + 1] ^= 1;
                ca ^= 1;
            }
        } else {
            tr.modify(1, 1, n, 1, pos, (b[pos] == 1 ? 1 : -1));
            b[pos] ^= 1, ca ^= 1;
            if(pos + 1 <= n) {
                tr.modify(1, 1, n, 1, pos + 1, (b[pos + 1] == 1 ? 1 : -1));
                b[pos + 1] ^= 1, ca ^= 1;
            }
        }
        if(tr.qmin() >= 0 && ca == cb) puts("YES");
        else puts("NO");
    }
}

int main() {
    FILE("string");
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while(T--) solv();
}