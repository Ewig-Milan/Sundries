#include <bits/stdc++.h>
using namespace std;

int n;
int ma0, mi0 = 1e9, ma1, mi1 = 1e9, A, B;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++) {
        int a; scanf("%d", &a);
        if(i != n || j != 1) ma0 = max(ma0, a), mi0 = min(mi0, a);
        else A = a;
        if(i != 1 || j != n) ma1 = max(ma1, a), mi1 = min(mi1, a);
        else B = a;
    }
    printf("%d", min(max(ma0 - A, A - mi0), max(ma1 - B, B - mi1)));
    return 0;
}