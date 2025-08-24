#include <bits/stdc++.h>
using namespace std;

const int N = 100;

int n;

char S[N], T[N];
string f[N], h[N];

int main() {
    scanf("%s%s", S + 1, T + 1);
    n = strlen(S + 1);
    for(int i = 1; i <= n; i++) for(int j = i - 1; j >= 0; j--) {
        string nw = f[j] + S[i], nw_ = h[j] + T[i];
        if(nw > f[j + 1]) f[j + 1] = nw, h[j + 1] = nw_;
        else if(nw == f[j + 1] && nw_ > h[j + 1]) h[j + 1] = nw_;
    }
	string ans = "";
    for(int i = 1; i <= n; i++) ans = max(ans, f[i] + h[i]);
    cout << ans;
    return 0;
}