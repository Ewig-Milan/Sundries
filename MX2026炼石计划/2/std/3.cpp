#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1100;
int n;
int A[N];
bitset<N> f[N], g[N];

int main() {

    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);

    int mi = *min_element(A + 1, A + n + 1);
    int ma = *max_element(A + 1, A + n + 1);
    int pl = 1, pr = n;
    while(A[pl] != mi && A[pl] != ma) pl++;
    while(A[pr] != mi && A[pr] != ma) pr--;
    bitset<N> bsl, bsr;
    f[0][0] = 1;
    for(int i = 1; i < pl; i++) {
        f[i] |= f[i - 1] << (A[i] == A[1]);
        for(int j = 1; j < i; j++) {
            if(A[i] < A[1] && A[j] > A[1]) f[i] |= f[j];
            else if(A[i] > A[1] && A[j] < A[1]) f[i] |= f[j];
        }
        if(A[i] != A[1]) bsl |= f[i];
    }
    bsl |= f[pl - 1];

    g[n + 1][0] = 1;
    for(int i = n; i > pr; i--) {
        g[i] = g[i + 1] << (A[i] == A[n]);
        for(int j = n; j > i; j--) {
            if(A[i] < A[n] && A[j] > A[n]) g[i] |= g[j];
            else if(A[i] > A[n] && A[j] < A[n]) g[i] |= g[j];
        }
        if(A[i] != A[n]) bsr |= g[i];
    }
    bsr |= g[pr + 1];
    
    int offset = 0;
    for(int i = pl; i <= pr; i++) offset += A[i] == mi || A[i] == ma;
    
    vector<int> out;

    for(int i = 0; i <= pl; i++)
    for(int j = 0; j <= n - pr + 1; j++)
        if(bsl[i] && bsr[j]) out.push_back(offset + i + j);

    sort(out.begin(), out.end());
    out.erase(unique(out.begin(), out.end()), out.end());
    for(int x : out) printf("%d ", x);
    return 0;
}