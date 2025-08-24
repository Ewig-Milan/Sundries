#include <bits/stdc++.h>
using namespace std;

int n, cnt;

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        char c[10]; scanf("%s", c);
        for(int j = 0; j < n; j++) cnt += c[j] == '.';
    }
    if(cnt <= 1) {
        puts("0");
        return 0;
    }
    if(cnt < 4) puts("1");
    else puts("2");
    return 0; 
}