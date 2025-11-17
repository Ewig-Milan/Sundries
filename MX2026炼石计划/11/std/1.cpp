#include <bits/stdc++.h>
#define int long long
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 55;

int n, m, k;
int ans;

struct Node {int x, y;} P[N];

int X(Node &a, Node &b) {return (a.x - b.x) * (a.x - b.x);}
int Y(Node &a, Node &b) {return (a.y - b.y) * (a.y - b.y);}
int dis(Node &a, Node &b) {return X(a, b) + Y(a, b);}

bool check(Node &A, Node &B, Node &C, Node &D) {
    int R = dis(A, B);
    if(R > (n - A.x) * (n - A.x)) return false;
    if(R > A.x * A.x) return false;
    if(R > (m - A.y) * (m - A.y)) return false;
    if(R > A.y * A.y) return false;

    int tmp = dis(A, B) - dis(A, C) - dis(C, D);
    if(tmp < 0) return false;
    if(dis(A, C) * 4 * dis(C, D) >= tmp * tmp) return false;

    return true;
}

bool vis[N];

void dfs(int cnt, vector<Node> &p) {
    if(cnt == 4) {
        ans += check(p[0], p[1], p[2], p[3]);
        return;
    }
    for(int i = 1; i <= k; i++) if(!vis[i]) {
        vis[i] = 1, p.push_back(P[i]);
        dfs(cnt + 1, p);
        vis[i] = 0, p.pop_back();
    }
}

signed main() {
    FILE("circle");
    scanf("%lld%lld%lld", &k, &n, &m);
    for(int i = 1; i <= k; i++) scanf("%lld%lld", &P[i].x, &P[i].y);
    vector<Node> p;
    dfs(0, p);
    printf("%lld", ans);
    return 0;
}