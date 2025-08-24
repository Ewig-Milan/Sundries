#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100;
const int Pmod = 100007;

int A, B, C, a, b, c, s;
int ans[N];

struct Cup {int a, b, dep;} sta[Pmod * 3];
bool vis[Pmod * 3];
int h[Pmod + 100], ne[Pmod * 3], idx;

int get(Cup x) {
    int key = (x.a * N % Pmod + x.b) % Pmod;
    for(int i = h[key]; ~i; i = ne[i]) if(sta[i].a == x.a && sta[i].b == x.b) return i;
    sta[idx] = x, ne[idx] = h[key], h[key] = idx++;
    return idx - 1;
}

void bfs() {
    queue<Cup> q;
    q.push({a, b, 0});
    while(!q.empty()) {
        Cup x = q.front();
        q.pop();
        if(vis[get(x)]) continue;
        vis[get(x)] = true;
        ans[x.a] = min(ans[x.a], x.dep);
        ans[x.b] = min(ans[x.b], x.dep);
        ans[s - x.a - x.b] = min(ans[s - x.a - x.b], x.dep);
        if(x.a) q.push({max(x.a + x.b - B, 0ll), min(B, x.a + x.b), x.dep + 1}), 
                q.push({max(s - x.b - C, 0ll), x.b, x.dep + 1});
        if(x.b) q.push({min(x.a + x.b, A), max(0ll, x.a + x.b - A), x.dep + 1}), 
                q.push({x.a, max(0ll, s - x.a - C), x.dep + 1});
        if(s - x.a - x.b) q.push({min(A, s - x.b), x.b, x.dep + 1}), 
                q.push({x.a, min(B, s - x.a), x.dep + 1});
    }
}

signed main() {
    // freopen("juice.in", "r", stdin);
    // freopen("juice.out", "w", stdout);
    memset(h, -1, sizeof h);
    memset(ans, 63, sizeof ans);
    scanf("%lld%lld%lld", &A, &B, &C);
    scanf("%lld%lld%lld", &a, &b, &c);
    s = a + b + c;
    bfs();
    for(int i = 0; i <= C; i++)
        printf("%lld ", ans[i] >= 1e8 ? -1 : ans[i]);
    return 0;
}