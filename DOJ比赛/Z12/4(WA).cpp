#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 200100;

struct Node {
    int x, B, S;
}d[N];

int n, C, ans;
int nxt[N];

struct TR {
    vector<int> ma;
    void cl(int n) {ma.resize(0), ma.resize(n << 2);}

    void push_up(int rt) {ma[rt] = max(ma[rt << 1], ma[rt << 1 | 1]);}

    void build(int rt, int l, int r) {
        if(l == r) {
            ma[rt] = d[l].S;
            return;
        }
        int mid = l + r >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    int query(int rt, int l, int r, int ql, int qr) {
        if(ql > qr) return -1;
        if(l <= ql && r >= qr) return ma[rt];
        int mid = l + r >> 1, res = 0;
        if(ql <= mid) res = query(rt << 1, l, mid, ql, qr);
        if(qr > mid) res = max(res, query(rt << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
}t;

signed main() {
    freopen("data.in", "r", stdin);
    scanf("%lld%lld", &n, &C);
    n++;
    for(int i = 2; i <= n; i++) scanf("%lld", &d[i].x);
    for(int i = 1; i < n; i++) scanf("%lld%lld", &d[i].B, &d[i].S);
    d[n].B = 1e9;

    t.cl(n), t.build(1, 1 ,n);

    deque<int> q; // 递增
    for(int i = 1, r = 2; i < n; i++) {
        while(!q.empty() && q.front() <= i) q.pop_front();
        while(r <= n && d[r].x - d[i].x <= C) {
            while(!q.empty() && d[q.back()].B > d[r].B) q.pop_back();
            q.push_back(r);
            r++;
        }
        nxt[i] = q.front();
    }
    for(int i = 1; i < n; i = nxt[i]) {
        if(d[nxt[i]].B <= d[i].B) {
            int j = i + 1;
            while(d[j].B > d[i].B) j++;
            nxt[i] = j;
        } else if(d[n].x - d[i].x <= C) nxt[i] = n;
    }
    int rem = 0;
    for(int i = 1; i < n; i = nxt[i]) {
        int dis = d[nxt[i]].x - d[i].x;
        if(d[nxt[i]].B <= d[i].B || nxt[i] == n) {
            int S_max = t.query(1, 1, n, i + 1, nxt[i] - 1);
            if(S_max > d[i].B) ans += (C - rem) * d[i].B, ans -= (C - dis) * S_max, rem = 0;
            else ans += max((dis - rem) * d[i].B, 0ll), rem = max(0ll, rem - dis);
        } else {
            ans += (C - rem) * d[i].B;
            int S_max = t.query(1, 1, n, i + 1, nxt[i] - 1);
            if(S_max > d[nxt[i]].B) ans -= (C - dis) * S_max, rem = 0;
            else rem = C - dis;
        }
    }
    printf("%lld", ans);
    return 0;
}