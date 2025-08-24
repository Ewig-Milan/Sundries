#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, q;
char c[N];
bool last[N];
int pre_need[N], suf_need[N];

int main() {
    scanf("%d%d", &n, &q);
    scanf("%s", c + 1);
    for(int i = 1; i <= n; i++) c[i] -= 'A' - 1;
    for(int i = 1; i <= n; i++) {
        pre_need[i] = pre_need[i - 1];
        if(!last[c[i]]) pre_need[i]++;
        last[c[i]] = 1;
        for(int j = c[i] + 1; j <= 26; j++) last[j] = 0;
    }
    memset(last, 0, sizeof last);
    for(int i = n; i; i--) {
        suf_need[i] = suf_need[i + 1];
        if(!last[c[i]]) suf_need[i]++;
        last[c[i]] = 1;
        for(int j = c[i] + 1; j <= 26; j++) last[j] = 0;
    }
    while(q--) {
        int a, b; scanf("%d%d", &a, &b);
        printf("%d\n", pre_need[a - 1] + suf_need[b + 1]);
    }
    return 0;
}