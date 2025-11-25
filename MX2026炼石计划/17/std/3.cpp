#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define pb emplace_back
#define fi first
#define se second
using vi=vector<int>;
using pi=pair<int,int>;

template<typename T0, typename T1> bool chmin(T0 &x,const T1 &y){
    if(y<x){x=y; return true;} return false;
}
template<typename T0, typename T1> bool chmax(T0 &x,const T1 &y){
    if(y>x){x=y; return true;} return false;
}

namespace Debug{
    template<typename T> void _debug(char *s, T x){
        cerr<< s <<" = "<< x <<endl;
    }
    template<typename T, typename ...Ar> void _debug(char *s, T x, Ar... y){
        while(*s != ',') cerr<< *s++;
        cerr<< " = "<< x <<",";
        _debug(s+1, y...);
    }
}
using namespace Debug;
#define gdb(...) _debug((char*)#__VA_ARGS__, __VA_ARGS__)

#ifdef LOCAL
mt19937_64 rnd(3663);
#else
mt19937_64 rnd(time(0));
#endif

using u64 = uint64_t;

signed main(){
    freopen("autumn.in","r",stdin);
    freopen("autumn.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);
    
    int tid;
    cin >> tid;
    int n;
    cin >> n;
    vector<u64> w(n);
    rep(i, 0, n - 1){
        w[i] = rnd();
    }
    vi a(n * 2);
    rep(i, 0, n * 2 - 1){
        cin >> a[i];
        a[i]--;
    }

    vector<u64> ans(n * 2);
    auto slv = [&](){
        vector<u64> pre(n * 2 + 1);
        vi occ(n), stk;
        gp_hash_table<u64, int> cnt;
        cnt[0] = 1;
        rep(i, 0, n * 2 - 1){
            pre[i + 1] = pre[i] ^ w[ a[i] ];
            occ[ a[i] ] ++;
            stk.pb(i);
            while(stk.size() && occ[ a[stk.back()] ] == 2){
                stk.pop_back();
            }
            if(stk.size()){
                int x = stk.back();
                ans[x] += cnt[ w[ a[x] ] ^ pre[i + 1] ];
            }
            cnt[ pre[i + 1] ] ++;
        }
    };
    slv();
    reverse(a.begin(), a.end());
    reverse(ans.begin(), ans.end());
    slv();
    reverse(ans.begin(), ans.end());
    rep(i, 0, n * 2 - 1){
        cout << ans[i] <<' ';
    }
    cout <<'\n';
}