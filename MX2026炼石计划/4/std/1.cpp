#include <bits/stdc++.h>
using namespace std;

const int N = 1100000;

int n, m;

int A[N], prex[N];
int L[N], R[N];
int cnt[N];
long long pres[N];

int main() {

    freopen("xorseg.in", "r", stdin);
    freopen("xorseg.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]), prex[i] = prex[i - 1] ^ A[i];
    deque<int> q;
    for(int i = 1; i <= n; i++) {
        while(!q.empty() && A[i] >= A[q.back()]) R[q.back()] = i - 1, q.pop_back();
        if(!q.empty()) L[i] = q.back() + 1;
        q.push_back(i);
    }
    for(int i = 1; i <= n; i++) L[i] ? 1 : (L[i] = 1), R[i] ? 1 : (R[i] = n);
    for(int i = 1; i <= n; i++) {
        for(int l = max(L[i], i - A[i] + 1); l + A[i] - 1 <= R[i] && l <= i; l++) {
            int r = l + A[i] - 1;
            cnt[prex[r] ^ prex[l - 1]]++;
        }
    }
    pres[0] = cnt[0];
    for(int i = 1; i < N; i++) pres[i] = pres[i - 1] + cnt[i];
    while(m--) {
        int a; scanf("%d", &a);
        printf("%lld\n", pres[a]);
    }
    return 0;
}