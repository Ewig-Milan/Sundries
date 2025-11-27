#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define ull unsigned long long
using namespace std;

const int N = 2000100;

int n, ans;
int A[N];

int L[N], R[N];
struct Intv {int l, r;};
vector<Intv> Q;

mt19937_64 rd(time(nullptr));
ull w[N], sum[N], pres[N], Aw[N];
void prepare() {
    for(int i = 0; i < n; i++) w[i] = rd();
    sum[0] = w[0];
    for(int i = 1; i < n; i++) sum[i] = w[i] + sum[i - 1];
    for(int i = 1; i <= n; i++) Aw[i] = (A[i] < n ? w[A[i]] : 0);
    for(int i = 1; i <= n; i++) pres[i] = pres[i - 1] + Aw[i];
}
bool check(int l, int r) {return pres[r] - pres[l - 1] == sum[r - l];}

int main() {
    FILE("mex");
    scanf("%d", &n);
    int mi = 1e9;
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]), mi = min(mi, A[i]);
    if(mi != 0) {printf("%lld\n", (long long)n * (n + 1) / 2); return 0;}
    prepare();
    deque<int> q;
    for(int i = 1; i <= n; i++) {
        while(!q.empty() && A[q.back()] <= A[i]) R[q.back()] = i - 1, q.pop_back();
        if(!q.empty()) L[i] = q.back() + 1;
        q.push_back(i);
    }
    for(int i = 1; i <= n; i++) {if(!L[i]) L[i] = 1; if(!R[i]) R[i] = n;}
    for(int i = 1; i <= n; i++) {
        int l = max(L[i], i - A[i]), r = l + A[i];
        while(r <= R[i] && l <= i) Q.push_back({l, r}), l++, r++;
    }
    for(Intv x : Q) ans += check(x.l, x.r);
    printf("%d\n", ans);
    return 0;
}