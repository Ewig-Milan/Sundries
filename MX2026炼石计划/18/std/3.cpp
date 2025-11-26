#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5;

void solve() {
    int n, c;
    cin >> n >> c;
    
    bitset<N + 1> a{}, b{};
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[x] = b[N - x] = 1;
    }
    
    double ans = -1;
    
    vector<int> lst(2 * c + 1);
    for (int i = 1; i <= 2 * c; i++) {
        lst[i] = i <= N && a[i] ? i : lst[i - 1];
    }
    
    for (int s = 2 * c; s >= 3; s--) {
        int z = lst[s - 1];
        if (2 * z >= s) {
            auto v = a & (s < N ? b >> (N - s) : b << (s - N));
            int x = v._Find_next(s - z);
            int y = s - x;
            if (x < y && y < z) {
                double p = 0.5 * (x + y + z);
                double area = sqrt(p * (p - x) * (p - y) * (p - z));
                if (ans < 0 || ans > area) {
                    ans = area;
                }
            }
        }
    }
    for (int z = 1; z <= c; z++) {
        if (a[z]) {
            int y = lst[z - 1];
            if (!y) {
                continue;
            }
            int x = a._Find_next(z - y);
            if (x < y) {
                double p = 0.5 * (x + y + z);
                double area = sqrt(p * (p - x) * (p - y) * (p - z));
                if (ans < 0 || ans > area) {
                    ans = area;
                }
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}