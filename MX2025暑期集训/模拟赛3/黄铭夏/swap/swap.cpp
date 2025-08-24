#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

inline int read() {
    int x = 0;
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c <= '9' && c >= '0') {
        x *= 10, x += c - '0';
        c = getchar();
    }
    return x;
}

int n, k;
int ans[N];
int en[N], ne[N];
bool flag[N];
unordered_set<int> vis[N];

int main() {
    n = read(), k = read();
    for(int i = 1; i <= n; i++) en[i] = i, vis[i].insert(i);
    for(int i = 1; i <= k; i++) {
        int a = read(), b = read();
        vis[en[a]].insert(b), vis[en[b]].insert(a);
        swap(en[a], en[b]);
    }
    for(int i = 1; i <= n; i++) ne[en[i]] = i;
    for(int i = 1; i <= n; i++) {
        if(flag[i]) continue;
        flag[i] = 1;
        int tmp = ne[i];
        while(tmp != i) {
            flag[tmp] = 1;
            for(int j : vis[tmp]) vis[i].insert(j);
            tmp = ne[tmp];
        }
        ans[i] = vis[i].size();
        tmp = ne[i];
        while(tmp != i) ans[tmp] = ans[i], tmp = ne[tmp];
    }
    for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}