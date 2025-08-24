#include <bits/stdc++.h>
using namespace std;

const int N = 1000100;

int t, n, p;

bitset<N> f, tmp;

vector<int> change;

int main() {
    freopen("op.in", "r", stdin);
    freopen("op.out", "w", stdout);
    scanf("%d", &t);
    while(t--) {
        change.resize(0);
        f.reset(), tmp.reset();
        scanf("%d%d", &p, &n);
        for(int i = 0; i < p; i++) tmp[i] = 1;
        for(int i = 1; i <= n; i++) {
            int mode, x; scanf("%d%d", &mode, &x);
            if(mode) change.push_back(x);
            else f[x] = 1;
        }
        for(int i : change) {
            f |= ((f >> (p - i)) | ((f << i) & tmp));
        }
        printf("%d\n", p - f.count());
    }
    return 0;
}