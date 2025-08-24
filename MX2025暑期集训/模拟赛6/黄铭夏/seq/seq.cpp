#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, m;
int A[N], chose[N]; // chose下标为rk 存的是A下标

bool cmp(int a, int b) {return A[a] < A[b];}

struct TR {
    vector<int> num, ly; // 绝对标记
    void cl(int n) {
        num.resize(0), num.resize(n + 10);
        ly.resize(n << 2);
        for(int i = 0; i < (n << 2); i++) ly[i] = -1;
    }
    void push_down(int rt, int l, int r) {
        if(ly[rt] == -1) return;
        ly[rt << 1] = ly[rt << 1 | 1] = ly[rt];
        int mid = l + r >> 1;
        if(l == mid) num[l] = ly[rt];
        if(mid + 1 == r) num[r] = ly[rt];
        ly[rt] = -1;
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        if(ql <= l && qr >= r) {
            ly[rt] = x;
            if(l == r) num[l] = x;
            return;
        }
        push_down(rt, l, r);
        int mid = l + r >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
    }
    int query(int rt, int l, int r, int x) {
        if(l == r) return num[l];
        push_down(rt, l, r);
        int mid = l + r >> 1;
        if(x <= mid) return query(rt << 1, l, mid, x);
        else return query(rt << 1 | 1, mid + 1, r, x);
    }
}tL, tR;

bool check(int x) {
    int res = 1;
    tL.cl(n), tR.cl(n);
    tL.modify(1, 1, n, 1, n, chose[1]);
    tR.modify(1, 1, n, 1, n, chose[1]);
    for(int i = 2; i <= n; i++) {
        int nw = chose[i];
        int l = tL.query(1, 1, n, nw), r = tR.query(1, 1, n, nw);
        if(A[l] + A[nw] > x || A[nw] + A[r] > x) continue;
        res++;
        if(r < nw) {
            tL.modify(1, 1, n, nw, n, nw);
            tL.modify(1, 1, n, 1, r, nw);
            tR.modify(1, 1, n, l, nw, nw);
        } else if(l > nw) {
            tR.modify(1, 1, n, 1, nw, nw);
            tR.modify(1, 1, n, l, n, nw);
            tL.modify(1, 1, n, nw, r, nw);
        } else {
            tL.modify(1, 1, n, nw, r, nw);
            tR.modify(1, 1, n, l, nw, nw);
        }
    }
    return res >= m;
}

int main() {
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]), chose[i] = i;
    sort(chose + 1, chose + n + 1, cmp);
    int l = A[chose[1]] * 2, r = A[chose[n]] * 2;
    while(l < r) {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}