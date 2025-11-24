#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
using namespace std;

const int N = 100100;

int n, A[N];
int cnt;
vector<int> ans;

int main() {
    FILE("game");
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for(int l = n, r = n; l; l--) {
        if(!((l & 1) ^ (A[l] & 1))) {
            cnt += r - l + 1, ans.push_back(A[l]);
            while(r > l) ans.push_back(A[r]), r--;
            r--;
        }
    }
    printf("%d\n", cnt);
    for(int x : ans) printf("%d ", x);
    return 0;
}