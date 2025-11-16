#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
using namespace std;
const int N=2505,inf=0x3f3f3f3f;
int n,k,ans=inf,a[N],f[2][N][2][6][7];
char s[N];
void chk(int&x,int y) {if(x>y) x=y;}
int main(){
    FILE("match");
    memset(f,0x3f,sizeof f);f[0][0][0][0][0]=0;
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&k);
    for(int i=1,o=1;i<=n;i++,o^=1){
        memset(f[o],0x3f,sizeof f[o]);
        int p=s[i]-'a';
        for(int j=0;j<i&&j<=n/2;j++) for(int u:{0,1}) for(int c=0;c<6;c++) for(int t=0;t<=k;t++){
            int v=f[o^1][j][u][c][t]+j*100+a[i];
            if(t<k) chk(f[o][j][u][c][t+1],v-a[i]);
            if(!j) chk(f[o][1][0][p][t],v);
            else if(u){
                if(c==p) chk(f[o][j-1][1][c][t],v);
                else chk(f[o][j+1][1][c][t],v);
            }else{
                if(c==p) chk(f[o][j+1][0][c][t],v);
                else{
                    chk(f[o][j-1][0][c][t],v);
                    for(int q=0;q<6;q++) if(q!=c&&q!=p) chk(f[o][j+1][1][q][t],v);
                }
            }
        }
    }
    for(int o:{0,1}) for(int i=0;i<6;i++) chk(ans,f[n&1][0][o][i][k]);
    printf("%d\n",ans==inf?-1:ans);
    return 0;
}