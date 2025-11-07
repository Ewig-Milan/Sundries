#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 200100;

int n, m, l;
int last[N]; // 到 i 城市的委托的出发时间

int t[N];

struct Task {
    bool mode; // 0 - 到城市   1 - 回去
    int d, c; // day, city
    friend bool operator < (const Task &a, const Task &b) {
        return (a.mode ? a.d : a.d + t[a.c]) < (b.mode ? b.d : b.d + t[b.c]);
    }
};
vector<Task> Q;

struct Node {
    int l, r;
    friend bool operator < (const Node &a, const Node &b) {
        return a.r < b.r;
    }
};
vector<Node> T;

signed main() {

    freopen("entrust.in", "r", stdin);
    freopen("entrust.out", "w", stdout);

    scanf("%lld%lld%lld", &n, &m, &l);
    for(int i = 1; i <= n; i++) scanf("%lld", &t[i]);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        Q.push_back({0, b, a});
    }
    for(int i = 1; i <= l; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        Q.push_back({1, b, a});
    }
    sort(Q.begin(), Q.end());
    for(auto x : Q) {
        if(!x.mode) last[x.c] = x.d;
        else if(last[x.c] && last[x.c] + t[x.c] < x.d) {
            T.push_back({last[x.c], x.d + t[x.c]});
            last[x.c] = 0;
        }
    }
    sort(T.begin(), T.end());
    int ans = 0, en = 0;
    for(auto x : T) if(x.l > en) en = x.r, ans += 2;
    for(auto x : Q) if(!x.mode && x.d > en) {ans++; break;}
    printf("%lld", ans);
    return 0;
}