#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 500100;

int tid, n, m;
int A[N], ne[N], lst[N];

bool check(int x) {
    for(int i = 1; i < n; i++) ne[i] = i + 1;
    for(int i = 2; i <= n; i++) lst[i] = i - 1;
    ne[n] = 1, lst[1] = n;
    int del = 0;
    int l = 1, r = 2;
    int stable = 1; // 上一个修改后稳定的左端点
    while(true) {
        if(A[l] + A[r] > x) {
            while(A[l] + A[r] > x) {
                if(A[l] > A[r]) l = lst[l], del++;
                else r = ne[r], del++;
                if(l == r) return (del + (A[l] + A[r] > x ? 1 : 0)) <= m;
            }
            stable = l;
        } else if(r == stable) break;
        ne[l] = r, lst[r] = l;
        l = r, r = ne[r];
    }
    return del <= m;
}

int main() {
    FILE("necklace");
    scanf("%d%d%d", &tid, &n, &m);
    m = n - m;
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    int l = 0, r = 2e9;
    while(l < r) {
        int mid = ((long long)l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}