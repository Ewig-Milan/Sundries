#include <bits/stdc++.h>
using namespace std;

const int N = 200000;

int n, q;
int g[N][18];

struct Node {int g, nxt[18];};
vector<Node> nx[N];

int get_gcd(int l, int r) {
    int res = 0;
    for(int i = 17; i >= 0; i--)
        if(l + (1 << i) - 1 <= r) res = __gcd(g[l][i], res), l += (1 << i);
    return res;
}

unordered_map<int, int> Mp[N];

void work(int x, int id) {
    int tmp = 0, r = id, cnt = 0, G = x;
    Node ttt;
    while(r <= n) {
        for(int i = 17; i >= 0; i--) {
            int tt = __gcd(g[r][i], tmp);
            if(tt > G && r + (1 << i) - 1 <= n)
                tmp = tt, r += (1 << i);
        }
        ttt.g = G, ttt.nxt[0] = ++r, tmp = G;
        for(int i = 1; i < 18; i++) {
            if(Mp[ttt.nxt[i - 1]][G])
                ttt.nxt[i] = nx[ttt.nxt[i - 1]][Mp[ttt.nxt[i - 1]][G] - 1].nxt[i - 1];
            else ttt.nxt[i] = n + 2;
        }
        Mp[id][G] = ++cnt;
        nx[id].push_back(ttt);
        for(int i = 17; i >= 0; i--) if(g[r][i] % G == 0 && r + (1 << i) - 1 <= n) r += (1 << i);
        G = __gcd(g[r][0], tmp);
    }
}

int main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &g[i][0]);
    for(int i = 1; i < 18; i++) 
    for(int j = 1; j <= n; j++)
        g[j][i] = __gcd(g[j][i - 1], g[j + (1 << (i - 1))][i - 1]);

    for(int i = n; i; i--) work(g[i][0], i);

    while(q--) {
        int l, r; scanf("%d%d", &l, &r);
        int ans = 0, G = get_gcd(l, r), ltmp = l;
        for(int i = 17; i >= 0; i--)
            if(Mp[l][G] && nx[l][Mp[l][G] - 1].nxt[i] - 1 <= r) ans += (1 << i), l = nx[l][Mp[l][G] - 1].nxt[i];
        printf("%d\n", r - ltmp + 1 - ans);
    }
    return 0;
}