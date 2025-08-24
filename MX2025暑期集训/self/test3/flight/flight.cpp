#include <bits/stdc++.h>
#define int long long
#define PLL pair<int, int>
#define xx first
#define yy second

using namespace std;

const int N = 100100;
const PLL O = {0, 0};

int n;
int f[N];
int A[N], B[N];
vector<int> trans; // 可换乘的点
bool cmp(int a, int b) {return B[a] > B[b];}

int h[N], e[N << 1], ne[N << 1], idx;
int v[N << 1];
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

struct LCA_you_know {
    int dis[N];
    int fa[N][18], dep[N];
    void dfs_pre(int x, int l) {
        fa[x][0] = l, dep[x] = dep[l] + 1;
        for(int i = 1; i < 18; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == l) continue;
            dis[j] = dis[x] + v[i];
            dfs_pre(j, x);
        }
    }
    int LCA(int x, int y) {
        if(dep[x] < dep[y]) swap(x, y);
        for(int i = 17; i >= 0; i--)
            if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
        if(x == y) return y;
        for(int i = 17; i >= 0; i--) if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
        return fa[y][0];
    }
    int get_dis(int x, int y) {return dis[x] + dis[y] - (dis[LCA(x, y)] << 1);}
}LCA;

int fa[N];
bool del[N];

int get_tot(int x, int l) {
    if(del[x]) return 0;
    int sum = 1;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        sum += get_tot(j, x);
    }
    return sum;
}

int get_wc(int x, int l, int tot, int &wc) {
    if(del[x]) return 0;
    int ma = 0, sum = 1;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        int tmp = get_wc(j, x, tot, wc);
        sum += tmp, ma = max(ma, tmp);
    }
    ma = max(ma, tot - sum);
    if(ma <= (tot >> 1)) wc = x;
    return sum;
}

void calc(int rt, int l) {
    if(del[rt]) return;
    get_wc(rt, 0, get_tot(rt, 0), rt);
    fa[rt] = l, del[rt] = 1;
    for(int i = h[rt]; ~i; i = ne[i]) calc(e[i], rt);
}

struct Convex_Hull {
    struct Point {int xx, yy, id;};
    int id;
    vector<Point> cvh;
    int l, r = -1;

    int X(int j) {return -B[j];}
    int Y(int j) {return f[j] + A[j] + B[j] * LCA.get_dis(j, id);}
    int F(int i, int j) {return j == -1 ? (int)1e18 : Y(j) + B[j] * LCA.get_dis(i, id);}

    bool cmp_k(PLL a, PLL b, PLL c, PLL d) {
        return (__int128)(b.yy - a.yy) * (d.xx - c.xx)
        >= (__int128)(b.xx - a.xx) * (d.yy - c.yy);
    }
    PLL P(int id) {return {X(id), Y(id)};}
    int get_ans(int x, int k) {
        if(cvh.empty()) return -1;
        l = 0, r = cvh.size() - 1;
        while(l < r) {
            int mid = l + r >> 1;
            if(cvh[mid].yy - k * cvh[mid].xx <=
                cvh[mid + 1].yy - k * cvh[mid + 1].xx) r = mid;
            else l = mid + 1;
        }
        int tmp = cvh[l].id;
        l = 0, r = cvh.size() - 1;
        return tmp;
    }
    void add_back(int x) {
        auto Px = P(x);
        while(l <= r && Px.xx == cvh[r].xx) {
            if(cvh[r].yy >= Px.yy) r--;
            else {
                cvh.resize(r + 1);
                return;
            }
        }
        while(l < r && cmp_k({cvh[r - 1].xx, cvh[r - 1].yy}, Px, {cvh[r].xx, cvh[r].yy}, Px)) r--;
        cvh.resize(++r), cvh.push_back({Px.xx, Px.yy, x});
    }
}cvh[N];

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &A[i]);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &B[i]);
        if(i != 1 && B[i] < B[1]) trans.push_back(i);
    }
    for(int i = 1; i < n; i++) {
        int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        a++, b++;
        add(a, b, c);
    }
    sort(trans.begin(), trans.end(), cmp);
    LCA.dep[0] = -1;
    LCA.dfs_pre(1, 0), calc(1, 0);
    for(int i = 1; i <= n; i++) cvh[i].id = i;
    memset(f, 127, sizeof f);
    f[1] = 0;
    int tmp = 1;
    while(tmp) {
        cvh[tmp].add_back(1);
        tmp = fa[tmp];
    }
    for(int x : trans) {
        int tmp = x;
        while(tmp) {
            f[x] = min(f[x], cvh[tmp].F(x, cvh[tmp].get_ans(x, LCA.get_dis(x, tmp))));
            tmp = fa[tmp];
        }
        tmp = x;
        while(tmp) {
            cvh[tmp].add_back(x);
            tmp = fa[tmp];
        }
    }
    for(int x = 2; x <= n; x++) {
        int tmp = x; int res = 1e18;
        while(tmp) {
            res = min(res, cvh[tmp].F(x, cvh[tmp].get_ans(x, LCA.get_dis(x, tmp))));
            tmp = fa[tmp];
        }
        printf("%lld\n", res);
    }
    return 0;
}