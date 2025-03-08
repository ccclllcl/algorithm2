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
const int N=2e5+6;
const int SIZ=1e7;
const LL inf=1e17;
LL mod=1e9+7;
LL inv2;
LL qpow(LL a,LL t){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=mod;
        a*=a,a%=mod;
        t>>=1;
    }
    return res;
}
LL fang(LL x){
    return x*x;
}
LL p[N],sp[N];
bool has[N];
int pcnt;
LL le[N+1],ge[N+1];
LL nn;
LL lim;
#define idx(y) (y<=lim?le[y]:ge[nn/y])
void init(){
    LL y;
    inv2=qpow(2,mod-2);
    for(int i=2;i<N;i++){
        if(!has[i])pcnt++,sp[pcnt]= sp[pcnt - 1] + i,sp[pcnt]%=mod, p[pcnt]=i;
        for(int j=1; j <= pcnt && (y= p[j] * i) < N; j++){
            has[y]=true;
            if(i%p[j]==0)break;
        }
    }
}
int cnt;
LL lis[N+1];
LL G[N][2];
void init2(){
    for(LL i=1,j;i<=nn;i=nn/j+1){
        j=nn/i;
        LL val=j%mod;
        lis[++cnt]=j;
        idx(j)=cnt;
        G[cnt][0]=val-1;
        G[cnt][1]=(val+2)*(val-1)%mod*inv2%mod;
    }
}
LL Fp[N];
void Fprime(){
    for(int k=1;k<=pcnt;k++){
        LL pp=p[k];
        LL sqp=fang(pp);
        for(LL i=1;lis[i]>=sqp;i++){
            LL val=lis[i]/pp;
            int ii=idx(val);
            G[i][0]-=G[ii][0]-(k-1);
            G[i][0]%=mod;
            G[i][1]-=pp*(G[ii][1]-sp[k-1])%mod;
            G[i][1]%=mod;
        }
    }
    for(int i=1;i<=cnt;i++)Fp[i]=(G[i][1]-G[i][0])%mod;
}
LL fp(LL p,LL c){
    return p^c;
}
LL F(LL k,LL n){
    if(n<p[k]||n<=1)return 0;
    LL id=idx(n);
    LL ans=Fp[id]-sp[k-1]+k-1;
    if(k==1)ans+=2;
    ans%=mod;
    for(LL i=k;i<=pcnt&&fang(p[i])<=n;i++){
        LL pw=p[i],pw2=fang(pw);
        for(LL c=1;pw2<=n;c++,pw=pw2,pw2*=p[i]){
            ans+=(fp(p[i],c)*F(i+1,n/pw)%mod+fp(p[i],c+1))%mod;
            ans%=mod;
        }
    }
    return ans;
}
signed main(){
    IOS;
    cin>>nn;
    lim=sqrt(nn);
    init();
    init2();
    Fprime();
    LL ans=F(1,nn)+1;
    ans=(ans%mod+mod)%mod;
    cout<<ans;
}
