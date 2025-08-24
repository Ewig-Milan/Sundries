#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 100100, M = 400100;

int n, m;

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

int bl_cnt;
int dfn[N], low[N], cnt;
struct Node {int x, l;};
stack<Node> S;

void tarjan(int x_, int l_) {
    S.push({x_, l_});
    while(!S.empty()) {
        bool jump = false;
        int x = S.top().x, l = S.top().l;
        if(!dfn[x]) dfn[x] = low[x] = ++cnt;
        for(int &i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if((i ^ 1) == l) continue;
            if(!dfn[j]) {
                S.push({j, i}), jump = true;
                break;
            }
            low[x] = min(low[x], low[j]);
        }
        if(jump) continue;
        if(dfn[x] == low[x]) bl_cnt++;
        S.pop();
    }
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, -1);
    printf("%d", n - bl_cnt + 1);
    return 0;
}