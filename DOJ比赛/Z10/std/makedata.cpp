#include<bits/stdc++.h>
using namespace std;
struct Equation{
	unsigned long long vec;bool res;
	Equation():vec(0),res(0){}
	Equation(unsigned long long V,bool R):vec(V),res(R){}
};
unsigned long long fre;
Equation equ[64];
unsigned long long mat[100005][64];
int perm[100005],pos[100005];
int A[100005];
int n;
namespace Validator{
	unsigned long long seed;
	int tmp[100005];
	inline unsigned long long Rand(){
		seed^=seed<<13;
		seed^=seed>>7;
		seed^=seed<<17;
		return seed;
	}
	inline bool Validate(const unsigned long long&X){
		seed=X;
		for(int i=1;i<=n;i++){
			tmp[i]=i;
			swap(tmp[i],tmp[Rand()%i+1]);
		}
		for(int i=1;i<=n;i++)if(tmp[i]!=A[i])return 0;
		return 1;
	}
}
inline Equation operator^(const Equation&a,const Equation&b){
	return Equation(a.vec^b.vec,a.res^b.res);
}
inline Equation&operator^=(Equation&a,const Equation&b){
	return a=a^b;
}
inline void AddEquation(Equation nw){
	for(int i=0;i<64;i++){
		if(nw.vec>>i&1){
			if(!equ[i].vec){
				equ[i]=nw;break;
			}
			nw^=equ[i];
		}
	}
}
inline unsigned long long Generate(const unsigned long long&freState){
	unsigned long long ret=freState;
	for(int k=0;k<64;k++)if(equ[k].vec){
		int idx=__builtin_ctzll(equ[k].vec);
		ret^=(1llu*(__builtin_parityll(equ[k].vec&freState)^equ[k].res))<<idx;
	}
	return ret;
}
int main(){
    freopen("makedata.in","r",stdin);
    freopen("makedata.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		perm[i]=A[i],pos[perm[i]]=i;
	}
	for(int i=0;i<64;i++)mat[0][i]=1llu<<i;
	for(int i=1;i<=n;i++){
		for(int j=0;j<64;j++){
			mat[i][j]=mat[i-1][j];
			mat[i][j]^=mat[i][j]<<13;
			mat[i][j]^=mat[i][j]>>7;
			mat[i][j]^=mat[i][j]<<17;
		}
	}
	for(int i=n;i>=1;i--){
		int r=pos[i]-1;
		swap(pos[i],pos[perm[i]]);
		swap(perm[pos[perm[i]]],perm[i]);
		int t=__builtin_ctz(i);
		for(int j=0;j<t;j++){
			Equation tmp;tmp.res=r>>j&1;
			for(int k=0;k<64;k++)
				tmp.vec|=(mat[i][k]>>j&1)<<k;
			AddEquation(tmp);
		}
	}
	fre=64==64?-1:(1llu<<64)-1;
	for(int k=0;k<64;k++)if(equ[k].vec){
		int idx=__builtin_ctzll(equ[k].vec);
		fre^=1llu<<idx;
		for(int j=0;j<64;j++)
			if(j^k&&equ[j].vec>>idx&1)equ[j]^=equ[k];
	}
	bool ever=0;unsigned long long ans;
	for(unsigned long long s=fre;s;s=(s-1)&fre){
		ans=Generate(s);
		if(Validator::Validate(ans)){
			ever=1;break;
		}
	}
	if(!ever){
		ans=Generate(0);
		if(Validator::Validate(ans))ever=1;
	}
	printf("%llu\n",ans);
	return 0;
}