#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 1000100;

int n, k, r;
int A[N], last[N];

bool check(int x) {
    int p = 1;
    while(p <= x) last[p] = A[p], p++;
    for(int cnt = 1; cnt < k; cnt++)
    for(int i = 1; i <= x; i++) {
        while(p <= n && (long long)A[p] - r < (long long)last[i]) p++;
        if(p > n) return false;
        last[i] = A[p++];
    }
    return true;
}

int main() {
    FILE("pagoda");
    scanf("%d%d%d", &n, &k, &r);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    sort(A + 1, A + n + 1);
    int l = 0, r = n / k;
    while(l < r) {
        int mid = (l + r + 1) >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%d", l);
    return 0;
}