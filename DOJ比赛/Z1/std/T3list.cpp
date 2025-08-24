#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int p[N << 1], q[N << 1], n, ans;

struct TR {
    struct Node {int mi, ly = 0;};
    vector<Node> t;

	void cl(int n) {t.resize(n << 2);}

    void push_up(int rt) {t[rt].mi = min(t[rt << 1].mi, t[rt << 1 | 1].mi);}

    void push_down(int rt) {
        if(!t[rt].ly) return;
        t[rt << 1].mi += t[rt].ly, t[rt << 1].ly += t[rt].ly;
        t[rt << 1 | 1].mi += t[rt].ly;
        t[rt << 1 | 1].ly += t[rt].ly;
        t[rt].ly = 0;
    }

    void build(int rt, int l, int r) {
        if(l == r) {
            t[rt].mi = 2 * l;
            return;
        }
        int mid =(l + r) >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }

    void modify(int x, int y, int rt, int l, int r) {
        if(x <= l) {
            t[rt].mi += y, t[rt].ly += y;
            return;
        }
        if(l == r) return;
        push_down(rt);
        int mid =(l + r) >> 1;
        if(x <= mid) modify(x, y, rt << 1, l, mid);
        modify(x, y, rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
}t;

void work(int x, int y) {
    if(x == n + 1) return;
    x = min(2 * n + 2 - x, x);
    t.modify(x, y, 1, 1, n);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n * 2 + 1; i++) {
        scanf("%d", &p[i]);
        q[p[i]] = i;
	}
    t.cl(n), t.build(1, 1, n);

    for(int i = 1, j = 1; i <= 2 * n + 1; i++) {
        while(j <= 2 * n + 1) {
            work(q[j], -2);
            if(t.t[1].mi < 0) {
                work(q[j], 2);
                break;
            }
            j++;
        }
        ans = max(ans, j - i);
        work(q[i], 2);
    }
    printf("%d\n", ans);
    return 0;
}