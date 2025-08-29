#include <bits/stdc++.h>
using namespace std;

const int N = 100100;
const int M = 1000100;

int n, a[N], b[N], sta[N], top;
int op[M], x[M], y[M], z[M], cnt;
int rk[N], pos[N];
pair<int, int> tmp[N];

struct Bit_T {
    int sum[N], tot;
    void cl(int n) {
        memset(sum, 0, sizeof(int) * (n + 5));
        tot = n;
    }
    void modify(int x, int delta) {while(x) sum[x] += delta, x -= x & -x;}

    int query(int x) {
        int res = 0;
        while(x <= tot) res += sum[x], x += x & -x;
        return res;
    }
}t;

bool is_ok() {
    for(int i = 1; i <= n; ++i) b[i] = a[i];
    sort(b + 1, b + n + 1);
    top = 0;
    int t = 1;
    for(int i = n; i; --i) {
        if(a[i] == b[t]) ++t;
        else sta[++top] = a[i];
        while(top && b[t] == sta[top]) ++t, --top;
    }
    return top ? false : true;
}

void add(int op_type, int x_, int y_, int z_) {
    if(op_type == 1 && y_ == 0) return;
    if(op_type == 3 && z_ == 0) return;
    ++cnt;
    op[cnt] = op_type;
    x[cnt] = x_;
    y[cnt] = y_;
    z[cnt] = z_;
}

void print() {
    printf("%d\n", cnt);
    for(int i = 1; i <= cnt; ++i) {
        printf("%d %d", op[i], x[i]);
        if(op[i] == 1 || op[i] == 3) printf(" %d", y[i]);
        if(op[i] == 3) printf(" %d", z[i]);
        printf("\n");
    }
}

void solve() {
    cnt = top = 0;
    int t = 1;
    for(int i = n; i; --i) {
        if(a[i] == b[t]) {
            add(1, 1, 1, 0);
            add(2, 1, 0, 0);
            ++t;
        } else {
            sta[++top] = a[i];
            add(1, 1, 1, 0);
        }
        while(top && b[t] == sta[top]) {
            add(2, 1, 0, 0);
			t++, top--;
        }
    }
    print();
}

void solve_() {
    top = cnt = 0;
    for(int i = 1; i <= n; ++i) tmp[i] = make_pair(a[i], i);
    sort(tmp + 1, tmp + n + 1);
    for(int i = 1; i <= n; ++i) rk[i] = tmp[i].second;
    t.cl(n);
    for(int i = 1, now = n; i <= n; ++i) {
        if(rk[i] <= now) {
            for(int j = now; j > rk[i]; --j) {
                pos[j] = ++top;
                t.modify(top, 1);
            }
            add(1, 1, now - rk[i] + 1, 0);
            add(2, 1, 0, 0);
            now = rk[i] - 1;
        } else {
            int u = pos[rk[i]], num = t.query(u);
            add(3, 1, 2, num - 1);
            add(2, 1, 0, 0);
            add(3, 2, 1, num - 1);
            t.modify(u, -1);
        }
    }
    print();
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        if(is_ok()) solve();
        else solve_();
    }
    return 0;
}