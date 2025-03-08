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
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e17;
map<pll,tll> M;
LL mod=1e9+7;
LL inv2=(mod+1)>>1;
LL sum(LLL v){
    v%=mod;
    return v*(v+1)%mod*inv2%mod;
}
tll calc(LL n,LL k){
    if(k<0)return {0,0,0};
    if(n==1)return {1,1,1};
    if(M.count({n,k}))return M[{n,k}];
    LL bt=63-__builtin_clzll(n);
    tll l,r;
    LLL m=1ll<<bt;
    if(m==n){
        m>>=1;
        bt--;
    }
    l=calc(m,k);
    r=calc(n-m,k-1);
    auto [ansl,ll,lr]=l;
    auto [ansr,rl,rr]=r;
    LLL dec1=sum(lr)+sum(rl);
    dec1%=mod;
    LLL ans=((ansl+ansr)%mod-dec1)%mod+sum(((LLL)lr)+rl);
    ans%=mod;
    ans+=mod;
    ans%=mod;
    LLL al,ar;
    if(ll==m)al=ll+rl;
    else al=ll;
    if(rr==n-m)ar=rr+lr;
    else ar=rr;
    if(n==lowbit(n))M[{n,k}]={ans,al,ar};
    return {ans,al,ar};
}
void solve(){
    LL n,k;
    cin>>n>>k;
    cout<<get<0>(calc(n,k))<<'\n';
}
signed main(){
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
