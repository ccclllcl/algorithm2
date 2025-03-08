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
#define tll tuple<LL,LL,LL>
#define tii tuple<int,int,int>
#define LL long long
#define LLL __int128
#define ld long double
using namespace std;
template<typename T>
istream& operator>>(istream& in,vector<T>& arr){
    for(auto& v:arr)in>>v;
    return in;
}
template<typename T>
ostream& operator<<(ostream& out,vector<T>& arr){
    for(auto& v:arr)out<<v<<' ';
    return out;
}
template<typename t1,typename t2>
istream& operator>>(istream& in,pair<t1,t2>& pa){
    in>>pa.first>>pa.second;
    return in;
}
template<typename t1,typename t2>
ostream& operator<<(ostream& out,const pair<t1,t2>& pa){
    out<<pa.first<<' '<<pa.second;
    return out;
}
const int N=4e6+5;
const int SIZ=1e7;
const LL inf=1e17;
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
/*
求积性函数f的前缀和sum of f(n)记作F(n),n~O(1e10),时间复杂度O((n^3/4)/logn)
PN:一个数素因子分解后所有质数的幂次都>=2,则称该数为PN(Powerful Number)  (1也属于PN)
PN筛流程:
 1.选择积性函数g满足其前缀和(记作G(n))可快速求解(或可利用杜教筛求解),并且对任意的素数p,有g(p)=f(p),这是为了f(p)=g(p)*h(1)+g(1)*h(p)
    f(p)=g(p)+h(p) -> h(p)=0 由于h是积性函数,所有非PN的d都有h(d)=0
 2.计算h=f/g在p^k处的值,此处的除法为狄利克雷卷积除法,即要求h*g=f
     h(1)=1
    根据 h*g=f ->  f(p^k)=sum of (i:0~k) h(p^k-i)*g(p^i)
    得到 h(p^k)=f(p^k)- sum of (i:1~k) g(p^i)*h(p^k-i)
    F(n)=sum of (d is PN and d<=n) h(d)*G(n/d)
*/
bool has[N];
LL p[N];
int cnt;
LL fi[N];
LL G[N];
LL inv2,inv6;
map<LL,LL> mem_G;
LL s1(LL n){
    n%=mod;
    return n*(n+1)%mod*inv2%mod;
}
LL s2(LL n){
    n%=mod;
    return n*(n+1)%mod*(2*n+1)%mod*inv6%mod;
}
LL s3(LL n){
    n%=mod;
    LL tp=n*(n+1)%mod;
    return tp*tp%mod;
}

void init(){
    inv2=qpow(2,mod-2);
    inv6=qpow(6,mod-2);
    fi[1]=1;
    LL y;
    for(LL i=2;i<N;i++){
        if(!has[i])p[cnt++]=i,fi[i]=i-1;
        for(int j=0;j<cnt&&(y=p[j]*i)<N;j++){
            has[y]=1;
            if(i%p[j]){
                fi[y]=fi[i]*(p[j]-1);
            }else{
                fi[y]=fi[i]*p[j];
                break;
            }
        }
    }
    G[1]=1;
    for(int i=2;i<N;i++)G[i]=(G[i-1]+i*fi[i]%mod)%mod;
}
LL sum_g(LL x){
    if(x<N)return G[x];
    if(mem_G.count(x))return mem_G[x];
    LL res=s2(x);
    for(LL i=2,j;i<=x;i=j+1){
        j=x/(x/i);
        res-=(s1(j)-s1(i-1))%mod*sum_g(x/i)%mod;
        res%=mod;
    }
    return mem_G[x]=res;
}
LL ans;
LL n;
LL h[N][35];
void init2(){
    for(int i=0;i<cnt;i++){
        h[i][0]=1;
        LL pv=1;
        LL tv=p[i]*p[i]%mod;
        LL tp=p[i]*(p[i]-1)%mod;
        LL s=0;
        for(int j=1;j<35;j++){
            s=(s*tv%mod+h[i][j-1]*tp%mod)%mod;
            pv*=p[i];
            if(pv>n)break;
            LL f=pv%mod;
            f=f*(f-1)%mod;
            h[i][j]=(f-s)%mod;
        }
    }
}
void dfs(LL d,LL hd,int now){
    ans+=hd*sum_g(n/d)%mod;
    ans%=mod;
    for(int i=now;i<cnt;i++){
        if(d>n/p[i]/p[i])break;
        LL td=d*p[i];
        for(int c=2;c<35;c++){
            td*=p[i];
            if(td>n)break;
            LL th=hd*h[i][c]%mod;
            if(th)dfs(td,th,i+1);
        }
    }
}
signed main(){
    IOS;
    cin>>n;
    init();
    init2();
    dfs(1,1,0);
    ans+=mod;
    ans%=mod;
    cout<<ans;
}
