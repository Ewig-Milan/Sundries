#include <bits/stdc++.h>
using namespace std;

int T, n, m;
string ans, tmp;

string solve(int n, int m) {
    if(n < 2) return "-1";
    ans = "";
    while(n > 0 && n != 3) ans += "11", n -= 2;
    if(n == 3) ans += "10101", m -= 2;
    if(m < 0) return "-1";
    while(m) ans += "0", m--;
    return ans;
}

string solve_(int n, int m) {
    if(n < 2) return "-1";
    ans = "1";
    int need = ((n + m) & 1) ? 2 : 1;
    n--;
    tmp = "";
    while(n > 2) tmp += "11", n -= 2;
    if(need == 1) {
        if(n == 1) tmp += "1", n--;
        else tmp += "0101", n -= 2, m -= 2;
    } else {
        if(n == 1) tmp += "01", n--, m--;
        else tmp += "1010", n -= 2, m -= 2;
    }
    if(m < 0) return "-1";
    while(m) tmp += "0", m--;
    reverse(tmp.begin(), tmp.end());
    ans += tmp;
    return ans;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        cout << solve(n, m) << '\n' << solve_(n, m) << '\n';
    }
    return 0;
}