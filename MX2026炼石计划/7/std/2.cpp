#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;

const int N = 100100;

int t,n;
string s[N],ret[N];
int val[N][26], tmpa[26], tmpb[26];
vector<vector<int>> g[5000100];
vector<int> v[N];
bool flag = 1;
void work(int id,int a[],int pre) {
    if(!pre) return;
    if(id == 1) {
        vector<int> x;
        x.resize(26);
        for(int i=0;i<26;i++) {
            x[i] = a[i];
            if(x[i] < 0) {flag=false; return;}
        }
        g[pre - 1].push_back(x);
        return;
    }
    if(!v[id][pre]) {work(1, a, pre); return;}
    int x=s[v[id][pre]].length(),y=pre;
    int now=y/x;
    y %= x;
    for(int j=0;j<26;j++){
        a[j]-=val[v[id][pre]][j]*now;
        if(a[j]<0){
            flag=false;
            return;
        }
    }
    work(v[id][pre],a,y);
    return;
}

int main(){
    FILE("era");
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>s[i];
            v[i].resize(s[i].length()+1); 
            memset(val[i],0,sizeof(val[i]));
            for(int j=0;j<s[i].length();j++){
                val[i][s[i][j]-'a']++;
                if(j+1<=s[i-1].length())v[i][j+1]=v[i-1][j+1];
                else v[i][j+1]=i-1;
            }
        }
        for(int i=0;i<s[1].length();i++)g[i].clear();
        flag=true;
        for(int i=n;i>1;i--) {
            if(s[i].length()>s[i-1].length()) {
                int x=s[i-1].length(),y=s[i].length();
                memcpy(tmpa,val[i-1],sizeof(tmpa));
                memcpy(tmpb,val[i],sizeof(tmpb));
                int now=y/x;
                y%=x;
                for(int j=0;j<26;j++){
                    tmpb[j]-=tmpa[j]*now;
                    if(tmpb[j]<0){flag=false;break;}
                }
                if(!flag)break;
                work(i-1,tmpb,y);
            }
            else if(s[i].length()<s[i-1].length()) work(i-1,val[i],s[i].length());
            else for(int k=0;k<26;k++) if(val[i][k]!=val[i-1][k]) {flag=false; break;}
            if(!flag)break;
        }
        if(!flag) {
            cout<<"NO"<<'\n';
            continue;
        }
        for(int i=0;i<s[1].length();i++) {
            for(int j=1;j<g[i].size();j++) {
                for(int k=0;k<26;k++) {
                    if(g[i][j][k]!=g[i][j-1][k]) {flag=false; break;}
                }
                if(!flag) break;
            }
            if(!flag) break;
        }
        if(!flag) {puts("NO"); continue;}
        int las=-1;
        memset(tmpb,0,sizeof(tmpb));
        for(int i=1;i<=n;i++) ret[i].resize(s[i].length());
        for(int i=0;i<s[1].length();i++) {
            if(g[i].size()) {
                for(int j=0;j<26;j++) tmpa[j]=g[i][0][j];
                for(int k=0;k<26;k++) if(tmpa[k]<tmpb[k]) {flag=false; break;}
                if(!flag) break;
                for(int j=las+1;j<=i;j++)
                for(int k=0;k<26;k++)
                    if(tmpa[k]>tmpb[k]) {ret[1][j]='a'+k,tmpb[k]++;break;}
                
                las=i;
            }
            if(!flag) break;
        }
        for(int i=las+1;i<s[1].length();i++) {
            for(int k=0;k<26;k++) if(val[1][k]<tmpb[k]) {flag=false; break;}
            if(!flag) break;
            for(int k=0;k<26;k++)
                if(val[1][k]>tmpb[k]) {ret[1][i]='a'+k,tmpb[k]++; break;}
        }
        for(int i=0;i<26;i++) if(tmpb[i]!=val[1][i]) {flag=false; break;}
        if(!flag) {puts("NO"); continue;}
        puts("YES");
        for(int i=2;i<=n;i++)
        for(int j=0;j<s[i].length();j++)
            ret[i][j]=ret[i-1][j%s[i-1].length()];
        for(int i=1;i<=n;i++) cout<<ret[i]<<'\n';
    }
}