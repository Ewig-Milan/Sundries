#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 300100;

int n;
int t, c;

int h[N], e[N << 1], ne[N << 1], v[N << 1], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

vector<int> cir;
bool in_cir[N];
int pa[N];
void find_cir(int x, int l) {
    for(int i = h[x]; ~i; i = ne[i]) if((i ^ 1) != l) if(pa[e[i]] && cir.empty())
    for(int t = x; t != pa[e[i]]; t = pa[t]) cir.push_back(t), in_cir[t] = 1;
    else if(!pa[e[i]]) pa[e[i]] = x, find_cir(e[i], i);
}

void dfs(int x, int l) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(in_cir[j] || j == l) continue;
        t += (v[i] ^ 1), dfs(j, x);
    }
}

int main() {
    FILE("c");
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a, b; char c; scanf("%d%d %c", &a, &b, &c);
        add(a, b, c == '+');
    }
    pa[1] = -1, find_cir(1, -1);
    for(int j = 0; j < (int)cir.size(); j++) for(int i = h[cir[j]]; ~i; i = ne[i])
        if(e[i] == cir[(j + 1) % (int)cir.size()]) c += (v[i] ^ 1);
    for(int x : cir) dfs(x, 0);

    printf("%d\n", t + c);
    for(int k = 2; k <= n; k++) {
        if(c > 1) printf("%d\n", k <= t + c ? t + c - k : k - t - c);
        else if(c == 1) printf("%d\n", k <= t + 1 ? t + c + 1 - k : k - t - c);
        else {
            if(k <= t + 1) printf("%d\n", t + 1 - k);
            else if(k <= n - (int)cir.size() + 1) printf("%d\n", k - 1 - t);
            else printf("%d\n", k - t);
        } 
    }
    return 0;
}