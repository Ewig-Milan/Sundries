#include<bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
using namespace std;
#define ll long long
#define mod 998244353
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
inline int read()
{
    char ch=getchar(); int nega=1; while(!isdigit(ch)) {if(ch=='-') nega=-1; ch=getchar();}
    int ans=0; while(isdigit(ch)) {ans=ans*10+ch-48;ch=getchar();}
    if(nega==-1) return -ans;
    return ans;
}
void print(vector<int> x){for(int i=0;i<(int)x.size();i++) printf("%d%c",x[i]," \n"[i==(int)x.size()-1]);}
inline int add(int x,int y) {return x+y>=mod?x+y-mod:x+y;}
inline int add(int x,int y,int z) {return add(add(x,y),z);}
inline int sub(int x,int y) {return x-y<0?x-y+mod:x-y;}
inline int mul(int x,int y) {return 1LL*x*y%mod;}
inline int mul(int x,int y,int z) {return mul(mul(x,y),z);}
#define inc(x,y) x=add(x,y)
#define dec(x,y) x=sub(x,y)
#define N 1000005
char s[N];
int n;
vector<int> ch[26];
namespace Hash
{
    int B=13131;
    int a[N],pw[N];
    void init()
    {
        pw[0]=1;
        for(int i=1;i<=n;i++) pw[i]=mul(pw[i-1],B);
        for(int i=1;i<=n;i++) a[i]=add(mul(a[i-1],B),s[i]);
    }
    int query(int l,int r)
    {
        return sub(a[r],mul(a[l-1],pw[r-l+1]));
    }
    int lcp(int l1,int l2)
    {
        if(s[l1]!=s[l2]) return 0;
        int l=1,r=n-max(l1,l2)+1,ans;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(query(l1,l1+mid-1)==query(l2,l2+mid-1)) ans=mid,l=mid+1;
            else r=mid-1;
        }
        return ans;
    }
};
using Hash::lcp;
struct Ans
{
    int len[26];
    int l,r;
    Ans() {memset(len,0,sizeof(len)); l=r=0;}
};
Ans getans(int l,int r,int k)
{
    Ans res; res.r=r,res.l=r+1;
    for(int i=0;i<26;i++)
    {
        int p=lower_bound(ch[i].begin(),ch[i].end(),l)-ch[i].begin();
        int q=upper_bound(ch[i].begin(),ch[i].end(),r)-ch[i].begin()-1;
        res.len[i]=min(k,q-p+1);
        k-=res.len[i];
        int L=p,R=p+res.len[i]-1,ans=-1;
        while(L<=R)
        {
            int mid=(L+R)/2;
            if(k>r-ch[i][mid]-(q-mid)) ans=mid,R=mid-1;
            else L=mid+1;
        }
        if(ans!=-1)
        {
            k-=r-ch[i][ans]-(q-ans);
            res.l=ch[i][ans];
            r=ch[i][ans]-1;
            res.len[i]-=(q-ans+1);
            if(ans-1>=p) l=ch[i][ans-1]+1;
        }
        else if(res.len[i]>=1) l=ch[i][q]+1;
    }
    return res;
}
signed main()
{
    FILE("airport");
    scanf("%s",s+1); n=strlen(s+1);
    Hash::init();
    for(int i=1;i<=n;i++) ch[s[i]-'A'].push_back(i);
    int Q=read();
    while(Q--)
    {
        int l1=read(),r1=read(),k1=read(),l2=read(),r2=read(),k2=read();
        Ans a1=getans(l1,r1,k1),a2=getans(l2,r2,k2);
        char ans='?';
        for(int i=0;i<26;i++)
        {
            if(a1.len[i]!=a2.len[i])
            {
                int g=min(a1.len[i],a2.len[i]);
                a1.len[i]-=g,a2.len[i]-=g;
                char n1=0,n2=0;
                for(int j=i;j<26;j++)
                {
                    if(!n1&&a1.len[j]>0) n1=j+'A';
                    if(!n2&&a2.len[j]>0) n2=j+'A';
                }
                if(!n1&&a1.r>=a1.l) n1=s[a1.l];
                if(!n2&&a2.r>=a2.l) n2=s[a2.l];
                assert(n1!=n2);
                ans="<>"[n1>n2];
                break;
            }
        }
        if(ans=='?')
        {
            int L=lcp(a1.l,a2.l);
            if(L>=max(a1.r-a1.l+1,a2.r-a2.l+1))
            {
                if(k1==k2) ans='=';
                else ans="<>"[k1>k2];
            }
            else
            {
                char n1=(a1.l+L)<=a1.r?s[a1.l+L]:0;
                char n2=(a2.l+L)<=a2.r?s[a2.l+L]:0;
                ans="<>"[n1>n2];
            }
        }
        printf("%c\n",ans);
    }
    return 0;
}