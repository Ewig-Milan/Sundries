#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll gcd(ll a, ll b) {
    if(!b) return a;
    return gcd(b, a % b);
}

const int N = 13;

ll n, pb[N];
int b;
bool need;


bool flag1, flag2, used[N];

void dfs1(ll x, int y, bool lz) {
    if(y == b) {
        if(x % n == 0) {
            if(flag1) {
                printf("%lld\n", x);
                exit(0);
            } else flag1 = 1;
        }
        return;
    }
    if(need && y == 0) dfs1(0, 1, 1);
    else for(int i = b - 1; i >= 0; --i) {
        if(!used[i]) {
            if(i || !lz) used[i] = 1;
            dfs1(x + i * pb[b - y - 1], y + 1, lz && !i);
            used[i] = 0;
        }
    }
}

void dfs2(ll x, int y, bool lz, int tmp) {
    if(y == b - 5 && n > pb[5] &&(x + n - 1) / n * n - x >= pb[5]) return;
    if(y == b - 4 && n > pb[4] &&(x + n - 1) / n * n - x >= pb[4]) return;
    if(y == b - 3) {
        ll z =(x + n - 1) / n * n - x;
        if(z >= b * b * b) return;
        ll a[3] = {z /(b * b), z / b % b, z % b};
        if(a[1] && a[1] == a[2]) return;
        if((a[0] || !lz) &&(a[1] == a[2] || a[2] == a[0] || a[0] == a[1])) return;
        if((a[0] || !lz) && !((tmp >> a[0]) & 1)) return;
        if((a[0] || a[1] || !lz) && !((tmp >> a[1]) & 1)) return;
        if((a[0] || a[1] || a[2] || !lz) && !((tmp >> a[2]) & 1)) return;
        if(flag2) {
            printf("%lld\n", x + z);
            exit(0);
        } else flag2 = 1;
        return;
    }
    if(need && y == 0) dfs2(0, 1, 1,(1 << b) - 1);
    else {
        int nw = tmp;
        while(tmp) {
            int i = 31 - __builtin_clz(tmp);
            dfs2(x + i * pb[b - y - 1], y + 1, lz && !i, nw ^((i || !lz) << i));
            tmp ^= 1 << i;
        }
    }
}

int main() {
    scanf("%lld%d", &n, &b);
    int g = gcd(n, b - 1);
    int s = b * (b - 1) / 2;
    if(s % g) need = 1;
    if(n % (b * b) == 0) {
        puts("-1");
        return 0;
    }
    pb[0] = 1;
    for(int i = 1; i <= b; i++) pb[i] = pb[i - 1] * b;

    if(n <= b * b * b || b <= 4) {
        dfs1(0, 0, 1);
        puts("-1");
    } else {
        dfs2(0, 0, 1, (1 << b) - 1);
        puts("-1");
    }
    return 0;
}