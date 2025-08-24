#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int T, n;

char A[N], B[N], C[N];

int cnt[26];

int main() {
    freopen("lcp.in", "r", stdin);
    freopen("lcp.out", "w", stdout);
    scanf("%d", &T);
    while(T--) {
        memset(cnt, 0, sizeof cnt);
        scanf("%d", &n);
        scanf("%s%s%s", A + 1, B + 1, C + 1);
        for(int i = 3; i <= n; i++) cnt[C[i] - 'a']++;
        cnt[A[1] - 'a'] = 0;

        bool flag = false;

        for(int i = 2; i <= n - 1; i++) {
            if(B[i] == A[1]) continue;
            for(int j = 0; j < 26; j++) if(B[i] - 'a' != j && cnt[j] > 0) {
                flag = true;
                break;
            }
            if(flag) break;
            cnt[C[i + 1] - 'a']--;
        }
        if(flag) {
            puts("0");
            continue;
        }
        bool flag_ = true;
        for(int i = 2; i <= n - 1; i++) flag_ &= (B[i] == A[1]);
        for(int i = 3; i <= n; i++) flag_ &= (C[i] == A[1]);
        if(flag_) {
            puts("3");
            continue;
        }
        puts("1");
    }
    return 0;
}