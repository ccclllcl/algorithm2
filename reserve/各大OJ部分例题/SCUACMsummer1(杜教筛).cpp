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
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e12;
LL mod=1e9+7;
LL inv2,inv6;
const LL maxn=5e6;
LL fi[maxn+1];
LL p[maxn+1];
int cnt;
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
    inv2=qpow(2,mod-2);
    inv6=qpow(6,mod-2);
    fi[1]=1;
    for(LL i=2;i<=maxn;i++){
        if(!fi[i])p[cnt++]=i,fi[i]=i-1;
        for(int j=0;j<cnt&&p[j]*i<=maxn;j++){
            if(i%p[j]==0){
                fi[p[j]*i]=fi[i]*(p[j]);
                break;
            }else{
                fi[p[j]*i]=fi[i]*(p[j]-1);
            }
        }
    }
    for(int i=2;i<=maxn;i++)fi[i]=fi[i]*i%mod*i%mod;
    for(int i=2;i<=maxn;i++)fi[i]=(fi[i-1]+fi[i])%mod;
}
LL n;
map<LL,LL> M;
LL S1(LL x){x%=mod;return x*(x+1)%mod*inv2%mod;}
LL S2(LL x){x%=mod;return x*(x+1)%mod*(2LL*x+1)%mod*inv6%mod;}
LL S3(LL x){
    x%=mod;
    LL tp=S1(x);
    return tp*tp%mod;
}
LL sum_fi(LL x){
    if(x<=maxn)return fi[x];
    if(M.count(x))return M[x];
    LL ans=0;
    for(LL l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        ans+=sum_fi(x/l)*((S2(r)-S2(l-1))%mod)%mod;
        ans%=mod;
    }
    return M[x]=(S3(x)-ans)%mod;
}
signed main(){
    IOS;
    cin>>n;
    init();
    LL res=0;
    for(LL l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        res+=S1(n/l)*(sum_fi(r)- sum_fi(l-1))%mod;
        res%=mod;
    }
    res=(res+mod)%mod;
    cout<<(res+S1(n))%mod;
}
