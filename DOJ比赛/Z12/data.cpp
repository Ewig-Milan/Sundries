#include <bits/stdc++.h>
#include <sys/timeb.h>
using namespace std;

int Rand(int l, int r) {
    int x = rand();
    x += l;
    return x % (r - l + 1) + l;
}

int main() {
    freopen("data.in", "w", stdout);
    struct _timeb T;
    _ftime(&T), srand(T.millitm);
    int n = Rand(2, 10), C = Rand(1, 20);
    printf("%d %d\n", n, C);
    for(int i = 1, old = 0; i < n; i++) {
        int tmp = Rand(old + 1, old + C);
        printf("%d ", tmp);
        old = tmp;
    }
    puts("");
    for(int i = 1; i < n; i++) {
        int a = Rand(0, 20);
        printf("%d %d\n", Rand(a, 20), a);
    }
    return 0;
}