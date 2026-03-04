#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int md(int x){return x>=mod?x-mod:x;}
const int t=510;
int n,f[2][183][797][2],ans;
char s[505];
int main(){
	freopen("insertion.in","r",stdin);
	freopen("insertion.out","w",stdout); 
	scanf("%d%s",&n,s+1);
	for(int i=1;i<n+1-i;i++) swap(s[i],s[n+1-i]);
	f[0][0][t][0]=1;
	for(int i=1;i<=n;i++){
		int o=(i&1);
		for(int j=0;j<=i/3+1;j++)
			for(int k=t-i;k<=t+j;k++) f[o][j][k][0]=f[o][j][k][1]=0;
		if(s[i]!='0')
			for(int j=0;j<=(i-1)/3+1;j++)
				for(int k=t-(i-1);k<=t+j;k++)
					if(k+3-t<=j+1)
						f[o][max(j,k+3-t)][k+3][1]=md(f[o][max(j,k+3-t)][k+3][1]+f[o^1][j][k][0]);
		if(s[i]!='1')
			for(int j=0;j<=(i-1)/3+1;j++)
				for(int k=t-(i-1);k<=t+j;k++)
					f[o][j][k-1][0]=md(f[o][j][k-1][0]+md(f[o^1][j][k][1]+f[o^1][j][k][0]));
	}
	for(int i=0;i<=n/3+1;i++) ans=md(ans+f[n&1][i][t][0]);
	printf("%d",ans);
} 
