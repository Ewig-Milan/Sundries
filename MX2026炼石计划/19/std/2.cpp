#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) (x&(-x))
const int inf = 1e18;
struct DS{
    priority_queue<int,vector<int>,greater<int> >q1,del1;
    priority_queue<int>q2,del2;
    int sum = 0;
    void clear(){
        sum = 0;
        while(q1.size())q1.pop();
        while(q2.size())q2.pop();
        while(del1.size())del1.pop();
        while(del2.size())del2.pop();
    }
    void add(int x){
        while(del1.size() and del1.top() == q1.top())del1.pop(),q1.pop();
        if(q1.size() and x>=q1.top())q1.push(x),sum+=x;
        else q2.push(x);
    }
    void del(int x){
        while(del1.size() and del1.top() == q1.top())q1.pop(),del1.pop();
        if(q1.size() and x>=q1.top())del1.push(x),sum-=x;
        else del2.push(x);
    }
    int query(int k){
        while(q1.size()-del1.size()<k and q2.size()>del2.size()){
            while(del2.size() and del2.top() == q2.top())del2.pop(),q2.pop();
            q1.push(q2.top());sum+=q2.top();q2.pop();
        }
        while(q1.size()-del1.size()>k){
            while(del1.size() and del1.top() == q1.top())del1.pop(),q1.pop();
            q2.push(q1.top());sum-=q1.top();q1.pop();
        }
        return sum;
    }
}T;
int n,x;
int a[300005],b[300005];
int pre[300005],ans[300005];
void solve(int l,int r,int pl,int pr){
    if(l>r)return;
    int p = -1,mx = -inf,mid = l+r>>1;
    for(int i = pr;i>=pl;i--){
        if(i!=n+1)T.add(b[i]);
        int v = T.query(mid)+pre[i-1];
        if(v>mx)mx = v,p = i;
    }
    ans[mid] = mx;
    for(int i = pl;i<=p;i++)if(i!=n+1)T.del(b[i]);
    solve(mid+1,r,pl,p);
    for(int i = p+1;i<=pr;i++)if(i!=n+1)T.del(b[i]);
    solve(l,mid-1,p,pr);
}
void solve(){
    T.clear();
    cin >> n >> x;
    for(int i = 1;i<=n;i++)cin >> a[i];
    for(int i = 1;i<=n;i++)cin >> b[i];
    for(int i = 1;i<=n;i++)pre[i] = pre[i-1]+a[i];
    for(int i = 1;i<=n;i++)b[i] += a[i];
    solve(1,n,1,n+1);
    for(int i = 1;i<=n;i++)ans[i]-=pre[n];
    sort(b+1,b+1+n),reverse(b+1,b+1+n);
    int sum = 0;
    for(int i = 1;i<=n;i++){
        sum+=b[i];
        ans[i] = max(x+sum-pre[n],ans[i]);
    }
    for(int i = 1;i<=n;i++)cout << ans[i] << ' ';
    cout << '\n';
}
signed main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;cin >> t;
    while(t--)solve();
    return 0;
}