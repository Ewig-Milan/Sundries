#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;

const int N = 100100;

char c[N];
int n, d, p, D, T[N], cnt_2, cnt_5, t;
int f1[N], f2[N];
int h[1000100], g[1000100];

int main() {
    scanf("%s%d", c + 1, &d);
    cnt_2 = cnt_5 = 0;
    D = d, p = 1;
    n = strlen(c + 1);
    while(d % 2 == 0) d /= 2, p *= 2, cnt_2++;
    while(d % 5 == 0) d /= 5, p *= 5, cnt_5++;
    t = max(cnt_2, cnt_5);

    for(int i = n, pw = 1; i > 0; i--, pw = pw * 10 % d)
        T[i] =(T[i + 1] +(c[i] - '0') * pw) % d;

    f1[0] = 1, f2[0] = 0;
    h[T[1]] = !t;

    for(int i = 1, sum = 1; i <= n; i++) {
        f2[i] = sum;
        int v = 0;
        for(int j = 0, pw = 1; j < i && j < t; j++, pw = 10 * pw % D) {
            v =(v + pw *(c[i - j] - '0')) % D;
            if(!v) {
                f1[i] =(f1[i] + f2[i - j - 1]) % mod;
                f1[i] =(f1[i] + f1[i - j - 1]) % mod;
                f2[i] =(f2[i] + mod - f1[i - j - 1]) % mod;
            }
        }
        if(v % p == 0) {
            f1[i] =(f1[i] + g[T[i + 1]]) % mod;
            f1[i] =(f1[i] + h[T[i + 1]]) % mod;
            f2[i] =(f2[i] + mod - h[T[i + 1]]) % mod;
        }
        sum =(sum + f1[i]) % mod;
        if(i >= t) {
            h[T[i - t + 1]] =(h[T[i - t + 1]] + f1[i - t]) % mod;
            g[T[i - t + 1]] =(g[T[i - t + 1]] + f2[i - t]) % mod;
        }
    }
    printf("%d\n", (f1[n] + f2[n]) % mod);
    return 0;
}