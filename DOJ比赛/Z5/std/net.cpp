#include<bits/stdc++.h>

using namespace std;
#define popc __builtin_popcount

const int inf=0x77777777;
const int MXK=4,MXM=4,MXT=20,MXQ=30000,MXN=MXM+MXQ;
int m,q,k,t,n,it;
int fixp[MXT][MXK], fixintern;
int p[MXN][MXK], fix[MXN];
int dp[2][1<<(MXK*MXM)]; // dp[i%2][S] 表示考虑前i个，排名矩阵为S的情况下
vector<int> ss[MXM], snormal[MXM+1][MXK], sfull[MXM+1]; // 所有popc为指定值的数，以及实际存在的状态，以及一行完毕后的状态

int& tr(int &x, int y){return x=max(x,y);}
int mask(int S, int x){return (S>>(x*m))&((1<<m)-1);} // 第x维
int bit(int S,int x, int y){return (S>>(x*m+y))&1;} // 第x维第y排名
int coeff(int x){return 2*x-m+1;} //贡献系数（等于 x - (m-1-x)）
int dis(int a[], int b[]){
    int r=0;
    for(int i=0;i<k;i++)
    r+=abs(a[i]-b[i]);
    return r;
}
void dfs(int x, int pc, int S=0, int col=0){
    // x当前搜到的维数 pc当前需要的popcount S当前集合 col折角的位置
    if(x>=k){ // 搜完了
        if(col<k){ // 合法状态
            if(col==0)sfull[pc].push_back(S); // 每一列恰好popcount相等
            else snormal[pc][col].push_back(S); // 前col列的popcount多1
        }
    }
    else{
        for(auto s:ss[col?pc-1:pc]){
            dfs(x+1,pc,S|(s<<(x*m)),col);
            if(col==0&&pc>0)dfs(x+1,pc,S|(s<<(x*m)),x+1);
        }
    }
}
void debug_bin(int i){
    for(int j=0;j<k;cerr<<'|',j++)
    for(int x=0;x<m;x++)
        cerr<<bit(i,j,x);
    cerr<<"    ";
}
void cleardp(int a[]){
    for(int i=0;i<=m;i++)
        for(auto s:sfull[i])a[s]=(~inf);
    for(int c=1;c<k;c++)
        for(int i=1;i<=m;i++)
            for(auto s:snormal[i][c])
                a[s]=(~inf);
}
int dpwork(){
    for(;it<n;it++){ //插入点it
        int *f=dp[it&1], *fl=dp[(it&1)^1];
        cleardp(f); // 清零
        for(int i=0;i<m;i++){
            for(auto s:sfull[i])if(fl[s]>(~inf)){ //从上一行的s转移
                for(int j=0;j<m;j++)if(bit(s,0,j)==0){
                    tr(f[s|(1<<j)],fl[s]+coeff(j)*p[it][0]+fix[it]);
                }
            }
        }
        #ifdef LCADEBUG
        cerr<<"f(mid)["<<it<<"]\n";
        for(int i=0;i<(1<<(k*m));i++)
            cerr<<f[i]<<' ';
        cerr<<endl;
        for(int i=0;i<(1<<(k*m));i++)if(f[i]>(~inf)){
            debug_bin(i);
        }
        cerr<<endl;
        #endif
        for(int c=1;c<k;c++){ // 枚举列
            for(int i=1;i<=m;i++){
                for(auto s:snormal[i][c])if(f[s]>(~inf)){
                    for(int j=0;j<m;j++)if(bit(s,c,j)==0){
                        tr(f[s|(1<<(c*m+j))],f[s]+coeff(j)*p[it][c]);
                    }
                }
            }
        }
        for(int i=0;i<=m;i++){
            for(auto s:sfull[i])if(fl[s]>(~inf)){ //从上一行的s转移
                tr(f[s],fl[s]);
            }
        }
        #ifdef LCADEBUG
        cerr<<"f["<<it<<"]\n";
        for(int i=0;i<(1<<(k*m));i++)
            cerr<<f[i]<<' ';
        cerr<<endl;
        for(int i=0;i<(1<<(k*m));i++)if(f[i]>(~inf)){
            debug_bin(i);
        }
        cerr<<endl;
        #endif
    }
    return dp[(n-1)&1][(1<<(k*m))-1]+fixintern;
}
void init(){
    cin>>m>>q>>k>>t;
    for(int i=0;i<t;i++)
        for(int j=0;j<k;j++)
            cin>>fixp[i][j];
    fixintern=0;
    for(int i=0;i<t;i++)
        for(int j=i+1;j<t;j++)
            fixintern+=dis(fixp[i],fixp[j]);
    for(int i=0;i<m;i++)
        for(int j=0;j<k;j++)
            cin>>p[i][j];
    for(int i=0;i<m;i++){
        fix[i]=0;
        for(int j=0;j<t;j++)
            fix[i]+=dis(p[i],fixp[j]);
    }
    for(int i=0;i<(1<<m);i++)
        ss[popc(i)].push_back(i);
    for(int i=0;i<=m;i++)
        dfs(0,i);
    
    #ifdef LCADEBUG
    for(int i=0;i<=m;i++)
        for(int j=0;j<m;j++){
            cerr<<"snormal "<<i<<' '<<j<<' '<<endl;
            for(auto s:snormal[i][j])debug_bin(s);
            cerr<<endl;    
        }
    #endif

    n=m,it=0;
    cleardp(dp[1]); // dp[-1][] 初始化
    dp[1][0]=0;
    dpwork();
}

int main(){
    freopen("net.in", "r", stdin);
    freopen("net.out", "w", stdout);
    ios::sync_with_stdio(false);
    init();
    for(int i=1;i<=q;i++){
        {
            for(int j=0;j<k;j++)
                cin>>p[n][j];
            fix[n]=0;
            for(int j=0;j<t;j++)
                fix[n]+=dis(p[n],fixp[j]);
            n++;
        }
    }cout<<dpwork()<<endl;
    return 0;
}