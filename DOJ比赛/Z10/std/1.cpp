#include <bits/stdc++.h>
using namespace std;

int n, ans;

int main() {
    freopen("gcdxor.in", "r", stdin);
    freopen("gcdxor.out", "w", stdout);
    scanf("%d", &n);
    int tmp = (n >> 1);
    for(int i = 1; i <= tmp; i++)
    for(int b = (i << 1); b <= n; b += i)
        if(b - (b ^ i) == i) ans++;
    printf("%d", ans);
    return 0;
}