#include <bits/stdc++.h>
using namespace std;

const int N = 200100, sqrtN = 450;

int n, q, k, ans, sum;
int d[N], mp[N], idx, Bcnt;
vector<int> col[N];
bool on[N];
int Bb[sqrtN][sqrtN], Bs[sqrtN]; // Big-Big & Big-Small
// 以上基于新颜色
int d_[N], cnt[N]; // d_ 原颜色 cnt 原颜色计数

int main() {
    scanf("%d%d%d", &n, &q, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &d_[i]);
        cnt[d_[i]]++;
    }
    for(int i = 1; i <= k; i++) if(cnt[i] > 440) mp[i] = ++idx;
    Bcnt = idx;
    for(int i = 1; i <= k; i++) if(cnt[i] && cnt[i] <= 440) mp[i] = ++idx;

    for(int i = 1; i <= n; i++)
        col[mp[d_[i]]].push_back(i), d[i] = mp[d_[i]]; // mp[d_[i]] 是它的新颜色

    for(int i = 1; i < n; i++)
    if(d[i] <= Bcnt && d[i + 1] <= Bcnt) {
        Bb[d[i]][d[i + 1]]++;
        if(d[i] != d[i + 1]) Bb[d[i + 1]][d[i]]++;
    }
    while(q--) {
        int a; scanf("%d", &a); a = mp[a];
        on[a] ^= 1;
        int k = on[a] ? 1 : -1;
        sum += k * col[a].size();
        if(a <= Bcnt) {
            ans += k * Bs[a];
            for(int i = 1; i <= Bcnt; i++)
                if(on[i] || i == a) ans += k * Bb[a][i];
        } else {
            for(int i : col[a]) {
                if(i > 1 && (on[d[i - 1]] || d[i - 1] == a)) ans += k;
                if(i > 1 && d[i - 1] <= Bcnt) Bs[d[i - 1]] += k;
                if(i < n && on[d[i + 1]] && d[i + 1] != a) ans += k;
                if(i < n && d[i + 1] <= Bcnt) Bs[d[i + 1]] += k;
            }
        }
        printf("%d\n", sum - ans);
    }
    return 0;
}