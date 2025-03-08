#include<bits/stdc++.h>
#define pdd pair<double,double>
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
#define ld long double
using namespace std;
const int N=1e6+5;
LL fac[N],inv[N];
LL mod=998244353;
//快速幂
LL qpow(LL a,LL t,LL md){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=md;
        a*=a,a%=md;
        t>>=1;
    }
    return res;
}
LL qpow(LL a,LL t){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=mod;
        a*=a,a%=mod;
        t>>=1;
    }
    return res;
}

//组合数
void init(){
    fac[0]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    for(int i=N-2;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
LL C(LL m,LL n){
    if(m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
//Lucas定理
LL Lucas(LL m,LL n){
    if(m<n)return 0;
    if(n==0)return 1;
    return Lucas(m/mod,n/mod)*C(m%mod,n%mod)%mod;
}

//素数筛
LL pre[N],p[N/10];
int cnt;
void init2(){
    for(int i=2;i<N;i++){
        if(!pre[i])p[cnt++]=i,pre[i]=i;
        for(int j=0;j<cnt&&p[j]*i<N;j++){
            pre[p[j]*i]=p[j];
            if(i%p[j]==0)break;
        }
    }
}
//素因子分解(带指数)
vector<pll> factorize__(LL val){
    vector<pll> res;
    while(val>1){
        LL pv=pre[val];
        int c=0;
        while(pre[val]==pv)c++,val/=pre[val];
        res.emplace_back(pv,c);
    }
    return res;
}
//素因子分解(不带指数)
vector<LL> factorize(LL val){
    vector<LL> res;
    while(val>1){
        LL pv=pre[val];
        res.push_back(pv);
        while(pre[val]==pv)val/=pre[val];
    }
    return res;
}

//根号分治的循环写法
LL geng(LL z,LL n){   //i=1,2,...n,sum of F(z/i)
    LL res=0;
    for(LL i=1,j;i<=n;i=j+1){
        j=min(j,z/(z/i));
        //res+=(j-i+1)*F(z/i);
    }
    return res;
}