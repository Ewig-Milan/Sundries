#include <bits/stdc++.h>
using namespace std;

const int N = 1100;

int n;
int d[N];

int main() {

    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);

    scanf("%d", &n);
    int ma = 0, mi = 1e9;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
        ma = max(ma, d[i]), mi = min(mi, d[i]);
    }
    int ma_cnt = 0, mi_cnt = 0;
    for(int i = 1; i <= n; i++) ma_cnt += (d[i] == ma), mi_cnt += (d[i] == mi);
    if(ma == mi) ma_cnt = 0;
    printf("%d", ma_cnt + mi_cnt + ((d[1] != ma && d[1] != mi) ? 1 : 0) + ((d[n] != ma && d[n] != mi) ? 1 : 0));
    return 0;
}