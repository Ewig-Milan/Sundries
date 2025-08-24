#include <bits/stdc++.h>
using namespace std;

const int N = 30, M = 500100;

int n, s_n, ans;
int cnt[26][2];
char s[N][M];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
    s_n = strlen(s[1] + 1);
    for(int i = 1; i <= n; i++)
    for(int j = i + 1; j <= n; j++) {
        bool same = true;
        for(int k = 1; k <= s_n; k++) same &= s[i][k] == s[j][k];
        if(same) continue;
        memset(cnt, 0, sizeof cnt);
        for(int k = 1; k <= s_n; k++) cnt[s[i][k] - 'a'][0]++;
        for(int k = 1; k <= s_n; k++) cnt[s[j][k] - 'a'][1]++;
        bool solvable = true;
        for(int k = 0; k < 26; k++) if(cnt[k][0] != cnt[k][1]) {
            ans += 6666, solvable = false;
            break;
        }
        if(!solvable) continue;
        int l = 1, r = 1;
        for(int k = 1; k <= s_n; k++) if(s[i][k] != s[j][k]) {
            l = k;
            break;
        }
        for(int k = s_n; k; k--) if(s[i][k] != s[j][k]) {
            r = k;
            break;
        }
        bool sorted = false;
        int k = l;
        for(int nw = 0; k <= r; k++) {
            if(nw > s[i][k] - 'a') break;
            nw = s[i][k] - 'a';
        }
        if(k == r + 1) sorted |= true;
        k = l;
        for(int nw = 0; k <= r; k++) {
            if(nw > s[j][k] - 'a') break;
            nw = s[j][k] - 'a';
        }
        if(k == r + 1) sorted |= true;
        ans += sorted ? 1 : 2;
    }
    printf("%d", ans);
    return 0;
}