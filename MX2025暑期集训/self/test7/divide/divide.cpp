#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 300100, mod = 998244353;

int n, A[N], mex;
int pre[N], sum[N];
int f[N]; // f0 = 1
int cnt[N];

bool check(int x) {
    memset(cnt, 0, sizeof cnt);
    for(int i = 1; i <= x; i++) cnt[A[i]] = 1;
    for(int i = 0; i <= n; i++) if(!cnt[i]) {
        if(i != mex) return false;
        else return true;
    }
    return true;
}

signed main() {
    freopen("divide.in", "r", stdin);
    freopen("divide.out", "w", stdout);
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &A[i]), cnt[A[i]] = 1;
    for(int i = 0; i <= n; i++) if(!cnt[i]) {
        mex = i;
        break;
    }
    if(mex) {
        int l = 1, r = n;
        while(l < r) {
            int mid = l + r >> 1;
            if(check(mid)) r = mid;
            else l = mid + 1;
        }
        memset(cnt, 0, sizeof cnt);
        for(int i = 1; i < l; i++) cnt[A[i]]++;
        int p = 1;
        for(int i = l; i <= n; i++) {
            if(A[i] < mex) cnt[A[i]]++;
            while(A[p] >= mex || cnt[A[p]] > 1) {
                if(A[p] < mex) cnt[A[p]]--;
                p++;
            }
            pre[i] = p;
        }
    } else for(int i = 1; i <= n; i++) pre[i] = i;

    f[0] = sum[0] = 1;
    for(int i = 1; i <= n; i++) {
        if(pre[i] > 0) f[i] = sum[pre[i] - 1];
        sum[i] = sum[i - 1] + f[i], sum[i] %= mod;
    }
    printf("%lld", f[n]);
    return 0;
}