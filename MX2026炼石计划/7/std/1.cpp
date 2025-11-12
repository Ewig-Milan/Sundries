#include <bits/stdc++.h>
#define ll long long
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 1000100;

int n;
struct Node {
    ll a, b;
    friend bool operator < (const Node &a, const Node &b) {
        return a.a == b.a ? a.b > b.b : a.a > b.a;
    }
}p[N];

int main() {
    FILE("connected");
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        p[i] = {(ll)a - i, (ll)i - b};
    }
    sort(p + 1, p + n + 1);
    deque<int> q;
    for(int i = 1; i <= n; i++) {
        if(q.empty() || p[q.back()].b < p[i].b) q.push_back(i);
        else {
            int tmp = q.back();
            while(!q.empty() && p[q.back()].b >= p[i].b) q.pop_back();
            q.push_back(tmp);
        }
    }
    printf("%d", q.size());
    return 0;
}