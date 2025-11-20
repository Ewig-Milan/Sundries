#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define INF ((1 << 30) - 1)
#define FI(n) FastIO::read(n)
#define mst(a, b) memset(a, b, sizeof(a))
#define For(i, k, j) for(int i =(k); i <=(j); i++)
#define Fin(s) freopen(s, "r", stdin)
#define Fout(s) freopen(s, "w", stdout)
#define file(s) Fin(s ".in"), Fout(s ".out")

const int P = 998244353;
using namespace std;

inline void addmod(int &a, int b) {
    int t = a + b;
    a = t % P;
    if(a < 0) a += P;
}
inline int ksm(int a, int b) {
    int ans = 1;
    for(; b; b >>= 1) {
        if(b & 1) ans = 1ll * ans * a % P;
        a = 1ll * a * a % P;
    }
    return ans;
}
inline int inv(int a) {return ksm(a, P - 2);}

inline void printarray(int *a, int n) {
    For(i, 1, n) fprintf(stderr, "%d ", a[i]);
    fprintf(stderr, "\n");
}
namespace FastIO {
    const int SIZE=1<<16;char buf[SIZE],obuf[SIZE],str[64];int bi=SIZE,bn=SIZE,opt;
    int read(char *s) {while(bn){for(;bi<bn&&buf[bi]<=' ';bi++);if(bi < bn)break;
    bn=fread(buf,1,SIZE,stdin),bi=0;}int sn=0;while(bn){for(;bi<bn&&buf[bi]>' ';bi++)
    s[sn++]=buf[bi];if(bi<bn)break;bn=fread(buf,1,SIZE,stdin),bi=0;}s[sn]=0;return sn;}
    bool read(int &x){if(x)x=0;int bf=0,n=read(str);if(!n)return 0;int i=0;if(str[i]=='-')
    bf=1,i=1;for(x=0;i<n;i++)x=x*10+str[i]-'0';if(bf)x=-x;return 1;}
    void write(int x){if(!x)obuf[opt++]='0';else{if(x<0)obuf[opt++]='-',x=-x;int sn=0;
    while(x)str[sn++]=x%10+'0',x/=10;for(int i=sn-1;i>=0;i--)obuf[opt++]=str[i];}
    if(opt >=(SIZE >> 1)){fwrite(obuf,1,opt,stdout);opt=0;}}
    void write(char x){obuf[opt++]=x;if(opt>=(SIZE>>1)){fwrite(obuf,1,opt,stdout);opt=0;}}
    void Fflush(){if(opt)fwrite(obuf,1,opt,stdout);opt=0;}
};
inline int read() {int x; FI(x); return x;}
const int MAXN = 3e5 + 5;
int n, a[MAXN];
inline int Highbit(int x) {
    for(int i = 30; i >= 0; i--) if((x >> i) & 1) return i;
    return 0;
}
inline int G(int x, int y) {
    if(x == y) return 0;
    int t = Highbit(x ^ y);
    return(1 << t);
}
int SS(vector<int> v) {
    if(v.size() == 1) return v[0];
    int n = v.size(), ans = INF;
    For(i, 0, n - 1) {
        For(j, i + 1, n - 1) {
            vector<int> x;
            for(int k = 0; k < i; k++) x.pb(v[k]);
            for(int k = i + 1; k < j; k++) x.pb(v[k]);
            for(int k = j + 1; k < n; k++) x.pb(v[k]);
            x.pb(G(v[i], v[j])), ans = min(ans, SS(x));
        }
    }
    return ans;
}
int calc(vector<int> t) {
    sort(t.begin(), t.end());
    int ans = SS(t);
    for(int i = 0; i < t.size(); i++)
        if(t[i]) t[i] = 1 << Highbit(t[i]);
    
    sort(t.begin(), t.end(), greater<int>());
    if(t.size() == 1) ans -= t[0];
    else if(t.size() == 2 && t[1] != t[0]) ans -= t[0];
    else if(t.size() == 3 &&(t[2] == t[0] || t[1] != t[0])) ans -= t[0];
    else if(t.size() == 4 &&((t[2] == t[0] && t[3] != t[0]) || t[1] != t[0])) ans -= t[0];
    else return(ans + P) % P;
    return(ans + P) % P;
}
int L[MAXN], R[MAXN];
int TT(vector<int> pos) {
    vector<int> sum;
    sum.resize(pos.size() + 3);
    for(int i = pos.size() - 1; i >= 0; i--) sum[i] = sum[i + 2] + R[pos[i]];
    int res = 0;
    for(int i = 0; i < pos.size(); i++)
        addmod(res, 1ll * L[pos[i]] *(sum[i] % P) % P);

    return res;
}
int solve() {
    For(i, 1, n) if(a[i]) a[i] = (1 << Highbit(a[i]));
    int res = 0;
    For(bit, 0, 30) {
        mst(L, 0), mst(R, 0);
        vector<int> pos;
        int tl = 0, tr = 0;
        a[n + 1] = INF;
        For(i, 1, n + 1) {
            if(a[i] >(1 << bit)) {
                tl = 0;
                if(!pos.size()) {tr = 0; continue;}
                R[pos[pos.size() - 1]] = tr + 1;
                tr = 0;
                addmod(res, 1ll * TT(pos) *(1 << bit) % P);
                pos.clear();
            } else {
                tl++, tr++;
                if(a[i] ==(1 << bit)) {
                    if(pos.size()) R[pos[pos.size() - 1]] = tr;
                    pos.pb(i);
                    L[pos[pos.size() - 1]] = tl;
                    tl = tr = 0;
                }
            }
        }
    }
    return res;
}
signed main() {
    file("xor");
    n = read();
    For(i, 1, n) a[i] = read();
    int res = 0;
    For(i, 1, n) {
        For(j, i, min(n, i + 3)) {
            vector<int> t;
            t.clear();
            For(k, i, j) t.pb(a[k]);
            addmod(res, calc(t));
        }
    }
    printf("%d\n",(res + solve()) % P);
    return FastIO::Fflush(), 0;
}