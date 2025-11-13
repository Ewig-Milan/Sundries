#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
const int mod=1000000009;
const ll inff=1ll<<60;
template <typename T> inline void chkmin(T& x, T y){ x=min(x,y); }
int tid,tc,n,m,nn,cnt,w[N],ha[N],pw[N],nxt[N][27],mustnxt[N];
int le[27],ri[27],b[55],l[55],r[55],mus[27],id[N];
ll sum[N],f[N][55]; string S,T;
// dp 数组记录每一段末尾位置的答案 段与段的分界处转移要特殊考虑
inline int Hash(int l,int r){ return (ha[r]-1ll*ha[l-1]*pw[r-l+1]%mod+mod)%mod; }
inline void solve(){
    cin>>n>>m>>S>>T; S='#'+S; T='#'+T;
    for(int i=1;i<=n;i++) cin>>w[i];
    memset(le,0,sizeof le); memset(ri,0,sizeof ri); nn=0;
    for(int i=1;i<=m;i++){
        if(!le[T[i]-'a']) le[T[i]-'a']=i;
        ri[T[i]-'a']=i;
    }
    for(int i=0;i<26;i++)
        if(le[i])
            b[++nn]=le[i],b[++nn]=ri[i];
    b[0]=1; b[++nn]=m+1; sort(b,b+nn+1); nn=unique(b,b+nn+1)-b-1;
    for(int i=1;i<=nn;i++) l[i]=b[i-1],r[i]=b[i]-1;
    for(int i=0;i<26;i++) nxt[n+1][i]=n+1;
    for(int i=n;i;i--){
        for(int j=0;j<26;j++) nxt[i][j]=nxt[i+1][j];
        nxt[i][S[i]-'a']=i;
    }
    pw[0]=1; for(int i=1;i<=n;i++) pw[i]=131ll*pw[i-1]%mod;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=nn;j++)
            f[i][j]=inff;
    f[0][0]=0;
    for(int j=0;j<=nn;j++){
        for(int i=0;i<n;i++)
            if(l[j]<le[S[i+1]-'a']||l[j]>=ri[S[i+1]-'a'])
                chkmin(f[i+1][j],f[i][j]+w[i+1]);
        if(j==nn) break; cnt=0;
        for(int k=0;k<26;k++) mus[k]=(l[j+1]>=le[k]&&l[j+1]<ri[k]);
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1];
            if(mus[S[i]-'a']) id[++cnt]=i;
            else sum[i]+=w[i];
        }
        mustnxt[n+1]=n+1;
        for(int i=n;i;i--) mustnxt[i]=(mus[S[i]-'a']?i:mustnxt[i+1]);
        for(int i=1;i<=cnt;i++) ha[i]=(131ll*ha[i-1]+S[id[i]]-'a'+13)%mod;
        int len=r[j+1]-l[j+1],hb=0;
        for(int i=l[j+1]+1;i<=r[j+1];i++) hb=(131ll*hb+T[i]-'a'+13)%mod;
        for(int i=0,z=1;i<n;i++){
            if(f[i][j]==inff||nxt[i+1][T[l[j+1]]-'a']==n+1||mustnxt[i+1]<nxt[i+1][T[l[j+1]]-'a'])
                continue;
            int pos=nxt[i+1][T[l[j+1]]-'a'],tval=w[pos];
            if(len){
                while(z<=cnt&&id[z]<=pos) z++;
                if(z+len-1>cnt||Hash(z,z+len-1)!=hb) continue;
                pos=id[z+len-1];
            }
            ll tmp=sum[pos]-sum[i];
            if(!mus[T[l[j+1]]-'a']) tmp-=tval;
            chkmin(f[pos][j+1],f[i][j]+tmp);
        }
    }
    if(f[n][nn]==inff) cout<<"-1\n";
    else cout<<f[n][nn]<<'\n';
}
int main(){
    freopen("letter.in","r",stdin);
    freopen("letter.out","w",stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>tid>>tc; while(tc--) solve();
    return 0;
}