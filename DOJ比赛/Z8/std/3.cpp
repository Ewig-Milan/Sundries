#include <bits/stdc++.h>
#define Lb(x) ((x) & -(x))
using namespace std;

const int N = 2000100, Nn = 2000000;

int n, q;
int ans[N];

struct Node {int a/*x*/, b/*y*/, c/*x + y*/, id;} M[N], Q[N];

bool cmp1(const Node &a, const Node &b) {return a.a < b.a;}
bool cmp2(const Node &a, const Node &b) {return a.c > b.c;}

struct Bit_T {
    int sum[N];    
    void cl() {memset(sum, 0, sizeof sum);}

    void modify(int x, int delta) {while(x <= Nn) sum[x] += delta, x += Lb(x);}

    int query(int x) {
        int res = 0;
        while(x) res += sum[x], x -= Lb(x);
        return res;
    }
}t;

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        M[i] = {a, b, a + b, 0};
    }
    for(int i = 1; i <= q; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        Q[i] = {a, b, a + b + c, i}, ans[i] = n;
    }
    for(int i = 1; i <= n; i++) t.modify(M[i].a, 1);
    for(int i = 1; i <= q; i++) ans[i] -= t.query(Q[i].a - 1);
    t.cl();
    for(int i = 1; i <= n; i++) t.modify(M[i].b, 1);
    for(int i = 1; i <= q; i++) ans[i] -= t.query(Q[i].b - 1);
    t.cl();
    for(int i = 1; i <= n; i++) t.modify(M[i].c, 1);
    for(int i = 1; i <= q; i++) ans[i] -= t.query(Nn) - t.query(min(Q[i].c, Nn));
    t.cl();

    sort(M + 1, M + n + 1, cmp1);
    sort(Q + 1, Q + q + 1, cmp1);
    for(int i = 1, j = 1; i <= q; i++) {
        while(M[j].a < Q[i].a && j <= n) t.modify(M[j].b, 1), j++;
        ans[Q[i].id] += t.query(Q[i].b - 1);
    }
    t.cl();

    sort(M + 1, M + n + 1, cmp2);
    sort(Q + 1, Q + q + 1, cmp2);
    for(int i = 1, j = 1; i <= q; i++) {
        while(M[j].c > Q[i].c && j <= n) t.modify(M[j].a, 1), j++;
        ans[Q[i].id] += t.query(Q[i].a - 1);
    }
    t.cl();
    for(int i = 1, j = 1; i <= q; i++) {
        while(M[j].c > Q[i].c && j <= n) t.modify(M[j].b, 1), j++;
        ans[Q[i].id] += t.query(Q[i].b - 1);
    }
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}