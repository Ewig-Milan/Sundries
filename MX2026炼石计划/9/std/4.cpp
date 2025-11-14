#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#include<bits/stdc++.h>
#define FF first
#define SS second
#define MP make_pair
#define PB push_back
typedef long long ll;
using namespace std;
ll qpow(ll x, ll k, ll md) {
  return k==0?1:qpow(x*x%md, k>>1, md)*(k&1?x:1)%md;
}
const int maxn = 2222;
const int maxv = 44;
const int K = 80;
const int maxK = 100;
const int Mods[] = {1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000103, 1000000123, 1000000181, 1000000207, 1000000223, 1000000241, 1000000271, 1000000289, 1000000297, 1000000321, 1000000349, 1000000363, 1000000403, 1000000409, 1000000411, 1000000427, 1000000433, 1000000439, 1000000447, 1000000453, 1000000459, 1000000483, 1000000513, 1000000531, 1000000579, 1000000607, 1000000613, 1000000637, 1000000663, 1000000711, 1000000753, 1000000787, 1000000801, 1000000829, 1000000861, 1000000871, 1000000891, 1000000901, 1000000919, 1000000931, 1000000933, 1000000993, 1000001011, 1000001021, 1000001053, 1000001087, 1000001099, 1000001137, 1000001161, 1000001203, 1000001213, 1000001237, 1000001263, 1000001269, 1000001273, 1000001279, 1000001311, 1000001329, 1000001333, 1000001351, 1000001371, 1000001393, 1000001413, 1000001447, 1000001449, 1000001491, 1000001501, 1000001531, 1000001537, 1000001539, 1000001581, 1000001617, 1000001621, 1000001633, 1000001647, 1000001663, 1000001677, 1000001699, 1000001759, 1000001773, 1000001789, 1000001791, 1000001801, 1000001803, 1000001819, 1000001857, 1000001887, 1000001917, 1000001927, 1000001957, 1000001963, 1000001969, 1000002043, 1000002089};
int T, n, m;
int a[maxn], b[maxn], pos[maxn];
map<int, int> E[maxn];
void addto(const vector<int> &y, const int c, vector<int> &x, const int md) { //x += y*c
  assert(x.size()==y.size());
  for (int i=0; i<x.size(); i++) x[i] = (x[i]+1ll*y[i]*c)%md;
}

