#include <bits/stdc++.h>
using namespace std;

const int N = 500100;

int n, q, k, t;
char s[N], s_new[N];
int s_idx;
int id[N];
int white[N], pres[N], idx, st[N][20]; // 下标 idx

int main() {

    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);

    int nothing; scanf("%d", &nothing);
    scanf("%d%d%d%d", &n, &q, &k, &t);
    scanf("%s", s + 1);
    for(int i = 1, jp_cnt = 0, black = 0; i <= n; i++) {
        if(s[i] == '0') black++;
        else {
            id[i] = ++idx, pres[idx] = jp_cnt;
            while(black > 0) s_new[++s_idx] = '0', black--;
            s_new[++s_idx] = '1';
        }
        if(black == k) black = 0, jp_cnt++;
    }
    idx = 0;
    for(int i = 1; i <= s_idx; i++) if(s_new[i] == '1') white[++idx] = i;
    for(int i = 1, r = 1; i <= idx; i++) {
        while(r <= idx && white[r] - white[i] <= k) r++;
        st[i][0] = r - 1;
    }
    for(int i = 1; i < 20; i++) for(int j = 1; j <= idx; j++)
        st[j][i] = st[st[j][i - 1]][i - 1];

    while(q--) {
        int l, r; scanf("%d%d", &l, &r);
        if(l > r) swap(l, r);
        l = id[l], r = id[r];
        int mi = pres[r] - pres[l], step = 0;
        for(int i = 19; i >= 0; i--) if(st[l][i] < r)
            l = st[l][i], step += (1 << i);
        printf(t ? "%d %d\n" : "%d\n", mi, mi + step + 1);
    }
    return 0;
}