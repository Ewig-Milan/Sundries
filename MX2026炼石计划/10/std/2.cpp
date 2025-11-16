#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

using ll = long long;

int trie[3000005][26], dep[3000005], val[3000005];

ll calc(int m, vector<vector<string>> &s) {
    int tot = 1, S = 0;
    vector<string> g;
    for (auto &v : s) {
        size_t min_size = 1e9;
        for (string t : v) {
            min_size = min(min_size, t.size());
        }
        for (string &t : v) {
            t.resize(min_size);
        }
        string t;
        for (int i = 0; i < min_size; i++) {
            for (int j = 0; j < m; j++) {
                t += v[j][i];
            }
        }
        g.push_back(t);
        S += t.size();
    }
    memset(trie, 0, (S + 2) * 26 * sizeof(int));
    memset(val, 0, (S + 2) * sizeof(int));
    for (auto t : g) {
        int now = 1;
        for (char ch : t) {
            int &to = trie[now][ch - 'a'];
            if (!to) to = ++tot, dep[tot] = dep[now] + 1;
            now = to;
        }
        val[now]++;
    }
    ll ans = 0;
    for (int i = tot; i > 1; i--) {
        ll total = 0, sum = val[i];
        total += 1ll * val[i] * val[i];
        for (int j = 0; j < 26; j++) {
            if (trie[i][j]) {
                total += sum * val[trie[i][j]] * 2;
                sum += val[trie[i][j]];
                val[i] += val[trie[i][j]];
            }
        }
        ans += 1ll * total * (dep[i] / m);
    }
    return ans;
}

int main() {
    FILE("lcp");
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<string>> s(n, vector<string>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> s[i][j];
        }
    }
    ll ans = 0;
    for (int S = 1; S < (1 << m); S++) {
        int cnt = __builtin_popcount(S);
        vector<vector<string>> p(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                if (S >> j & 1) {
                    p[i].push_back(s[i][j]);
                }
            }
        }
        ans += calc(cnt, p) * (cnt % 2 ? 1 : -1);
    }
    cout << ans << "\n";
    return 0;
}