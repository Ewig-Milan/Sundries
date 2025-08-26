#include <bits/stdc++.h>
using namespace std;

const int N = 700, mod = 1e9 + 7;

int n, m;
int a[N];

struct Node {
    int x, y;
	friend bool operator < (const Node & a, const Node & b) {
		return a.x > b.x;
	}
};

struct F {
    int cnt;
    Node v[N];

    void cl() {cnt = 0;}
    void add(int A, int B) {v[++cnt] = {A, B};}

    void comb() {
        sort(v + 1, v + cnt + 1);
        int k = 0;
        for(int i = 1, j; i <= cnt; i = j) {
            int sum = 0;
            for(j = i; j <= cnt && v[i].x == v[j].x; j++)
                sum =(sum + v[j].y) % mod;
            v[++k] = {v[i].x, sum};
            if(k >= m) break;
        }
        cnt = k;
    }
}f[2][N][3];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", a + i);

    sort(a + 1, a + n + 1);

    for(int i = 0; i < 2; i++)
	for(int j = 0; j <= n; j++)
	for(int k = 0; k < 3; k++)
		f[i][j][k].cl();

    f[1][1][0].add(0, 1);
    f[1][1][1].add(0, 2);

    int nw = 1, pre = 0;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= n; j++)
		for(int k = 0; k < 3; k++)
        	f[pre][j][k].cl();

        for(int j = 0; j <= n; j++)
            for(int k = 0; k < 3; k++) {
                f[nw][j][k].comb();
                int cnt = f[nw][j][k].cnt;
                if(!cnt) continue;
                int base = (a[i + 1] - a[i]) *(j * 2 - k);
                for(int l = 1; l <= cnt; l++) {
                    int A = base + f[nw][j][k].v[l].x;
                    int B = f[nw][j][k].v[l].y;
                    if(j + 1 > k)
                        f[pre][j + 1][k].add(A, (long long)B * (j + 1 - k) % mod);
                    if(j > 1)
                        f[pre][j - 1][k].add(A, (long long)B * (j - 1) % mod);
                    if(j * 2 > k)
                        f[pre][j][k].add(A, (long long)B * (j * 2 - k) % mod);
                    if(k < 2) {
                        f[pre][j + 1][k + 1].add(A, (long long)B * (2 - k) % mod);
                        f[pre][j][k + 1].add(A, (long long)B * (2 - k) % mod);
                    }
                }
            }
		swap(nw, pre);
    }

    f[nw][1][2].comb();
    int i = 1;
	while(i <= f[nw][1][2].cnt && i <= m) {
        printf("%d %d\n", f[nw][1][2].v[i].x,(f[nw][1][2].v[i].y % mod + mod) % mod);
		i++;
	}
	while(i <= m) {
		puts("-1 -1");
		i++;
	}
    return 0;
}