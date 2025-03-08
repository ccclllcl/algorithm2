#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pdd pair<double,double>
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
#define ld long double
using namespace std;
const int N=5e5+5;
const int SIZ=1e7;
const LL inf=1e12;
LL mod=998244353;
LL qpow(LL a,LL t){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=mod;
        a*=a,a%=mod;
        t>>=1;
    }
    return res;
}
LL fac[N];
signed main(){
    IOS;
    LL n;
    cin>>n;
    fac[0]=1;
    for(LL i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
    cout<<qpow(2,n)*qpow(fac[n+1],mod-2)%mod*fac[2*n]%mod;
}
