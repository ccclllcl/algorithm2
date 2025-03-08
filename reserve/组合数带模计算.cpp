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
using namespace std;
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e12;
LL fac[N],inv[N];
LL p[N];
LL mod=1e9+7;
LL qpow(LL a,LL t){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=mod;
        a*=a,a%=mod;
        t>>=1;
    }
    return res;
}
void init(){
    fac[0]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    for(int i=N-2;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    p[0]=1;
    for(int i=1;i<N;i++)p[i]=p[i-1]*10%mod;
}
LL C(LL m,LL n){
    if(m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
signed main(){
    IOS;
    init();
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    LL ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            ans+=(s[i]-'0')*C(i,k-1-j)*C(n-1-i,j)%mod*p[j]%mod;
            ans%=mod;
        }
    }
    ans+=mod;
    ans%=mod;
    cout<<ans;
}
