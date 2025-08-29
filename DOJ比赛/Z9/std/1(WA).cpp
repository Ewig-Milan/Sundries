#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

vector<int> factor[1100];
int pr[200], cnt, id[1100];
int n, q, A[N], go[N][200], p[1100], c[N], c0[N];

void prepare() {
    for(int i = 1; i <= 1000; i++) {
        int tmp = i;
        for(int k = 2; k * k <= tmp; k++) {
            if(tmp % k == 0) factor[i].push_back(k);
            while(tmp % k == 0) tmp /= k;
        }
        if(tmp > 1) factor[i].push_back(tmp);
        if(i > 1 && tmp == i) pr[++cnt] = i, id[i] = cnt;
    }
}

int main() {
    prepare();

    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        c[i] = c[i - 1] + (A[i] > 1);
        c0[i] = c0[i - 1] + (A[i] == 0);
    }
    for(int i = n; i; i--) {
        for(int t = 1; t <= cnt; t++) go[i][t] = n + 1;
        for(int a : factor[A[i]]) {
            if(p[a]) {
                for(int t = 1; t <= cnt; t++)
                    go[i][t] = min(go[i][t], go[p[a]][t]);
                go[i][id[a]] = p[a];
            }
            p[a] = i;
        }
    }
    while(q--) {
        int a, b;
        scanf("%d%d", &a, &b);
        if(a == b) puts("Shi");
        else if(A[a] == 1 || A[b] == 1) puts("Fou");
		else if(A[a] == 0 || A[b] == 0) puts(c[b] - c[a - 1] > 0 ? "Shi" : "Fou");
        else if(c0[b] - c0[a - 1] > 0) puts("Shi");
    	else {
            bool flag = 0;
            for(int a : factor[A[b]]) {
                if(go[a][id[a]] <= b) {
                    flag = 1;
                    break;
                }
            }
            puts(flag ? "Shi" : "Fou");
        }
    }
    return 0;
}