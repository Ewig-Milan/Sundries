#include<bits/stdc++.h>
#define up(a, b, c) for(int a = b; a <= c; ++a)
#define dn(a, b, c) for(int a = b; a >= c; --a)
const int N=11e6;
using namespace std;
int n, w[3][3], sm[N], g[N][2], dt, e[6];
string s, t;
void bfs(char a) {
    int c[2]={0};
    up(i, 0, n-1)
        if(t[i] == a)
            ++c[s[i]==')'];
    // cout<<c[0]<<' '<<c[1]<<'\n';
    for(int i = n - 1; i >= 0 && c[0] > c[1]; --i)
        if(t[i] == a && s[i] == '(')
            --c[0], ++c[1], s[i] = ')', ++dt;
    for(int i = 0; i < n && c[0] < c[1]; ++i)
        if(t[i] == a && s[i] == ')')
            --c[1], ++c[0], s[i] = '(', ++dt;
}
void dfs(int *w, char a, char b) {
    int cnt[2] = {0};
    up(i, 0, n - 1) {
        if(i == 0) sm[i] = 0;
        else sm[i] = sm[i - 1];
        if(t[i] == a || t[i] == b)
        {
            if(s[i] == '(')
                sm[i] += 1;
            else sm[i] -= 1, ++cnt[t[i] == b];
            up(z, 0, 1)g[i][z] = cnt[z];
        }
    }
    assert(sm[n-1]==0);
    cnt[0] = cnt[1] = 0;
    dn(i, n - 1, 0) 
        if(t[i] == a || t[i] == b) {
            up(z, 0, 1)g[i][z] = min(cnt[z], g[i][z]);
            cnt[t[i] == b] += s[i] == '(';
        }
    up(i, 0, n - 1)
        if(sm[i] < 0 && (t[i] == a || t[i] == b))
            w[0] = max(w[0], (1 - sm[i]) / 2 - g[i][1]),
            w[1] = max(w[1], (1 - sm[i]) / 2 - g[i][0]),
            w[2] = max(w[2], (1 - sm[i]) / 2);
}
bool check()
{
    for(auto [z, x, y] : { make_tuple(0, 0, 1), make_tuple(1, 0, 2), make_tuple(2, 1, 2)})
        if(w[z][0] > e[x] || w[z][1] > e[y] || w[z][2] > e[x] + e[y])
            return 0;
    return 1;
}
int main() {
    
    freopen("witch.in", "r", stdin);
    freopen("witch.out", "w", stdout);
    cin >> s >> t, n = s.size();
    for (auto x : {'1','2','3'})bfs(x);
    for (auto [x, y, z] : { make_tuple(0, '1', '2'), make_tuple(1, '1', '3'), make_tuple(2, '2', '3') })
        dfs(w[x], y, z);
    e[0] = max(w[0][0], w[1][0]),
    e[1] = max(w[0][1], w[2][0]),
    e[2] = max(w[1][1], w[2][1]),
    e[3] = w[0][2],
    e[4] = w[1][2],
    e[5] = w[2][2];
    cout<<dt+2*max(
    {
        e[0] + e[1] + e[2],
        e[0] + e[5],
        e[1] + e[4],
        e[2] + e[3],
        (e[3]+e[4]+e[5]+1)/2
    }
    );
    return 0;
}