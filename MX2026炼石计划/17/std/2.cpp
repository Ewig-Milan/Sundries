#include <bits/stdc++.h>
using namespace std;
#define rep(i, j, k) for(int i = (j); i <= (k); i++)
#define per(i, j, k) for(int i = (j); i >= (k); i--)
#define pb emplace_back
#define fi first
#define se second
using vi = vector<int>;
using pi = pair<int, int>;

template<typename T0, typename T1> bool chmin(T0 &x, const T1 &y){
    if(y < x){x = y; return true;} return false;
}
template<typename T0, typename T1> bool chmax(T0 &x, const T1 &y){
    if(x < y){x = y; return true;} return false;
}

template<typename T> void debug(char *s, T x){
    cerr << s <<" = "<< x <<endl;
}
template<typename T, typename ...Ar> void debug(char *s, T x, Ar... y){
    int dep = 0;
    while(!(*s == ',' && dep == 0)){
        if(*s == '(') dep++;
        if(*s == ')') dep--;
        cerr << *s++;
    }
    cerr <<" = "<< x <<",";
    debug(s + 1, y...);
}
#define gdb(...) debug((char*)#__VA_ARGS__, __VA_ARGS__)

const int B = 1024;
signed main(){
    freopen("summer.in", "r", stdin);
    freopen("summer.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int tid;
    cin >> tid;
    int T, n, A;
    cin >> T >> n >> A;
    vector<vi> a(A + 1);
    rep(i, 1, n){
        int k, b;
        cin >> k >> b;
        a[k].pb(b);
    }
    vi q(T + 1), ans(T + 1);
    rep(i, 1, T){
        cin >> q[i];
    }

    vector<vi> cnt(B, vi(B));
    vi ccnt(A + 1);
    auto add = [&](int x, int w){
        rep(i, 1, B - 1){
            cnt[i][x % i] += w;
        }
        ccnt[x] += w;
    };

    rep(i, 1, A){
        if(a[i].empty()){
            continue;
        }
        sort(a[i].begin(), a[i].end());
        for(auto x:a[i]){
            add(x, 1);
        }
        int mx = min(T, A / i);
        rep(j, 1, mx){
            while(a[i].size() && a[i].back() + i * j > A){
                add(a[i].back(), -1);
                a[i].pop_back();
            }
            if(q[j] < B){
                int r = q[j] - i * j % q[j];
                if(r == q[j]) r = 0;
                ans[j] += cnt[ q[j] ][r];
            } else{
                for(int k = q[j]; k <= A; k += q[j]){
                    if(k >= i * j){
                        ans[j] += ccnt[k - i * j];
                    }
                }
            }
        }
        while(a[i].size()){
            add(a[i].back(), -1);
            a[i].pop_back();
        }
    }
    rep(i, 1, T){
        cout << ans[i] <<'\n';
    }
}