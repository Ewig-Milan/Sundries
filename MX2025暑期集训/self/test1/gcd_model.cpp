#include <bits/stdc++.h>
using namespace std;
const int N = 6e5 + 5, M = 17, INF = 1e9;
int n, q, a[N];
int st[N][M];
struct S
{
    int val, nxt[M];
};
vector<S> vec[N];
inline S* find(int pos, int val)
{
    if (!vec[pos].size()) return NULL;
    int l = 0, r = vec[pos].size() - 1;
    while (l < r)
    {
        int m = (l + r) >> 1;
        if (vec[pos][m].val > val) l = m + 1;
        else r = m;
    }
    if (vec[pos][r].val == val) return &vec[pos][r];
    return NULL;
}
int main()
{
    freopen("gcd.in","r",stdin);
    freopen("gcd.out","w",stdout); 
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
 
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    for (int j = 1; j < M; j++)
        for (int i = 1; i <= n; i++) if (i + (1 << j) - 1 <= n)
            st[i][j] = __gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
 
    for (int i = 1; i <= n; i++)
    {
        int cur = a[i], now = i;
        S tmp;
        tmp.val = cur;
        tmp.nxt[0] = i + 1;
        for (int j = 1; j < M; j++) tmp.nxt[j] = INF;
        vec[i].emplace_back(tmp);
        while (now <= n)
        {
            for (int j = M - 1; j >= 0; j--)
                if (now + (1 << j) - 1 <= n && st[now][j] % cur == 0)
                    now += (1 << j);
            if (now <= n)
            {
                cur = __gcd(cur, a[now]);
                S tmp;
                tmp.val = cur;
                tmp.nxt[0] = now + 1;
                for (int j = 1; j < M; j++) tmp.nxt[j] = INF;
                vec[i].emplace_back(tmp);
            }
        }
    }
 
    for (int i = n; i >= 1; i--)
        for (auto& it : vec[i])
            for (int j = 1; j < M; j++) if (it.nxt[j - 1] <= n)
            {
                S* tmp = find(it.nxt[j - 1], it.val);
                if (tmp != NULL) it.nxt[j] = tmp->nxt[j - 1];
            }
 
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int k = __lg(r - l + 1);
        int g = __gcd(st[l][k], st[r - (1 << k) + 1][k]);
        int p = l, cnt = 0;
        for (int j = M - 1; j >= 0; j--)
        {
            S* tmp = find(p, g);
            if (tmp == NULL) break;
            if (tmp->nxt[j] <= r + 1)
                p = tmp->nxt[j], cnt += (1 << j);
        }
        printf("%d\n", r - l + 1 - cnt);
    }
    return 0;
}