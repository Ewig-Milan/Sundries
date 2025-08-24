#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 32;

int n, f[N][N];
char ch[N];

bool check(char c1, char c2) {
	if (c1 == '(' && c2 == ')') return true;
	if (c1 == '[' && c2 == ']') return true;
	if (c1 == '{' && c2 == '}') return true;
	if (c1 == '<' && c2 == '>') return true;
	if (c1 == '?' && c2 == ')') return true;
	if (c1 == '?' && c2 == ']') return true;
	if (c1 == '?' && c2 == '}') return true;
	if (c1 == '?' && c2 == '>') return true;
	if (c1 == '(' && c2 == '?') return true;
	if (c1 == '[' && c2 == '?') return true;
	if (c1 == '{' && c2 == '?') return true;
	if (c1 == '<' && c2 == '?') return true;
	return false;
}

int count(int l, int r) {
	if (check(ch[l], ch[r])) return 1;
	if (ch[l] == '?' && ch[r] == '?') return 4;
	return 0;
}

signed main() {
    scanf("%s", ch + 1);
    n = strlen(ch + 1);
    for(int i = 0; i <= n; i++) f[i + 1][i] = 1;

    for(int len = 2; len <= n; len++)
    for(int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1;
        for(int i = l + 1; i <= r; i++) f[l][r] += ((count(l, i) * f[l + 1][i - 1] * f[i + 1][r]));
    }
    printf("%lld", f[1][n]);
    return 0;
}