#include <bits/stdc++.h>
using namespace std;

const int N = 1000100;

int t, n, m;
int h[N], cnt[N];
queue<int> q;

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) scanf("%d", &h[i]);
        int ans = 0;
        for(int y = 0; y <= m / max((n - 1), 1); y++) {
            for(int i = 1; i <= n; i++) {
                int h_ = h[i] - (i - 1) * y;
                if(h_ + y * (n - 1) <= m && h_ > 0) cnt[h_]++, q.push(h_);
            }
            while(!q.empty()) {
                ans = max(ans, cnt[q.front()]);
                cnt[q.front()] = 0, q.pop();
            }
        }
        printf("%d\n", n - ans);
    }
    return 0;
}