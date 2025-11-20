#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;
const int N=300030;
const int mod=998244353;
int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=1LL*ans*a%mod;
        a=1LL*a*a%mod;
        b>>=1;
    }
    return ans;
}
set<pair<int,int> > S,T;
bool Ins(set<pair<int,int> > &S,int x){
    if(x>0){
        auto it=S.lower_bound({x+1,0});
        if(it!=S.begin()&&x>=prev(it)->first&&x<=prev(it)->second){
            --it;
            auto [l,r]=*it;
            S.erase(it);
            if(l<x){
                S.insert({l,x-1});
            }
            Ins(S,r+1);
        }
        else{
            int L=x,R=x;
            if(it!=S.begin()&&prev(it)->second==x-1){
                L=prev(it)->first;
                --it;
                S.erase(it);
                it=S.lower_bound({x+1,0});
            }
            if(it!=S.end()&&it->first==x+1){
                R=it->second;
                S.erase(it);
            }
            S.insert({L,R});
        }
    }
    else{
        x=-x;
        if(S.empty()||x>S.rbegin()->second)return false;
        auto it=S.lower_bound({x+1,0});
        if(it!=S.begin()&&x>=prev(it)->first&&x<=prev(it)->second){
            --it;
            auto [l,r]=*it;
            S.erase(it);
            if(l<x){
                S.insert({l,x-1});
            }
            if(r>x){
                S.insert({x+1,r});
            }
        }
        else{
            int L=x,R=it->first-1;
            int k=it->second;
            S.erase(it);
            if(R+2<=k){
                S.insert({R+2,k});
            }
            it=S.lower_bound({x+1,0});
            if(it!=S.begin()){
                --it;
                if(it->second==L-1){
                    L=it->first;
                    S.erase(it);
                }
            }
            S.insert({L,R});
        }
    }
    return true;
}
int n,a[N];
int main(){
    FILE("subsegment");
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    int las=0;
    for(int i=1;i<=n;++i){
        if(!Ins(T,a[i])){
            for(int j=i-1;j>las;--j){
                Ins(S,a[j]);
            }
            T.clear();
            las=i;
        }
        else{
            if(!Ins(S,-a[i])){
                S.clear();
            }
        }
    }
    int ans=0;
    for(auto [l,r]:S){
        ans=(ans+qpow(2,r+1)-qpow(2,l))%mod;
    }
    for(auto [l,r]:T){
        ans=(ans+qpow(2,r+1)-qpow(2,l))%mod;
    }
    cout<<(ans+mod)%mod<<'\n';
    return 0;
}