struct Gauss {
  int mod;
  ll qpow(ll x, ll k) {
    return k==0?1:qpow(x*x%mod, k>>1)*(k&1?x:1)%mod;
  }
  int getinv(int x) {
    assert(x!=0);
    if (x==1) return 1;
    if (x==2) return (mod+1)/2;
    if (x<0) return getinv(-x);
    return qpow(x, mod-2);
  }
  vector<int> con[maxn];
  int A[maxn][maxv], a[maxv][maxv];
  int vid[maxn], vn;
  void addto(int y[], const int c, int x[], const int n) { //x += y*c
    for (int i=0; i<n; i++) x[i] = (x[i]+1ll*y[i]*c)%mod;
  }
  bool gauss(int n, int m) {
    for (int i=0; i<n; i++) for (int j=0; j<=m; j++) a[i][j] %= mod;
    for (int i=0; i<n; i++) {
      int p = -1, x = m-1-i;
      for (int j=i; j<n; j++) if (a[j][x]%mod!=0) p = j;
      if (p==-1) return false;
      for (int j=0; j<m; j++) swap(a[i][j], a[p][j]);
      int c = qpow(a[i][x], mod-2);
      for (int j=0; j<m; j++) a[i][j] = 1ll*a[i][j]*c%mod;
      for (int j=0; j<n; j++) {
        if (i==j) continue;
        int t = a[j][x];
        if (!t) continue;
        for (int k=0; k<m; k++) a[j][k] = (a[j][k]-1ll*a[i][k]*t)%mod;
      }
    }
    return true;
  }
  bool prework() {
    memset(A, 0, sizeof(A));
    memset(a, 0, sizeof(a));
    memset(vid, -1, sizeof(vid));
    vn = 0;
    for (int i=n+1; i<n+2+m; i++) vid[i] = vn++, A[i][vid[i]] = 1;
    for (int i=2; i<=n; i++) if (b[i-1]==2&&b[i]==1) {
        vid[i] = vn++;
        A[i][vid[i]] = 1;
      }
    assert(vn<maxv);
    int e = 0;
    for (int i=n+1; i>=1; i--) {
      int x = E[i].begin()->FF, c = getinv(E[i].begin()->SS);
      if (x<i) {
        for (auto p : E[i]) {
          if (p.FF==x) continue;
          assert(p.FF>x||vid[p.FF]!=-1);
          addto(A[p.FF], -1ll*p.SS*c%mod, A[x], vn);
        }
      } else {
        for (auto p : E[i]) {
          addto(A[p.FF], p.SS, a[e], vn);
        }
        e++;
      }
    }
    assert(vn-e==m+1);
    if (!gauss(e, vn)) return false;
    for (int i=0; i<=n; i++) {
      for (int j=m+1; j<vn; j++) {
        if (A[i][j]!=0) {
          addto(a[vn-j-1], -A[i][j], A[i], vn);
        }
      }
    }
    return true;
  }
};
Gauss allG[maxK], G[K];
int mods[K], invs[K];
const int mod = 1e9+7;
int A[maxn][maxn], val[maxn][K], dlt[maxn];
int par[maxn];
int getmodval(int x, int md) {
  int prod = 1;
  for (int i=0; i<K; i++) prod = 1ll*prod*mods[i]%md;
  int ans = -1ll*prod*dlt[x]%md;
  for (int i=0; i<K; i++) {
    ans = (ans+1ll*prod*qpow(mods[i], md-2, md)%md*(1ll*val[x][i]*invs[i]%mods[i]))%md;
  }
  return ans;
}
bool getvals(int x, int msk) {
  for (int i=0; i<K; i++) {
    ll v = G[i].A[x][0];
    for (int j=0; j<m; j++) if ((msk>>j)&1) v += G[i].A[x][j+1];
    val[x][i] = (v%mods[i]+mods[i])%mods[i];
  }
  double t = 0;
  int p = 0;
  dlt[x] = 0;
  for (int i=0; i<K; i++) {
    ll c = 1ll*val[x][i]*invs[i]%mods[i];
    t += 1.0*c/mods[i];
    if (t>1-0.1/n) p ^= 1, t--, dlt[x]++;
    p ^= c&1;
  }
  if (x>0&&p!=par[x]) return false;
  if (t>0.1/n&&t<1-0.1/n) return false;
  return true;
}


void solve() {
  scanf("%d", &n);
  vector<int> v;
  for (int i=1; i<=n; i++) {
    scanf("%d", &a[i]);
    a[i] = i-a[i];
  }
  memset(pos, -1, sizeof(pos));
  a[0] = -1;
  b[0] = 1;
  for (int i=1; i<=n; i++) {
    scanf("%d", &b[i]);
    if (b[i]==2) {
      m++;
      pos[i+1] = v.size();
      v.PB(i+1);
    }
  }
  assert(v.size()==m);

  for (int i=0; i<=n+1; i++) E[i].clear();
  for (int i=0; i<=n; i++) {
    E[i][i]-=2;
    E[i-a[i]][i]++;
    E[i+b[i]][i]++;
  }
  E[0][n+1]+=2;
  E[n+1][n+1]-=2;
  for (int i=0; i<m; i++) {
    int x = v[i];
    E[x-a[x]][n+2+i]++;
    E[x+b[x]][n+2+i]--;
  }
  int tot = 0;
  for (int i=0; i<maxK&&tot<K; i++) {
    if (allG[i].prework()) {
      G[tot] = allG[i];
      mods[tot++] = Mods[i];
    }
  }
  assert(tot==K);
  for (int i=0; i<K; i++) {
    int x = 1;
    for (int j=0; j<K; j++) {
      if (i!=j) x = 1ll*x*mods[j]%mods[i];
    }
    invs[i] = G[i].getinv(x);
  }

  memset(par, 0, sizeof(par));
  bool flag = false;
  ll s = 0;
  for (int msk=0; msk<(1<<m); msk++) {
    for (int i=0; i<m; i++) par[v[i]] = (msk>>i)&1;
    bool ok = true;
    for (int i=0; ok&&i<=n; i++) {
      ok &= getvals(i, msk);
      s++;
    }
    if (ok) {
      ll sum = 0;
      for (int i=0; i<=n; i++) sum += getmodval(i, mod);
      cout<<(sum%mod+mod)%mod<<endl;
      flag = true;
      break;
    }
  }
  assert(flag);
}
int main() {
  FILE("game");
  for (int i=0; i<maxK; i++) allG[i].mod = Mods[i];
  T = 1;
  while (T--) {
    solve();
  }
  return 0;
}