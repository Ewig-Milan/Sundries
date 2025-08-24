#include <bits/stdc++.h>
using namespace std;

const int N = 1000100;

int n, L[N], R[N], ans;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d%d", &L[i], &R[i]);
    deque<int> q;
    for(int i = 1, last = 0; i <= n; i++) {
        while(!q.empty() && L[q.front()] > R[i]) last = q.front(), q.pop_front();
        while(!q.empty() && L[i] >= L[q.back()]) q.pop_back();
        q.push_back(i);
        ans = max(ans, i - last);
    }
    printf("%d", ans);
    return 0;
}