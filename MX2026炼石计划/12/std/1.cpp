#include <bits/stdc++.h>
#define int long long
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 200100;

int n, q;
int A[N], B[N];

int st1[19][N], st2[19][N], Log2[N];
int s1[N], s2[N];

void prepare() {
    Log2[2] = 1;
    for(int i = 3; i < N; i++) Log2[i] = Log2[i / 2] + 1;
    
    for(int i = 1; i <= n; i++) st1[0][i] = st2[0][i] = i;
    for(int j = 1; j < 19; j++) for(int i = 1; i + (1 << j) - 1 <= n; i++) {
        if(A[st1[j - 1][i]] > A[st1[j - 1][i + (1 << (j - 1))]]) st1[j][i] = st1[j - 1][i];
        else st1[j][i] = st1[j - 1][i + (1 << (j - 1))];
        if(B[st2[j - 1][i]] > B[st2[j - 1][i + (1 << (j - 1))]]) st2[j][i] = st2[j - 1][i];
        else st2[j][i] = st2[j - 1][i + (1 << (j - 1))];
    }
    for(int i = 1; i <= n; i++) s1[i] = s1[i - 1] + A[i], s2[i] = s2[i - 1] + B[i];
}

int query_A(int x, int y) {
    int s = Log2[y - x + 1];
    if(A[st1[s][x]] > A[st1[s][y -(1 << s) + 1]]) return st1[s][x];
    return st1[s][y -(1 << s) + 1];
}
int query_B(int x, int y) {
    int s = Log2[y - x + 1];
    if(B[st2[s][x]] > B[st2[s][y -(1 << s) + 1]]) return st2[s][x];
    return st2[s][y -(1 << s) + 1];
}
int get_A(int l, int r) {return s1[r] - s1[l - 1];}
int get_B(int l, int r) {return s2[r] - s2[l - 1];}

signed main() {
    FILE("max");
    scanf("%lld%lld", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%lld", &A[i]);
    for(int i = 1; i <= n; i++) scanf("%lld", &B[i]);
    prepare();
    while(q--) {
        int l1, r1, l2, r2;
        scanf("%lld%lld%lld%lld", &l1, &r1, &l2, &r2);
        int ma1 = query_A(l1, r1) - l1, ma2 = query_B(l2, r2) - l2;
        int sm1 = get_A(l1, r1), sm2 = get_B(l2, r2);
        int rem = -1;
        if(A[ma1 + l1] > sm2 - B[ma1 + l2] && B[ma1 + l2] > sm1 - A[ma1 + l1]) rem = ma1;
        else if(B[ma2 + l2] > sm1 - A[ma2 + l1] && A[ma2 + l1] > sm2 - B[ma2 + l2]) rem = ma2;
        if(rem == -1) printf("%lld\n", min(sm1, sm2) + abs(sm1 - sm2));
        else {
            int ans = sm1 - A[rem + l1] + sm2 - B[rem + l2];
            ans += B[rem + l2] - (sm1 - A[rem + l1]) + A[rem + l1] - (sm2 - B[rem + l2]);
            printf("%lld\n", ans);
        }
    }
    return 0;
}