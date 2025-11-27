#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int pre[1000005];
int qp(int p,int q){
    int ans = 1,pro = p;
    while(q){
        if(q&1)ans = ans*pro%mod;
        pro = pro*pro%mod;q>>=1;
    }
    return ans;
}
int n,m;
void init(){
    int pro = 1;
    for(int i = 1;i<=n+m;i++)pro = pro*i%mod;
    int inv = qp(pro,mod-2);
    for(int i  =0;i<=n+m;i++)pre[i] = pro;
    for(int i = n+m;i>=0;i--){
        pre[i] = pre[i]*inv%mod;
        pre[n+m-i] = pre[n+m-i]*inv%mod;
        inv = inv*i%mod;
    }
    for(int i= 1;i<=n+m;i++)pre[i] = (pre[i-1]+pre[i])%mod;
}
void mi(int& x,int& y,int b){y-=b,x+=b;swap(x,y);}
void mi(int &c,int& b){c = 2*b-c;swap(b,c);}
int C(int x){return (x == 0)?1:(pre[x]-pre[x-1]+mod)%mod;}
int work(int b,int c){
    int x = n,y = m,pro = 1,tot = 0;
    while(x>=0 and y>=0){
        tot = (tot+pro*C(x)+mod)%mod;
        mi(x,y,c);
        mi(b,c);
        pro = -pro;
    }
    return tot;
}
int calc(int b,int c){
    if(b+n<m or c+n>m){return 0;}
    return (work(b+1,c-1)+work(c-1,b+1)-C(n)+mod)%mod;
}
int slove(int b,int c,int l,int r){
    int x = n,y = m,pro = 1,tot = 0;
    while(x>=0 and y>=0 and l<=r){
        if(pro == 1)tot = (tot+C(x)*(r-l+1))%mod;
        else{
            int ll = y-(r-l+1);
            tot = (tot-(pre[y]-(ll>=0?pre[ll]:0))+mod)%mod;
        }
        mi(x,y,c);
        mi(b,c);
        if(pro == 1){
            if(y<0)break;
            if(x<0){
                r += x;
                b += x;
                c += x;
                y += x;
                x = 0;
            }
            l = max(l,r-y);
        }
        pro = -pro;
    }
    return tot;
}
int WORK(int k){
    int l = max(0ll,m-n),r = min(k,m+k-n);
    if(l>r)return 0;
    int ans = slove(r+1,r-k-1,l,r)+slove(r-k-1,r+1,l,r)-(r-l+1)*C(n)%mod+mod;
    return ans%mod;
}
int ans[1000005];
signed main(){
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    cin >> n >> m;
    init();
    for(int i = 1;i<=n+m;i++)ans[i] = WORK(i);
    for(int i = 1;i<=n+m;i++)cout << (ans[i]-ans[i-1]+mod)%mod << " ";cout << endl;
    return 0;
}